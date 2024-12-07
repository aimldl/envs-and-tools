* Rev.1: 2021-06-09 (Wed)
* Draft: 2021-04-06 (Tue)

# How to Change `hostname` on Ubuntu

## Summary

```bash
$ sudo hostnamectl set-hostname <hostname>
$ sudo reboot
```

## Contents

Google search: ubuntu how to change hostname

* [Ubuntu 18.04 LTS change hostname permanently](https://www.cyberciti.biz/faq/ubuntu-18-04-lts-change-hostname-permanently/)
* [How To Change Hostname On Ubuntu 20.04](https://phoenixnap.com/kb/ubuntu-20-04-change-hostname)

* How to Check Current Hostname on Ubuntu 20.04

```bash
$ hostname
$ hostnamectl
```

* Temporarily change hostname (Reboot not required)

```bash
$ sudo hostname new-hostname
```

* Permanently change the hostname (Reboot required)

```bash
$ sudo hostnamectl set-hostname <new_hostname>
$ sudo nano /etc/hosts
$ sudo reboot
```

To do it manually, open the following files and edit the old host name to a new one.

```bash
/etc/hostname
/etc/hosts
```

For example, change `ubuntu` to `new-hostname`.

| File          | Before                                                       | After                                                        |
| ------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| /etc/hostname | ubuntu                                                       | new-hostname                                                 |
| /etc/hosts    | 127.0.0.1 localhost<br/>127.0.0.1 ubuntu<br/><br/># The following lines are desirable for IPv6 capable hosts<br/>::1 ip6-localhost ip6-loopback<br/>fe00::0 ip6-localnet<br/>ff00::0 ip6-mcastprefix<br/>ff02::1 ip6-allnodes<br/>ff02::2 ip6-allrouters<br/>ff02::3 ip6-allhosts | 127.0.0.1 localhost<br/>127.0.0.1 new-hostname<br/><br/># The following lines are desirable for IPv6 capable hosts<br/>::1 ip6-localhost ip6-loopback<br/>fe00::0 ip6-localnet<br/>ff00::0 ip6-mcastprefix<br/>ff02::1 ip6-allnodes<br/>ff02::2 ip6-allrouters<br/>ff02::3 ip6-allhosts |

