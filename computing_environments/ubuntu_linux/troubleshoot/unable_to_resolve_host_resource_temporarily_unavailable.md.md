* Draft: 2020-06-07 (Mon)
# sudo: unable to resolve host ip-w-x-y-z: Resource temporarily unavailable

## Problem
The following error message occurs.

```bash
$ sudo apt-get upgrade
sudo: unable to resolve host ip-123-45-67-890: Resource temporarily unavailable
  ...
$
```

## Hint
```
Sudo Unable To Resolve Host. When the terminal is stuck on "sudo: unable to resolve host(none)", it means that you have not provided a hostname to your system. Hostname is the name of your device that the network identifies with. The hostname is stored locally in the file "/etc/hostname".May 31, 2017
Source: [Sudo Unable To Resolve Host](https://www.psychz.net/client/question/en/sudo-unable-to-resolve-host.html)
```

##
[Error message “sudo: unable to resolve host (none)”](https://askubuntu.com/questions/59458/error-message-sudo-unable-to-resolve-host-none)
```
(base) ubuntu@123-45-67-890:~$ cat /etc/hostname
ip-123-45-67-890
(base) ubuntu@123-45-67-890:~$ cat /etc/hosts
127.0.0.1 localhost

# The following lines are desirable for IPv6 capable hosts
::1 ip6-localhost ip6-loopback
fe00::0 ip6-localnet
ff00::0 ip6-mcastprefix
ff02::1 ip6-allnodes
ff02::2 ip6-allrouters
ff02::3 ip6-allhosts
$
```
