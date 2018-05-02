# namespace InvalidConfiguration

从github上拿到的json中，示例如下：

    "__namespaces": {
        "excluded.collection": false,
        "excluded_wildcard.*": false,
        "*.exclude_collection_from_every_database": false,
        "included.collection1": true,
        "included.collection2": {},
        ...
    }

在这个基础上增加 include 等字段后，会提示:

    mongo_connector.errors.InvalidConfiguration: Invalid option __included.collection2 in old style (pre 2.5.0) namespaces configuration. The only valid option names are: ['__mapping', '__include', 'mapping', '__exclude', '__gridfs', 'gridfs', '__comment__', 'exclude', 'include']

为此，可以把原来的那些字段都删除掉，而改用这里错误提示的字段。示例:

    "namespaces": {
        "include": ["your_db_name.*"]
    }
