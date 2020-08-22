##### aimldl/computing_environments/ubuntu_linux/how_to/check_the_linux_version.md
* Draft: 2020-0312 (Thu)
# How to Check the Linux Version (on Command Line)
This page summarizes the commands from a well-written article [How to Check your Ubuntu Version](https://linuxize.com/post/how-to-check-your-ubuntu-version/).
For details, please read the article.

## How to Check Ubuntu Version from the Command Line
```bash
$ lsb_release -a
Description:    Ubuntu 18.04 LTS
$
```
The command tested on
* Amazon EC2 instance: Ubuntu Linux AMI

The command fails on
* Docker container: Ubuntu Linux
```bash
user@0ea530773393:~$ lsb_release -a
bash: lsb_release: command not found
user@0ea530773393:~$ 
```
## Check Ubuntu version using the /etc/issue file
```bash
$ cat /etc/issue
Ubuntu 18.04 LTS \n \l
$
```
Command tested on
* Docker container: Ubuntu Linux

## Check Ubuntu version using the /etc/os-release file
```bash
$ cat /etc/os-release
NAME="Ubuntu"
VERSION="18.04.4 LTS (Bionic Beaver)"
ID=ubuntu
ID_LIKE=debian
PRETTY_NAME="Ubuntu 18.04.4 LTS"
VERSION_ID="18.04"
HOME_URL="https://www.ubuntu.com/"
SUPPORT_URL="https://help.ubuntu.com/"
BUG_REPORT_URL="https://bugs.launchpad.net/ubuntu/"
PRIVACY_POLICY_URL="https://www.ubuntu.com/legal/terms-and-policies/privacy-policy"
VERSION_CODENAME=bionic
UBUNTU_CODENAME=bionic
$
```
Command tested on
* Docker container: Ubuntu Linux

## Check Ubuntu version using the hostnamectl command
```bash
$ hostnamectl
   Static hostname: linuxize
         Icon name: computer-vm
           Chassis: vm
        Machine ID: f1ce51f447c84509a86afc3ccf17fa24
           Boot ID: 2b3cd5003e064382a754b1680991040d
    Virtualization: kvm
  Operating System: Ubuntu 18.04 LTS
            Kernel: Linux 4.15.0-22-generic
      Architecture: x86-64
```

## Check Ubuntu Version in the Gnome Desktop
<img src="https://linuxize.com/post/how-to-check-your-ubuntu-version/ubuntu-system-settings.jpg">
<img src="https://linuxize.com/post/how-to-check-your-ubuntu-version/check-ubuntu-version.jpg">
