#!/bin/bash

if [ $# -ne 1 ]
then 
	echo "parameters error"
fi
count=0
for line in $(more $1)
do
	flag=0
	for((i=0;i<$count;i++))
	do
		if [ $line = ${vect[$i]} ]
		then
			occorrences[$i]=$((${occorrences[$i]}+1))
			flag=1
		fi
	done
	if [ $flag -ne 1 ]
	then
		vect[$count]=$line
		occorrences[$count]=1
		let count=$count+1
	fi

done

for(( i=0;i<$count;i++))
do 
	echo ${vect[$i]} ":" ${occorrences[$i]}
done
exit 0
