#!/usr/bin/env python

import datetime
import threading
import time

timer = None

def get_current_time():
    return time.strftime("%H:%M:%S", time.localtime())

# Demo here.
def is_valid_time():
    _, _, _, hour, minute, second, _, _, _ = time.localtime()
    if second < 15:
        print "Ignored."
        return False
    else:
        print "Just do it."
        return True 

def reset_timer():
    global timer

    if timer:
        timer.cancel()

    timer = threading.Timer(3, schedule)
    timer.start()

def schedule():
    print "schedule() run at", get_current_time()
    if is_valid_time():
        do_task()

    reset_timer()

def do_task():
    print "do_task() run at", get_current_time()

reset_timer()
time.sleep(20)
timer.cancel()

'''
$ chmod +x main.py
$ ./main.py 
schedule() run at 19:11:50
Just do it.
do_task() run at 19:11:50
schedule() run at 19:11:53
Just do it.
do_task() run at 19:11:53
schedule() run at 19:11:56
Just do it.
do_task() run at 19:11:56
schedule() run at 19:11:59
Just do it.
do_task() run at 19:11:59
schedule() run at 19:12:02
Ignored.
schedule() run at 19:12:05
Ignored.
$ 
'''
