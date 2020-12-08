#!/bin/bash

if [ $# ==  "1" ] 
then
	fileinput=$1
else
	read fileinput
fi

n=$(more $fileinput  | wc -l)

echo "the number of lines is : $n"

longest=0
for ((var = 1 ; var <= $n ; var++ ))
do
	echo "line number $var :"
	tmp=$(sed -n ${var}p $fileinput | wc -m)
	echo $tmp

	if [ $tmp -gt $longest ]
	then
		echo "longest has changed with $tmp"
		longest=$tmp
	fi	
done

echo "the longest line has $longest characters"

exit 0
