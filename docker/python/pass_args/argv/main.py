#!/usr/bin/env python
import string
import sys

if __name__ == "__main__":
    print "args:", sys.argv
    argc = len(sys.argv)
    if argc != 3:
        print "Usage: main.py a b"
        sys.exit(1)

    a = string.atoi(sys.argv[1])
    b = string.atoi(sys.argv[2])
    print "result:", a + b
