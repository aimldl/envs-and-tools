* Rev.2: 2020-05-28 (Thu)
* Rev.1: 2019-11-01 (Fri)
* Draft: 2019-10-31 (Thu)
# SELECT
A sequence of example to use the `SELECT` command is below.

## Example 1
* Assume a database "sample" has already been imported.
* Database "sample" has a collection of sample databases such as sample21 & sample24 in it.
### Step 1. connect to the MySQL server
```bash
$ sudo mysql -uroot -p
Enter password:
   ...
mysql>
```
Note `show` is not the standard SQL command.
```sql
mysql> show databases;
+--------------------+
| Database           |
+--------------------+
  ...
| sample             |
  ...
+--------------------+
```

### Step 2. `use` a database
```sql
mysql> use sample
Reading table information for completion of table and column names
You can turn off this feature to get a quicker startup with -A

Database changed
mysql> 
```
Note: the `SELECT` command will fail without running the `use` command.
```sql
mysql> SELECT * FROM sample21;
ERROR 1046 (3D000): No database selected
mysql> SELECT * FROM sample;
ERROR 1046 (3D000): No database selected
mysql>
```
### Step 3. run `SELECT` commands
#### `SELECT *`
``` sql
mysql> SELECT * FROM sample21;
+------+-----------+------------+---------------------------+
| no   | name      | birthday   | address                   |
+------+-----------+------------+---------------------------+
|    1 | 박준용    | 1976-10-18 | 대구광역시 수성구         |
|    2 | 김재진    | NULL       | 대구광역시 동구           |
|    3 | 홍길동    | NULL       | 서울특별시 마포구         |
+------+-----------+------------+---------------------------+
3 rows in set (0.00 sec)

mysql> DESC sample21;
+----------+-------------+------+-----+---------+-------+
| Field    | Type        | Null | Key | Default | Extra |
+----------+-------------+------+-----+---------+-------+
| no       | int(11)     | YES  |     | NULL    |       |
| name     | varchar(20) | YES  |     | NULL    |       |
| birthday | date        | YES  |     | NULL    |       |
| address  | varchar(40) | YES  |     | NULL    |       |
+----------+-------------+------+-----+---------+-------+
4 rows in set (0.00 sec)

#### `SELECT` specific columns
```sql
mysql> SELECT no, name FROM sample21;
+------+-----------+
| no   | name      |
+------+-----------+
|    1 | 박준용    |
|    2 | 김재진    |
|    3 | 홍길동    |
+------+-----------+
3 rows in set (0.00 sec)

#### `SELECT ... where`
```sql
mysql> SELECT no, name FROM sample21 where no=2;
+------+-----------+
| no   | name      |
+------+-----------+
|    2 | 김재진    |
+------+-----------+
1 row in set (0.00 sec)
```
```sql
mysql> SELECT no, name FROM sample21 where no!=2;
+------+-----------+
| no   | name      |
+------+-----------+
|    1 | 박준용    |
|    3 | 홍길동    |
+------+-----------+
2 rows in set (0.00 sec)
```
```sql
mysql> SELECT no, name FROM sample21 where no<>2;
+------+-----------+
| no   | name      |
+------+-----------+
|    1 | 박준용    |
|    3 | 홍길동    |
+------+-----------+
2 rows in set (0.00 sec)
```
```sql
mysql> SELECT no, name FROM sample21 where name="박준용";
+------+-----------+
| no   | name      |
+------+-----------+
|    1 | 박준용    |
+------+-----------+
1 row in set (0.00 sec)

mysql> SELECT no, name FROM sample21 where name="박준";
Empty set (0.00 sec)
```
```sql
mysql> SELECT * from sample21 WHERE birthday=NULL;
Empty set (0.00 sec)

mysql> SELECT * from sample21 WHERE birthday IS NULL;
+------+-----------+----------+---------------------------+
| no   | name      | birthday | address                   |
+------+-----------+----------+---------------------------+
|    2 | 김재진    | NULL     | 대구광역시 동구           |
|    3 | 홍길동    | NULL     | 서울특별시 마포구         |
+------+-----------+----------+---------------------------+
2 rows in set (0.00 sec)
```
```sql
mysql> SELECT * FROM sample24;
+------+------+------+------+
| no   | a    | b    | c    |
+------+------+------+------+
|    1 |    1 |    0 |    0 |
|    2 |    0 |    1 |    0 |
|    3 |    0 |    0 |    1 |
|    4 |    2 |    2 |    0 |
|    5 |    0 |    2 |    2 |
+------+------+------+------+
5 rows in set (0.00 sec)
```
```sql
mysql> SELECT * FROM sample24 where a<>0 AND b<>0;
+------+------+------+------+
| no   | a    | b    | c    |
+------+------+------+------+
|    4 |    2 |    2 |    0 |
+------+------+------+------+
1 row in set (0.00 sec)

mysql> SELECT * FROM sample24 where a<>0 OR b<>0;
\+------+------+------+------+
| no   | a    | b    | c    |
+------+------+------+------+
|    1 |    1 |    0 |    0 |
|    2 |    0 |    1 |    0 |
|    4 |    2 |    2 |    0 |
|    5 |    0 |    2 |    2 |
+------+------+------+------+
4 rows in set (0.00 sec)

mysql> SELECT * FROM sample24 where no=1 OR no=2;
+------+------+------+------+
| no   | a    | b    | c    |
+------+------+------+------+
|    1 |    1 |    0 |    0 |
|    2 |    0 |    1 |    0 |
+------+------+------+------+
2 rows in set (0.00 sec)

mysql> SELECT * FROM sample24 where no=1 OR 2;
+------+------+------+------+
| no   | a    | b    | c    |
+------+------+------+------+
|    1 |    1 |    0 |    0 |
|    2 |    0 |    1 |    0 |
|    3 |    0 |    0 |    1 |
|    4 |    2 |    2 |    0 |
|    5 |    0 |    2 |    2 |
+------+------+------+------+
5 rows in set (0.00 sec)

mysql> SELECT * FROM sample24 where a=1 OR a=2 AND b=1 OR b=2;
+------+------+------+------+
| no   | a    | b    | c    |
+------+------+------+------+
|    1 |    1 |    0 |    0 |
|    4 |    2 |    2 |    0 |
|    5 |    0 |    2 |    2 |
+------+------+------+------+
3 rows in set (0.00 sec)

mysql> SELECT * FROM sample24 where a=1 OR (a=2 AND b=1) OR b=2;
+------+------+------+------+
| no   | a    | b    | c    |
+------+------+------+------+
|    1 |    1 |    0 |    0 |
|    4 |    2 |    2 |    0 |
|    5 |    0 |    2 |    2 |
+------+------+------+------+
3 rows in set (0.00 sec)

mysql> SELECT * FROM sample24 where (a=1 OR a=2) AND (b=1 OR b=2);
+------+------+------+------+
| no   | a    | b    | c    |
+------+------+------+------+
|    4 |    2 |    2 |    0 |
+------+------+------+------+
1 row in set (0.00 sec)

mysql> SELECT * FROM sample24 where NOT (a<>0 OR b<>0);
+------+------+------+------+
| no   | a    | b    | c    |
+------+------+------+------+
|    3 |    0 |    0 |    1 |
+------+------+------+------+
1 row in set (0.00 sec)

mysql>
```
