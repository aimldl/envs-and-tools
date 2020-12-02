* Rev.2: 2020-12-02 (Wed)
* Rev.1: 2020-07-15 (Wed)
* Draft: 2020-06-22 (Mon)

# 우분투 18.04 설치하기 (Install Ubuntu 18.04)

## 설치 하기
* [003. 리눅스 운영체제 설치하기-Ubuntu Linux 설치](https://m.blog.naver.com/PostView.nhn?blogId=aimldl&logNo=221478627994&referrerCode=0&searchKeyword=linux)

## 패키지 설치하기
운영체제를 설치한 후에 필요한 프로그램의 패키지를 설치하는 Bash Script를 준비했습니다. 다운로드 받아서 실행하면 자동으로 설치가 진행됩니다.

```bash
$ sudo apt-get install -y software-properties-common
```

* 기본 패키지: [bash_scripts/install_ubuntu_basic_packages](./bash_scripts/install_ubuntu_basic_packages)
* 생산성 향상을 위한 패키지: [bash_scripts/install_ubuntu_productivity_packages](bash_scripts/install_ubuntu_productivity_packages)

* (필요 시) `NVIDIA Display Driver` 설치 하기 
NVIDIA GPU카드가 탑재된 컴퓨터는 `Display Driver`를 별도로 설치해야 합니다.
```bash
 $ sudo ubuntu-drivers autoinstall
 $ reboot
```
설치 여부는 
```bash
 $ nvidia-smi
```
명령어를 써서 그래픽카드가 인식되었는지 확인하면 됩니다. 안 됐을 경우엔 에러메세지가 발생합니다.

자세한 내용은 [Install NVIDIA Graphics Card Driver on Ubuntu Automatically](../technical_skills/computing_environments/gpgpu/how_to/install_nvidia_graphics_card_driver_automatically.md)를 참고하세요.
