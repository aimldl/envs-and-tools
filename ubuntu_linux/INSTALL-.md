* Rev.1: 2020-12-01 (Tue)
* Draft: 2020-06-22 (Mon)

# 우분투 리눅스 설치하기 (How to Install Ubuntu Linux)
## 개요
우분투 리눅스의 설치 과정은 크게 아래의 단계로 나뉩니다.

* 운영 체제의 설치
  * 우분투 리눅스 설치 준비하기 or 설치용 USB 메모리 만들기
  * 우분투 리눅스 설치하기
* 필수 소프트웨어 설치
* 사용할 소프트웨어 설치
* 시스템 설정

윈도우즈/우분투 듀얼부트 시스템을 구축할 경우 [Ubuntu 20.04와 Windows10를 듀얼 부트로 설치하기](INSTALL-dual_boot_system.md)를 참고하세요. 

## Step 1. 운영 체제의 설치
운영 체제의 설치과정은 유사하나 버전 별로 화면구성 등에서 약간의 차이가 있습니다. 각 버전의 설치는 아래의 링크를 참고하세요.
* 우분투 20.04의 설치: [INSTALL-20_04.md](INSTALL-20_04.md)
* 우분투 18.04의 설치: * [003. 리눅스 운영체제 설치하기-Ubuntu Linux 설치](https://m.blog.naver.com/PostView.nhn?blogId=aimldl&logNo=221478627994&referrerCode=0&searchKeyword=linux)

설치가 완료되면 설치된 운영 체제로 부팅할 수 있습니다.

## Step 2. 사용할 패키지의 설치
사용할 프로그램의 패키지를 설치하는 작업이 남았습니다. 다음 명령어를 실행하거나 자동으로 실행해주는 기본 패키지 설치용 Bash script를 다운로드 받아서 실행합니다.
* 기본 패키지: [bash_scripts/install_ubuntu_basic_packages](./bash_scripts/install_ubuntu_basic_packages)

그 외에도
* 생산성 향상을 위한 패키지: [bash_scripts/install_ubuntu_productivity_packages](bash_scripts/install_ubuntu_productivity_packages)

* (필요 시) `NVIDIA Display Driver` 설치 하기 
NVIDIA GPU카드가 탑재된 컴퓨터는 `Display Driver`를 별도로 설치해야 합니다.
```bash
 $ sudo ubuntu-drivers autoinstall
 $ reboot
```
설치 확인은
```bash
 $ nvidia-smi
```
명령어를 실행 후 그래픽카드의 인식 여부를 확인합니다. 인식이 안 됐을 경우엔 에러메세지가 발생합니다. 자세한 내용은 [Install NVIDIA Graphics Card Driver on Ubuntu Automatically](../technical_skills/computing_environments/gpgpu/how_to/install_nvidia_graphics_card_driver_automatically.md)를 참고하세요.

## 부록.
### 기본 패키지의 명령어 모음 [bash_scripts/install_ubuntu_basic_packages](./bash_scripts/install_ubuntu_basic_packages)
```bash
sudo apt update && sudo apt-get upgrade -y
sudo apt-get install -y software-properties-common
sudo apt install -y build-essential
sudo apt install -y cmake
sudo apt install -y git
sudo apt-get install -y python-dev python3-dev python-pip python3-pip
sudo apt install -y tree
sudo apt install -y vim
sudo apt install -y curl
sudo apt install -y screen
sudo apt install -y net-tools
sudo apt install -y pkg-config
wget https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
sudo apt install -y ./google-chrome-stable_current_amd64.deb
sudo add-apt-repository universe
sudo apt install -y gnome-tweak-tool
```
