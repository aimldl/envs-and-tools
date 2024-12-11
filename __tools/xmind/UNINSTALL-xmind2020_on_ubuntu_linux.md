* Draft: 2021-08-04 (Wed)

# How to Uninstall XMind 2020 from Ubuntu 18.04

Google search: how to uninstall xmind2020 on ubuntu
> * [Uninstall Xmind Zen](https://askubuntu.com/questions/1133548/uninstall-xmind-zen)
>   $ sudo apt-get purge xen*
>   $ sudo dpkg --remove xmind-vana

```bash
$ sudo apt purge -y xmind*
```
did the job.

I haven't tried the following command, but
```bash
$ sudo apt purge -y xmind-vana
```
may work as well.
