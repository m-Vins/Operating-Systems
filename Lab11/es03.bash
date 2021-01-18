#!/bin/bash

if [ $# -ne 2 ]
then
	echo " parameters error"
fi

for var in $(find $2 -user $1 -type f)
do
	grep -e "\*\*\*Da modificare.*" $var

	if [ $? -eq 0 ]
	then
		grep -ve "\*\*\*Da modificare.*" > ${var}_mod
		rm $var
	fi
done
exit 0

