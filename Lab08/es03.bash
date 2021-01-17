#!/bin/bash

if [ $# -ne 1 ]
then
	echo "parameters error"
fi

for x in $(ls $1)
do
	mv $1/$x $1/$(echo $x | tr [:upper:] [:lower:])
done	
