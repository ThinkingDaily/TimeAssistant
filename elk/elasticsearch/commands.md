# count

    GET _count 
    curl -XGET "http://localhost:9200/_count"

# search

    GET _search
    {
      "query": {
        "match_all": {}
      }
    }

    curl -XGET "http://localhost:9200/_search" -H 'Content-Type: application/json' -d'
    {
      "query": {
        "match_all": {}
      }
    }'


# All Indices

    GET _cat/indices
    curl -XGET "http://localhost:9200/_cat/indices"

# Delete Index

    DELETE test_index 
    curl -XDELETE "http://localhost:9200/test_index"

# Find Docs in Index

    GET test_index/_search
    curl -XGET "http://localhost:9200/test_index/_search"


# Index a Doc

    POST my_index/my_type
    {
      "name": "Tom"
    }
