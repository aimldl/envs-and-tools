* Rev.2: 2020-08-07 (Fri)
* Rev.1: 2020-08-06 (Thu)
* Rev.1: 2020-05-21 (Thu)
* Draft: 2020-03-25 (Wed)

# Install Oracle JDK on Ubuntu 18.04 directly from the Oracle website
## Download Oracle JDK directly from Oracle website.

Download "Linux Debian Package" or [jdk-14_linux-x64_bin.deb](https://www.oracle.com/java/technologies/javase-jdk14-downloads.html#license-lightbox). 

<img src="images/Java SE Development Kit 14.png">

```bash
Click the right version, accept the license and download the file.
$ wget https://download.oracle.com/otn-pub/java/jdk/14.0.1+7/664493ef4a6946b186ff29eb326336a2/jdk-14.0.1_linux-x64_bin.deb
$ ls
anaconda3  bin  h2o-3.30.0.3  h2o-3.30.0.3.zip  hands-ons  history.log  jdk-14.0.1_linux-x64_bin.deb  projects
$
```

TODO: Rewrite

wget doesn't work any more. Download it from a web browser after accepting the license. 

```bash
(base) user@d24d8fc9d727:~$ ls -al
  ...
-rw-r--r-- 1 user user      5307 Mar 20  2012 jdk-14.0.1_linux-x64_bin.deb
(base) user@d24d8fc9d727:~$ sudo dpkg -i jdk-14.0.1_linux-x64_bin.deb
dpkg: error processing archive jdk-14.0.1_linux-x64_bin.deb (--install):
 dpkg-deb --control subprocess returned error exit status 2
Errors were encountered while processing:
 jdk-14.0.1_linux-x64_bin.deb
$
```

When the same file is downloaded from a web browser, the file size is a lot bigger.

```bash
(base) user@d24d8fc9d727:~$ ls -al
  ...
-rw-rw-r-- 1 user user 165593818 May 21 08:11 jdk-14.0.1_linux-x64_bin.deb

```

### Install the .deb File

```bash
$ sudo dpkg -i jdk-14_linux-x64_bin.deb 
  ...
Selecting previously unselected package jdk-14.
(데이터베이스 읽는중 ...현재 217860개의 파일과 디렉터리가 설치되어 있습니다.)
Preparing to unpack jdk-14_linux-x64_bin.deb ...
Unpacking jdk-14 (14-1) ...
Configuring jdk-14 (14-1) ...
$
```

2020-05-21 (Thu)

The above method failed. So I've followed.

Google search: how to install java in ubuntu 18.04 docker container

* [How To Install Java On Ubuntu 18.04](https://phoenixnap.com/kb/how-to-install-java-ubuntu)

* The following link looks useful to install java inside a Docker container.
  * [Docker: install Java8 automatically on ubuntu/debian](https://newfivefour.com/docker-java8-auto-install.html)

### Remove the unwanted existing Oracle Java version
Say my target jar file fails to run with the following error
```bash
$ java -jar h2o.jar 
Only Java 8, 9, 10, 11, 12 and 13 are supported, system version is 14.0.2
$
```
while my current java is version 14.
```bash
$ java --version
java 14.0.2 2020-07-14
Java(TM) SE Runtime Environment (build 14.0.2+12-46)
Java HotSpot(TM) 64-Bit Server VM (build 14.0.2+12-46, mixed mode, sharing)
$
```
Let's remove the unsupported version of 14.

First, check the current version
```bash
$ sudo dpkg --list | grep -i jdk
ii  oracle-java14-installer                    14.0.2-1~linuxuprising1                          amd64        Oracle Java(TM) Development Kit (JDK) 14
ii  oracle-java14-set-default                  14.0.2-1~linuxuprising1                          amd64        Set Oracle JDK 14 as default Java
$
```
and uninstall 
```bash
$ sudo apt-get purge oracle-java14-installer
  ...
$ sudo apt-get autoremove
  ...
$
```
To double-check,nothing is left in the machine.
```bash
$ sudo dpkg --list | grep -i jdk
$
```
For details, refer to [How to uninstall Oracle JDK in Ubuntu 16.04 LTS [duplicate]](https://askubuntu.com/questions/850729/how-to-uninstall-oracle-jdk-in-ubuntu-16-04-lts). 


