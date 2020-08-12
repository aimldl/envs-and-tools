* Rev.2: 2020-08-12 (Wed)
* Rev.1: 2020-08-11 (Tue)
* Draft: 2020-03-24 (Tue)

# Uninstall docker on Ubuntu

## Uninstall the old versions of Docker

```
$ sudo apt-get remove docker docker-engine docker.io
  ...
$
```

## Uninstall Docker

This part is an excerpt from [How to completely uninstall docker](https://askubuntu.com/questions/935569/how-to-completely-uninstall-docker).

Step 1. Identify the installed packages

```bash
$ dpkg -l | grep -i docker
ii  docker.io                                  19.03.6-0ubuntu1~18.04.1                         amd64        Linux container runtime
$
```

Step 2. Remove the installed packages.

```bash
$ sudo apt-get purge -y docker-engine docker docker.io docker-ce
$ sudo apt-get autoremove -y --purge docker-engine docker docker.io docker-ce
```

Step 3. Remove the remnants. 

The commands in step 2 will not remove images, containers, volumes, or user created configuration files on your host. If you wish to delete all images, containers, and volumes run the following commands:

```bash
$ sudo rm -rf /var/lib/docker /etc/docker
$ sudo rm /etc/apparmor.d/docker
$ sudo groupdel docker
$ sudo rm -rf /var/run/docker.sock
```
