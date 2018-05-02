#!/usr/bin/env python

import sys
import getopt 

def foo(argv):
    options = 'a:bcd:'
    long_options = ['b_option=', 'a_option', 'c_option', 'option_d=']
        
    try:
        opts, args = getopt.getopt(argv, options, long_options)
        for option, value in opts:
            if option in ('-a', '--a_option'):
                print "option a:", value
            elif option in ('-b', '--b_option'):
                print "option b"
            elif option in ('-c', '--c_option'):
                print "option c"
            elif option in ('-d', '--option_d'):
                print "option d:", value
            else:
                print "Unknown option:", option
    except getopt.GetoptError as err:
        print "usage:..."
        print "**", str(err), "**"
        sys.exit(1)

    print "args:", args 

if __name__ == "__main__":
    foo(sys.argv[1:])

