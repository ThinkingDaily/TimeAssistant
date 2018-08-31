
## Query

### Key Points

- Find(), Count(), Iter(), All()

### Code

see mgo_ex_query.go

Result:


    $ go run main.go 
    Count: 6
    count: 5
            records: &{Timestamp:968058598 Name:Spike Age:7}
            records: &{Timestamp:968058598 Name:Spike-0 Age:7}
            records: &{Timestamp:968058598 Name:Spike-1 Age:7}
            records: &{Timestamp:968058598 Name:Spike-2 Age:7}
            records: &{Timestamp:968058598 Name:Spike-3 Age:7}
    $ 

### Mongo Command

    > db.getCollection('my_collection').find()
    { "_id" : ObjectId("....a42b1"), "ns" : 968058298, "name" : "Tom", "age" : 10 }
    { "_id" : ObjectId("....a42b2"), "ns" : 968058398, "name" : "Jerry", "age" : 11 }
    { "_id" : ObjectId("....80e15"), "ns" : 968058598, "name" : "Spike", "age" : 7 }
    { "_id" : ObjectId("....822f3"), "ns" : 968058598, "name" : "Spike-0", "age" : 7 }
    { "_id" : ObjectId("....822f4"), "ns" : 968058598, "name" : "Spike-1", "age" : 7 }
    { "_id" : ObjectId("....822f5"), "ns" : 968058598, "name" : "Spike-2", "age" : 7 }
    { "_id" : ObjectId("....822f6"), "ns" : 968058598, "name" : "Spike-3", "age" : 7 }
    { "_id" : ObjectId("....822f7"), "ns" : 968058598, "name" : "Spike-4", "age" : 7 }
    > 
    > 
    > db.getCollection('my_collection').find({"age": 7}).count()
    6
    > db.getCollection('my_collection').find({"age": 7})
    { "_id" : ObjectId("....80e15"), "ns" : 968058598, "name" : "Spike", "age" : 7 }
    { "_id" : ObjectId("....822f3"), "ns" : 968058598, "name" : "Spike-0", "age" : 7 }
    { "_id" : ObjectId("....822f4"), "ns" : 968058598, "name" : "Spike-1", "age" : 7 }
    { "_id" : ObjectId("....822f5"), "ns" : 968058598, "name" : "Spike-2", "age" : 7 }
    { "_id" : ObjectId("....822f6"), "ns" : 968058598, "name" : "Spike-3", "age" : 7 }
    { "_id" : ObjectId("....822f7"), "ns" : 968058598, "name" : "Spike-4", "age" : 7 }
    > 
    > 
