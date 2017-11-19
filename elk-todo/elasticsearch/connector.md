connector - 更新Elasticsearch的流程

# mongo_connector/oplog_manager.py

## oplog解析&处理

run()函数中（做了部分简化）：

    for n, entry in enumerate(cursor):
        LOG.debug("OplogThread: Iterating through cursor,"
                  " document number in this cursor is %d"
                  % n)

        # Sync the current oplog operation
        operation = entry['op']
        ns = entry['ns']
        timestamp = util.bson_ts_to_long(entry['ts'])
        for docman in self.doc_managers:
            try:
                # Remove
                if operation == 'd':
                    docman.remove(
                        entry['o']['_id'], ns, timestamp)
                    remove_inc += 1

                # Insert
                elif operation == 'i':  # Insert
                    # Retrieve inserted document from
                    # 'o' field in oplog record
                    doc = entry.get('o')
                    docman.upsert(doc, ns, timestamp)
                    upsert_inc += 1

                # Update
                elif operation == 'u':
                    docman.update(entry['o2']['_id'],
                                  entry['o'],
                                  ns, timestamp)
                    update_inc += 1

                # Command
                elif operation == 'c':
                    # use unmapped namespace
                    doc = entry.get('o')
                    docman.handle_command(doc,
                                          entry['ns'],
                                          timestamp)

            except errors.OperationFailed:
                LOG.exception(
                    "Unable to process oplog document %r"
                    % entry)
            except errors.ConnectionFailed:
                LOG.exception(
                    "Connection failed while processing oplog "
                    "document %r" % entry)

        ...
    ...

这里遍历oplog中的每条记录，针对delete/insert/update/create，即noop之外的记录，同步到Elasticsearch中。

# self.doc_managers

doc_managers是connector构造OplogThread对象时传入的。

    class OplogThread(threading.Thread):
        def __init__(self, primary_client, doc_managers,
                     oplog_progress_dict, namespace_config,
                     mongos_client=None, **kwargs):
            super(OplogThread, self).__init__()
            ...
            # The document manager for each target system.
            # These are the same for all threads.
            self.doc_managers = doc_managers

# Connector

## run()

    @log_fatal_exceptions
    def run(self):
        ...
        # non sharded configuration
        oplog = OplogThread(
            self.main_conn, self.doc_managers, self.oplog_progress,
            self.namespace_config, **self.kwargs)
        self.shard_set[0] = oplog
        LOG.info('MongoConnector: Starting connection thread %s' %
                 self.main_conn)
        oplog.start()

## __init__()

而Connector.doc_managers是构造时指定的，是elstic2_doc_manager.DocManager对象。

    def __init__(self, mongo_address, doc_managers=None, **kwargs):
        super(Connector, self).__init__()
        ...
        # List of DocManager instances
        if doc_managers:
            self.doc_managers = doc_managers
        else:
            LOG.warning('No doc managers specified, using simulator.')
            # Avoid circular import on get_mininum_mongodb_version.
            from mongo_connector.doc_managers import doc_manager_simulator
            self.doc_managers = (doc_manager_simulator.DocManager(),)

## from_config()

    @classmethod
    def from_config(cls, config):
        """Create a new Connector instance from a Config object."""
        ...
        connector = Connector(
            mongo_address=config['mainAddress'],
            doc_managers=config['docManagers'],
            oplog_checkpoint=os.path.abspath(config['oplogFile']),
            ...
        )
        return connector

# main()

config对象是main()中生成的:

    # Parse configuration and setup logging.
    conf = config.Config(get_config_options())
    conf.parse_args()
    
# 存储到Elasticsearch中的数据

对于MongoDB中的database/collection/document，会映射到Elasticsearch中的index/type/document。

此外，在Elasticsearch中还会创建一个mongodb_meta/mongodb_meta，其document仅包括oplog的namespace和timestamp。

两种document示例：

curl -XGET "http://localhost:9900/mongodb_meta/_search?pretty"

      {
        "_index" : "mongodb_meta",
        "_type" : "mongodb_meta",
        "_id" : "59f7ee43631357381ab36011",
        "_score" : 1.0,
        "_source" : {
          "ns" : "test_db.test_collection",
          "_ts" : 6482912160153337866
        }
      },

curl -XGET "http://localhost:9900/test_db/test_collection/59f7ee43631357381ab36011/_search?pretty"

curl -XGET "http://localhost:9900/test_db/test_collection/_search?q=_id:59f7ee43631357381ab36011&pretty"


    3c9d154d1035:~/db1$ curl -XGET "http://localhost:9900/test_db/test_collection/_search?q=_id:59f7ee43631357381ab36011&pretty"
    {
      ...
      "hits" : {
        "total" : 1,
        "max_score" : 1.0,
        "hits" : [
          {
            "_index" : "test_db",
            "_type" : "test_collection",
            "_id" : "59f7ee43631357381ab36011",
            "_score" : 1.0,
            "_source" : {
              "value" : 3.0
            }
          }
        ]
      }
    }
    3c9d154d1035:~/db1$ 


59f7ee43-631357-381a-b36011
timestamp - machine - pid - increment



mongodb_meta的目的: https://github.com/mongodb-labs/mongo-connector/wiki/FAQ#what-is-the-mongodb_meta-index-in-elasticsearch

    What is the mongodb_meta index in Elasticsearch?

    Mongo Connector creates a mongodb_meta index in Elasticsearch 
    in order to keep track of when documents were last modified. 
    This is used to resolve conflicts in the event of a replica 
    set rollback event, but is kept in a separate index so that 
    it can be removed easily if necessary.

