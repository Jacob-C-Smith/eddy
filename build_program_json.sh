#!/bin/bash

#########################
# Build an EDDY program #
#                       #
# @author Jacob Smith   #
# @file test.sh         #
# @date 3/5/2024        #
#########################

# Argumenet check
case $# in 
1);;
*) echo "Usage: "`basename $0`" <file.eds> "; exit 1;;
esac

printf "{"
printf "\"name\" : \"Product of sums\","
printf "\"source\" : \""
echo -n "$(cat $1 | base64 -w 0)"
printf "\","
printf "\"input\" :"
printf "["
printf "{ \"name\" : \"A\", \"type\" : \"i32\" },"
printf "{ \"name\" : \"B\", \"type\" : \"i32\" },"
printf "{ \"name\" : \"C\", \"type\" : \"i32\" },"
printf "{ \"name\" : \"D\", \"type\" : \"i32\" }"
printf "],"
printf "\"output\" :" 
printf "["
printf "{ \"name\" : \"O\", \"type\" : \"i64\" }"
printf "]"
printf "}"

