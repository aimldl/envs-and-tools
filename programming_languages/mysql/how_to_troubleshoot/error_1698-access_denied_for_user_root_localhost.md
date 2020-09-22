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
### Solution: an easy fix
For the full remedy, refer to `Solution: the real solution'.

Use `sudo` to run the mysql command.
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

### Solution: the real solution
If MySQL 5.7 or higher is installed on Ubuntu, the root user's password configuration becomes a bit more triky.

#### Step 1. Log into the MySQL database with the `sudo` command.
```bash
$ sudo mysql -u root -p
[sudo] password for aimldl: 
Enter password: 
Welcome to the MySQL monitor.  Commands end with ; or \g.
Your MySQL connection id is 16
Server version: 5.7.31-0ubuntu0.18.04.1 (Ubuntu)

Copyright (c) 2000, 2020, Oracle and/or its affiliates. All rights reserved.

Oracle is a registered trademark of Oracle Corporation and/or its
affiliates. Other names may be trademarks of their respective
owners.

Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

mysql>
```

#### Step 2. Check the authentication mode.
```mysql
mysql> SELECT user, plugin, host FROM mysql.user;
+------------------+-----------------------+-----------+
| user             | plugin                | host      |
+------------------+-----------------------+-----------+
| root             | auth_socket           | localhost |
| mysql.session    | mysql_native_password | localhost |
| mysql.sys        | mysql_native_password | localhost |
| debian-sys-maint | mysql_native_password | localhost |
+------------------+-----------------------+-----------+
4 rows in set (0.00 sec)

mysql>
```
The root user uses `auth_socket`

#### Step 3. Alter the password.
The syntax is below.
```mysql
mysql> ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'password';
```
If `test1234` is used for the password, the SQL command becomes like below.
```mysql
mysql> ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'test1234';
Query OK, 0 rows affected (0.00 sec)
mysql> 
```
The following command takes effect the altered configuration.
```mysql
mysql> FLUSH PRIVILEGES;
Query OK, 0 rows affected (0.00 sec)

mysql>
```
Double-check if the password change has taken effect.
```mysql
mysql> SELECT user, authentication_string, plugin, host FROM mysql.user;
+------------------+-------------------------------------------+-----------------------+-----------+
| user             | authentication_string                     | plugin                | host      |
+------------------+-------------------------------------------+-----------------------+-----------+
| root             | *3D3B92F242033365AE5BC6A8E6FC3E1679F4140A | mysql_native_password | localhost |
| mysql.session    | *THISISNOTAVALIDPASSWORDTHATCANBEUSEDHERE | mysql_native_password | localhost |
| mysql.sys        | *THISISNOTAVALIDPASSWORDTHATCANBEUSEDHERE | mysql_native_password | localhost |
| debian-sys-maint | *EFEB68E11DA5DE91FF05C80D8C809AD5CCD450B4 | mysql_native_password | localhost |
+------------------+-------------------------------------------+-----------------------+-----------+
4 rows in set (0.00 sec)

mysql> exit
Bye
$
```
#### Step 4. Double-check the change.
Now, the `sudo` command is not needed.
```bash
$ mysql -u root -p
Enter password: 
Welcome to the MySQL monitor.  Commands end with ; or \g.
Your MySQL connection id is 20
Server version: 5.7.31-0ubuntu0.18.04.1 (Ubuntu)

Copyright (c) 2000, 2020, Oracle and/or its affiliates. All rights reserved.

Oracle is a registered trademark of Oracle Corporation and/or its
affiliates. Other names may be trademarks of their respective
owners.

Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

mysql> 
```
