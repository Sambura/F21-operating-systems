#!/bin/sh

# if we will run two instances of this script, 
# we will observe them in the race condition immediately

# in my case, all numbers in the file started to repeat, e.g.
# 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, and so on

touch ~/file.txt
echo 0 > ~/file.txt
while :
do
# the critical region - read and write operations here
  echo $(($( tail -n 1 file.txt )+1)) >> ~/file.txt
# the end of the critical region
done