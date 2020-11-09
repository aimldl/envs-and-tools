* Draft: 2020-09-22 (Tue)

# How to Create a Database and Tables

* Source: 깔끔한 파이썬 탄탄한 백엔드, 6장 데이터베이스, pp.141-153, 송은우 지음

## Log into MySQL Database

```bash
$ sudo mysql -u root -p
Enter password: 
Welcome to the MySQL monitor.  Commands end with ; or \g.
Your MySQL connection id is 5
Server version: 5.7.31-0ubuntu0.18.04.1 (Ubuntu)

Copyright (c) 2000, 2020, Oracle and/or its affiliates. All rights reserved.

Oracle is a registered trademark of Oracle Corporation and/or its
affiliates. Other names may be trademarks of their respective
owners.

Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

mysql> 
```

Notice the prompt has been changed to `mysql>`. 

Without the `sudo` command, an error will occur.

```bash
$ mysql -u root -p
Enter password: 
ERROR 1698 (28000): Access denied for user 'root'@'localhost'
$
```

## Create a database

`CREATE DATABASE` command creates a database. Say you want to create a `miniter` database

```mysql
mysql> CREATE DATABASE miniter;
Query OK, 1 row affected (0.00 sec)

mysql>
```

To check the create database, run:

```mysql
mysql> SHOW DATABASES;
+--------------------+
| Database           |
+--------------------+
| information_schema |
| miniter            |
| mysql              |
| performance_schema |
| sys                |
+--------------------+
5 rows in set (0.00 sec)

mysql> 
```

`miniter` does exist along with other default databases. Note MySQL is a database system that can contain multiple databases in it.

## Switch to a database

```mysql
mysql> USE miniter;
Database changed
mysql>
```

## Create tables

The syntax to create a table is below.

```mysql
CREATE TABLE table_name (
  column1 data_type,
  column2 data_type,
    ...
  PRIMARY KEY(column1),
  CONSTRAINT 1,
  CONSTRAINT 2,
)
```

### Example

#### `users` table

```mysql
mysql> CREATE TABLE users(
    -> id INT NOT NULL AUTO_INCREMENT,
    -> name VARCHAR(255) NOT NULL,
    -> email VARCHAR(255) NOT NULL,
    -> hashed_password VARCHAR(255) NOT NULL,
    -> profile VARCHAR(2000) NOT NULL,
    -> created_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    -> updated_at TIMESTAMP NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP,
    -> PRIMARY KEY (id),
    -> UNIQUE KEY email (email)
    -> );
Query OK, 0 rows affected (0.07 sec)

mysql> 
```

#### `users_follow_list` table

```mysql
mysql> CREATE TABLE users_follow_list(
    -> user_id INT NOT NULL,
    -> follow_user_id INT NOT NULL,
    -> created_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    -> PRIMARY KEY (user_id, follow_user_id),
    -> CONSTRAINT users_follow_list_user_id_fkey FOREIGN KEY (user_id)
    -> REFERENCES users(id),
    -> CONSTRAINT users_follow_list_follow_user_id_fkey FOREIGN KEY (follow_user_id) REFERENCES users(id)
    -> );
Query OK, 0 rows affected (0.07 sec)

mysql> 
```

#### `tweets` table

```mysql
mysql> CREATE TABLE tweets(
    -> id INT NOT NULL AUTO_INCREMENT,
    -> user_id INT NOT NULL,
    -> tweet VARCHAR(300) NOT NULL,
    -> created_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    -> PRIMARY KEY (id),
    -> CONSTRAINT tweets_user_id_fkey FOREIGN KEY (user_id) REFERENCES users(id)
    -> );
Query OK, 0 rows affected (0.06 sec)

mysql> 
```

#### Check the created tables

```mysql
mysql> SHOW TABLES;
+-------------------+
| Tables_in_miniter |
+-------------------+
| tweets            |
| users             |
| users_follow_list |
+-------------------+
3 rows in set (0.00 sec)

mysql> 
```

For details about each table, run the `EXPLAIN table_name` command.

```mysql
mysql> EXPLAIN users;
+-----------------+---------------+------+-----+-------------------+-----------------------------+
| Field           | Type          | Null | Key | Default           | Extra                       |
+-----------------+---------------+------+-----+-------------------+-----------------------------+
| id              | int(11)       | NO   | PRI | NULL              | auto_increment              |
| name            | varchar(255)  | NO   |     | NULL              |                             |
| email           | varchar(255)  | NO   | UNI | NULL              |                             |
| hashed_password | varchar(255)  | NO   |     | NULL              |                             |
| profile         | varchar(2000) | NO   |     | NULL              |                             |
| created_at      | timestamp     | NO   |     | CURRENT_TIMESTAMP |                             |
| updated_at      | timestamp     | YES  |     | NULL              | on update CURRENT_TIMESTAMP |
+-----------------+---------------+------+-----+-------------------+-----------------------------+
7 rows in set (0.00 sec)

mysql> 
```

```mysql
mysql> EXPLAIN users_follow_list;
+----------------+-----------+------+-----+-------------------+-------+
| Field          | Type      | Null | Key | Default           | Extra |
+----------------+-----------+------+-----+-------------------+-------+
| user_id        | int(11)   | NO   | PRI | NULL              |       |
| follow_user_id | int(11)   | NO   | PRI | NULL              |       |
| created_at     | timestamp | NO   |     | CURRENT_TIMESTAMP |       |
+----------------+-----------+------+-----+-------------------+-------+
3 rows in set (0.00 sec)

mysql> 
```

```mysql
mysql> EXPLAIN tweets;
+------------+--------------+------+-----+-------------------+----------------+
| Field      | Type         | Null | Key | Default           | Extra          |
+------------+--------------+------+-----+-------------------+----------------+
| id         | int(11)      | NO   | PRI | NULL              | auto_increment |
| user_id    | int(11)      | NO   | MUL | NULL              |                |
| tweet      | varchar(300) | NO   |     | NULL              |                |
| created_at | timestamp    | NO   |     | CURRENT_TIMESTAMP |                |
+------------+--------------+------+-----+-------------------+----------------+
4 rows in set (0.00 sec)

mysql> 
```

## Exit MySQL

```bash
mysql> exit
Bye
$
```

