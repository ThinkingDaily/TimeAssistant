elasticsearch - date & mapping

# Ref

- https://www.elastic.co/guide/en/elasticsearch/reference/current/mapping.html#field-conflicts
- https://www.elastic.co/guide/en/elasticsearch/reference/current/date.html
- https://www.elastic.co/guide/en/elasticsearch/reference/current/mapping-date-format.html

# Example

    PUT the_index
    {
      "mappings": {
        "the_type_one": {
          "properties": {
            "date": {
              "type": "date",
              "format": "yyyy-MM-dd HH:mm:ss||epoch_second"
            },
            "msg": {
              "type": "text"
            }
          }
        },
        
        "the_type_two": {
          "properties": {
            "date": {
              "type": "date",
              "format": "yyyy-MM-dd HH:mm:ss||epoch_second"
            }
          }
        }
      }
    }
