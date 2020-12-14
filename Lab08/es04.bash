#!/bin/bash

if [ $# ==  "1" ] 
then
	file=$1
else
	read file
fi
echo "file name is: " $file
l=0
for word in $(cat $file)
do
	echo "current word is: " $word
	flag=0
	for(( i=0;i<${#words_array[*]};i++))
	do
		if [ "${words_array[$i]}" = "$word" ]
		then 
			nwords[$i]=$((nwords[$i]+1))
			echo "the word is already present in the vector"
			flag=1
		fi
	done

	if [ $flag -eq 0 ]
	then
		words_array[$l]=$word
		nwords[$l]=1
		let l=$(($l+1))
	fi
done

for((i=0;i<${#words_array[*]};i++))
do 
	echo ${words_array[$i]} ":" ${nwords[$i]}
done
exit 0
