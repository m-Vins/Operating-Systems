#!/bin/bash

directory=$1
function=$2
outputfile=$3

echo "$(find $directory -name $function) " >$outputfile
exit 0
