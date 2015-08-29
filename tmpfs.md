Before start, it would be better to use `free` command to check the RAM left in the system.

Creat a tmpfs is rather simple, just create a folder to use as the mount point of the tmpfs, and mount it.

       cd /mnt
       sudo mkdir tmpDisk
       mount -t tmpfs -o size=1024m tmpfs /mnt/tmpDisk

To auto-mount the tmpfs each time after the reboot,	add the following mount entry into /etc/fstab:

       tmpfs /mnt/tmpDisk tmpfs nodev,nosuid,noexec,nodiratime,size=1024M 0 0

Tmpfs 的用法，举例来说是像： `mount -t tmpfs -o size=1G,nr_inodes=10k,mode=0700 tmpfs /mnt/tmpDish` 这样就会使用 1 GiB 的置换空间，里头有 10240 inodes 且规定是在 /space 目录下存取。这个档案系统的大小是可以随时调整的，像是再追加一个指令如：`mount -o remount,size=2G /mnt/tmpDish`。

如果要开机启用tmpfs，那就在fstab里面加个参数： `tmpfs /media/tmpDish tmpfs size=2G,defaults,noatime,mode=1777 0 0` 其中 2G 是固定大小。要注记一点，如果/tmp 有安全上的顾虑的话，最好追加 sticky bit 上来，就是权限应该被设作 `mode=1777`，而不是 `mode=0777` 或 `mode=777`。

Ref:
1. http://www.jamescoyle.net/knowledge/951-the-difference-between-a-tmpfs-and-ramfs-ram-disk
1. http://www.jamescoyle.net/how-to/943-create-a-ram-disk-in-linux
1. https://zh.wikipedia.org/wiki/Tmpfs
