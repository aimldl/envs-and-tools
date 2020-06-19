* Rev.1: 2020-05-28 (Thu)
* Draft: 2019-10-31 (Thu)
# Import a Database from a Dump File
An example to import a dumpfile `sample.dump` and select all from the database.
* Download [source.zip](http://download.hanbit.co.kr/exam/2231/source.zip)
* Unzip the .zip file.
```bash
  $ unzip source.zip
  $ ls
  sample.dump  source.zip
  $
```
* Import the .dump file.
```bash
  $ sudo mysql -u root -p < sample.dump 
  Enter password: 
  $
```
* Access MySQL server & show database 'sample21'.
```bash
$ sudo mysql -u root -p
mysql> use sample;
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

mysql> exit
Bye
$ 
```
