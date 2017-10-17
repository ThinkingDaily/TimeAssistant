#!/usr/bin/env python

import tempfile

def write_temp_file(content):
    f = tempfile.NamedTemporaryFile(prefix="hello-", dir="/tmp", delete=False)
    f.write(content)
    f.close()
    return f.name 


name = write_temp_file("hello\n")
print name
