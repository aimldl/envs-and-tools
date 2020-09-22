



## SQLAlchemy를 사용하여 API와 데이터베이스 연결하기

`config.py`

```python
# config.py
# * Draft: 2020-09-22 (Tue)

db = {
  'user'     : 'root',
  'password' : 'test1234',
  'host'     : 'localhost',
  'port'     : 3306,
  'database' : 'miniter'
}

# mysql+mysqlconnector://{username}:{password}@{host}:{port}/{database}
DB_URL = f"mysql+mysqlconnector://{db['user']}:{db['password']}@{db['host']}:{db['port']}/{db['database']}?charset=utf8"
```

여기서 `password`를 로컬에 설치된 MySQL 서버의 root 패스워드로 변경해야 한다. 그러지 않으면 나중에 데이터베이스에 접촉이 필요할 때 `Access denied for user 'root'@'localhost'`에러가 발생한다.

```bash
  ...
sqlalchemy.exc.ProgrammingError: (mysql.connector.errors.ProgrammingError) 1698 (28000): Access denied for user 'root'@'localhost'
(Background on this error at: http://sqlalche.me/e/13/f405)
```

