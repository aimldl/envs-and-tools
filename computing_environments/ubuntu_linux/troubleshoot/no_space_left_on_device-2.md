* Draft: 2020-06-07 (Sun)
# sudo apt-get update fails!

## Situation
When I ssh to an EC2 instance, `/` is full.
```bash
$ ssh -i my_private_key.pem -L 8888:localhost:8888 -X ubuntu@12.345.678.901
Welcome to Ubuntu 18.04.4 LTS (GNU/Linux 4.15.0-1063-aws x86_64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/advantage

  System information as of Sun Jun  7 11:51:42 UTC 2020

  System load:  0.0               Processes:           111
  Usage of /:   99.8% of 7.69GB   Users logged in:     0
  Memory usage: 1%                IP address for eth0: 172.31.19.223
  Swap usage:   0%

  => / is using 99.8% of 7.69GB


 * Canonical Livepatch is available for installation.
   - Reduce system reboots and improve kernel security. Activate at:
     https://ubuntu.com/livepatch

6 packages can be updated.
0 updates are security updates.


Last login: Mon Mar 23 20:42:20 2020 from 112.169.219.12
/usr/bin/xauth:  unable to write authority file /home/ubuntu/.Xauthority-n


(base) ubuntu@ip-123-45-67-890:~$
```
`df -h` shows `/dev/xvda1      7.7G  7.7G     0 100% /`.
```bash
(base) ubuntu@ip-123-45-67-890:~$ df -h
Filesystem      Size  Used Avail Use% Mounted on
udev            7.9G     0  7.9G   0% /dev
tmpfs           1.6G  8.7M  1.6G   1% /run
/dev/xvda1      7.7G  7.7G     0 100% /
tmpfs           7.9G     0  7.9G   0% /dev/shm
tmpfs           5.0M     0  5.0M   0% /run/lock
tmpfs           7.9G     0  7.9G   0% /sys/fs/cgroup
/dev/loop1       90M   90M     0 100% /snap/core/8268
/dev/loop0       92M   92M     0 100% /snap/core/8689
/dev/loop2       18M   18M     0 100% /snap/amazon-ssm-agent/1566
/dev/loop3       18M   18M     0 100% /snap/amazon-ssm-agent/1480
tmpfs           1.6G     0  1.6G   0% /run/user/1000
(base) ubuntu@ip-123-45-67-890:~$
```

## Phenominon 1
`sudo apt update` fails to work.
```bash
ubuntu@ip-123-45-67-890:~$ sudo apt update
sudo: unable to resolve host ip-123-45-67-890: Resource temporarily unavailable
Err:1 http://ap-northeast-2.ec2.archive.ubuntu.com/ubuntu bionic InRelease
  ...
W: Some index files failed to download. They have been ignored, or old ones used instead.
ubuntu@ip-123-45-67-890:~$
```

## Phenominon 2
Tab doesn't auto-fill the rest of directory name.
```bash
(base) ubuntu@ip-123-45-67-890:~$ ls
anaconda3  downloads  github
(base) ubuntu@ip-123-45-67-890:~$ cd git-bash: cannot create temp file for here-document: No space left on device

-bash: cd: git: No such file or directory
(base) ubuntu@ip-123-45-67-890:~$ cd github
```

## Action 1
A directory with large data is deleted and the disk space is reduced to 81% `/dev/xvda1      7.7G  6.2G  1.6G  81% /`. As a matter of fact, `no space left on device` error has occured because this directory `github` is too large to fit into this EC2 instance's disk space. 

```bash
(base) ubuntu@ip-123-45-67-890:~$ cd github
(base) ubuntu@ip-123-45-67-890:~/github$ rm -rf *
(base) ubuntu@ip-123-45-67-890:~/github$ cd ..
(base) ubuntu@ip-123-45-67-890:~$ rmdir github
(base) ubuntu@ip-123-45-67-890:~$ df -h
Filesystem      Size  Used Avail Use% Mounted on
udev            7.9G     0  7.9G   0% /dev
tmpfs           1.6G  8.7M  1.6G   1% /run
/dev/xvda1      7.7G  6.2G  1.6G  81% /
tmpfs           7.9G     0  7.9G   0% /dev/shm
tmpfs           5.0M     0  5.0M   0% /run/lock
tmpfs           7.9G     0  7.9G   0% /sys/fs/cgroup
/dev/loop1       90M   90M     0 100% /snap/core/8268
/dev/loop0       92M   92M     0 100% /snap/core/8689
/dev/loop2       18M   18M     0 100% /snap/amazon-ssm-agent/1566
/dev/loop3       18M   18M     0 100% /snap/amazon-ssm-agent/1480
tmpfs           1.6G     0  1.6G   0% /run/user/1000
(base) ubuntu@ip-123-45-67-890:~$ 
```
## These attemps fail to fix the problem.
The following commands doesn't fix the problem, though.

### $ sudo apt-get update
```bash
(base) ubuntu@ip-123-45-67-890:~$ sudo apt-get update
sudo: unable to resolve host ip-123-45-67-890: Resource temporarily unavailable
  ...
W: Failed to fetch http://security.ubuntu.com/ubuntu/dists/bionic-security/InRelease  Temporary failure resolving 'security.ubuntu.com'
W: Some index files failed to download. They have been ignored, or old ones used instead.
(base) ubuntu@ip-123-45-67-890:~$
```
### $ sudo apt-get update --fix-missing
```bash
(base) ubuntu@ip-123-45-67-890:~$ sudo apt-get update --fix-missing
sudo: unable to resolve host ip-123-45-67-890: Resource temporarily unavailable
  ...
W: Some index files failed to download. They have been ignored, or old ones used instead.
(base) ubuntu@ip-123-45-67-890:~$ 
```

### $ sudo apt-get upgrade
```bash
$ sudo apt-get upgrade
Reading package lists... Done
Building dependency tree       
Reading state information... Done
Calculating upgrade... Done
0 upgraded, 0 newly installed, 0 to remove and 0 not upgraded.
$
```

### $ sudo apt autoclean
```bash
$ sudo apt autoclean
Reading package lists... Done
Building dependency tree       
Reading state information... Done
$
```

### $ sudo apt autoremove
```bash
$ sudo apt autoremove
Reading package lists... Done
Building dependency tree       
Reading state information... Done
0 upgraded, 0 newly installed, 0 to remove and 0 not upgraded.
$
```
