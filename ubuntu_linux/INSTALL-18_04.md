* Rev.2: 2020-12-02 (Wed)
* Rev.1: 2020-07-15 (Wed)
* Draft: 2020-06-22 (Mon)

# 우분투 18.04 설치하기 (Install Ubuntu 18.04)

## 설치 하기
* [003. 리눅스 운영체제 설치하기-Ubuntu Linux 설치](https://m.blog.naver.com/PostView.nhn?blogId=aimldl&logNo=221478627994&referrerCode=0&searchKeyword=linux)

## 사용할 패키지 설치하기
사용할 프로그램의 패키지를 설치하는 작업이 남았습니다. 다음 명령어를 실행하거나 자동으로 실행해주는 기본 패키지 설치용 Bash script를 다운로드 받아서 실행합니다.
* 기본 패키지: [bash_scripts/install_ubuntu_basic_packages](./bash_scripts/install_ubuntu_basic_packages)

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

첫 명령어는 운영체제의 패키지 중 업그레이드된 것을 설치해서 모든 패키지를 최신 버전으로 유지시켜줍니다.
```bash
$ sudo apt-get update && sudo apt-get upgrade -y
```

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
