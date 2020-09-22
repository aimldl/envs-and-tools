* Rev.3: 2020-09-22 (Tue)
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
Set up the root password and so on. An example for the testing purpose is below. Note the first question is "no". Setting this option to "yes" complicates the password for improved security. Improved security is a must for a production MySQL server, but not for testing or educational purposes.

```bash
$ sudo mysql_secure_installation

Securing the MySQL server deployment.

Connecting to MySQL using a blank password.

VALIDATE PASSWORD PLUGIN can be used to test passwords
and improve security. It checks the strength of password
and allows the users to set only those passwords which are
secure enough. Would you like to setup VALIDATE PASSWORD plugin?

Press y|Y for Yes, any other key for No: n
Please set the password for root here.

New password: 

Re-enter new password: 
By default, a MySQL installation has an anonymous user,
allowing anyone to log into MySQL without having to have
a user account created for them. This is intended only for
testing, and to make the installation go a bit smoother.
You should remove them before moving into a production
environment.

Remove anonymous users? (Press y|Y for Yes, any other key for No) : n

 ... skipping.


Normally, root should only be allowed to connect from
'localhost'. This ensures that someone cannot guess at
the root password from the network.

Disallow root login remotely? (Press y|Y for Yes, any other key for No) : y
Success.

By default, MySQL comes with a database named 'test' that
anyone can access. This is also intended only for testing,
and should be removed before moving into a production
environment.


Remove test database and access to it? (Press y|Y for Yes, any other key for No) : n

 ... skipping.
Reloading the privilege tables will ensure that all changes
made so far will take effect immediately.

Reload privilege tables now? (Press y|Y for Yes, any other key for No) : y
Success.

All done! 
$
```

### Step 3. Verify if MySQL is Up & Running
If these commands run without an error, the MySQL server is up & running.
`$ systemctl status mysql.service`
`$ sudo mysqladmin -p -u root version`

#### To check the status of the MySQL server, run:
```bash
$ systemctl status mysql.service
```
##### An example
The server should be loaded and active (running) like below.

```bash
$ systemctl status mysql.service
● mysql.service - MySQL Community Server
   Loaded: loaded (/lib/systemd/system/mysql.service; enabled; vendor preset: enabled)
   Active: active (running) since Tue 2020-09-22 13:30:21 KST; 10min ago
 Main PID: 29949 (mysqld)
    Tasks: 28 (limit: 4915)
   CGroup: /system.slice/mysql.service
           └─29949 /usr/sbin/mysqld --daemonize --pid-file=/run/mysqld/mysqld.pid

Sep 22 13:30:21 Home-Laptop systemd[1]: Starting MySQL Community Server...
Sep 22 13:30:21 Home-Laptop systemd[1]: Started MySQL Community Server.
$
```

#### To print the version of the MySQL server, run:
```bash
$ sudo mysqladmin -p -u root version
```
##### An example
The version information will be displayed.
```bash
$ sudo mysqladmin -p -u root version
Enter password: 
mysqladmin  Ver 8.42 Distrib 5.7.31, for Linux on x86_64
Copyright (c) 2000, 2020, Oracle and/or its affiliates. All rights reserved.

Oracle is a registered trademark of Oracle Corporation and/or its
affiliates. Other names may be trademarks of their respective
owners.

Server version		5.7.31-0ubuntu0.18.04.1
Protocol version	10
Connection		Localhost via UNIX socket
UNIX socket		/var/run/mysqld/mysqld.sock
Uptime:			10 min 58 sec

Threads: 1  Questions: 8  Slow queries: 0  Opens: 113  Flush tables: 1  Open tables: 106  Queries per second avg: 0.012
$
```
