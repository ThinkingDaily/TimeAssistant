#!/usr/bin/python

import os
import pycurl
import StringIO

def get_text_file(filename):
	f = open(filename, "r")
	content = f.read()
	f.close()

	return content

'''
curl -v --tlsv1.2 --cert client-cert.pem
     --key client-key.plain.pem
     --cacert ca-cert.pem
     -H "Content-Type: application/json"
     --date @test.json
     https://your_ip:port/a/b/c
     -H "User-Agent: xyz/1.1.0"
'''
def curl_ex():
	filename = "test.json"
	content = get_text_file(filename)

	url = "https://your_ip:port/a/b/c"

	c = pycurl.Curl()
	header = ["Content-Type: application/json", "User-Agent: xyz/1.1.0"]
	b = StringIO.StringIO()
	c.setopt(c.WRITEFUNCTION, b.write)
	c.setopt(c.URL, url)
	c.setopt(c.VERBOSE, True)
	c.setopt(c.HTTPHEADER, header)
	c.setopt(c.SSLVERSION, c.SSLVERSION_TLSv1_2)
	c.setopt(c.SSLCERT, "client-cert.pem")
	c.setopt(c.SSLKEY, "client-key.plain.pem")
	c.setopt(c.CAINFO, "ca-cert.pem")
	c.setopt(c.POST, 1)
	c.setopt(c.POSTFIELDS, content)
	c.setopt(c.HEADER, True)

	c.perform()
	print b.getvalue()

	b.close()
	c.close()
	