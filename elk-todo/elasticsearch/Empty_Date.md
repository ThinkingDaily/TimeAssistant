Elasticsearch - Empty Date

# 问题

## 语句

    DELETE my_index 

    PUT my_index/type_one/1
    {
      "other": "one", 
      "date": "2017/11/03"
    }

    PUT my_index/type_one/2
    {
      "other": "two", 
      "date": "2017/11/04"
    }

    PUT my_index/type_one/3
    {
      "other": "three", 
      "date": ""
    }

## 执行结果

    {
      "_index": "my_index",
      "_type": "type_one",
      "_id": "1",
      "_version": 1,
      "result": "created",
      "_shards": {
        "total": 2,
        "successful": 1,
        "failed": 0
      },
      "created": true
    }

    {
      "_index": "my_index",
      "_type": "type_one",
      "_id": "2",
      "_version": 1,
      "result": "created",
      "_shards": {
        "total": 2,
        "successful": 1,
        "failed": 0
      },
      "created": true
    }

    {
      "error": {
        "root_cause": [
          {
            "type": "mapper_parsing_exception",
            "reason": "failed to parse [date]"
          }
        ],
        "type": "mapper_parsing_exception",
        "reason": "failed to parse [date]",
        "caused_by": {
          "type": "illegal_argument_exception",
          "reason": "Invalid format: \"\""
        }
      },
      "status": 400
    }

## 分析

前两个doc成功索引，但第三个失败。因为在前两个的时候，Elasticsearch自动把date字段当成了date类型；而索引第三个文档的时候，无法从空字符串解析出一个date出来。所以，抛出异常。

# 解决方法一 - mapping text

一种简单的方法就是把date字段定义成text类型。

## 命令

    DELETE my_index 

    PUT my_index 
    {
      "mappings": {
        "type_one": { 
          "properties": { 
            "date":  {
              "type":   "text"
            }
          }
        }
      }
    }

    PUT my_index/type_one/_bulk
    { "index" : {"_id": "1"} }
    {"other": "one", "date": "2017/11/03"}
    { "index" : {"_id": "2"} }
    {"other": "two", "date": "2017/11/04"}
    { "index" : {"_id": "3"} }
    {"other": "three", "date": ""}

    GET my_index/_search 

## 执行结果

    {
      "took": 249,
      "errors": false,
      "items": [
        {
          "index": {
            "_index": "my_index",
            "_type": "type_one",
            "_id": "1",
            "_version": 1,
            "result": "created",
            "_shards": {
              "total": 2,
              "successful": 1,
              "failed": 0
            },
            "created": true,
            "status": 201
          }
        },
        {
          "index": {
            "_index": "my_index",
            "_type": "type_one",
            "_id": "2",
            "_version": 1,
            "result": "created",
            "_shards": {
              "total": 2,
              "successful": 1,
              "failed": 0
            },
            "created": true,
            "status": 201
          }
        },
        {
          "index": {
            "_index": "my_index",
            "_type": "type_one",
            "_id": "3",
            "_version": 1,
            "result": "created",
            "_shards": {
              "total": 2,
              "successful": 1,
              "failed": 0
            },
            "created": true,
            "status": 201
          }
        }
      ]
    }

    {
      "took": 1,
      "timed_out": false,
      "_shards": {
        "total": 5,
        "successful": 5,
        "failed": 0
      },
      "hits": {
        "total": 3,
        "max_score": 1,
        "hits": [
          {
            "_index": "my_index",
            "_type": "type_one",
            "_id": "2",
            "_score": 1,
            "_source": {
              "other": "two",
              "date": "2017/11/04"
            }
          },
          {
            "_index": "my_index",
            "_type": "type_one",
            "_id": "1",
            "_score": 1,
            "_source": {
              "other": "one",
              "date": "2017/11/03"
            }
          },
          {
            "_index": "my_index",
            "_type": "type_one",
            "_id": "3",
            "_score": 1,
            "_source": {
              "other": "three",
              "date": ""
            }
          }
        ]
      }
    }

# 解决方法二 - 剔除空值字段

这种方法是在索引的时候，把值为空的字段剔除掉。

## 命令

    DELETE my_index 

    PUT my_index/type_one/_bulk
    { "index" : {"_id": "1"} }
    {"other": "one", "date": "2017/11/03"}
    { "index" : {"_id": "2"} }
    {"other": "two", "date": "2017/11/04"}
    { "index" : {"_id": "3"} }
    {"other": "three"}

    GET my_index/_search 

## 执行结果

    {
      "took": 394,
      "errors": false,
      "items": [
        {
          "index": {
            "_index": "my_index",
            "_type": "type_one",
            "_id": "1",
            "_version": 1,
            "result": "created",
            "_shards": {
              "total": 2,
              "successful": 1,
              "failed": 0
            },
            "created": true,
            "status": 201
          }
        },
        {
          "index": {
            "_index": "my_index",
            "_type": "type_one",
            "_id": "2",
            "_version": 1,
            "result": "created",
            "_shards": {
              "total": 2,
              "successful": 1,
              "failed": 0
            },
            "created": true,
            "status": 201
          }
        },
        {
          "index": {
            "_index": "my_index",
            "_type": "type_one",
            "_id": "3",
            "_version": 1,
            "result": "created",
            "_shards": {
              "total": 2,
              "successful": 1,
              "failed": 0
            },
            "created": true,
            "status": 201
          }
        }
      ]
    }


    {
      "took": 0,
      "timed_out": false,
      "_shards": {
        "total": 5,
        "successful": 5,
        "failed": 0
      },
      "hits": {
        "total": 3,
        "max_score": 1,
        "hits": [
          {
            "_index": "my_index",
            "_type": "type_one",
            "_id": "2",
            "_score": 1,
            "_source": {
              "other": "two",
              "date": "2017/11/04"
            }
          },
          {
            "_index": "my_index",
            "_type": "type_one",
            "_id": "1",
            "_score": 1,
            "_source": {
              "other": "one",
              "date": "2017/11/03"
            }
          },
          {
            "_index": "my_index",
            "_type": "type_one",
            "_id": "3",
            "_score": 1,
            "_source": {
              "other": "three"
            }
          }
        ]
      }
    }

# 解决方法三 - ignore_malformed

## 命令

    DELETE my_index 

    PUT my_index 
    {
      "mappings": {
        "type_one": { 
          "properties": { 
            "date":  {
              "type":   "date",
              "format": "yyyy/MM/dd",
              "ignore_malformed": true
            }
          }
        }
      }
    }

    PUT my_index/type_one/_bulk
    { "index" : {"_id": "1"} }
    {"other": "one", "date": "2017/11/03"}
    { "index" : {"_id": "2"} }
    {"other": "two", "date": "2017/11/04"}
    { "index" : {"_id": "3"} }
    {"other": "three", "date": ""}

    GET my_index/_search 

## 执行结果

最后一步查询结果：

    {
      "took": 0,
      "timed_out": false,
      "_shards": {
        "total": 5,
        "successful": 5,
        "failed": 0
      },
      "hits": {
        "total": 3,
        "max_score": 1,
        "hits": [
          {
            "_index": "my_index",
            "_type": "type_one",
            "_id": "2",
            "_score": 1,
            "_source": {
              "other": "two",
              "date": "2017/11/04"
            }
          },
          {
            "_index": "my_index",
            "_type": "type_one",
            "_id": "1",
            "_score": 1,
            "_source": {
              "other": "one",
              "date": "2017/11/03"
            }
          },
          {
            "_index": "my_index",
            "_type": "type_one",
            "_id": "3",
            "_score": 1,
            "_source": {
              "other": "three",
              "date": ""
            }
          }
        ]
      }
    }
