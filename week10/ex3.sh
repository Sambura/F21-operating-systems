#!/usr/bin/env bash

# (create) and replace contents with string "Some contents"
echo "Some contents" > _ex3.txt
# remove execution permission for all users
chmod -v ugo-x _ex3.txt > ex3.txt
# grant all permissions to the owner and other users
chmod -v uo+rwx _ex3.txt >> ex3.txt
# make group permissions equal to user permissions
chmod -v g=o _ex3.txt >> ex3.txt

# output the answers to the questions to ex3.txt
echo "\n660 means permission 6 for owner and for the group, for other users - the permission is 0. permission 6 is 2 + 4 => 110 => RWx (only read and write is permitted). Permission 0 is obviously 000 => rwx (no permissions)" >> ex3.txt
echo "\n775 means permission 7 for owner and for the group, for other users - the permission is 5. permission 7 is 4 + 2 + 1 => 111 => RWX (everything is permitted). Permission 5 is 4 + 1 => RwX (no write permission)" >> ex3.txt
echo "\n777 means permission 7 for all users, that is, any user has full set of permissions" >> ex3.txt
