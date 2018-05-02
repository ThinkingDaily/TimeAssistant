#!/usr/bin/env python

def foo(a, b=1, c=2):
    print "a=%d, b=%d, c=%d" % (a, b, c)

foo(100) # a=100, b=1, c=2
foo(100, 200, 300) # a=100, b=200, c=300
foo(100, b=300) # a=100, b=300, c=2
foo(100, c=200) # a=100, b=1, c=200
