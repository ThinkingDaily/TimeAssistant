#coding=gbk

'''
Ref: http://cn.python-requests.org/zh_CN/latest/user/quickstart.html
'''

import requests

r = requests.get('https://github.com/timeline.json')

#payload = {'key1': 'value1', 'key2': 'value2'}
#payload = {'key1': 'value1', 'key2': ['value2', 'value3']}
#r = requests.get('http://httpbin.org/get', params=payload)

print "Headers:", r.headers
print 'Status Code:', r.status_code 
if r.status_code == requests.codes.ok:
	print 'OK'
print 'URL:', r.url 
print 'Encoding:', r.encoding 
print 'Text:', r.text 
print 'Content:', r.content 
print 'JSON:', r.json() 
