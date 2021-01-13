#!/bin/bash

if [ $# -ne 1 ]
then
	echo "argument error"
fi

echo "argument is $1"

if [ ! -d "logs" ]
then 
	mkdir logs
fi

while read line
do
	echo $line
	echo $line | grep -qe "#"
	if [ $? -eq 0 ]
	then
		name=$(echo $line | grep -v "#" )
		continue
	fi
	
	echo $line | grep -qe "END" 
	if [ $? -eq 0 ]
	then
		gcc -Wall -o $name $files > "./logs/${name}.log
		name=""
		files=""
		continue
	fi
	files=${files}" "$line
 
done < $1
exit 0
