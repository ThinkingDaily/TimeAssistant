#!/usr/bin/env python

def foo():
    print "foo()..."
    s1 = set([1, 3, 5, 7, 8, 10])
    s2 = set([2, 4, 6, 8, 10, 12])

    common = s1.intersection(s2)
    only_in_s1 = s1.difference(common)
    only_in_s2 = s2.difference(common)

    print "s1:", s1
    print "s2:", s2
    print "common:", common
    print "only in s1:", only_in_s1
    print "only in s2:", only_in_s2

    '''
    s1: set([1, 3, 5, 7, 8, 10])
    s2: set([2, 4, 6, 8, 10, 12])
    common: set([8, 10])
    only in s1: set([1, 3, 5, 7])
    only in s2: set([12, 2, 4, 6])
    '''

def bar():
    print "bar()..."
    s1 = set(["tom", "Tom", "Helen", "John"])
    s2 = set(["Tom", "Helen", "Jerry", "Mary"])

    common = s1.intersection(s2)
    only_in_s1 = s1.difference(common)
    only_in_s2 = s2.difference(common)

    print "s1:", s1
    print "s2:", s2
    print "common:", common
    print "only in s1:", only_in_s1
    print "only in s2:", only_in_s2

def baz():
    print "baz()..."
    s1 = set([(0, 0), (0, 1), (1, 0), (1, 1)])
    s2 = set([(-1, 0), (0, 1), (-1, 0), (1, 1), (-1, -1)])

    common = s1.intersection(s2)
    only_in_s1 = s1.difference(common)
    only_in_s2 = s2.difference(common)

    print "s1:", s1
    print "s2:", s2
    print "common:", common
    print "only in s1:", only_in_s1
    print "only in s2:", only_in_s2

foo()
bar()
baz()

