# grant all permissions to everyone
sudo chmod 777 lofsdisk

# create two files on the LOFS
echo "Kirill" > lofsdisk/file1
echo "Samburskiy" > lofsdisk/file2

# compile a program and place it onto LOFS
gcc ./ex2.c -w -o lofsdisk/ex2.out

# bind some system binaries to the LOFS
mkdir ./lofsdisk/bin
mkdir ./lofsdisk/usr
mkdir ./lofsdisk/lib
mkdir ./lofsdisk/lib64
sudo mount --bind /bin ./lofsdisk/bin
sudo mount --bind /usr ./lofsdisk/usr
sudo mount --bind /lib ./lofsdisk/lib
sudo mount --bind /lib64 ./lofsdisk/lib64

# run the program and chroot it to lofsdisk
sudo chroot ./lofsdisk/ ./ex2.out > ex2.txt

# add a separator in a file
echo "------------------" >> ex2.txt

# run the program again, but without chrooting it
./lofsdisk/ex2.out >> ex2.txt

# unbind previously binded directories
sudo umount ./lofsdisk/bin
sudo umount ./lofsdisk/usr
sudo umount ./lofsdisk/lib
sudo umount ./lofsdisk/lib64
rm -r -f ./lofsdisk/bin
rm -r -f ./lofsdisk/usr
rm -r -f ./lofsdisk/lib
rm -r -f ./lofsdisk/lib64