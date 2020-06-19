##### No_space_left_on_device.md

# Problem: "No space left on device" Error
My AWS EC2 instance on Ubuntu 18.04 suffers from the following errors.
```bash
$ cd a-bash: cannot create temp file for here-document: No space left on device
```
Increasing the Volume Size Is Not the Solution. The disk volume is increaed to 1 TB. However the disk space is filled up soon after and the error occured again!

## Phenomenon: Root Directory / is 100%
The df command reveals the root directory or / is fully occupied.
```bash
/dev/nvme0n1p1  970G  970G     0 100% /
```
In details, 
```bash
$ df -h
Filesystem      Size  Used Avail Use% Mounted on
udev            7.6G     0  7.6G   0% /dev
tmpfs           1.6G  146M  1.4G  10% /run
/dev/nvme0n1p1  970G  970G     0 100% /
tmpfs           7.7G     0  7.7G   0% /dev/shm
tmpfs           5.0M     0  5.0M   0% /run/lock
tmpfs           7.7G     0  7.7G   0% /sys/fs/cgroup
/dev/loop0       77M   77M     0 100% /snap/xmind/3
/dev/loop2       18M   18M     0 100% /snap/amazon-ssm-agent/1480
/dev/loop3       77M   77M     0 100% /snap/xmind/5
/dev/loop1       55M   55M     0 100% /snap/core18/1650
/dev/loop6       45M   45M     0 100% /snap/gtk-common-themes/1353
/dev/loop4       92M   92M     0 100% /snap/core/8592
/dev/loop5      161M  161M     0 100% /snap/gnome-3-28-1804/116
/dev/loop7       18M   18M     0 100% /snap/amazon-ssm-agent/1455
/dev/loop8       55M   55M     0 100% /snap/core18/1668
/dev/loop9       90M   90M     0 100% /snap/core/8268
/dev/loop10      45M   45M     0 100% /snap/gtk-common-themes/1440
/dev/loop11     157M  157M     0 100% /snap/gnome-3-28-1804/110
tmpfs           1.6G     0  1.6G   0% /run/user/1000
```
Google search: aws ec2 root is 100%

The following command is supposed to sort out the largest files. But the du command fails to identify oversize files.
```bash
$ sudo du -x -h | sort -n | tail
sudo: unable to resolve host ip-10-0-2-222: Resource temporarily unavailable
1019M	./aimldl/python3/.git/objects/bb
  ...
1022M	./aimldl/python3/.git/objects/f6
1022M	./aimldl/python3/.git/objects/ff
```
### Hint: Check the space with "-printf '%12s %p\n' 2>/dev/null|awk '{if($1>999999999)print $0;}"
Instead the following command successfully reveals the oversize files. The command is posted by Swat at [xvda1 is 100% full, What is it? how to fix?](https://serverfault.com/questions/330532/xvda1-is-100-full-what-is-it-how-to-fix). Thanks, Swat!
```bash
$ sudo find / -type f -printf '%12s %p\n' 2>/dev/null|awk '{if($1>999999999)print $0;}'
  1783930916 /home/ubuntu/aimldl/private/.git/objects/pack/pack-96ec78f3e5c2cdfb0fb67d27fb23c15e4e8c77fe.pack
  ...
 143760175104 /home/ubuntu/aimldl/python3/.git/objects/pack/tmp_pack_2fS9GK
154768473324 /home/ubuntu/aimldl/python3/.git/objects/pack/pack-b238f50e44e07f4cb425c0c7629e106c9e4b46d4.pack
140737477885952 /proc/kcore
$
```
### Solution1: Remove the git Command's Temporary File
Removing an oversize file frees up some space. Baam! From 1000 to 87%. 
```bash
$ rm /home/ubuntu/aimldl/python3/.git/objects/pack/tmp_pack_2fS9GK
rm: remove write-protected regular file '/home/ubuntu/aimldl/python3/.git/objects/pack/tmp_pack_2fS9GK'? y
$ df -h
Filesystem      Size  Used Avail Use% Mounted on
  ...
/dev/nvme0n1p1  970G  836G  134G  87% /
  ...
$
```
Removing the rest of git's temp files frees up some extra space.
```bash
$ rm /home/ubuntu/aimldl/python3/.git/objects/pack/pack-b238f50e44e07f4cb425c0c7629e106c9e4b46d4.pack
rm: remove write-protected regular file '/home/ubuntu/aimldl/python3/.git/objects/pack/pack-b238f50e44e07f4cb425c0c7629e106c9e4b46d4.pack'? y
(base) ubuntu@ip-10-0-2-222:~$ df -h
Filesystem      Size  Used Avail Use% Mounted on
  ...
/dev/nvme0n1p1  970G  690G  280G  72% /
  ...
$
```
In my case, the next one didn't help much.
```bash
$ rm /home/ubuntu/aimldl/private/.git/objects/pack/pack-96ec78f3e5c2cdfb0fb67d27fb23c15e4e8c77fe.pack
rm: remove write-protected regular file '/home/ubuntu/aimldl/private/.git/objects/pack/pack-96ec78f3e5c2cdfb0fb67d27fb23c15e4e8c77fe.pack'? y
$ df -h
Filesystem      Size  Used Avail Use% Mounted on
  ...
/dev/nvme0n1p1  970G  835G  136G  87% /
  ...
$
```
Unfortunately, /proc/kcore cannot be deleted. I may use sudo, but wait. "/proc/kcore" is 128 TB (terabyte) while the disk volume size is 1TB. What's going on with this?
```bash
$ rm /proc/kcore
rm: remove write-protected regular file '/proc/kcore'? y
rm: cannot remove '/proc/kcore': Permission denied
$
```
Later, I found "sudo rm" cannot delete the file (as a matter of fact).
```bash
$ sudo rm /proc/kcore
sudo: unable to resolve host ip-10-0-2-222: Resource temporarily unavailable
rm: cannot remove '/proc/kcore': Operation not permitted
$
```
### /proc/kcore is 128 TB!
Google search: 140737477885952 in terabyte

[Impossibly large file](https://forums.opensuse.org/showthread.php/532456-Impossibly-large-file)
* A 128 terabyte (140,737,477,885,952 bytes) file. On a volume that has about 300GB free.  ... An attempt to remove it did not succeed: "Read-only file system".
* It represents the physical memory of your system - it's there because dhcp runs in chroot. You should never backup proc directories as those are virtual and are re-created on every system startup (as well as /dev, /sys, /tmp, /run and a few other locations).

Google search: what is "/proc/kcore"?
[/proc kcore file is huge](https://stackoverflow.com/questions/21170795/proc-kcore-file-is-huge)
* My question is, is it safe to delete the /proc/kcore file? Or is there a solution on getting it to an normal size. The filesize of /proc/kcore is 140.737.486.266.368 bytes

