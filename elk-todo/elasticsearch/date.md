Elasticsearch - date

# Ref

http://www.joda.org/joda-time/apidocs/org/joda/time/format/DateTimeFormat.html

# Example

    DELETE my_index 

    PUT my_index 
    {
      "mappings": {
        "user": { 
          "properties": { 
            "date":  {
              "type":   "date", 
              "format": "EEE, dd MMM yyyy HH:mm:ss zzz"
            }
          }
        }
      }
    }

    PUT my_index/user/1
    {
      "other": "some content...", 
      "date": "Thu, 11 May 2017 22:55:10 EDT"
    }
