* Draft: 2020-11-16 (Mon)
# 우분투 리눅스에서 부팅 USB 만들기 (우분투 20.04용)

## 개요

우분투 리눅스에서 

* 우분투 리눅스 20.04 설치용 부팅USB를 만드는 방법을 설명합니다.
* 윈도우10과 MacOS용은 아래 내용을 참고하세요.

### 관련 검색 & 문서

Google search: make a bootable usb for ubuntu

* Ubuntu Linux: [Create a bootable USB stick on Ubuntu | Ubuntu](https://ubuntu.com/tutorials/create-a-usb-stick-on-ubuntu#1-overview) (영어)
* 윈도우10: 
  * 주의: WoeUSB를 써서 윈도우10 설치를 위한 부팅 USB를 우분투 리눅스 18.04에서 만들 수 없습니다.
  * 이유는 아래 문서를 참고하세요.
    * [how_to/create_a_bootable_usb_for_windows_10_in_ubuntu_linux.md](../../windows/how_to/create_a_bootable_usb_for_windows_10_in_ubuntu_linux.md)
    * [linux_commands/woeusb.md](linux_commands/woeusb.md)

* MacOS: [Create a bootable USB stick on macOS | Ubuntu](https://ubuntu.com/tutorials/create-a-usb-stick-on-macos) (영어)

## Ubuntu 20.04 시동 디스크를 만들기

1. USB 메모리를 준비합니다. 용량은 4GB 이상이 필요합니다.
2. 우분투 ISO파일을 다운로드 받습니다.
   
* [Download Ubuntu Desktop](https://ubuntu.com/download/desktop)
  
3. `시동 디스크 만들기` 프로그램을 시작합니다.

   프로그램 표시`에 들어가서 `시동 디스크 만들기`라는 검색어를 입력합니다.

<img src='images/ubuntu_linux_18_04-show_applications-startup_disk_creator-korean.png'>

​		`시동 디스크 만들기`의 화면입니다.

<img src='images/ubuntu_linux_18_04-startup_disk_creator-korean.png'>

​	USB메모리를 삽입하면 `사용할 디스크`에 자동으로 인식됩니다. 

<img src='images/ubuntu_linux_18_04-startup_disk_creator-with_usb-korean.png'>

`시동 디스크 만들기` 버튼을 클릭한 후 `Yes`를 누르면 인증을 위해 비밀번호를 입력을 받습니다.

<img src='images/ubuntu_linux_18_04-startup_disk_creator-create_window-korean.png'>

<img src='images/ubuntu_linux_18_04-startup_disk_creator-password_authentication-korean'>

비밀번호를 인증하면 디스크 이미지를 기록하기 시작합니다.

<img src='images/ubuntu_linux_18_04-startup_disk_creator-creating_2percentkorean'>

설치가 완료가 되면 `OK`버튼을 누르고

<img src='images/ubuntu_linux_18_04-startup_disk_creator-completed-korean.png'>

내용물을 확인합니다.

<img src='images/ubuntu_linux_18_04-files-ubuntu20_04_startup_usb.png'>


