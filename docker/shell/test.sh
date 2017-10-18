#!/bin/bash

g_call_python_script=0

function f_usage()
{
    echo "./test.sh [-p] [-h]"
    echo "    -p run python script"
    echo "    -h display this usage"
    echo 
}

function f_python_script()
{
    echo "Calling python script ..."
    program="python ./main.py"
    echo "$program"
    $program 

    if [ $? -ne 0 ]; then
        echo "Python script run failed"
        exit 1
    else
        echo "Python script run  success"
    fi
}

echo "Parsing options..."

while getopts "p" arg
do 
    case $arg in 
        p)
            g_call_python_script=1
            ;;

        ?)
            echo "Unknown argument"
            f_usage 
            exit 1
            ;;

    esac
done 

if [ $g_call_python_script -eq 1 ]; then 
    f_python_script
fi 

echo 'All Done!!!'
