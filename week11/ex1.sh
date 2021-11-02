# create a file of 50MiB size filled with zeros
dd if=/dev/zero of=lofs.img bs=1M count=50

# get a name of the free loopback device, which will be used afterwards
LOOPNAME=$(losetup -f)

# setup a loopback device
sudo losetup $LOOPNAME lofs.img

# setup a file system in a file
mkfs.ext4 ./lofs.img

# create a folder "lofsdisk"
mkdir lofsdisk

# mount a device onto a created folder
sudo mount -o loop $LOOPNAME ./lofsdisk/