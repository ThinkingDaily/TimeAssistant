# 错误现象

如果es/nginx增加了鉴权过程，但ES的url中没有提供用户名和密码，则会如下如下错误：

      File "/usr/local/lib/python2.7/dist-packages/elasticsearch/connection/http_urllib3.py", line 129, in perform_request
        self._raise_error(response.status, raw_data)
      File "/usr/local/lib/python2.7/dist-packages/elasticsearch/connection/base.py", line 125, in _raise_error
        raise HTTP_EXCEPTIONS.get(status_code, TransportError)(status_code, error_message, additional_info)
    AuthenticationException: TransportError(401, u'<html>\r\n<head><title>401 Authorization Required</title></head>\r\n<body bgcolor="white">\r\n<center><h1>401 Authorization Required</h1></center>\r\n<hr><center>nginx</center>\r\n</body>\r\n</html>\r\n')

# 修改方法

es的url中增加用户名和密码部分，如:

    -t <es_user>:<es_password>@<es_host>:<es_port>
