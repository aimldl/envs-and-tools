* Draft: 2020-05-28 (Thu)

# debconf-set-selections

* `debconf-set-selections` inserts new values into the `debconf` database.
* It can be used:
  * to pre-seed the `debconf` database with answers.
  * to change answers in the database.
* Each question will be marked as seen to prevent `debconf` from asking the question interactively.

**See also**: [debconf-get-selections](debconf-get-selections.md)

## Example: MySQL Server Installation

`debconf-set-selections` pre-configures the installation of MySQL server and automates the installation process.

```bash
MYSQL_PASSWORD=MYSQL_PASSWORD
echo "mysql-server-5.5 mysql-server/root_password password ${MYSQL_PASSWORD}
mysql-server-5.5 mysql-server/root_password seen true
mysql-server-5.5 mysql-server/root_password_again password ${MYSQL_PASSWORD}
mysql-server-5.5 mysql-server/root_password_again seen true
" | debconf-set-selections
DEBIAN_FRONTEND=noninteractive apt-get install -y --force-yes mysql-server
```

Source: [debconf 개념 > 미리 설정한 debconf 프롬프트](https://docs.openstack.org/liberty/ko_KR/install-guide-debian/debconf/debconf-concepts.html)

## Install `debconf-utils` package

```bash
$ sudo apt-get install debconf-utils
```

**See also**: [debconf-get-selections](debconf-get-selections.md)

## References

* [debconf-set-selections](http://manpages.ubuntu.com/manpages/trusty/man1/debconf-set-selections.1.html)
* [debconf 개념 > 미리 설정한 debconf 프롬프트](https://docs.openstack.org/liberty/ko_KR/install-guide-debian/debconf/debconf-concepts.html)

* [How to read and insert new values into the debconf database](https://blog.sleeplessbeastie.eu/2018/09/17/how-to-read-and-insert-new-values-into-the-debconf-database/)

