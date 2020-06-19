* Rev.2: 2020-05-28 (Thu)
* Rev.1: 2019-10-25 (Fri)
* Draft: 2019-10-24 (Thu)

# Prepare the Computing Environment for MySQL
* Refer to [Getting Started with MySQL](https://dev.mysql.com/doc/mysql-getting-started/en/) to set up the MySQL computing environment.
* This document explains:
  * Installing and Starting MySQL
  * Connecting to the MySQL Server with the mysql Client
  * Some Basic Operations with MySQL
  * Other Important Tasks to Perform
  * Troubleshooting
  * Other Helpful Resources
  
[Ubuntu 18.04에 MySQL 설치하기](https://blog.naver.com/aimldl/221688199728) explains how to install MySQL on Ubuntu 18.04 in Korean.

## Step 1. Install MySQL Community Server
MySQL Community Server is a freely downloadable version of MySQL.
To install on Ubuntu (tested only on Ubuntu 18.04.), run:
```bash
$ sudo apt update
$ sudo apt install mysql-server
```
### Progress
* Ubuntu Linux 18.04 (Done)
* CentOS 7 -> Failed on an AWS SageMaker instance (CentOS 7)
* Windows 10 -> Failed on Win10 (Guest OS) on Ubuntu 18.04 (Host OS). Hypervisor is Oracle VM VirtualBox.
                  because the installation .msi file is for a 32-bit OS.
Refer to [MySQL Installer for Microsoft Windows](https://dev.mysql.com/downloads/windows/installer/8.0.html)

### Step 2. Configure MySQL 
Run:
```bash
$ sudo mysql_secure_installation
```
Set up the root password and so on.

### Step 3. Verify if MySQL is Up & Running
To check the status of the MySQL server, run:
```bash
$ systemctl status mysql.service
```
The server should be loaded and active (running).

To print the version of the MySQL server, run:
```bash
$ sudo mysqladmin -p -u root version
```
The version information will be displayed.

If these commands run without an error, the MySQL server is up & running.

