* Draft: 2020-12-09 (Wed)

# How to Install SSH on Ubuntu

## Google search
ubuntu 20.04 ssh 설치

* [우분투 데스크탑 sshd server 활성화](https://www.lesstif.com/lpt/sshd-server-24445601.html)

## Install
```bash
$ sudo apt install openssh-server
$ sudo vi /etc/ssh/sshd_config
```

## Enable sshd (SSH Daemon)
```bash
$ sudo  systemctl enable sshd
$ sudo  systemctl restart sshd
```
