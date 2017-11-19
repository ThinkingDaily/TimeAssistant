MongoDB - Elasticsearch Connector

# References

- https://blog.jixee.me/how-to-use-mongo-connector-with-elasticsearch/

# Create Images

## image with software

    docker pull frolvlad/alpine-python2
    docker run -it --name temp_inst --tty frolvlad/alpine-python2
        apk update
        apk add bash curl openjdk8-jre

        # elasticsearch
        mkdir /mongo-es
        curl https://artifacts.elastic.co/downloads/elasticsearch/elasticsearch-5.6.3.tar.gz -o /mongo-es/elasticsearch-5.6.3.tar.gz

        # mongodb
        apk add --no-cache mongodb

        # mongo connector
        pip install mongo-connector
        pip install 'mongo-connector[elastic5]'

        # add user elasticsearch and create work dir
        adduser -D -u 1000 -h /usr/share/elasticsearch elasticsearch
        su - elasticsearch
        cp /mongo-es/elasticsearch-5.6.3.tar.gz .
        tar -xzf elasticsearch-5.6.3.tar.gz 
        mkdir -p es_node/data es_node/logs
        cp -rf elasticsearch-5.6.3/config es_node/
        vi es_node/config/elasticsearch.yml 
        # change port to 9600

        # Create a MongoDB database and insert a document.
        mkdir ~/db
        exit # back to root 
        exit 

    docker commit -a "mongo-es@examples.com" -m "mongo connector for elasticsearch" temp_inst mongo_es/alpine:v1
    docker rm temp_inst

## Image which starts elasticsearch and mongodb

    docker run -it --name temp_inst --tty mongo_es/alpine:v1
        su - elasticsearch

        # Start Elasticsearch        
        ./elasticsearch-5.6.3/bin/elasticsearch -Enode.name=es_node -Epath.conf=./es_node/config/ -Epath.data=./es_node/data -Epath.logs=./es_node/logs -p ./es_node/pid
        # Ctrl+C
        ./elasticsearch-5.6.3/bin/elasticsearch -Enode.name=es_node -Epath.conf=./es_node/config/ -Epath.data=./es_node/data -Epath.logs=./es_node/logs -p ./es_node/pid &
        curl localhost:9600

        # Start mongodb and verify it.
        mongod --port 20000 --dbpath /usr/share/elasticsearch/db &
        mongo --nodb
            conn = new Mongo("localhost:20000")
            db = conn.getDB("mytest")
            db.coll.insert({name:'Tom'})
            db.coll.find()
            exit
        
        # Test connector, now it will fail.
        mongo-connector --auto-commit-interval=0 -m mongo:20000 -t elasticsearch:9600 -d elastic2_doc_manager -n mytest.coll

        exit // Back to root
        exit
    docker commit -a "mongo-es@examples.com" -m "starts elasticsearch and mongodb service" temp_inst mongo_es/alpine:v2
    docker rm temp_inst

# Connector Test

## Method 1 

Uses the mothod describe in [https://blog.jixee.me/how-to-use-mongo-connector-with-elasticsearch/](https://blog.jixee.me/how-to-use-mongo-connector-with-elasticsearch/).

    docker run -it --rm --tty mongo_es/alpine:v2
        # start Elasticsearch
        su - elasticsearch
        ./elasticsearch-5.6.3/bin/elasticsearch -Enode.name=es_node -Epath.conf=./es_node/config/ -Epath.data=./es_node/data -Epath.logs=./es_node/logs -p ./es_node/pid &
        curl localhost:9600

        # Create test directory
        mkdir ~/test_db
    
        # Prepare mongod.conf
        vi ~/test_db/mongod.conf

        # Start mongod
        mongod -f /usr/share/elasticsearch/test_db/mongod.conf &

        # Create db & insert data
        mongo --port 20000
            rs.initiate()
            use connectortest
            db.createCollection("syncthis");
            for (var i = 1; i <= 10; i++) {
               db.syncthis.insert( { value : i } )
            }
            db.syncthis.find()
            exit

        # Start connector
        mongo-connector -m localhost:20000 -t http://localhost:9600 -o /usr/share/elasticsearch/test_db/mongo-connector.oplog -d elastic2_doc_manager -n connectortest.syncthis
        ^C # Break it and run it as a deamon
        mongo-connector -m localhost:20000 -t http://localhost:9600 -o /usr/share/elasticsearch/test_db/mongo-connector.oplog -d elastic2_doc_manager -n connectortest.syncthis &

        # Search Elasticsearch
        curl 127.0.0.1:9600/connectortest/_count # count is 10
        curl 127.0.0.1:9600/connectortest/_search?pretty
    
        # Insert additional 5 records and verify the Elasticsearch
        mongo --port 20000
            use connectortest
            rs0:PRIMARY> for (var i = 1; i <= 5; i++) {    db.syncthis.insert( { value : 10 + i } ) }
            rs0:PRIMARY> exit
        curl 127.0.0.1:9600/connectortest/_count
        ps -ef # Display the mongod, es, mongo-connector
        # kill them and exit

## Method 2

### Commands

see <<Deploy Replica Set>>, and continue with the following commands:

    ./elasticsearch-5.6.3/bin/elasticsearch -Enode.name=es_node -Epath.conf=./es_node/config/ -Epath.data=./es_node/data -Epath.logs=./es_node/logs -p ./es_node/pid &
    curl localhost:9600
    mongo-connector -m localhost:20001 -t http://localhost:9600 -o /usr/share/elasticsearch/test_db1/mongo-connector.oplog -d elastic2_doc_manager -n test_db.test_collection &
    curl 127.0.0.1:9600/test_db/_count

### Detail

    43c40e621eea:~$ ./elasticsearch-5.6.3/bin/elasticsearch -Enode.name=es_node -Epath.conf=./es_node/config/ -Epath.data=./es_node/data -Epath.logs=./es_node/logs -p ./es_node/pid &
    43c40e621eea:~$ [2017-10-30T10:43:30,064][INFO ][o.e.n.Node               ] [es_node] initializing ...
    [2017-10-30T10:43:30,548][INFO ][o.e.e.NodeEnvironment    ] [es_node] using [1] data paths, mounts [[/ (overlay)]], net usable_space [55.5gb], net total_space [62.7gb], spins? [possibly], types [overlay]
    [2017-10-30T10:43:30,549][INFO ][o.e.e.NodeEnvironment    ] [es_node] heap size [1.9gb], compressed ordinary object pointers [true]
    [2017-10-30T10:43:30,553][INFO ][o.e.n.Node               ] [es_node] node name [es_node], node ID [1ZDKIQVVQqGMoXRt2I_tcg]
    [2017-10-30T10:43:30,554][INFO ][o.e.n.Node               ] [es_node] version[5.6.3], pid[305], build[1a2f265/2017-10-06T20:33:39.012Z], OS[Linux/4.9.12-moby/amd64], JVM[Oracle Corporation/OpenJDK 64-Bit Server VM/1.8.0_131/25.131-b11]
    [2017-10-30T10:43:30,554][INFO ][o.e.n.Node               ] [es_node] JVM arguments [-Xms2g, -Xmx2g, -XX:+UseConcMarkSweepGC, -XX:CMSInitiatingOccupancyFraction=75, -XX:+UseCMSInitiatingOccupancyOnly, -XX:+AlwaysPreTouch, -Xss1m, -Djava.awt.headless=true, -Dfile.encoding=UTF-8, -Djna.nosys=true, -Djdk.io.permissionsUseCanonicalPath=true, -Dio.netty.noUnsafe=true, -Dio.netty.noKeySetOptimization=true, -Dio.netty.recycler.maxCapacityPerThread=0, -Dlog4j.shutdownHookEnabled=false, -Dlog4j2.disable.jmx=true, -Dlog4j.skipJansi=true, -XX:+HeapDumpOnOutOfMemoryError, -Des.path.home=/usr/share/elasticsearch/elasticsearch-5.6.3]
    [2017-10-30T10:43:33,734][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [aggs-matrix-stats]
    [2017-10-30T10:43:33,735][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [ingest-common]
    [2017-10-30T10:43:33,735][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [lang-expression]
    [2017-10-30T10:43:33,735][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [lang-groovy]
    [2017-10-30T10:43:33,735][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [lang-mustache]
    [2017-10-30T10:43:33,736][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [lang-painless]
    [2017-10-30T10:43:33,736][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [parent-join]
    [2017-10-30T10:43:33,736][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [percolator]
    [2017-10-30T10:43:33,736][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [reindex]
    [2017-10-30T10:43:33,737][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [transport-netty3]
    [2017-10-30T10:43:33,737][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [transport-netty4]
    [2017-10-30T10:43:33,738][INFO ][o.e.p.PluginsService     ] [es_node] no plugins loaded
    [2017-10-30T10:43:36,507][INFO ][o.e.d.DiscoveryModule    ] [es_node] using discovery type [zen]
    [2017-10-30T10:43:37,374][INFO ][o.e.n.Node               ] [es_node] initialized
    [2017-10-30T10:43:37,375][INFO ][o.e.n.Node               ] [es_node] starting ...
    [2017-10-30T10:43:37,629][INFO ][o.e.t.TransportService   ] [es_node] publish_address {127.0.0.1:9300}, bound_addresses {[::1]:9300}, {127.0.0.1:9300}
    [2017-10-30T10:43:38,381][INFO ][o.e.m.j.JvmGcMonitorService] [es_node] [gc][1] overhead, spent [325ms] collecting in the last [1s]
    [2017-10-30T10:43:40,737][INFO ][o.e.c.s.ClusterService   ] [es_node] new_master {es_node}{1ZDKIQVVQqGMoXRt2I_tcg}{3DDhP1NBRq2ba5jku1G3HQ}{127.0.0.1}{127.0.0.1:9300}, reason: zen-disco-elected-as-master ([0] nodes joined)
    [2017-10-30T10:43:40,763][INFO ][o.e.h.n.Netty4HttpServerTransport] [es_node] publish_address {127.0.0.1:9600}, bound_addresses {[::1]:9600}, {127.0.0.1:9600}
    [2017-10-30T10:43:40,763][INFO ][o.e.n.Node               ] [es_node] started
    [2017-10-30T10:43:40,832][INFO ][o.e.g.GatewayService     ] [es_node] recovered [0] indices into cluster_state

    43c40e621eea:~$ 
    43c40e621eea:~$ 
    43c40e621eea:~$ curl localhost:9600
    {
      "name" : "es_node",
      "cluster_name" : "elasticsearch",
      "cluster_uuid" : "VblwEGsfQiGk3uaUwjwV7g",
      "version" : {
        "number" : "5.6.3",
        "build_hash" : "1a2f265",
        "build_date" : "2017-10-06T20:33:39.012Z",
        "build_snapshot" : false,
        "lucene_version" : "6.6.1"
      },
      "tagline" : "You Know, for Search"
    }
    43c40e621eea:~$ 
    43c40e621eea:~$ 
    43c40e621eea:~$ 
    43c40e621eea:~$ mongo-connector -m localhost:20001 -t http://localhost:9600 -o /usr/share/elasticsearch/test_db1/mongo-connector.oplog -d elastic2_doc_manager -n test_db.test_collection &
    43c40e621eea:~$ Logging to /usr/share/elasticsearch/mongo-connector.log.
    [2017-10-30T10:45:16,811][INFO ][o.e.c.m.MetaDataCreateIndexService] [es_node] [test_db] creating index, cause [auto(bulk api)], templates [], shards [5]/[1], mappings []
    [2017-10-30T10:45:17,223][INFO ][o.e.c.m.MetaDataCreateIndexService] [es_node] [mongodb_meta] creating index, cause [auto(bulk api)], templates [], shards [5]/[1], mappings []
    [2017-10-30T10:45:18,748][INFO ][o.e.c.m.MetaDataMappingService] [es_node] [test_db/hkb_ZPvGSMaUGXPu6d_K4A] create_mapping [test_collection]
    [2017-10-30T10:45:19,106][INFO ][o.e.c.m.MetaDataMappingService] [es_node] [mongodb_meta/32UOIbD3QXe9qoqfrVul2Q] create_mapping [mongodb_meta]

    43c40e621eea:~$ 
    43c40e621eea:~$ curl 127.0.0.1:9600/connectortest/_count
    {"error":{"root_cause":[{"type":"index_not_found_exception","reason":"no such index","resource.type":"index_or_alias","resource.id":"connectortest","index_uuid":"_na_","index":"connectortest"}],"type":"index_not_found_exception","reason":"no such index","resource.type":"index_or_alias","resource.id":"connectortest","index_uuid":"_na_","index":"connectortest"},"status":404}43c40e621eea:~$ 
    43c40e621eea:~$ 
    43c40e621eea:~$ curl 127.0.0.1:9600/test_db/_count
    {"count":10,"_shards":{"total":5,"successful":5,"skipped":0,"failed":0}}43c40e621eea:~$ 
    43c40e621eea:~$ 
    43c40e621eea:~$ 


### Shutdown

    mongod --port 20001 --dbpath /usr/share/elasticsearch/test_db1 --shutdown
    mongod --port 20002 --dbpath /usr/share/elasticsearch/test_db2 --shutdown
    mongod --port 20003 --dbpath /usr/share/elasticsearch/test_db3 --shutdown

# Appendix

## mongod.conf

    # mongod.conf
     
    # for documentation of all options, see:
    #   http://docs.mongodb.org/manual/reference/configuration-options/
     
    # Where and how to store data.
    storage:
      dbPath: /usr/share/elasticsearch/test_db
      journal:
        enabled: true
    #  engine:
    #  mmapv1:
    #  wiredTiger:
     
    # where to write logging data.
    systemLog:
      destination: file
      logAppend: true
      path: /usr/share/elasticsearch/test_db/mongod.log
     
    # network interfaces
    net:
      port: 20000
    #  bindIp: 127.0.0.1
     
     
    #processManagement:
     
    #security:
     
    #operationProfiling:
     
    replication:
      replSetName: rs0
      oplogSizeMB: 100
     
    #sharding:
     
    ## Enterprise-Only Options:
     
    #auditLog:
     
    #snmp:

## Method 1 - Commands & Results

    $ docker run -it --rm --tty mongo_es/alpine:v2
    / # su - elasticsearch
    2dc76fcb4cd3:~$ ls
    db                          elasticsearch-5.6.3.tar.gz  mongo-connector.log
    elasticsearch-5.6.3         es_node                     oplog.timestamp
    2dc76fcb4cd3:~$ curl localhost:9600
    curl: (7) Failed to connect to localhost port 9600: Connection refused
    2dc76fcb4cd3:~$ curl 127.0.0.1:9600
    curl: (7) Failed to connect to 127.0.0.1 port 9600: Connection refused
    2dc76fcb4cd3:~$ ps -ef
    PID   USER     TIME   COMMAND
        1 root       0:00 /bin/sh
        7 elastics   0:00 -sh
       12 elastics   0:00 ps -ef
    2dc76fcb4cd3:~$ ./elasticsearch-5.6.3/bin/elasticsearch -Enode.name=es_node -Epath.conf=./es_node/config/ -Epath.data=./es_node/data -Epath.logs=./es_node/lo
    gs -p ./es_node/pid &
    2dc76fcb4cd3:~$ curl 127.0.0.1:9600
    curl: (7) Failed to connect to 127.0.0.1 port 9600: Connection refused
    2dc76fcb4cd3:~$ [2017-10-30T06:02:01,216][INFO ][o.e.n.Node               ] [es_node] initializing ...
    [2017-10-30T06:02:01,524][INFO ][o.e.e.NodeEnvironment    ] [es_node] using [1] data paths, mounts [[/ (overlay)]], net usable_space [56.4gb], net total_space [62.7gb], spins? [possibly], types [overlay]
    [2017-10-30T06:02:01,524][INFO ][o.e.e.NodeEnvironment    ] [es_node] heap size [1.9gb], compressed ordinary object pointers [true]
    [2017-10-30T06:02:01,527][INFO ][o.e.n.Node               ] [es_node] node name [es_node], node ID [1ZDKIQVVQqGMoXRt2I_tcg]
    [2017-10-30T06:02:01,527][INFO ][o.e.n.Node               ] [es_node] version[5.6.3], pid[13], build[1a2f265/2017-10-06T20:33:39.012Z], OS[Linux/4.9.12-moby/amd64], JVM[Oracle Corporation/OpenJDK 64-Bit Server VM/1.8.0_131/25.131-b11]
    [2017-10-30T06:02:01,527][INFO ][o.e.n.Node               ] [es_node] JVM arguments [-Xms2g, -Xmx2g, -XX:+UseConcMarkSweepGC, -XX:CMSInitiatingOccupancyFraction=75, -XX:+UseCMSInitiatingOccupancyOnly, -XX:+AlwaysPreTouch, -Xss1m, -Djava.awt.headless=true, -Dfile.encoding=UTF-8, -Djna.nosys=true, -Djdk.io.permissionsUseCanonicalPath=true, -Dio.netty.noUnsafe=true, -Dio.netty.noKeySetOptimization=true, -Dio.netty.recycler.maxCapacityPerThread=0, -Dlog4j.shutdownHookEnabled=false, -Dlog4j2.disable.jmx=true, -Dlog4j.skipJansi=true, -XX:+HeapDumpOnOutOfMemoryError, -Des.path.home=/usr/share/elasticsearch/elasticsearch-5.6.3]
    [2017-10-30T06:02:04,935][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [aggs-matrix-stats]
    [2017-10-30T06:02:04,936][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [ingest-common]
    [2017-10-30T06:02:04,936][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [lang-expression]
    [2017-10-30T06:02:04,937][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [lang-groovy]
    [2017-10-30T06:02:04,938][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [lang-mustache]
    [2017-10-30T06:02:04,938][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [lang-painless]
    [2017-10-30T06:02:04,939][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [parent-join]
    [2017-10-30T06:02:04,939][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [percolator]
    [2017-10-30T06:02:04,939][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [reindex]
    [2017-10-30T06:02:04,939][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [transport-netty3]
    [2017-10-30T06:02:04,940][INFO ][o.e.p.PluginsService     ] [es_node] loaded module [transport-netty4]
    [2017-10-30T06:02:04,941][INFO ][o.e.p.PluginsService     ] [es_node] no plugins loaded
    [2017-10-30T06:02:07,713][INFO ][o.e.d.DiscoveryModule    ] [es_node] using discovery type [zen]
    [2017-10-30T06:02:08,418][INFO ][o.e.n.Node               ] [es_node] initialized
    [2017-10-30T06:02:08,419][INFO ][o.e.n.Node               ] [es_node] starting ...
    [2017-10-30T06:02:08,684][INFO ][o.e.t.TransportService   ] [es_node] publish_address {127.0.0.1:9300}, bound_addresses {[::1]:9300}, {127.0.0.1:9300}
    [2017-10-30T06:02:09,426][INFO ][o.e.m.j.JvmGcMonitorService] [es_node] [gc][1] overhead, spent [332ms] collecting in the last [1s]
    [2017-10-30T06:02:11,807][INFO ][o.e.c.s.ClusterService   ] [es_node] new_master {es_node}{1ZDKIQVVQqGMoXRt2I_tcg}{pVJGWCHXQoWxj8jRE9VbkA}{127.0.0.1}{127.0.0.1:9300}, reason: zen-disco-elected-as-master ([0] nodes joined)
    [2017-10-30T06:02:11,854][INFO ][o.e.h.n.Netty4HttpServerTransport] [es_node] publish_address {127.0.0.1:9600}, bound_addresses {[::1]:9600}, {127.0.0.1:9600}
    [2017-10-30T06:02:11,854][INFO ][o.e.n.Node               ] [es_node] started
    [2017-10-30T06:02:11,912][INFO ][o.e.g.GatewayService     ] [es_node] recovered [0] indices into cluster_state
    2dc76fcb4cd3:~$ curl 127.0.0.1:9600
    {
      "name" : "es_node",
      "cluster_name" : "elasticsearch",
      "cluster_uuid" : "VblwEGsfQiGk3uaUwjwV7g",
      "version" : {
        "number" : "5.6.3",
        "build_hash" : "1a2f265",
        "build_date" : "2017-10-06T20:33:39.012Z",
        "build_snapshot" : false,
        "lucene_version" : "6.6.1"
      },
      "tagline" : "You Know, for Search"
    }
    2dc76fcb4cd3:~$ 
    2dc76fcb4cd3:~$ 
    2dc76fcb4cd3:~$ mkdir ~/test_db
    2dc76fcb4cd3:~$ vi ~/test_db/mongod.conf
    2dc76fcb4cd3:~$ mongo --port 20000
    MongoDB shell version v3.4.4
    connecting to: mongodb://127.0.0.1:20000/
    2017-10-30T06:05:47.796+0000 W NETWORK  [thread1] Failed to connect to 127.0.0.1:20000, in(checking socket for error after poll), reason: Connection refused
    2017-10-30T06:05:47.821+0000 E QUERY    [thread1] Error: couldn't connect to server 127.0.0.1:20000, connection attempt failed :
    connect@src/mongo/shell/mongo.js:237:13
    @(connect):1:6
    exception: connect failed
    2dc76fcb4cd3:~$ mongod -f /usr/share/elasticsearch/test_db/mongod.conf &
    2dc76fcb4cd3:~$ mongo --port 20000
    MongoDB shell version v3.4.4
    connecting to: mongodb://127.0.0.1:20000/
    MongoDB server version: 3.4.4
    Server has startup warnings: 
    2017-10-30T06:06:08.417+0000 I CONTROL  [initandlisten] 
    2017-10-30T06:06:08.417+0000 I CONTROL  [initandlisten] ** WARNING: Access control is not enabled for the database.
    2017-10-30T06:06:08.417+0000 I CONTROL  [initandlisten] **          Read and write access to data and configuration is unrestricted.
    2017-10-30T06:06:08.417+0000 I CONTROL  [initandlisten] 
    > rs.initiate()
    {
        "info2" : "no configuration specified. Using a default configuration for the set",
        "me" : "2dc76fcb4cd3:20000",
        "ok" : 1
    }
    rs0:SECONDARY> use connectortest
    switched to db connectortest
    rs0:PRIMARY> db.createCollection("syncthis");
    { "ok" : 1 }
    rs0:PRIMARY> for (var i = 1; i <= 10; i++) {
    ...        db.syncthis.insert( { value : i } )
    ...     }
    WriteResult({ "nInserted" : 1 })
    rs0:PRIMARY> db.syncthis.find()
    { "_id" : ObjectId("59f6c17cd86212df7475eba3"), "value" : 1 }
    { "_id" : ObjectId("59f6c17cd86212df7475eba4"), "value" : 2 }
    { "_id" : ObjectId("59f6c17cd86212df7475eba5"), "value" : 3 }
    { "_id" : ObjectId("59f6c17cd86212df7475eba6"), "value" : 4 }
    { "_id" : ObjectId("59f6c17cd86212df7475eba7"), "value" : 5 }
    { "_id" : ObjectId("59f6c17cd86212df7475eba8"), "value" : 6 }
    { "_id" : ObjectId("59f6c17cd86212df7475eba9"), "value" : 7 }
    { "_id" : ObjectId("59f6c17cd86212df7475ebaa"), "value" : 8 }
    { "_id" : ObjectId("59f6c17cd86212df7475ebab"), "value" : 9 }
    { "_id" : ObjectId("59f6c17cd86212df7475ebac"), "value" : 10 }
    rs0:PRIMARY> exit
    bye
    2dc76fcb4cd3:~$ 
    2dc76fcb4cd3:~$ mongo-connector -m localhost:20000 -t http://localhost:9600 -o /usr/share/elasticsearch/test_db/mongo-connector.oplog -d elastic2_doc_manager
     -n connectortest.syncthis
    Logging to /usr/share/elasticsearch/mongo-connector.log.
    [2017-10-30T06:09:08,525][INFO ][o.e.c.m.MetaDataCreateIndexService] [es_node] [connectortest] creating index, cause [auto(bulk api)], templates [], shards [5]/[1], mappings []
    [2017-10-30T06:09:09,025][INFO ][o.e.c.m.MetaDataCreateIndexService] [es_node] [mongodb_meta] creating index, cause [auto(bulk api)], templates [], shards [5]/[1], mappings []
    [2017-10-30T06:09:10,582][INFO ][o.e.c.m.MetaDataMappingService] [es_node] [connectortest/epRRTCxsR0mhGSh6Lu0qfA] create_mapping [syncthis]
    [2017-10-30T06:09:10,595][INFO ][o.e.c.m.MetaDataMappingService] [es_node] [mongodb_meta/XKvbu4Z8TJe3P5fXoWpu5A] create_mapping [mongodb_meta]



    ^C
    2dc76fcb4cd3:~$ 
    2dc76fcb4cd3:~$ mongo-connector -m localhost:20000 -t http://localhost:9600 -o /usr/share/elasticsearch/test_db/mongo-connector.oplog -d elastic2_doc_manager
     -n connectortest.syncthis &
    2dc76fcb4cd3:~$ Logging to /usr/share/elasticsearch/mongo-connector.log.

    2dc76fcb4cd3:~$ curl 127.0.0.1:9600/connectortest/_count
    {"count":10,"_shards":{"total":5,"successful":5,"skipped":0,"failed":0}}2dc76fcb4cd3:~$ 
    2dc76fcb4cd3:~$ curl 127.0.0.1:9600/connectortest/_search?pretty
    {
      "took" : 44,
      "timed_out" : false,
      "_shards" : {
        "total" : 5,
        "successful" : 5,
        "skipped" : 0,
        "failed" : 0
      },
      "hits" : {
        "total" : 10,
        "max_score" : 1.0,
        "hits" : [
          {
            "_index" : "connectortest",
            "_type" : "syncthis",
            "_id" : "59f6c17cd86212df7475eba3",
            "_score" : 1.0,
            "_source" : {
              "value" : 1.0
            }
          },
          {
            "_index" : "connectortest",
            "_type" : "syncthis",
            "_id" : "59f6c17cd86212df7475eba5",
            "_score" : 1.0,
            "_source" : {
              "value" : 3.0
            }
          },
          {
            "_index" : "connectortest",
            "_type" : "syncthis",
            "_id" : "59f6c17cd86212df7475ebaa",
            "_score" : 1.0,
            "_source" : {
              "value" : 8.0
            }
          },
          {
            "_index" : "connectortest",
            "_type" : "syncthis",
            "_id" : "59f6c17cd86212df7475ebab",
            "_score" : 1.0,
            "_source" : {
              "value" : 9.0
            }
          },
          {
            "_index" : "connectortest",
            "_type" : "syncthis",
            "_id" : "59f6c17cd86212df7475eba6",
            "_score" : 1.0,
            "_source" : {
              "value" : 4.0
            }
          },
          {
            "_index" : "connectortest",
            "_type" : "syncthis",
            "_id" : "59f6c17cd86212df7475eba8",
            "_score" : 1.0,
            "_source" : {
              "value" : 6.0
            }
          },
          {
            "_index" : "connectortest",
            "_type" : "syncthis",
            "_id" : "59f6c17cd86212df7475eba9",
            "_score" : 1.0,
            "_source" : {
              "value" : 7.0
            }
          },
          {
            "_index" : "connectortest",
            "_type" : "syncthis",
            "_id" : "59f6c17cd86212df7475eba4",
            "_score" : 1.0,
            "_source" : {
              "value" : 2.0
            }
          },
          {
            "_index" : "connectortest",
            "_type" : "syncthis",
            "_id" : "59f6c17cd86212df7475ebac",
            "_score" : 1.0,
            "_source" : {
              "value" : 10.0
            }
          },
          {
            "_index" : "connectortest",
            "_type" : "syncthis",
            "_id" : "59f6c17cd86212df7475eba7",
            "_score" : 1.0,
            "_source" : {
              "value" : 5.0
            }
          }
        ]
      }
    }
    2dc76fcb4cd3:~$ mongo --port 20000
    MongoDB shell version v3.4.4
    connecting to: mongodb://127.0.0.1:20000/
    MongoDB server version: 3.4.4
    Server has startup warnings: 
    2017-10-30T06:06:08.417+0000 I CONTROL  [initandlisten] 
    2017-10-30T06:06:08.417+0000 I CONTROL  [initandlisten] ** WARNING: Access control is not enabled for the database.
    2017-10-30T06:06:08.417+0000 I CONTROL  [initandlisten] **          Read and write access to data and configuration is unrestricted.
    2017-10-30T06:06:08.417+0000 I CONTROL  [initandlisten] 
    rs0:PRIMARY> for (var i = 1; i <= 5; i++) {    db.syncthis.insert( { value : 10 + i } ) }
    WriteResult({ "nInserted" : 1 })
    rs0:PRIMARY> exit
    bye
    2dc76fcb4cd3:~$ curl 127.0.0.1:9600/connectortest/_count
    2dc76fcb4cd3:~$ curl 127.0.0.1:9600/connectortest/_count
    {"count":10,"_shards":{"total":5,"successful":5,"skipped":0,"failed":0}}2dc76fcb4cd3:~$ 
    2dc76fcb4cd3:~$ curl 127.0.0.1:9600/connectortest/_count
    {"count":10,"_shards":{"total":5,"successful":5,"skipped":0,"failed":0}}2dc76fcb4cd3:~$ 
    2dc76fcb4cd3:~$ curl 127.0.0.1:9600/connectortest/_count
    {"count":10,"_shards":{"total":5,"successful":5,"skipped":0,"failed":0}}2dc76fcb4cd3:~$ 
    2dc76fcb4cd3:~$ mongo --port 20000
    MongoDB shell version v3.4.4
    connecting to: mongodb://127.0.0.1:20000/
    MongoDB server version: 3.4.4
    Server has startup warnings: 
    2017-10-30T06:06:08.417+0000 I CONTROL  [initandlisten] 
    2017-10-30T06:06:08.417+0000 I CONTROL  [initandlisten] ** WARNING: Access control is not enabled for the database.
    2017-10-30T06:06:08.417+0000 I CONTROL  [initandlisten] **          Read and write access to data and configuration is unrestricted.
    2017-10-30T06:06:08.417+0000 I CONTROL  [initandlisten] 
    rs0:PRIMARY> use connectortest
    switched to db connectortest
    rs0:PRIMARY> for (var i = 1; i <= 5; i++) {    db.syncthis.insert( { value : 10 + i } ) }
    WriteResult({ "nInserted" : 1 })
    rs0:PRIMARY> exit
    bye
    2dc76fcb4cd3:~$ curl 127.0.0.1:9600/connectortest/_count
    {"count":11,"_shards":{"total":5,"successful":5,"skipped":0,"failed":0}}2dc76fcb4cd3:~$ 
    2dc76fcb4cd3:~$ curl 127.0.0.1:9600/connectortest/_count
    {"count":15,"_shards":{"total":5,"successful":5,"skipped":0,"failed":0}}2dc76fcb4cd3:~$ 
    2dc76fcb4cd3:~$ curl 127.0.0.1:9600/connectortest/_count
    {"count":15,"_shards":{"total":5,"successful":5,"skipped":0,"failed":0}}2dc76fcb4cd3:~$ 
    2dc76fcb4cd3:~$ ps -ef
    PID   USER     TIME   COMMAND
        1 root       0:00 /bin/sh
        7 elastics   0:00 -sh
       13 elastics   0:25 /usr/bin/java -Xms2g -Xmx2g -XX:+UseConcMarkSweepGC -XX:CMSInitiatingOccupancyFraction=75 -XX:+UseCMSInitiatingOccupancyOnly -XX:+Alwa
      104 elastics   0:06 mongod -f /usr/share/elasticsearch/test_db/mongod.conf
      205 elastics   0:00 {mongo-connector} /usr/bin/python /usr/bin/mongo-connector -m localhost:20000 -t http://localhost:9600 -o /usr/share/elasticsearch/tes
      256 elastics   0:00 ps -ef
    2dc76fcb4cd3:~$ 



# Appendix: FAQ

## ServerSelectionTimeoutError

如果MongoDB没有启用ReplicaSet，那么connector不可用。

    c51c8209868f:~$ mongo-connector --auto-commit-interval=0 -m mongo:20000 -t elasticsearch:9600 -d elastic2_doc_manager
    Logging to /usr/share/elasticsearch/mongo-connector.log.
    Exception in thread Thread-2:
    Traceback (most recent call last):
    ...
    ServerSelectionTimeoutError: mongo:20000: [Errno -3] Try again

    c51c8209868f:~$ 

日志文件的完整内容：

    2017-10-27 09:14:36,338 [ALWAYS] mongo_connector.connector:51 - Starting mongo-connector version: 2.5.1
    2017-10-27 09:14:36,338 [ALWAYS] mongo_connector.connector:51 - Python version: 2.7.13 (default, Apr 20 2017, 12:13:37) 
    [GCC 6.3.0]
    2017-10-27 09:14:36,340 [ALWAYS] mongo_connector.connector:51 - Platform: Linux-4.9.12-moby-x86_64-with
    2017-10-27 09:14:36,340 [ALWAYS] mongo_connector.connector:51 - pymongo version: 3.5.1
    2017-10-27 09:14:36,340 [WARNING] mongo_connector.connector:1260 - pymongo version 3.5.1 was installed without the C extensions. "InvalidBSON: Date value out of range" errors may occur if there are documents with BSON Datetimes that represent times outside of Python's datetime limit.
    2017-10-27 09:14:36,341 [WARNING] mongo_connector.connector:167 - MongoConnector: Can't find /usr/share/elasticsearch/oplog.timestamp, attempting to create an empty progress log
    2017-10-27 09:15:06,391 [ERROR] mongo_connector.util:106 - Fatal Exception
    Traceback (most recent call last):
      File "/usr/lib/python2.7/site-packages/mongo_connector/util.py", line 104, in wrapped
        func(*args, **kwargs)
      File "/usr/lib/python2.7/site-packages/mongo_connector/connector.py", line 347, in run
        self.main_conn.admin.command('buildInfo')['version'])
      File "/usr/lib/python2.7/site-packages/pymongo/database.py", line 513, in command
        with client._socket_for_reads(read_preference) as (sock_info, slave_ok):
      File "/usr/lib/python2.7/contextlib.py", line 17, in __enter__
        return self.gen.next()
      File "/usr/lib/python2.7/site-packages/pymongo/mongo_client.py", line 904, in _socket_for_reads
        with self._get_socket(read_preference) as sock_info:
      File "/usr/lib/python2.7/contextlib.py", line 17, in __enter__
        return self.gen.next()
      File "/usr/lib/python2.7/site-packages/pymongo/mongo_client.py", line 868, in _get_socket
        server = self._get_topology().select_server(selector)
      File "/usr/lib/python2.7/site-packages/pymongo/topology.py", line 214, in select_server
        address))
      File "/usr/lib/python2.7/site-packages/pymongo/topology.py", line 189, in select_servers
        self._error_message(selector))
    ServerSelectionTimeoutError: mongo:20000: [Errno -3] Try again
    c51c8209868f:~$ 

## ReplicaSet

在[How to Use mongo-connector with Elasticsearch](https://blog.jixee.me/how-to-use-mongo-connector-with-elasticsearch/)中提到：

    Edit the MongoDB config file and turn on replication. 
    Since mongo-connector uses MongoDB’s Replica Set Oplog 
    to sync, replication is an important feature that must 
    be turned on in order for mongo-connector to work.

即connector要求MongoDB打开了replication功能，connector使用的是MongoDB的Replica Set Oplog进行同步。

## docker多shell连接

先以后台方式运行，然后exec到容器。

    docker run -idt mongo_es/alpine:v2
    docker ps -a # get the container id

    docker exec -it <container_id> /bin/bash
  

## read-only directory

启动mongod的时候，提示：
    
    mongod --replSet spock -f mongod.conf --fork

    exception in initAndListen: 20 Attempted to create a lock file on a read-only directory: /data/db, terminating

服务无法成功启动。

解决步骤：

    sudo mkdir -p /data/db
    sudo chown -Rv `whoami` /data/db
    mongod --replSet singleNodeRepl

## Mac Service

- 启动服务: brew services start mongo
- 查看所有服务及状态: brew services list
- 停止服务: brew services stop mongo

不支持：

    $ brew services start mongodb --replSet singleNodeRepl
    Error: singleNodeRepl is not a url or existing file

Detail Log:

    $ brew services start mongo
    ==> Successfully started `mongodb` (label: homebrew.mxcl.mongodb)
    $ brew services list
    Name      Status  User      Plist
    emacs     stopped           
    mariadb   started the__user /Users/the__user/Library/LaunchAgents/homebrew.mxcl.mariadb.plist
    mongodb   started the__user /Users/the__user/Library/LaunchAgents/homebrew.mxcl.mongodb.plist
    mosquitto started the__user /Users/the__user/Library/LaunchAgents/homebrew.mxcl.mosquitto.plist
    $ brew services stop mongo
    Stopping `mongodb`... (might take a while)
    ==> Successfully stopped `mongodb` (label: homebrew.mxcl.mongodb)
    $ brew services list
    Name      Status  User      Plist
    emacs     stopped           
    mariadb   started the__user /Users/the__user/Library/LaunchAgents/homebrew.mxcl.mariadb.plist
    mongodb   stopped           
    mosquitto started the__user /Users/the__user/Library/LaunchAgents/homebrew.mxcl.mosquitto.plist
    $ 


mongo换成mongodb也行:

    $ brew services start mongodb
    ==> Successfully started `mongodb` (label: homebrew.mxcl.mongodb)
    $ brew services list
    Name      Status  User      Plist
    emacs     stopped           
    mariadb   started the__user /Users/the__user/Library/LaunchAgents/homebrew.mxcl.mariadb.plist
    mongodb   started the__user /Users/the__user/Library/LaunchAgents/homebrew.mxcl.mongodb.plist
    mosquitto started the__user /Users/the__user/Library/LaunchAgents/homebrew.mxcl.mosquitto.plist
    $ brew services stop mongodb
    Stopping `mongodb`... (might take a while)
    ==> Successfully stopped `mongodb` (label: homebrew.mxcl.mongodb)
    $ 
