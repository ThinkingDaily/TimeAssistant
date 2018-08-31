package main

import (
    "github.com/globalsign/mgo"
    "github.com/globalsign/mgo/bson"
    "fmt"
    "strconv"
)

type passenger struct {
    Timestamp int `bson:"ns,omitempty"`
    Name string `bson:"name"`
    Age int `bson:"age"`
}

func main() {
    url := "my_user_name:my_db_pwd@127.0.0.1:27017/my_db"

    database := "my_db"
    collection := "my_collection"

    session, err := mgo.Dial(url)
    if err != nil {
        fmt.Println("Dial failed:", err)
        return
    }

    defer session.Close()
    records := []*passenger{}
    session.SetMode(mgo.Monotonic, true)
    c := session.DB(database).C(collection)

    count, err := c.Find(bson.M{"age": 7}).Count()
    if err != nil {
        fmt.Println("Count failed:", err)
    } else {
        fmt.Println("Count:", count)
    }

    iter := c.Find(bson.M{"age": 7}).Limit(5).Iter()
    err = iter.All(&records)

    if err != nil && err != mgo.ErrNotFound {
        fmt.Println("Find failed:", err)
        return
    }

    count = len(records)
    fmt.Println("count:", count)
    for _, r := range records {
        fmt.Printf("\trecords: %+v\n", r)
    }
}
