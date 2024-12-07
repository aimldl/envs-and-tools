* Draft: 2021-07-19 (Mon)



## Problem

```bash
$ sudo apt update
  ...
$ sudo apt upgrade -y
E: /var/lib/dpkg/lock-frontend 잠금 파일을 얻을 수 없습니다 - open (11: 자원이 일시적으로 사용 불가능함)
E: Unable to acquire the dpkg frontend lock (/var/lib/dpkg/lock-frontend), is another process using it?
$
```

## Solution

Google search: ubuntu E: Unable to acquire the dpkg frontend lock (/var/lib/dpkg/lock-frontend), is another process using it?

* [리눅스 에러 Could not get lock /var/lib/dpkg/lock-frontend](https://kgu0724.tistory.com/71)

  > ```bash
  > # Kill all apt-related processes
  > $ sudo killall apt apt-get
  > # Delete all the following files related to "lock"
  > $ sudo rm /var/lib/apt/lists/lock
  > $ sudo rm /var/cache/apt/archives/lock
  > $ sudo rm /var/lib/dpkg/lock*
  > # Configure and update
  > $ sudo dpkg --configure -a
  > ```
  >
  > Now the following commands should work.
  >
  > ```bash
  > $ sudo apt update
  >   ...
  > # Now the
  > $ sudo apt upgrade -y
  >   ...
  > $ 
  > ```