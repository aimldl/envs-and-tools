* Draft: 2020-06-22 (Mon)

# Install Ubuntu 18.04
Find an Ubuntu installation manual and install it. There are a lot of such manuals.

[003. 리눅스 운영체제 설치하기-Ubuntu Linux 설치](https://m.blog.naver.com/PostView.nhn?blogId=aimldl&logNo=221478627994&referrerCode=0&searchKeyword=linux)

## Install some basic packages for Ubuntu
[bash_scripts/install_ubuntu_basic_packages](./bash_scripts/install_ubuntu_basic_packages) is a bash script that automatically installs some basic packages for Ubuntu. 

### Update & upgrade Ubuntu

You should always update your system first before you do anything else. Run the following commands:

```bash
$ apt-get update && apt-get upgrade
```

## Install the required package

```bash
$ sudo apt-get install -y software-properties-common
```

## References

* [003. 리눅스 운영체제 설치하기-Ubuntu Linux 설치](https://m.blog.naver.com/PostView.nhn?blogId=aimldl&logNo=221478627994&referrerCode=0&searchKeyword=linux)
