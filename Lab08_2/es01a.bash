#!/bin/bash

if [ $# -ne 3 ]
then 
	echo "parameters error"
	exit 1
fi

#find $1 -type f -exec grep -H -n  "$2 *(.*)" \{} \; > ./boh.txt
#sort -t ':' -k 1 -k 2rn ./boh.txt > $3
#rm -f ./boh.txt

grep -Hnr "$2 .*(.*)" $1 | sort -t ':' -k 1 -k 2rn > $3
exit 0
