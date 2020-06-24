* Rev.1: 2020-05-21 (Thu)
* Draft: 2020-03-25 (Wed)

# How to Install Oracle JDK on Ubuntu Linux 18.04

## Summary

Remove OpenJDK and install Official JDK

Step 1. Remove OpenJDK first

```bash
$ sudo apt-get purge openjdk*
```

Step 2. Add the repository for Official JDK and update

```bash
$ sudo add-apt-repository ppa:linuxuprising/java
$ sudo apt-get update
```

Step 3. Install Official JDK

  $ sudo apt-get install -y oracle-java12-installer

## Purpose

* XMind 8 Pro fails to launch. To make this program work, Ubuntu's default OpenJDK is removed and Oracle JDK is installed.
* Google search: ubuntu linux 18.04  How to remove OpenJDK and install Oracle JDK

## Prerequisite

### Check the Java Version

```bash
$ java -version
java version "12.0.2" 2019-07-16
Java(TM) SE Runtime Environment (build 12.0.2+10)
Java HotSpot(TM) 64-Bit Server VM (build 12.0.2+10, mixed mode, sharing)
$
```

### Remove the existing OpenJDK

```bash
$ sudo apt-get purge openjdk*
#  or
#$ sudo apt-get purge openjdk-\*
$ sudo apt autoremove
$
```

For other related commands, refer to [How to remove openjdk-8-jdk from Ubuntu 16.04 (Xenial Xerus)](https://www.howtoinstall.co/en/ubuntu/xenial/openjdk-8-jdk?action=remove).

## Installation

[How to (Easily) Install Java on Ubuntu](https://thishosting.rocks/install-java-ubuntu/#oracle-jdk) > How to install Java 11 or Java 13 using the Oracle JDK, 2019-12-18, ThisHosting.Rocks

This tutorial includes commands resulting in errors; so I had to fix them.

### Step 1: Add the Java repository

The first thing you need to do is add a 3-rd party repository to get the Oracle JDK. We’ll use the one from Linux Uprising, but you can use any other repository:

```bash
$ sudo add-apt-repository ppa:linuxuprising/java
$ sudo apt-get update
```

### Step 2: Install Official JDK

To install JDK 11,

```bash
$ sudo apt-get install -y oracle-java11-installer
```

To install JDK 12,

```bash
$ sudo apt-get install -y oracle-java12-installer
```

To install JDK 13,

```bash
$ sudo apt-get install oracle-java13-installer
```

And that’s it. You can now move on to step 4 and [configure your Java](about:blank#set-up).

### Download Oracle JDK

Download it from 

* [Java SE Development Kit 14 Downloads](https://www.oracle.com/java/technologies/javase-jdk14-downloads.html)
* [Java SE Development Kit 8 Downloads](https://www.oracle.com/java/technologies/javase-jdk8-downloads.html) (An example of an older link)

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

## References

* [remove-openjdk-and-install-oracle-jdk on ubuntu](https://flicsdb.com/remove-openjdk-and-install-oracle-jdk-on-ubuntu/) August 4, 2019 by [zshaik](https://flicsdb.com/author/zshaik/). 
* [How to Install Oracle Java 12 in Ubuntu 18.04 / 16.04](https://laptrinhx.com/how-to-install-oracle-java-12-in-ubuntu-18-04-16-04-2045321107/), 2019-03-25

