* Rev.1: 2020-05-28 (Thu)
* Draft: 2019-10-25 (Fri)
# ERROR 1698 (28000): Access denied for user 'root'@'localhost'
## Problem
ERROR 1698 (28000): Access denied for user 'root'@'localhost'
```bash
$ mysql -uroot -p < sample.dump 
Enter password: 
ERROR 1698 (28000): Access denied for user 'root'@'localhost'
$
```
### Solution
Use "sudo" to run the mysql command.
```bash
$ sudo mysql -u root -p
[sudo] password for aimldl: 
Enter password: 
Welcome to the MySQL monitor.  Commands end with ; or \g.
  ...
Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

mysql>
```
### Situation
MySQL Community Server is installed on Ubuntu 18.04. The root password is configured with "mysql_secure_installation" and the installation is verified with the following command.  

```bash
$ sudo mysqladmin -p -u root version
[sudo] password for aimldl: 
Enter password: 
mysqladmin  Ver 8.42 Distrib 5.7.27, for Linux on x86_64
Copyright (c) 2000, 2019, Oracle and/or its affiliates. All rights reserved.
  ...
Threads: 1  Questions: 11  Slow queries: 0  Opens: 113  Flush tables: ...
$
```
Even through the same root password is entered, an error has occured whenever I tried to access or log into the mysql server. This is the very first step to use MySQL. What happened?
```bash
$ mysql -uroot -p 
```
### Reason
```
Question:
I'm setting up a new server and keep running into this problem.
When I try to login to the MySQL database with the root user, I get the error:
  ERROR 1698 (28000): Access denied for user 'root'@'localhost' 
It doesn't matter if I connect through the terminal(SSH), through PHPMyAdmin 
  or a MySQL Client, e.g. Navicat. They all fail.

Answer:
Some systems like Ubuntu, mysql is using by default the UNIX auth_socket plugin.
Basically means that: db_users using it, will be "auth" by the system user credentias.
You can see if your root user is set up like this by doing the following:

$ sudo mysql -u root

I had to use "sudo" since the new installation.
```
Google searhc: ERROR 1698 (28000): Access denied for user 'root'@'localhost'
[ERROR 1698 (28000): Access denied for user 'root'@'localhost'](https://stackoverflow.com/questions/39281594/error-1698-28000-access-denied-for-user-rootlocalhost)
