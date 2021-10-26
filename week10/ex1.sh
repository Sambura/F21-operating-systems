# remove files in case they are present (suppress output)
rm -f ex1.txt
rm -f _ex1.txt
rm -f _ex1_1.txt
rm -f _ex1_2.txt

# create file and add contents
touch _ex1.txt
echo "Some contents\n" >> _ex1.txt

# hard link two file names
ln _ex1.txt _ex1_1.txt
ln _ex1.txt _ex1_2.txt

# Output files' i-node numbers in the file
ls -i _ex1.txt >> ex1.txt
ls -i _ex1_1.txt >> ex1.txt
ls -i _ex1_2.txt >> ex1.txt