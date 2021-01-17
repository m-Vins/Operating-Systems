#!/bin/bash

if [ $# -ne 1 ]
then
	echo "parameters error"
fi

echo "maximum lenght : $(more $1 | wc -L)"
echo "number of lines : " $(more $1 | wc -l)
