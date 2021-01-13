#!/bin/bash

if [ $# -ne 2 ]
then
	echo "argument error"
fi

files=$(find $2 -user $1)


for var in $files
do
	if [ -d $var ]
	then continue
	fi

	grep -qe "***Da modificare" $var
	if [ $? -eq 0 ]
	then 
		grep -v "***Da modificare" $var > "${var}_mod"
		rm $var
	fi
 done

