* Rev.2: 2020-12-08 (Tue)

* Rev.1: 2020-06-24 (Wed)
* Draft: 2019-05-22 (Wed)

# Install Gimp on Ubuntu (18.04)

## Commands to install Gimp 

### Ubuntu 20.04

but `snap` installs gimp successfully.

```bash
$ sudo snap install gimp
```

Note `apt` fails. The series of `set` commands used for Ubuntu 18.04 fails on Ubuntu 20.04 due to package dependencies as of 2020-12-08. 

```bash
$ sudo apt install gimp
  ...
다음 패키지의 의존성이 맞지 않습니다:
 gimp : 의존: libgimp2.0 (>= 2.10.18) 하지만 %s 패키지를 설치하지 않을 것입니다
        의존: libgimp2.0 (<= 2.10.18-z) 하지만 %s 패키지를 설치하지 않을 것입니다
        의존: libgegl-0.4-0 (>= 0.4.22) 하지만 %s 패키지를 설치하지 않을 것입니다
E: 문제를 바로잡을 수 없습니다. 망가진 고정 패키지가 있습니다.
$
```

### Ubuntu 18.04

```bash
$ sudo add-apt-repository ppa:otto-kesselgulasch/gimp
$ sudo apt-get update
$ sudo apt-get install -y gimp
```

## Verify the Installation

### On terminal

```bash
$ gimp &
```

### On `Show Applications`

or go to `Show Applications` and search for `gimp`

<img src="images/ubuntu_18_04-show_applications-search_box-gimp.png">

GIMP is launched as follows.

<img src="images/gimp-initial_launch.png">



## Uninstall

```bash
$ sudo apt-get autoremove gimp gimp-plugin-registry
```

## References

* [How to Install GIMP 2.10 on Ubuntu 18.04 LTS](https://tecadmin.net/install-gimp-on-ubuntu/)
* [[Linux] 포토샵 대용 프로그램인 Gimp 설치하기](https://m.blog.naver.com/PostView.nhn?blogId=aimldl&logNo=221543659176&referrerCode=0&searchKeyword=linux)