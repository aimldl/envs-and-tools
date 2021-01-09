* Draft: 2020-07-14 (Tue)

Google search: awk start from string

참고: [awk + print line only if the first field start with string as Linux1](https://unix.stackexchange.com/questions/72734/awk-print-line-only-if-the-first-field-start-with-string-as-linux1)

```bash
awk '$1 ~ /^Linux1/'
```

```bash
$ sudo swapoff -a
[sudo] password for k8smaster: 
$ sudo nano /etc/fstab
$ awk '{ print $0; }' /etc/fatab
awk: fatal: cannot open file `/etc/fatab' for reading (No such file or directory)
$ sudo awk '{ print $0; }' /etc/fatab
awk: fatal: cannot open file `/etc/fatab' for reading (No such file or directory)
$ awk '{ print $0; }' /etc/fstab
# /etc/fstab: static file system information.
#
# Use 'blkid' to print the universally unique identifier for a
# device; this may be used with UUID= as a more robust way to name devices
# that works even if disks are added and removed. See fstab(5).
#
# <file system> <mount point>   <type>  <options>       <dump>  <pass>
# / was on /dev/nvme0n1p1 during installation
UUID=68661764-1b74-4ecb-971a-c92568eb8282 /               ext4    errors=remount-ro 0       1
/swapfile                                 none            swap    sw              0       0
$ awk '{ if ($0 ~ ^/swapfile) { print $0; } }' /etc/fstab
awk: cmd. line:1: { if ($0 ~ ^/swapfile) { print $0; } }
awk: cmd. line:1:            ^ syntax error
awk: cmd. line:1: { if ($0 ~ ^/swapfile) { print $0; } }
awk: cmd. line:1:              ^ unterminated regexp
awk: cmd. line:1: { if ($0 ~ ^/swapfile) { print $0; } }
awk: cmd. line:1:                                       ^ unexpected newline or end of string
$ awk '{ if ($0 ~^/swapfile) { print $0; } }' /etc/fstab
awk: cmd. line:1: { if ($0 ~^/swapfile) { print $0; } }
awk: cmd. line:1:           ^ syntax error
awk: cmd. line:1: { if ($0 ~^/swapfile) { print $0; } }
awk: cmd. line:1:             ^ unterminated regexp
awk: cmd. line:1: { if ($0 ~^/swapfile) { print $0; } }
awk: cmd. line:1:                                      ^ unexpected newline or end of string
$ awk '{ if ($0 ~ /^/swapfile/ ) { print $0; } }' /etc/fstab
awk: cmd. line:1: { if ($0 ~ /^/swapfile/ ) { print $0; } }
awk: cmd. line:1:                         ^ syntax error
$ awk '{ if ($0 ~ /^UUID/ ) { print $0; } }' /etc/fstab
UUID=68661764-1b74-4ecb-971a-c92568eb8282 /               ext4    errors=remount-ro 0       1
$ awk '{ if ($0 ~ /^\/swapfile/ ) { print $0; } }' /etc/fstab 
/swapfile                                 none            swap    sw              0       0
$ awk '{ if ($0 ~ /^\/swapfile/ ) { print #$0; } }' /etc/fstab
awk: cmd. line:1: { if ($0 ~ /^\/swapfile/ ) { print #$0; } }
awk: cmd. line:1:                                    ^ syntax error
$ awk '{ if ($0 ~ /^\/swapfile/ ) { printf("%s\n",$0); } }' /etc/fstab
/swapfile                                 none            swap    sw              0       0
$ awk '{ if ($0 ~ /^\/swapfile/ ) { printf("#%s\n",$0); } }' /etc/fstab
#/swapfile                                 none            swap    sw              0       0
$ awk '{ if ($0 ~ /^\/swapfile/ ) { printf("#%s\n",$0); } } else { print $0; }' /etc/fstab
awk: cmd. line:1: { if ($0 ~ /^\/swapfile/ ) { printf("#%s\n",$0); } } else { print $0; }
awk: cmd. line:1:                                                      ^ syntax error
$ awk '{ if ($0 ~ /^\/swapfile/ ) { printf("#%s\n",$0); } else { print $0; }}' /etc/fstab
# /etc/fstab: static file system information.
#
# Use 'blkid' to print the universally unique identifier for a
# device; this may be used with UUID= as a more robust way to name devices
# that works even if disks are added and removed. See fstab(5).
#
# <file system> <mount point>   <type>  <options>       <dump>  <pass>
# / was on /dev/nvme0n1p1 during installation
UUID=68661764-1b74-4ecb-971a-c92568eb8282 /               ext4    errors=remount-ro 0       1
#/swapfile                                 none            swap    sw              0       0
$ sudo cp /etc/fstab /etc/fstab.backup
$ sudo awk '{ if ($0 ~ /^\/swapfile/ ) { printf("#%s\n",$0); } else { print $0; }}' /etc/fstab > /etc/fstab
bash: /etc/fstab: Permission denied
$ awk '{ if ($0 ~ /^\/swapfile/ ) { printf("#%s\n",$0); } else { print $0; }}' /etc/fstab > sudo /etc/fstab
$ cat /etc/fstab
# /etc/fstab: static file system information.
#
# Use 'blkid' to print the universally unique identifier for a
# device; this may be used with UUID= as a more robust way to name devices
# that works even if disks are added and removed. See fstab(5).
#
# <file system> <mount point>   <type>  <options>       <dump>  <pass>
# / was on /dev/nvme0n1p1 during installation
UUID=68661764-1b74-4ecb-971a-c92568eb8282 /               ext4    errors=remount-ro 0       1
/swapfile                                 none            swap    sw              0       0
$ awk '{ if ($0 ~ /^\/swapfile/ ) { printf("#%s\n",$0); } else { print $0; }}' /etc/fstab > fstab
$ cat fstab 
# /etc/fstab: static file system information.
#
# Use 'blkid' to print the universally unique identifier for a
# device; this may be used with UUID= as a more robust way to name devices
# that works even if disks are added and removed. See fstab(5).
#
# <file system> <mount point>   <type>  <options>       <dump>  <pass>
# / was on /dev/nvme0n1p1 during installation
UUID=68661764-1b74-4ecb-971a-c92568eb8282 /               ext4    errors=remount-ro 0       1
#/swapfile                                 none            swap    sw              0       0
$ cat fstab 
# /etc/fstab: static file system information.
#
# Use 'blkid' to print the universally unique identifier for a
# device; this may be used with UUID= as a more robust way to name devices
# that works even if disks are added and removed. See fstab(5).
#
# <file system> <mount point>   <type>  <options>       <dump>  <pass>
# / was on /dev/nvme0n1p1 during installation
UUID=68661764-1b74-4ecb-971a-c92568eb8282 /               ext4    errors=remount-ro 0       1
#/swapfile                                 none            swap    sw              0       0
$ sudo cp /etc/fstab /etc/fstab.backup
$ cat /etc/fstab.backup
# /etc/fstab: static file system information.
#
# Use 'blkid' to print the universally unique identifier for a
# device; this may be used with UUID= as a more robust way to name devices
# that works even if disks are added and removed. See fstab(5).
#
# <file system> <mount point>   <type>  <options>       <dump>  <pass>
# / was on /dev/nvme0n1p1 during installation
UUID=68661764-1b74-4ecb-971a-c92568eb8282 /               ext4    errors=remount-ro 0       1
/swapfile                                 none            swap    sw              0       0
$ sudo mv fstab /etc/fstab
$ cat /etc/fstab
# /etc/fstab: static file system information.
#
# Use 'blkid' to print the universally unique identifier for a
# device; this may be used with UUID= as a more robust way to name devices
# that works even if disks are added and removed. See fstab(5).
#
# <file system> <mount point>   <type>  <options>       <dump>  <pass>
# / was on /dev/nvme0n1p1 during installation
UUID=68661764-1b74-4ecb-971a-c92568eb8282 /               ext4    errors=remount-ro 0       1
#/swapfile                                 none            swap    sw              0       0
$ 

```

