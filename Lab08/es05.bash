#!/bin/bash

if [ $# -ne 2 ]
then 
	echo "parameters error"
fi

count=0
while true
do

	if [ $(ps -el | grep -e ".*\<$1$" | tr -s ' ' \
		| cut -d ' ' -f 2 ) = "Z" ]
	then
		echo " equal Z"
		count=$(($count+1))
		if [ $count -eq 5 ]
		then 
			exit 0
		fi
	else
		echo "not equal z"
		count=0
	fi

done 

exit 0
