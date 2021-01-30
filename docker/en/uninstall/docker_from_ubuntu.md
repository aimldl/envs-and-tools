* Rev.2: 2021-01-29 (Fri)
* Rev.1: 2020-08-12 (Wed)
* Draft: 2020-03-24 (Tue)

# How to Uninstall Docker from Ubuntu

* This document is tested on:
  * 19.03.6-0ubuntu1~18.04.1
  * 19.03.6-0ubuntu1~18.04.3

## Summary

[uninstall_docker_from_ubuntu](bash_scripts/uninstall_docker_from_ubuntu) is an executable Bash script:

```bash
## 1. Uninstall
##### Identify the installed packages and remove the installed packages
dpkg -l | grep -i docker
sudo apt-get purge -y docker-engine docker docker.io docker-ce
sudo apt-get autoremove -y --purge docker-engine docker docker.io docker-ce

## 2. Remove the remnants
##### Remove all images, containers, and volumes on your host
sudo rm -rf /var/lib/docker /etc/docker
sudo rm /etc/apparmor.d/docker
sudo groupdel docker
sudo rm -rf /var/run/docker.sock

## 3. Verify
##### Check if the `docker` command is purged
docker

printf "Check if docker does not exist in the list by running: \n \
  $ su - \${USER} \n \
  $ id -nG \n"
```

## 1. Uninstall

Identify the installed packages

```bash
$ dpkg -l | grep -i docker
ii  docker.io                                  19.03.6-0ubuntu1~18.04.3                         amd64        Linux container runtim
$
```

and remove the installed packages.

```bash
$ sudo apt-get purge -y docker-engine docker docker.io docker-ce
$ sudo apt-get autoremove -y --purge docker-engine docker docker.io docker-ce
```

You will see the following warning message becasue the above commands will not remove images, containers, volumes, or user created configuration files on your host.

```bash
dpkg: warning: while removing docker.io, directory '/etc/docker' not empty so not removed
```

## 2. Remove the remnants

Remove all images, containers, and volumes on your host

```bash
$ sudo rm -rf /var/lib/docker /etc/docker
$ sudo rm /etc/apparmor.d/docker
$ sudo groupdel docker
$ sudo rm -rf /var/run/docker.sock
```

Notice the first command removes everything in `/etc/docker` which takes care of the warning.

## 3. Verify

Check if the `docker` command is purged.

```bash
$ docker

Command 'docker' not found, but can be installed with:

sudo snap install docker     # version 19.03.11, or
sudo apt  install docker.io

See 'snap info docker' for additional versions.
$
```

Check if `docker` does not exist in the list by running:

```bash
$ su - ${USER}
password: 
$ id -nG
```

The expected output looks like this.

```bash
aimldl adm cdrom sudo dip plugdev lpadmin sambashare
$
```

## References

* [How to completely uninstall docker](https://askubuntu.com/questions/935569/how-to-completely-uninstall-docker).

## Appendix. The full message to run the Bash script

```bash
$ bash uninstall_docker_from_ubuntu 
```

outputs (in Korean)

```bash
ii  docker.io                                  19.03.6-0ubuntu1~18.04.3                         amd64        Linux container runtime
패키지 목록을 읽는 중입니다... 완료
의존성 트리를 만드는 중입니다       
상태 정보를 읽는 중입니다... 완료
패키지 'docker-engine'는 설치되어 있지 않아, 지우지 않았습니다.
패키지 'docker-ce'는 설치되어 있지 않아, 지우지 않았습니다.
패키지 'docker'는 설치되어 있지 않아, 지우지 않았습니다.
다음 패키지가 자동으로 설치되었지만 더 이상 필요하지 않습니다:
  bridge-utils cgroupfs-mount containerd pigz runc ubuntu-fan
Use 'sudo apt autoremove' to remove them.
다음 패키지를 지울 것입니다:
  docker.io*
0개 업그레이드, 0개 새로 설치, 1개 제거 및 3개 업그레이드 안 함.
이 작업 후 199 M바이트의 디스크 공간이 비워집니다.
(데이터베이스 읽는중 ...현재 199991개의 파일과 디렉터리가 설치되어 있습니다.)
Removing docker.io (19.03.6-0ubuntu1~18.04.3) ...
'/usr/share/docker.io/contrib/nuke-graph-directory.sh' -> '/var/lib/docker/nuke-graph-directory.sh'
Processing triggers for man-db (2.8.3-2ubuntu0.1) ...
(데이터베이스 읽는중 ...현재 199782개의 파일과 디렉터리가 설치되어 있습니다.)
Purging configuration files for docker.io (19.03.6-0ubuntu1~18.04.3) ...

Nuking /var/lib/docker ...
  (if this is wrong, press Ctrl+C NOW!)

+ sleep 10

+ rm -rf /var/lib/docker/builder /var/lib/docker/buildkit /var/lib/docker/containers /var/lib/docker/image /var/lib/docker/network /var/lib/docker/nuke-graph-directory.sh /var/lib/docker/overlay2 /var/lib/docker/plugins /var/lib/docker/runtimes /var/lib/docker/swarm /var/lib/docker/tmp /var/lib/docker/trust /var/lib/docker/volumes
dpkg: 경고: while removing docker.io, directory '/etc/docker' not empty so not removed
패키지 목록을 읽는 중입니다... 완료
의존성 트리를 만드는 중입니다       
상태 정보를 읽는 중입니다... 완료
패키지 'docker-engine'는 설치되어 있지 않아, 지우지 않았습니다.
패키지 'docker-ce'는 설치되어 있지 않아, 지우지 않았습니다.
패키지 'docker'는 설치되어 있지 않아, 지우지 않았습니다.
패키지 'docker.io'는 설치되어 있지 않아, 지우지 않았습니다.
다음 패키지를 지울 것입니다:
  bridge-utils* cgroupfs-mount* containerd* pigz* runc* ubuntu-fan*
0개 업그레이드, 0개 새로 설치, 6개 제거 및 3개 업그레이드 안 함.
이 작업 후 121 M바이트의 디스크 공간이 비워집니다.
(데이터베이스 읽는중 ...현재 199781개의 파일과 디렉터리가 설치되어 있습니다.)
Removing ubuntu-fan (0.12.10) ...
ubuntu-fan: removing default /etc/network/fan configuration
Removing bridge-utils (1.5-15ubuntu1) ...
Removing cgroupfs-mount (1.4) ...
Removing containerd (1.3.3-0ubuntu1~18.04.4) ...
Removing pigz (2.4-1) ...
Removing runc (1.0.0~rc10-0ubuntu1~18.04.2) ...
Processing triggers for man-db (2.8.3-2ubuntu0.1) ...
(데이터베이스 읽는중 ...현재 199674개의 파일과 디렉터리가 설치되어 있습니다.)
Purging configuration files for cgroupfs-mount (1.4) ...
Purging configuration files for containerd (1.3.3-0ubuntu1~18.04.4) ...
Purging configuration files for bridge-utils (1.5-15ubuntu1) ...
Purging configuration files for ubuntu-fan (0.12.10) ...
Processing triggers for systemd (237-3ubuntu10.44) ...
Processing triggers for ureadahead (0.100.0-21) ...
rm: '/etc/apparmor.d/docker'를 지울 수 없음: 그런 파일이나 디렉터리가 없습니다
uninstall_docker_from_ubuntu: 줄 23: docker: 명령어를 찾을 수 없음
Check if group does not exist in the list by running: 
   $ su - ${USER} 
   $ id -nG 
$
```



