Elasticsearch - ps

如下命令可以得到Elasticsearch启动的信息：

    ps | grep elasticsearch

/usr/bin/java -Xms2g -Xmx2g ... -Des.path.home=/your_dir/elasticsearch-5.5.0 -cp /your_dir/elasticsearch-5.5.0/lib/* org.elasticsearch.bootstrap.Elasticsearch
