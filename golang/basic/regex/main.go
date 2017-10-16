package main

import (
    "regexp"
    "fmt"
)

func foo(re *regexp.Regexp, str string) {
    fmt.Print("Pattern:", re.String(), ", string:", str, " Result: ")
    if re.MatchString(str) {
        fmt.Println("Match")
    } else {
        fmt.Println("Not match")
    }
}

func main() {
    date := "Today is 2017-06-28. Done!"
    re := regexp.MustCompile(`(\d+)-(\d+)-(\d+)`)
    foo(re, date)

    re2 := regexp.MustCompile(`^(\d+)-(\d+)-(\d+)$`)
    foo(re2, date)

    date2 := "2017-06-28"
    foo(re2, date2)

    re3 := regexp.MustCompile(`^(.+)(\d+)-(\d+)-(\d+)(.+)$`)
    foo(re3, date)

    if re3.MatchString(date) {
        items := re3.FindStringSubmatch(date)
        fmt.Println("left: ", items[1])
        fmt.Println("year: ", items[2])
        fmt.Println("month: ", items[3])
        fmt.Println("day: ", items[4])
        fmt.Println("right: ", items[5])
    }
}