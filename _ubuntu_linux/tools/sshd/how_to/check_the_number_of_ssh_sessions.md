* Rev.1: 2021-01-18 (Mon)
* Draft: 2020-08-10 (Mon)

# 접속 중인 SSH세션 개수 확인하는 방법

## Google search
> how to check the number of ssh sessions

* [6 commands to check and list active SSH connections in Linux](https://www.golinuxcloud.com/list-check-active-ssh-connections-linux/)

몇 가지 명령어를 쓸 수 있습니다.
* ss (socket statistics)
* last
* and so on

## 아무도 접속하고 있지 않을 때엔
```bash
$ ss | grep ssh
$
```

```bash
$ last -a | grep -i still
h2o      :0           Mon Aug 10 09:57   still logged in    :0
reboot   system boot  Mon Aug 10 09:57   still running      4.15.0-112-generi
$
```

### 접속 중인 사용자가 있을 때엔
```bash
$ ss | grep ssh
tcp   ESTAB  0  0  192.168.0.109:ssh  123.456.7.890:52400   
$
```

```bash
$ last -a | grep -i still
h2o      pts/2        Mon Aug 10 13:27   still logged in    123.456.7.890
h2o      :0           Mon Aug 10 09:57   still logged in    :0
reboot   system boot  Mon Aug 10 09:57   still running      4.15.0-112-generic
$
```
