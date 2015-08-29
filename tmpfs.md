Before start, it would be better to use `free` command to check the RAM left in the system.

Creat a tmpfs is rather simple, just create a folder to use as the mount point of the tmpfs, and mount it.

       cd /mnt
       sudo mkdir tmpDisk
       mount -t tmpfs -o size=1024m tmpfs /mnt/tmpDisk

To auto-mount the tmpfs each time after the reboot,	add the following mount entry into /etc/fstab:

       tmpfs /mnt/tmpDisk tmpfs nodev,nosuid,noexec,nodiratime,size=1024M 0 0

Ref:
    http://www.jamescoyle.net/knowledge/951-the-difference-between-a-tmpfs-and-ramfs-ram-disk
    http://www.jamescoyle.net/how-to/943-create-a-ram-disk-in-linux
