#!/bin/bash

if [ $# ==  "1" ] 
then
	dir=$1
else
	read dir
fi

list=$(ls  $dir)
cd $dir
for tmp in $list
do 
	up=$(echo $tmp | tr [:upper:] [:lower:])
	mv $tmp $up
done 
exit 0
