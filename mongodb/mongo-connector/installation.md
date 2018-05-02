mongo-connector - Installation

# Ref

- https://github.com/mongodb-labs/mongo-connector

# Command

两个命令：

    sudo pip install mongo-connector
    sudo pip install 'mongo-connector[elastic5]'

安装成功之后，就可以执行mongo-connector了。

# Detail

    $ sudo pip install mongo-connector
    Collecting mongo-connector
      Downloading https://pypi.nevint.com/packages/source/m/mongo-connector/mongo_connector-2.5.1-py2.py3-none-any.whl?remote=https%3A%2F%2Fmirrors.aliyun.com%2Fpypi%2Fpackages%2F62%2F8d%2Fe2be80a56bcbdbd846c8c62cc0eef8bb3a4c20c47f41453c2b629ca44c71%2Fmongo_connector-2.5.1-py2.py3-none-any.whl (58kB)
        100% |████████████████████████████████| 61kB 882kB/s 
    Collecting pymongo>=2.9 (from mongo-connector)
      Downloading https://pypi.nevint.com/packages/source/p/pymongo/pymongo-3.6.1-cp27-cp27mu-manylinux1_x86_64.whl?remote=https%3A%2F%2Fmirrors.aliyun.com%2Fpypi%2Fpackages%2Fdb%2F5a%2F77060da2196471c8c47eeed6526029bd35cb2f10b1e4fc0e5e5234ca1aa0%2Fpymongo-3.6.1-cp27-cp27mu-manylinux1_x86_64.whl (381kB)
        100% |████████████████████████████████| 389kB 9.3MB/s 
    Installing collected packages: pymongo, mongo-connector
      Found existing installation: pymongo 2.5.2
        Uninstalling pymongo-2.5.2:
          Successfully uninstalled pymongo-2.5.2
    Successfully installed mongo-connector-2.5.1 pymongo-3.6.1
    $ ls -l /usr/bin/mongo-connector
    -rwxr-xr-x. 1 root root 227 4月  19 15:39 /usr/bin/mongo-connector
    $ sudo pip install 'mongo-connector[elastic5]'
    Requirement already satisfied (use --upgrade to upgrade): mongo-connector[elastic5] in /usr/lib/python2.7/site-packages
    Requirement already satisfied (use --upgrade to upgrade): pymongo>=2.9 in /usr/lib64/python2.7/site-packages (from mongo-connector[elastic5])
    Collecting elastic2-doc-manager[elastic5]; extra == "elastic5" (from mongo-connector[elastic5])
      Downloading https://pypi.nevint.com/packages/source/e/elastic2-doc-manager/elastic2_doc_manager-0.3.0-py2.py3-none-any.whl?remote=https%3A%2F%2Fmirrors.aliyun.com%2Fpypi%2Fpackages%2Fc4%2F86%2F35b976c7c85745b46565335a07b811249204489a1565095238a8f6482493%2Felastic2_doc_manager-0.3.0-py2.py3-none-any.whl
    Collecting elasticsearch<6.0.0,>=5.0.0; extra == "elastic5" (from elastic2-doc-manager[elastic5]; extra == "elastic5"->mongo-connector[elastic5])
      Downloading https://pypi.nevint.com/packages/source/e/elasticsearch/elasticsearch-5.5.2-py2.py3-none-any.whl?remote=https%3A%2F%2Fmirrors.aliyun.com%2Fpypi%2Fpackages%2F7f%2Fb0%2Fc87bc0744c3193c7b7f07b0469bbeaaf7df363cb452d882783c283572345%2Felasticsearch-5.5.2-py2.py3-none-any.whl (59kB)
        100% |████████████████████████████████| 61kB 213kB/s 
    Collecting urllib3<1.23,>=1.21.1 (from elasticsearch<6.0.0,>=5.0.0; extra == "elastic5"->elastic2-doc-manager[elastic5]; extra == "elastic5"->mongo-connector[elastic5])
      Downloading https://pypi.nevint.com/packages/source/u/urllib3/urllib3-1.22-py2.py3-none-any.whl?remote=https%3A%2F%2Fmirrors.aliyun.com%2Fpypi%2Fpackages%2F63%2Fcb%2F6965947c13a94236f6d4b8223e21beb4d576dc72e8130bd7880f600839b8%2Furllib3-1.22-py2.py3-none-any.whl (132kB)
        100% |████████████████████████████████| 133kB 1.5MB/s 
    Installing collected packages: urllib3, elasticsearch, elastic2-doc-manager
      Found existing installation: urllib3 1.10.2
        Uninstalling urllib3-1.10.2:
          Successfully uninstalled urllib3-1.10.2
    Successfully installed elastic2-doc-manager-0.3.0 elasticsearch-5.5.2 urllib3-1.22
    $ 
