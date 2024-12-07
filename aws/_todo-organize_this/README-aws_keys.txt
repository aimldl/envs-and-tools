# README-amazon-key_pair

* Rev.4: 2021-02-17 (Wed)
* Rev.3: 2019-12-30 (Mon)
* Rev.2: 2019-11-25 (Mon)
* Rev.1: 2019-02-11 (Mon)
* Draft: 2018-12-18 (Tue)

## Overview
Two kinds of keys are in this directory.

1. SSH Keys
2. Access Keys

It is important to keep the file because it can't be reissued.

### SSH Keys
There are two types of SSH key files for Amazon key pair which is used for authentication.
* .pem
  * for Linux & iOS
* .ppk
  * for Windows

### Common problems
#### `Permissions 0644 for 'my_key_pair.pem' are too open.
You may encounter the following error.

```bash
$ ssh -i my_key_pair.pem -L 8888:localhost:8888 -X ubuntu@xx.xxx.xx.xx
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@         WARNING: UNPROTECTED PRIVATE KEY FILE!          @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
Permissions 0644 for 'my_key_pair.pem' are too open.
It is required that your private key files are NOT accessible by others.
This private key will be ignored.
Load key "my_key_pair.pem": bad permissions
ubuntu@xx.xxx.xx.xx: Permission denied (publickey).
$
```

#### Solution
Change the priviledge of the key pair.

```bash
$ chmod 400 my_key_pair.pem
```

### X11
`homepage_server` is a server without X11 which was not installed intentionally.
If X11 is necessary, run `sudo apt install -y xorg openbox`

OPTION='-L 8888:localhost:8888 -X'
#OPTION='-L 8888:localhost:8888'

Two kinds of Bash scripts exist:
* ssh
* sftp

## Files

README
├── README-amazon-key_pair

SSH Keys
├── key_pair-aimldl_office_2021.pem
├── key_pair-aimldl_office_2021.ppk

ssh
├── ssh-aws_ec2_seoul-aimldl-office-2021

sftp
├── sftp-aws_ec2_seoul-aimldl-office-2021
