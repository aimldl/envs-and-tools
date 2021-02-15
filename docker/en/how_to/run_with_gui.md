

## Summary

```bash
$ sudo apt install -y x11-xserver-utils
```



```bash
$ xhost +local:docker
non-network local connections being added to access control list
$
```

```bash
$ docker run -it --gpus all -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix:ro aimldl/darknet:gpu_cudnn_opencv_ver0.2 bash
#
```

```bash
# xclock
```

을 실행하면 잘 됩니다.





> 우분투는 `Xorg`라는 그래픽 프로그램을 이용한다. 즉, 얘가 있어야 그래픽을 띄워줄 수 있다는 얘기.그럼 도커에서 그래픽을 띄워주려면? 호스트의 자원을 공유하면 된다. 호스트의 Xorg를 컨테이너가 이용하면 된다는 말.
>
> 실행옵션을 추가해주면 컨테이너에서도 그래픽을 볼 수 있다.
>
>  도커를 gui로 실행하는 방법은 두 가지가 있다. 1. VNC를 이용하거나 2. 단순히 XServer를 공유하거나.
>
> VNC를 이용하는 방법은 여기와 여기를 참고하자. Xauthority 어쩌구저쩌구한다. (더보기)
>
> Xserver를 공유하는 방법이 더 간편하다.
>
> #### XServer 공유하기
>
> host의 XServer를 볼륨형태로 컨테이너와 공유하자. *DISPLAY* 환경 변수도 전달해줘야 한다.
>
> 유닉스 도메인 소켓을 이용하여 host의 XServer와 도커 컨테이너를 연결한다. readonly옵션을 준다.
>
> XServer소켓은 `/tmp/.X11-unix`에 존재한다.

```bash
--volume /tmp/.X11-unix:/tmp/.X11-unix:ro-e DISPLAY=unix$DISPLAY
```

>  호스트에서 도커가 xserver와 통신할 수 있도록 설정한다. 다른 터미널을 열고 작업한다.
>
> ```bash
> $ xhost +local:docker
> ```
>
> 이제 GUI로 도커 이미지를 실행할 수 있다.
>
> 출처: https://conservative-vector.tistory.com/entry/docker에서-컨테이너-gui-실행하기 [에움길]

[Running GUI Applications inside Docker Containers](https://medium.com/@SaravSun/running-gui-applications-inside-docker-containers-83d65c0db110), 2018-02-05, Medium, Saravanan Sundaramoorthy



## Prerequisites

### X11

```bash
$ echo $DISPLAY
:0
$
```

```bash
$ echo $XAUTHORITY
/run/user/1000/gdm/Xauthority
$
```

```bash
$ ls /tmp/.X11-unix
X0
$
```

```bash
$ id
uid=1000(k8smaster) gid=1000(k8smaster) 그룹들=1000(k8smaster),4(adm),24(cdrom),27(sudo),30(dip),46(plugdev),116(lpadmin),126(sambashare),129(docker)
$
```

```bash
$ id --user
1000
$ id --group
1000
$
```

```bash
$ id --help
Usage: id [OPTION]... [USER]
Print user and group information for the specified USER,
or (when USER omitted) for the current user.

  -a             ignore, for compatibility with other versions
  -Z, --context  print only the security context of the process
  -g, --group    print only the effective group ID
  -G, --groups   print all group IDs
  -n, --name     print a name instead of a number, for -ugG
  -r, --real     print the real ID instead of the effective ID, with -ugG
  -u, --user     print only the effective user ID
  -z, --zero     delimit entries with NUL characters, not whitespace;
                   not permitted in default format
      --help     이 도움말을 표시하고 끝냅니다
      --version  버전 정보를 출력하고 끝냅니다

옵션이 없으면, 약간의 유용한 식별된 정보 집합을 출력
  ..
$
```



### Docker options

`-e`, `--env`

`-e DISPLAY`, `--env="DISPLAY"`

`-v`, `--volume`

## Problem

```bash
Error: Can't open display: :0
```

## Hint

Google search: docker can't open x display

Google search: ubuntu docker how to run xclock

* [Is it possible to run Docker container and show its graphical application window on host?](https://askubuntu.com/questions/1161646/is-it-possible-to-run-docker-container-and-show-its-graphical-application-window)

* [Ubuntu – Is it possible to run Docker container and show its graphical application window on host](https://itectec.com/ubuntu/ubuntu-is-it-possible-to-run-docker-container-and-show-its-graphical-application-window-on-host/)



```bash
$ docker run -it -e DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix --user="$(id --user):$(id --group)" cuda_with_x11 bash
groups: cannot find name for group ID 1000
I have no name!@64994096281a:/$ xclock

```

```bash
$ docker run -it -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY cuda_with_x11 bash
root@49fc725be2b7:/# ls
bin   dev  home  lib64  mnt  proc  run   srv  tmp  var
boot  etc  lib   media  opt  root  sbin  sys  usr
root@49fc725be2b7:/# xclock
No protocol specified
Error: Can't open display: :0
root@49fc725be2b7:/# exit
exit
$
```

Google search: ubuntu how to install xclock

> ## xclock
>
> X applications
>
> Debian  Ubuntu  Raspbian  Kali Linux
>
> ```bash
> apt-get install x11-apps
> ```
>
>  Arch Linux
>
> ```bash
> pacman -S xorg-xclock
> ```
>
>  CentOS
>
> ```bash
> yum install xorg-xclock
> ```
>
>  Fedora
>
> ```bash
> dnf install xorg-xclock
> ```
>
> Source: https://command-not-found.com/xclock



Naver search: 우분투 도커에서 GUI 사용하기

* [Docker, 우분투에서 YOLO3 사용](https://blog.naver.com/tiled12/222028655760)
* [docker로 ubuntu를 desktop처럼 돌리기](https://lovemewithoutall.github.io/it/ubuntu-vnc-desktop/)