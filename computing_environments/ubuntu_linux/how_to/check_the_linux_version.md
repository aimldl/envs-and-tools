* Rev.1: 2020-10-06 (Tue)
* Draft: 2020-03-12 (Thu)
# How to Check the Linux Version (on Command Line)
## References
* [How to Check your Ubuntu Version](https://linuxize.com/post/how-to-check-your-ubuntu-version/).
* [Check os version in Linux](https://www.cyberciti.biz/faq/how-to-check-os-version-in-linux-command-line/)

## `$ cat /etc/os-release`
### Amazon SageMaker
```bash
$ cat /etc/os-release
NAME="Amazon Linux AMI"
VERSION="2018.03"
ID="amzn"
ID_LIKE="rhel fedora"
VERSION_ID="2018.03"
PRETTY_NAME="Amazon Linux AMI 2018.03"
ANSI_COLOR="0;33"
CPE_NAME="cpe:/o:amazon:linux:2018.03:ga"
HOME_URL="http://aws.amazon.com/amazon-linux-ami/"
$ 
```

### Ubuntu Linux
This command works also on a Docker container with Ubuntu Linux.
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
