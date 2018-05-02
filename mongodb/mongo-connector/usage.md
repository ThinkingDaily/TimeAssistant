# Ref

- https://github.com/mongodb-labs/mongo-connector

# help

    $ mongo-connector --help
    Usage: mongo-connector [options]

    ...
    $ 


mongo-connector -m <mongodb server hostname>:<replica set port> \
                -t <replication endpoint URL, e.g. http://localhost:8983/solr> \
                -d <name of doc manager, e.g., solr_doc_manager>

e.g:

    mongo-connector -m mgo_ip:mgo_port -a username -p password -n db_name.* -t es_ip:es_port -d elastic2_doc_manager

这里的-a不要写成-u

# Example

    mongo-connector -m <mongo_host>:<mongo_port> -a <mongo_user> -p <mongo_password> -t <es_user>:<es_password>@<es_host>:<es_port> -n <db_name>.* -o ./mongo-connector.oplog -d elastic2_doc_manager
