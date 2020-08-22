* Draft: 2020-08-10 (Mon)

# How to Check the Number of ssh Sessions

## Google search
> how to check the number of ssh sessions

* [6 commands to check and list active SSH connections in Linux](https://www.golinuxcloud.com/list-check-active-ssh-connections-linux/)

Several commands can be used
* ss (socket statistics)
* last
* and so on

## When nobody is accessing with ssh,
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

### When a user is remote-accessing the ssh server,
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
