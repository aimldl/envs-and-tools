##### aimldl/computing_environments/typora/TROUBLESHOOT-Installation.md

# Installation Fails

## Problem
```bash
(base) bitnami@EC2-Seoul:~/aimldl$ wget -qO - https://typora.io/linux/public-key.as                                                                                                                        c | sudo apt-key add -
OK
(base) bitnami@EC2-Seoul:~/aimldl$ sudo add-apt-repository 'deb https://typora.io/l                                                                                                                        inux ./'
(base) bitnami@EC2-Seoul:~/aimldl$ sudo apt-get update
Ign http://ap-northeast-2.ec2.archive.ubuntu.com trusty InRelease
  ...
Fetched 8,137 B in 17s (474 B/s)
Reading package lists... Done
(base) bitnami@EC2-Seoul:~/aimldl$ sudo apt-get install typora
Reading package lists... Done
Building dependency tree
Reading state information... Done
Suggested packages:
  gir1.2-gnomekeyring-1.0 libgnome-keyring0
The following NEW packages will be installed:
  typora
0 upgraded, 1 newly installed, 0 to remove and 164 not upgraded.
Need to get 0 B/59.0 MB of archives.
After this operation, 202 MB of additional disk space will be used.
dpkg-deb: error: archive '/var/cache/apt/archives/typora_0.9.83-1_amd64.deb' has premature member 'control.tar.xz' before 'control.tar.gz', giving up
dpkg: error processing archive /var/cache/apt/archives/typora_0.9.83-1_amd64.deb (--unpack):
 subprocess dpkg-deb --control returned error exit status 2
Errors were encountered while processing:
 /var/cache/apt/archives/typora_0.9.83-1_amd64.deb
E: Sub-process /usr/bin/dpkg returned an error code (1)
(base) bitnami@EC2-Seoul:~/aimldl$
```

## TODO: Fix it.
