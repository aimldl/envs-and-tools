* Rev.1: 2020-05-28 (Thu)
* Draft: 2019-10-25 (Fri)

# How to Connect to MySQL Server with the `mysql` command
The `mysql` command is the MySQL command-line client used to connect the MySQL server. Basically the `mysql db_name` command connects to the specified database `db_name`. Typically user ID and password are required.
```bash
shell> mysql -u user_name -p db_name
# or
shell> mysql --user=user_name --password db_name
```
The `-p` or `--password` option invokes:
```bash
Enter password: 
```

For example, sudo is necessary to run mysql on Ubuntu (18.04). 
```bash
aimldl@GPU-Desktop:~$ sudo mysql -uroot -p
```
To understand the reason, refer to [Connect To MySQL Database From Command Line Guide](https://www.a2hosting.com/kb/developer-corner/mysql/connect-to-mysql-from-the-command-line).

Enter the password and you are connected to the SQL server.
```bash
[sudo] password for aimldl: 
Enter password: 
Welcome to the MySQL monitor.  Commands end with ; or \g.
  ...
Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

mysql> 
```
Notice the prompt has changed to `mysql>`.

## To exit the server, run:
```bash
mysql> exit
$
```
The "mysql>" prompt has returned to the Bash prompt "$".

## Specify a database
Selecting the database is possible with the `mysql` command.
```bash
$ sudo mysql -u user_name -p database_name
mysql> 
```
The above command is equivalent to:
```bash
$ sudo mysql -u user_name -p
mysql> use database_name;
```
## Show available databases
It may be necessary to see available datases before using it.
```bash
mysql> show databases;
+--------------------+
| Database           |
+--------------------+
| information_schema |
| mysql              |
| performance_schema |
| sys                |
+--------------------+
mysql> 
```
As an example, my default databases are shown above.

## Example: connect to MySQL and use database 'sample'
Assuming database 'sample' has already been imported, the root user connects to MySQL server and uses database 'sample'.
```bash
$ sudo mysql -u root -p
Enter password: 
  ...
mysql> show databases;
+--------------------+
| Database           |
+--------------------+
| information_schema |
| mysql              |
| performance_schema |
| sample             |
| sys                |
+--------------------+
5 rows in set (0.00 sec)

mysql> use sample;
Reading table information for completion of table and column names
You can turn off this feature to get a quicker startup with -A
  ...
Database changed
mysql> exit
Bye
$ 
```
