

## Problem
The disk space filled up with Anaconda and a part of pytorch.
```bash
$ bash Anaconda3-2019.10-Linux-x86_64.sh
$ source .bashrc
$ python
$ conda create -n pytorch python=3 anaconda
  ...
CondaError: Failed to write to /home/ubuntu/anaconda3/pkgs/pygments-2.6.1-py_0.conda
  errno: 28

(base) ubuntu@ip-x-w-y-z:~$ df -h
Filesystem      Size  Used Avail Use% Mounted on
udev            2.0G     0  2.0G   0% /dev
tmpfs           395M  760K  394M   1% /run
/dev/xvda1      7.7G  7.7G     0 100% /
tmpfs           2.0G     0  2.0G   0% /dev/shm
tmpfs           5.0M     0  5.0M   0% /run/lock
tmpfs           2.0G     0  2.0G   0% /sys/fs/cgroup
/dev/loop0       92M   92M     0 100% /snap/core/8689
/dev/loop1       18M   18M     0 100% /snap/amazon-ssm-agent/1480
/dev/loop2       90M   90M     0 100% /snap/core/8268
/dev/loop3       18M   18M     0 100% /snap/amazon-ssm-agent/1566
tmpfs           395M     0  395M   0% /run/user/1000
(base) ubuntu@ip-x-w-y-z:~$ 
```
