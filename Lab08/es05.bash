#!/bin/bash

if [ $# -ne 2 ]
then
	echo "parameters error"
	exit 1
fi

iszombie=0
while :
do
	sleep $2

	echo "output is : " $(ps -el | grep $1)
	
	if [ $? -eq 0 ]
	then			
		
		processpid=$(ps -el | grep $1 | cut -d ' ' -f 4)
		echo "process pid is: " $processpid
		status=$(ps -el | grep $1 | cut -d ' ' -f 2)
		echo "process status is: " $status

		if [ $status == "Z" ]
		then 
			let iszombie=$iszombie+1
		fi

		if [ $iszombie -ge 5 ]
		then
			kill -9 $pid
			echo "process $1 killed"
			exit 0
		else
			iszombie=0
		fi
	fi

done

exit 0

	

