#!/bin/bash

#it doesn't work

if [ $# -ne 3 ]
then 
	echo "parameters error"
	exit 1
fi

for x in $(find $1 -type f )
do
	echo $x
	grep -H -n "$2 *(.*)" $x | sort -r -t ':' -k 1 -k 2n > $3

done
exit 0
