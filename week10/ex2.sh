#!/usr/bin/env bash

# remove files and folders in case they already exist (suppress the output)
rm -r -f week01
rm -r -f week10
rm -f ex2.txt

# create two folders
mkdir week01
mkdir week10

# create file.txt and put some contents in
echo "Some contents" > week01/file.txt

# hard link file to name _ex2.txt in week10 folder
ln week01/file.txt week10/_ex2.txt

# getting i-node number of file.txt
INN=$(ls -i week01/file.txt | cut -d " " -f1)

# find and delete all links to the file.txt in week01 folder
find week01 -inum $INN >> ex2.txt
find week01 -inum $INN -exec rm {} \; >> ex2.txt

# note: in my case the second find deletes _ex2.txt, but does not produce any output 