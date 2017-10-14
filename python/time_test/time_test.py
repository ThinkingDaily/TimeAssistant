#!/usr/bin/env python

import datetime
import time

start_time = datetime.datetime.now()
time.sleep(5)
end_time = datetime.datetime.now()
delta = end_time - start_time
delta_gmtime = time.gmtime(delta.total_seconds())
duration_str = time.strftime("%H:%M:%S", delta_gmtime)

print "start time:", start_time
print "end time:", end_time
print "delta_gmtime:", delta_gmtime
print "duration:", duration_str 

