# 错误现象

在mongo-connector中，只会对admin数据库进行授权。但如果要读取的数据库也需要授权，则会有如下的错误提示：

      File "/usr/local/lib/python2.7/dist-packages/pymongo/helpers.py", line 145, in _check_command_response
        raise OperationFailure(msg % errmsg, code, response)
    OperationFailure: not authorized on <your_mongodb_name> to execute command { listCollections: 1, cursor: {} }

# 修改方法

一种最简单的方法，是直接修改connector.py的代码，增加对应数据库的授权：

Command:

    sudo vi /usr/local/lib/python2.7/dist-packages/mongo_connector/connector.py

Code:

    def create_authed_client(self, hosts=None, **kwargs):
        kwargs.update(self.ssl_kwargs)
        if hosts is None:
            new_uri = self.address
        else:
            new_uri = self.copy_uri_options(hosts, self.address)
        client = MongoClient(new_uri, tz_aware=self.tz_aware, **kwargs)
        if self.auth_key is not None:
            client['admin'].authenticate(self.auth_username, self.auth_key)

            # Modify here: authenticate each mongodb
            client['your_mongodb_name'].authenticate(self.auth_username, self.auth_key)
        return client
