* Rev.1: 2020-11-21 (Sat)
* Draft: 2020-11-19 (Thu)

# XMind 2020를 우분투 리눅스에 설치하기

## 개요 (Overview)

마인드 매핑 도구인 XMind의 최신 버전 XMind 2020를 설치해봅니다. 

* 설치 환경: 리눅스

XMind 2020와 XMind 8 모두 무료 버전이 있습니다만 XMind 2020를 선택한 이유는 두 가지 입니다.

* 최신 버전이므로 몇 가지 유용한 기능들이 더 추가 되었습니다.
  * CJK폰트 지원으로 한국어를 쓰는게 편리해졌습니다.
  * 모바일에서도 지원합니다.
* 설치가 보다 간편합니다.
  * XMind 8은 리눅스에 설치할 때 JVM 버전 등의 이슈로 수동으로 에러를 수정하여 설정을 변경해야 하는 번거로움이 있었습니다.
    * [XMind 8 suddenly stopped working on Ubuntu 18.04 LTS after .ini fix](https://askubuntu.com/questions/1138225/xmind-8-suddenly-stopped-working-on-ubuntu-18-04-lts-after-ini-fix)
    * [Error unable to start XMind in Linux](https://www.danieblog.com/technology/software/error-unable-to-start-xmind-in-linux-67.html)
  * XMind 2020는 설치 명령어 한 줄로 깔끔하게 설치가 가능합니다.

XMind 8의 설치에 관해서는 아래 링크를 참고하세요.

* https://www.xmind.net/download/xmind8
* [How to install XMind 8 on generic Linux](https://www.xmind.net/m/PuDC/)

## 설치 파일 다운로드 하기

설치 파일은 두 가지 경로로 받을 수 있습니다. 

* XMind 2020 페이지
* XMind Download 페이지

### XMind 2020 페이지 https://www.xmind.net/xmind2020/

우분투 리눅스에서 크롬 웹브라우저를 써서 XMind 2020 페이지에 접속해서 `Free Download`를 클릭할 경우 .rpm파일을 받게 됩니다.

<img src='images/xmind-homepage-xmind2020_page.png'>

`XMind-2020-for-Linux-x86-64bit-10.2.1-202008051959.rpm`

### XMind Download 페이지 https://www.xmind.net/download/

우분투의 패키지 매니저는 .deb를 주로 사용하므로 XMind Download 페이지에 가서 .deb파일을 다운로드 받습니다.

<img src='images/xmind-homepage-download_page.png'>

* Linux (deb): `XMind-2020-for-Linux-amd-64bit-10.2.1-202008051959.deb`
* Linux (rpm): `XMind-2020-for-Linux-x86-64bit-10.2.1-202008051959.rpm`
  

## 다운로드 받은 파일로 XMind 2020 설치하기

`다운로드` 폴더에 설치파일이 다운로드 되어 있을 경우, 해당 폴더로 이동해서 `sudo dpkg -i` 명령어를 써서 프로그램을 설치합니다.

```bash
$ cd 다운로드
$ ls
XMind-2020-for-Linux-amd-64bit-10.2.1-202008051959.deb
$ sudo dpkg -i <installation_file>
```

`<installation_file>`이 `XMind-2020-for-Linux-amd-64bit-10.2.1-202008051959.deb`일 경우, 명령어는 아래와 같습니다. 전체 출력 메세지를 아래에 표시했습니다. `sudo` 명령어를 썼으므로 사용자 암호를 입력해야 합니다.

```bash
$ sudo dpkg -i XMind-2020-for-Linux-amd-64bit-10.2.1-202008051959.deb 
[sudo] aimldl의 암호: 
Selecting previously unselected package xmind-vana.
(데이터베이스 읽는중 ...현재 218775개의 파일과 디렉터리가 설치되어 있습니다.)
Preparing to unpack XMind-2020-for-Linux-amd-64bit-10.2.1-202008051959.deb ...
Unpacking xmind-vana (10.2.1-202008051959) ...
xmind-vana (10.2.1-202008051959) 설정하는 중입니다 ...
Processing triggers for hicolor-icon-theme (0.17-2) ...
Processing triggers for gnome-menus (3.13.3-11ubuntu1.1) ...
Processing triggers for desktop-file-utils (0.23-1ubuntu3.18.04.2) ...
Processing triggers for mime-support (3.60ubuntu1) ...
$
```

설치는 아주 빨리 진행되었습니다.

## 설치 확인하기

`프로그램 표시`를 클릭한 후

<img src='images/ubuntu-activities-kr.png'>

 검색 창에 `xmind`를 입력하면 아이콘 및 관련 내용을 볼 수 있습니다.

<img src='images/ubuntu-activities-kr-search_xmind.png'>

`XMind` 아이콘을 클릭하면 프로그램이 실행됩니다.

## 다음
* [XMind 2020 프로그램 시작하기](LAUNCH.md)
