#!/bin/bash

while read line 
do
	info=$(ps -ef | tr -s ' ' | grep -e "^.*\> \<$line")
	if [ $? -eq 0 ]
	then

		echo "process $line is running in the system"
		echo "the owner is : $(echo $info | cut -d " "  -f 1) "
		echo "pids of the childrens :$(ps -ef | tr -s ' ' |\
		       	cut -d " " -f 2,3 | \
			grep -e "$line$" | cut -d " " -f 1 )"


	fi

done < virus.dat
