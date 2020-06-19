

# apt / apt-get

## Install a package
```bash
$ sudo apt install -y [package_name]
```
## Remove a package (uninstall) 
```bash
$ sudo apt remove -y [package_name]
```
```bash
$ sudo apt autoremove
```
## Download a package and install from a `.deb` file


### Config files
/etc/apt/sources.list
```bash
$ grep -v '#' /etc/apt/sources.list
deb http://archive.ubuntu.com/ubuntu bionic main restricted
deb http://archive.ubuntu.com/ubuntu bionic-updates main restricted
deb http://archive.ubuntu.com/ubuntu bionic universe
deb http://archive.ubuntu.com/ubuntu bionic-updates universe
deb http://archive.ubuntu.com/ubuntu bionic multiverse
deb http://archive.ubuntu.com/ubuntu bionic-updates multiverse
deb http://archive.ubuntu.com/ubuntu bionic-backports main restricted universe multiverse
deb http://security.ubuntu.com/ubuntu bionic-security main restricted
deb http://security.ubuntu.com/ubuntu bionic-security universe
deb http://security.ubuntu.com/ubuntu bionic-security multiverse
$
```

#### Check the Ubuntu Version
```
$ cat /etc/issue
Ubuntu 18.04.3 LTS \n \l
$
```
LTS stands for Long-Term Support.

####
```bash
$ apt list --upgradable
```

```bash
$ sudo apt autoclean
Reading package lists... Done
Building dependency tree       
Reading state information... Done
$
```
```bash
$ sudo apt clean
$
```

```bash
$ sudo apt autoremove
Reading package lists... Done
Building dependency tree       
Reading state information... Done
The following packages will be REMOVED:
  libllvm8 linux-aws-headers-4.15.0-1056
0 upgraded, 0 newly installed, 2 to remove and 18 not upgraded.
After this operation, 140 MB disk space will be freed.
Do you want to continue? [Y/n] y
(Reading database ... 242367 files and directories currently installed.)
Removing libllvm8:amd64 (1:8-3~ubuntu18.04.2) ...
Removing linux-aws-headers-4.15.0-1056 (4.15.0-1056.58) ...
Processing triggers for libc-bin (2.27-3ubuntu1) ...
$
```
