#!/bin/bash

:<<!
for var in list
do 
	commands
done
!

for value in one two three four
do 
    echo $value
done

:<<!
Result:
$ ./test1.sh 
one
two
three
four
$ 
!