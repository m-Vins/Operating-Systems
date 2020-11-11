#!/bin/bash

echo "count the number of files/directories contained in your “home” directory (do not analyze sub-directories)"

(cd /home/vins ; ls | grep -c ".*")

echo "after downloading the file lab01e01in.txt in a directory, print the total number of strings in the file."

more file.txt | grep -c ".*"

echo "count the number of active processes in the system who are owned by the user “root” (Suggestion: use the command man ps to analyze the option -U of the command)."

ps -U root | grep -c ".*"
