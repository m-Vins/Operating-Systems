#!/bin/bash

directory=$1
function=$2
outputfile=$3

for f in $(ls -R $directory)
do

	if [ $f = $function ]
	then
		echo "matched $f"
		echo $f >>$outputfile
	fi
done

exit 0
