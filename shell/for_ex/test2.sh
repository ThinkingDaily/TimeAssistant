#!/bin/bash

values="one two three four"

for value in $values
do 
    echo $value
done

:<<!
Result:
$ ./test2.sh 
one
two
three
four
$ 
!