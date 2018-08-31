# Example

    require 'json'

    s = '{"name": "tom", "age": 10}'
    o = JSON.parse(s)
    print "object: #{o}"; puts
    print "name: ", o.key?("name"); puts
    print "name: ", o.key?("Name"); puts
    print "string again:", o.to_json; puts

Result:

    object: {"name"=>"tom", "age"=>10}
    name: true
    name: false
    string again:{"name":"tom","age":10}
