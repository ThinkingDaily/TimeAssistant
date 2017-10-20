# Ref

- MongoDB: The Definitive Guide, 2nd Edition: http://shop.oreilly.com/product/0636920028031.do

# Install mongoDB

Here is the steps on Mac OS X.

## Commands

    brew install mongodb
    (optional) brew upgrade mongodb
    brew services start mongodb, or 
    (optional) mongod --config /usr/local/etc/mongod.conf
    mongo
    (optional) http://localhost:27017/

## Details

### install

    $ brew install mongodb
    Updating Homebrew...
    ==> Auto-updated Homebrew!
    Updated 1 tap (homebrew/services).
    No changes to formulae.

    ==> Downloading https://homebrew.bintray.com/bottles/mongodb-3.4.7.el_capitan.bottle.1.tar.gz
    Already downloaded: /Users/tester/Library/Caches/Homebrew/mongodb-3.4.7.el_capitan.bottle.1.tar.gz
    ==> Pouring mongodb-3.4.7.el_capitan.bottle.1.tar.gz
    ==> Caveats
    To have launchd start mongodb now and restart at login:
      brew services start mongodb
    Or, if you don't want/need a background service you can just run:
      mongod --config /usr/local/etc/mongod.conf
    ==> Summary
    🍺  /usr/local/Cellar/mongodb/3.4.7: 19 files, 282.5MB
    $ 

### mongod.conf

    $ cat /usr/local/etc/mongod.conf
    systemLog:
      destination: file
      path: /usr/local/var/log/mongodb/mongo.log
      logAppend: true
    storage:
      dbPath: /usr/local/var/mongodb
    net:
      bindIp: 127.0.0.1
    $ ls -l /usr/local/var/mongodb/
    $ 

已经创建了缺省的数据库目录。

### servcie

    $ brew services start mongodb
    ==> Successfully started `mongodb` (label: homebrew.mxcl.mongodb)
    $ 

### mongo commands

    $ mongo
    MongoDB shell version v3.4.7
    connecting to: mongodb://127.0.0.1:27017
    MongoDB server version: 3.4.7
    Server has startup warnings: 
    ...  [initandlisten] 
    ...  [initandlisten] ** WARNING: Access control is not enabled for the database.
    ...  [initandlisten] **          Read and write access to data and configuration is unrestricted.
    ...  [initandlisten] 
    > show dbs
    admin  0.000GB
    local  0.000GB
    > exit
    bye
    $ 

# Shell

mongo启动的是MongoDB Shell，进入交互式模式。

## JavaScript

shell模式下，可以执行JavaScript程序。

    > 34+3
    37
    > print("Hello");
    Hello
    > function foo(x, y) {
    ... return x + y;
    ... }
    > 
    > foo(3, 5)
    8
    > 

## db

shell除了JavaScript语法，还有其他的语法，用于支持数据库的操作。

MongoDB shell启动后，会连接服务器的test数据库，并将这个服务器连接赋值给全局变量db。

- 查询当前的数据库

    > db
    test
    > 

- 切换数据库

    > use my_test_db
    switched to db my_test_db
    > db
    my_test_db
    > 

## CRUD

### Insert

    > employee = {"name":"Tom", "age":25}
    { "name" : "Tom", "age" : 25 }
    > db.employees.insert(employee)
    WriteResult({ "nInserted" : 1 })
    > db.employees.find()
    { "_id" : ObjectId("59e9914386dc8e1612f51d23"), "name" : "Tom", "age" : 25 }
    > 

### Read

    > employee = {"name":"Jerry", "age":26}
    { "name" : "Jerry", "age" : 26 }
    > db.employees.insert(employee)
    WriteResult({ "nInserted" : 1 })
    > db.employees.find()
    { "_id" : ObjectId("59e9914386dc8e1612f51d23"), "name" : "Tom", "age" : 25 }
    { "_id" : ObjectId("59e9921986dc8e1612f51d24"), "name" : "Jerry", "age" : 26 }
    > db.employees.findOne()
    { "_id" : ObjectId("59e9914386dc8e1612f51d23"), "name" : "Tom", "age" : 25 }
    > 

Key Points:

- find(): 返回多条文档；最多20条。
- findOne(): 仅返回一条。

### Update

    > jerry = {"name":"Jerry", "age":26, "hobby":"Swimming"}
    { "name" : "Jerry", "age" : 26, "hobby" : "Swimming" }
    > db.employees.find({name:"Jerry"})
    { "_id" : ObjectId("59e9921986dc8e1612f51d24"), "name" : "Jerry", "age" : 26 }
    > db.employees.update({name:"Jerry"}, jerry)
    WriteResult({ "nMatched" : 1, "nUpserted" : 0, "nModified" : 1 })
    > db.employees.find({name:"Jerry"})
    { "_id" : ObjectId("59e9921986dc8e1612f51d24"), "name" : "Jerry", "age" : 26, "hobby" : "Swimming" }
    > 

### Delete/Remove

    > db.employees.find({name:"Tom"})
    { "_id" : ObjectId("59e9914386dc8e1612f51d23"), "name" : "Tom", "age" : 25 }
    > 
    > db.employees.remove({name:"Tom"})
    WriteResult({ "nRemoved" : 1 })
    > db.employees.find({name:"Tom"})
    > 

# Connect

## host:port/db

启动shell的时候，指定数据库服务器和数据库名称。

    $ mongo localhost:27017/my_test_db
    MongoDB shell version v3.4.7
    connecting to: mongodb://localhost:27017/my_test_db
    MongoDB server version: 3.4.7
    Server has startup warnings: 
    2017-10-20T10:50:01.642+0800 I CONTROL  [initandlisten] 
    2017-10-20T10:50:01.642+0800 I CONTROL  [initandlisten] ** WARNING: Access control is not enabled for the database.
    2017-10-20T10:50:01.642+0800 I CONTROL  [initandlisten] **          Read and write access to data and configuration is unrestricted.
    2017-10-20T10:50:01.642+0800 I CONTROL  [initandlisten] 
    > db
    my_test_db
    > db.employees.find()
    { "_id" : ObjectId("59e9921986dc8e1612f51d24"), "name" : "Jerry", "age" : 26, "hobby" : "Swimming" }
    > exit
    bye
    $ 


## nodb

启动shell时不指定任何数据库。

    $ mongo --nodb
    MongoDB shell version v3.4.7
    > db
    2017-10-20T15:29:35.979+0800 E QUERY    [thread1] ReferenceError: db is not defined :
    @(shell):1:1
    > conn = new Mongo("localhost:27017")
    connection to localhost:27017
    > db = conn.getDB("my_test_db")
    my_test_db
    > db.employees.find()
    { "_id" : ObjectId("59e9921986dc8e1612f51d24"), "name" : "Jerry", "age" : 26, "hobby" : "Swimming" }
    > exit
    bye
    $ 

# help

## help

    $ mongo --nodb
    MongoDB shell version v3.4.7
    > help
        db.help()                    help on db methods
        db.mycoll.help()             help on collection methods
        sh.help()                    sharding helpers
        rs.help()                    replica set helpers
        help admin                   administrative help
        help connect                 connecting to a db help
        help keys                    key shortcuts
        help misc                    misc things to know
        help mr                      mapreduce

        show dbs                     show database names
        show collections             show collections in current database
        show users                   show users in current database
        show profile                 show most recent system.profile entries with time >= 1ms
        show logs                    show the accessible logger names
        show log [name]              prints out the last segment of log in memory, 'global' is default
        use <db_name>                set current database
        db.foo.find()                list objects in collection foo
        db.foo.find( { a : 1 } )     list objects in foo where a == 1
        it                           result of the last line evaluated; use to further iterate
        DBQuery.shellBatchSize = x   set default number of items to display on shell
        exit                         quit the mongo shell
    > exit
    bye
    $ 

## db help

    $ mongo
    MongoDB shell version v3.4.7
    connecting to: mongodb://127.0.0.1:27017
    MongoDB server version: 3.4.7
    ...
    > db.help()
    DB methods:
        ...
        db.dropDatabase()
        db.eval() - deprecated
        db.fsyncLock() flush data to disk and lock server for backups
        db.fsyncUnlock() unlocks server following a db.fsyncLock()
        db.getCollection(cname) same as db['cname'] or db.cname
        db.getCollectionInfos([filter]) - returns a list that contains the names and options of the db's collections
        db.getCollectionNames()
        ...
        db.stats()
        db.version() current version of the server
    > db.getCollectionNames()
    [ ]
    > exit
    bye
    $
    $ mongo localhost:27017/my_test_db
    MongoDB shell version v3.4.7
    connecting to: mongodb://localhost:27017/my_test_db
    MongoDB server version: 3.4.7
    ...
    > db.getCollectionNames()
    [ "employees" ]
    > exit
    bye
    $ 

## Collection Help

    $ mongo localhost:27017/my_test_db
    ...
    > db.employees.help()
    DBCollection help
        db.employees.find().help() - show DBCursor help
        ...
        db.employees.find([query],[fields]) - query is an optional query filter. fields is optional set of fields to return.
                                                      e.g. db.employees.find( {x:77} , {name:1, x:1} )
        db.employees.find(...).count()
        db.employees.find(...).limit(n)
        db.employees.find(...).skip(n)
        db.employees.find(...).sort(...)
        db.employees.findOne([query], [fields], [options], [readConcern])
        ...
    > exit
    bye
    $ 


## function help

    > db.employees.find
    function (query, fields, limit, skip, batchSize, options) {
        var cursor = new DBQuery(this._mongo,
                                 this._db,
                                 this,
                                 this._fullName,
                                 this._massageObject(query),
                                 fields,
                                 limit,
                                 skip,
                                 batchSize,
                                 options || this.getQueryOptions());
                                 
        var connObj = this.getMongo();
        var readPrefMode = connObj.getReadPrefMode();
        if (readPrefMode != null) {
            cursor.readPref(readPrefMode, connObj.getReadPrefTagSet());
        }
        
        var rc = connObj.getReadConcern();
        if (rc) {
            cursor.readConcern(rc);
        }
        
        return cursor;
    }
    > 
    
# Appendix

## id -u

获取当前用户的id:

    $ id -u
    502
    $

## Uninstall

    brew uninstall mongodb

## GUI Tools

Robo 3T (formerly Robomongo) is the free lightweight GUI for MongoDB enthusiasts.

- http://www.robomongo.org/

## Command List

    show dbs: 查看已经存在的数据库
    db: 查看当前连接的数据库
    exit

## Connection refused

在brew install mongodb之后，如果立即启动mongo，会提示失败：

    $ mongo
    MongoDB shell version v3.4.7
    connecting to: mongodb://127.0.0.1:27017
    ... Failed to connect to 127.0.0.1:27017, in(checking socket for error after poll), reason: Connection refused
    ... Error: couldn't connect to server 127.0.0.1:27017, connection attempt failed :
    connect@src/mongo/shell/mongo.js:237:13
    @(connect):1:6
    exception: connect failed

需要先启动mongod。

## Database Path

除了缺省的数据库目录，还可以使用其他的目录，只需要启动的时候使用--dbpath选项即可。

    mongo --dbpath your_dir_name


