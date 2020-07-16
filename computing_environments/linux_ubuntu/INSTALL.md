* Rev.1: 2020-07-15 (Wed)
* Draft: 2020-06-22 (Mon)

# Install Ubuntu 18.04
Find an Ubuntu installation manual and install it. There are a lot of such manuals.

[003. 리눅스 운영체제 설치하기-Ubuntu Linux 설치](https://m.blog.naver.com/PostView.nhn?blogId=aimldl&logNo=221478627994&referrerCode=0&searchKeyword=linux)

## Install some basic packages for Ubuntu
[bash_scripts/install_ubuntu_basic_packages](./bash_scripts/install_ubuntu_basic_packages) is a bash script that automatically installs some basic packages for Ubuntu. 

[bash_scripts/install_ubuntu_productivity_packages](bash_scripts/install_ubuntu_productivity_packages) installs some other packages other than the basic packages.

## (Optional) Set up the language settings

## (Optional) Install the NVIDIA Display Driver

```bash
 $ sudo ubuntu-drivers autoinstall
 $ reboot
```

 Verify the installation.

```bash
 $ nvidia-smi
```

 For details, refer to [Install NVIDIA Graphics Card Driver on Ubuntu Automatically](../technical_skills/computing_environments/gpgpu/how_to/install_nvidia_graphics_card_driver_automatically.md).

### Update & upgrade Ubuntu

You should always update your system first before you do anything else. Run the following commands:

```bash
$ sudo apt-get update && sudo apt-get upgrade -y
```

## Install the required package

```bash
$ sudo apt-get install -y software-properties-common
```

## References
* [003. 리눅스 운영체제 설치하기-Ubuntu Linux 설치](https://m.blog.naver.com/PostView.nhn?blogId=aimldl&logNo=221478627994&referrerCode=0&searchKeyword=linux)
