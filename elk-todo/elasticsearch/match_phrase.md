elasticsearch - match_phrase

# 增加3个document

不提前创建index、mapping等，直接put。

    PUT /index_test/type_test/id_1?pretty
    {
       "name": "abcde",
       "age": 10
    }

    PUT /index_test/type_test/id_2?pretty
    {
       "name": "abcdefg",
       "age": 10
    }

    PUT /index_test/type_test/id_5?pretty
    {
       "name": "abcde fg",
       "age": 10
    }

# 查询

希望查询name等于abcde，且age等于10的文档。不希望得到name为abcdefg以及(abcde fg)这两个文档。

    GET /index_test/type_test/_search?pretty
    {"query": {"bool": {"must": [{"match_phrase": {"name": "abcde"}}, {"match_phrase": {"age": 10}}]}}}


    {
      "took": 1,
      "timed_out": false,
      "_shards": {
        "total": 5,
        "successful": 5,
        "failed": 0
      },
      "hits": {
        "total": 2,
        "max_score": 1.2111092,
        "hits": [
          {
            "_index": "index_test",
            "_type": "type_test",
            "_id": "id_1",
            "_score": 1.2111092,
            "_source": {
              "name": "abcde",
              "age": 10
            }
          },
          {
            "_index": "index_test",
            "_type": "type_test",
            "_id": "id_5",
            "_score": 1.1414342,
            "_source": {
              "name": "abcde fg",
              "age": 10
            }
          }
        ]
      }
    }

实际返回了两个匹配结果。特别地，包括了{"name": "abcde fg"}，但不包括{"name": "abcdefg"}。
