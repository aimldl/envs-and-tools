##### aimldl > computing_environments > ubuntu_linux > commands > hostname.md
* Rev.1: 2020-0316 (Mon)
* Draft: 2019-1211 (Wed)
# hostname
The hostname command displays the current hostname. Equivalently, /etc/hostname is a text file containing the hostname. When GPU-Desktop is the hostname,
```bash
$ hostname
GPU-Desktop
$ cat /etc/hostname
GPU-Desktop
$
```
See also [lsb_release](#lsb_release.md), [uname](#uname.md)

## How to change hostname on Ubuntu
1. Edit the "/etc/hostname" file to delete the old name and write new name.
```bash
$ sudo nano /etc/hostname
```
The nano text editor is used above, but you may use any text editor like vi.
2. Edit the /etc/hosts file to replace any occurrence of the existing computer name with the new one.
```bash
$ sudo nano /etc/hosts
```
3. The system must be rebooted to take effect.
```bash
$ sudo reboot
```
For details, refer to [Ubuntu Linux Change Hostname (computer name)](https://www.cyberciti.biz/faq/ubuntu-change-hostname-command/). The following moving GIF shows the sample outputs.

<img src="https://www.cyberciti.biz/media/new/faq/2016/01/ubuntu-change-computer-name-demo-copy.gif">

## Docker Container: Ubuntu Linux
```bash
(base) user@7b9a22e6ed4f:~$ hostname
7b9a22e6ed4f
```
The hostname inside a Docker container can't be altered with the above method.
```bash
(base) user@7b9a22e6ed4f:~$ sudo nano /etc/hostname
# The text in the file "hostname" is changed from 7b9a22e6ed4f to aimldl.
(base) user@7b9a22e6ed4f:~$ cat /etc/hostname
aimldl

(base) user@7b9a22e6ed4f:~$ sudo nano /etc/hosts
# The text in the file "hostname" is changed from 7b9a22e6ed4f to aimldl.
# Old:
#   127.0.0.1       localhost
#     ...
#   172.17.0.2      7b9a22e6ed4f
# New:
#   172.17.0.2      aimldl

(base) user@7b9a22e6ed4f:~$ exit
exit

# Enter the container again
$ docker exec -it conda bash
(base) user@7b9a22e6ed4f:~$
# Well, the hostname has not been changed!
```

Other commands "hostnamectl" and "sudo hostname [new_hostname]" fail on the same Docker container.
```bash
(base) user@7b9a22e6ed4f:~$ hostnamectl
bash: hostnamectl: command not found
(base) user@7b9a22e6ed4f:~$ sudo hostname aimldl
sudo: unable to resolve host 7b9a22e6ed4f
hostname: you must be root to change the host name
(base) user@7b9a22e6ed4f:~$
```
