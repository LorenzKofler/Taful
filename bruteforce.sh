#!/bin/sh
curr_input=`pwgen 32 1`

( until LD_LIBRARY_PATH=:./ ./main $curr_input
do
    curr_input=`pwgen 32 1`
done
echo "Found Key: $curr_input" ) 2> /dev/null
