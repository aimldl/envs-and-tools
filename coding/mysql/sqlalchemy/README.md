* Draft: 2020-09-22 (Tue)

# SQLAlchemy

* Source: 깔끔한 파이썬 탄탄한 백엔드, 6장 데이터베이스, pp.154-155, 송은우 지음

## Install SQLAlchemy

```bash
$ pip install sqlalchemy
$ pip install mysql-connector-python
```

## Sample Python Code

```python
from sqlalchemy import create_engine, text

db = {
  'user'     : 'root',
  'password' : 'test1234',
  'host'     : 'localhost',
  'port'     : 3306,
  'database' : 'miniter'
}

# mysql+mysqlconnector://{username}:{password}@{host}:{port}/{database}
url_database = f"mysql+mysqlconnector://{db['user']}:{db['password']}@{db['host']}:{db['port']}/{db['database']}?charset=utf8"
#'mysql+mysqlconnector://root:test1234@localhost:3306/miniter?charset=utf8'

database = create_engine( url_database, encoding='utf-8', max_overflow=0 )
# Engine(mysql+mysqlconnector://root:***@localhost:3306/miniter?charset=utf8)

params = {'name': 'aimldl'}
rows = database.execute( text("SELECT * FROM users WHERE name = :name"), params ).fetchall()

for row in rows:
  print( f"name  : {row['name']}" )
  print( f"email  : {row['email']}" )
```



TODO: fix this error.

```python
rows = database.execute( text("SELECT * FROM users WHERE name = :name"), params ).fetchall()
rows = database.execute( "SELECT * FROM users WHERE name = 'aimldl'" ).fetchall()
```

is the cause of the following error.

```python
sqlalchemy.exc.ProgrammingError: (mysql.connector.errors.ProgrammingError) 1698 (28000): Access denied for user 'root'@'localhost'
(Background on this error at: http://sqlalche.me/e/13/f405)
>>> 
```

