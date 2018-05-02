#!/usr/bin/env python

dict = {'item1': "value 1", 'item2': 'value 2'}
value1 = dict.pop('item1', None)
value3 = dict.pop('item3', None)
value4 = dict.pop('item4', "default value")
print "dict:", dict
value2 = dict.pop('item2', None)
print "dict:", dict
print 'value1:', value1
print 'value2:', value2
print 'value3:', value3
print 'value4:', value4
