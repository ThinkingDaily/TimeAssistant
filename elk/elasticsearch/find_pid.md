Elasticsearch - 查找pid

	$ ps -ef | grep "elas"
	  502 23642     1   0 251017  ??        48:34.89 /usr/bin/java -Xms2g -Xmx2g -XX:+UseConcMarkSweepGC -XX:CMSInitiatingOccupancyFraction=75 -XX:+UseCMSInitiatingOccupancyOnly -XX:+AlwaysPreTouch -server -Xss1m -Djava.awt.headless=true -Dfile.encoding=UTF-8 -Djna.nosys=true -Djdk.io.permissionsUseCanonicalPath=true -Dio.netty.noUnsafe=true -Dio.netty.noKeySetOptimization=true -Dio.netty.recycler.maxCapacityPerThread=0 -Dlog4j.shutdownHookEnabled=false -Dlog4j2.disable.jmx=true -Dlog4j.skipJansi=true -XX:+HeapDumpOnOutOfMemoryError -Des.path.home=/your_dir/es/elasticsearch-5.5.2 -cp /your_dir/es/elasticsearch-5.5.2/lib/* org.elasticsearch.bootstrap.Elasticsearch -d -Ecluster.name=fota -Enode.name=node_a -Epath.conf=./node/config -Epath.data=./node/data -Epath.logs=./node/logs -p node_a_pid
	  502 49623 46251   0  3:35下午 ttys006    0:00.00 grep elas
	$ 
