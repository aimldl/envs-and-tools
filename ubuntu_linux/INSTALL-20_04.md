* Draft: 2020-11-14 (Sat)

# 우분투 데스크탑 20.04 설치하기 (Install Ubuntu Desktop 20.04)

## Step 1. 설치 파일 다운로드 하기
우분투 리눅스 20.04의 다운로드 페이지 [https://ubuntu.com/download](https://ubuntu.com/download)에 가면 몇 가지 선택사항이 있습니다.
* 우분투 데스크탑 (Ubuntu Desktop)
* 우분투 서버 (Ubuntu Server)
* 우분투 클라우드 (Ubuntu Cloud)
* IoT를 위한 우분투 (Ubuntu for IoT)
* 기타 우분투 종류들 (Ubuntu flavours)

<img src='images/ubuntu-different_options_for_installation.png'>

이 중 일반 데스크탑 혹은 랩탑 사용자를 위한 "우분투 데스크탑 (Ubuntu Desktop)"을 클릭하면, "우분투 데스크탑 다운로드 페이지"로 이동합니다. 직접 입력하려면
[https://ubuntu.com/download/desktop](https://ubuntu.com/download/desktop)를 웹브라우저의 주소창에 입력하면 됩니다.

우측의 다운로드 (Download) 버튼을 클릭하면

<img src='images/ubuntu-download_ubuntu_desktop.png'>

설치용 ISO파일의 다운로드가 시작됩니다. 다운로드가 완료되면 사용한 웹브라우저의 다온로드 폴더에 아래와 같은 파일이 보입니다.

<img src='images/ubuntu-ubuntu_20_04_1_desktop_amd64_iso.png'>

이로써 설치파일 다운로드가 완료되었습니다.

## Step 2. ISO파일로 Bootable USB를 생성합니다.


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
