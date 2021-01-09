* Draft: 2020-12-08 (Tue)
# df (Disk Free)
The `df` command displays the amount of available disk space for the file systems.

``` bash
$ df -h
Filesystem      Size  Used Avail Use% Mounted on
udev            7.8G     0  7.8G   0% /dev
tmpfs           1.6G  1.9M  1.6G   1% /run
/dev/nvme0n1p5  457G  8.1G  426G   2% /
tmpfs           7.8G     0  7.8G   0% /dev/shm
tmpfs           5.0M  4.0K  5.0M   1% /run/lock
tmpfs           7.8G     0  7.8G   0% /sys/fs/cgroup
/dev/nvme0n1p1  511M  4.0K  511M   1% /boot/efi
tmpfs           1.6G  104K  1.6G   1% /run/user/1000
/dev/loop0       30M   30M     0 100% /snap/snapd/8542
/dev/loop1       55M   55M     0 100% /snap/core18/1880
/dev/loop2      256M  256M     0 100% /snap/gnome-3-34-1804/36
/dev/loop3       63M   63M     0 100% /snap/gtk-common-themes/1506
/dev/loop4       50M   50M     0 100% /snap/snap-store/467
$
```
