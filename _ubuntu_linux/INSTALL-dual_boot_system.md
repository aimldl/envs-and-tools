* Rev.1: 2020-12-01 (Tue)
* Draft: 2020-11-26 (Thu)

# Ubuntu 20.04와 Windows10를 듀얼 부트로 설치하기

## 개요

### 참고

* [How to install Ubuntu 20.04 alongside Windows 10 (Dual Boot)](https://linuxconfig.org/how-to-install-ubuntu-20-04-alongside-windows-10-dual-boot), 2020-05-13, Korbin Brown, LinuxConfig.org

## 듀얼 부트 시스템 설치하기

Step 1. OS 설치를 위한 USB 메모리 2개를 준비합니다.

Step 2. 윈도우10 설치용 USB 메모리를 생성합니다.

Step 3. 윈도우10을 설치합니다.

Step 4. Ubuntu 20.04 설치용 USB 메모리를 생성합니다.

Step 5. 윈도우10 위에 Ubuntu 20.04를 설치합니다.

## 듀얼 부트 시스템 설치 확인하기

Step 6. `GRUB 부트로더`에 듀얼 부트 시스템으로 설치되었는지 확인합니다.

* 듀얼 부트로 설치가 완료되면, 컴퓨터를 시작했을 때 `GRUB 부트로더`의 OS 선택 화면이 나옵니다. 
* 부트로더의 리스트에 설치한 OS인 Ubuntu와 Windows가 보이는지 확인합니다.
* 리스트의 예입니다. 

```bash
*Ubuntu
 Ubunty용 고급 설정
 Windows Boot Manager (/dev/sda1에 있는)
 UEFI Firmware Settings
```

Step 7. 기본 설정인 Ubuntu로 부팅해봅니다.

Step 8. Ubuntu에서 재부팅해서, `GRUB 부트로더`가 나오면 키보드의 방향키를 아래로 눌러서  `Windows Boot Manager`를 선택하고, 엔터키를 눌러서 Windows로 부팅해봅니다.

(필요 시) 기본 설정을 Windows로 변경할 수 있습니다.

## 듀얼 부트 시스템 사용하기

`GNU GRUB`의 OS 선택화면은 검정색 바탕에 흰색 글씨로 표현됩니다. 여기에서 방향키와 엔터키를 눌러서 원하는 운영체계를 선택할 수 있습니다.

```bash
*Ubuntu
 Ubunty용 고급 설정
 Windows Boot Manager (/dev/sda1에 있는)
 UEFI Firmware Settings
```

7초를 기다리면 기본 설정인 우분투 리눅스로 자동 부팅됩니다. Windows를 사용할 때는 방향키를 눌러서 `Windows Boot Manager`를 선택해야합니다.

```bash
 Ubuntu
 Ubunty용 고급 설정
*Windows Boot Manager (/dev/sda1에 있는)
 UEFI Firmware Settings
```



## 부록

관련 내용입니다.

## Google search: install dual boot windows 10 ubuntu

Can I install Windows 10 and Linux on the same computer?
First, choose your Linux distribution. Download it and create USB installation media or burn it to a DVD. Boot it on a PC already running Windows—you may need to mess with Secure Boot settings on a Windows 8 or Windows 10 computer. Launch the installer, and follow the instructions.Aug 3, 2015
Dual-booting Linux with Windows: What you need to know | PCWorld
https://www.pcworld.com/.../dual-booting-linux-with-windows-what-you-need-to-know....


Can I install Windows after Ubuntu?
It's easy to install dual OS, but if you install Windows after Ubuntu, Grub will be affected. Grub is a boot-loader for Linux base systems. You can follow the above steps or you can do just the following: Make space for your Windows from Ubuntu.May 1, 2012
grub2 - How to install Windows 7 after Ubuntu and dual boot? - Ask ...
https://askubuntu.com/questions/.../how-to-install-windows-7-after-ubuntu-and-dual-boo...

Always install Linux after Windows

When you install Linux after Windows, the Linux installer knows how to deal with Windows, resize its partition, and set up a boot loader with an option allowing you to choose Windows at boot time.

When you install Windows after Linux, Windows ignores Linux, doesn’t know how to resize its partitions, and overwrites the Linux boot loader with its own. You’ll have to repair the Linux system’s boot loader before you can boot back into your Linux system again. 

You can always just reinstall Linux, too. But it’s best just to install Linux after Windows.

라이센스
How to Get Windows 10 for Free (or Under $30), https://www.tomshardware.com/reviews/get-windows-10-free-or-cheap,5717.html
by Scharon Harding April 19, 2019 at 12:27 PM

가격: 홈 정가=₩208,000(VAT 포함), 특가=₩166,400 (교직원)

구글 검색: download windows 10
다운로드 페이지: https://www.microsoft.com/ko-kr/software-download/windows10ISO
"64-bit 다운로드"를 선택하면, ISO파일을 다운로드 받음.
주의:
(1) October 2018 Update와 (2) April 2018 Update
최신버전인 (1)을 선택하면 파일 사이즈가 5.1GB로 DVD에 들어가지 않음.
(Win10_1809Oct_v2_Korean_x64.iso, 5.1GB) 
더 오래된 버전인 (2)의 파일 사이즈는 4.4GB로 DVD에 들어감.
(Win10_1803_Korean_x64.iso, 4.4GB)

## ISO파일에서 DVD로 굽기
물론

구글 검색: how to make a bootable windows 10 dvd from iso from ubuntu
검색 결과: 마땅한 것을 탑10에서 찾을 수 없음! 검색어 변경

구글 검색: how to burn an iso to dvd on ubuntu 18.04
참고 문서: How to burn a DVD on Ubuntu, https://tutorials.ubuntu.com/tutorial/tutorial-burn-a-dvd-on-ubuntu#0

DVD 설치 소프트웨어 설치
Brasero, K3b, Xfburn

3. Install DVD burning software, https://tutorials.ubuntu.com/tutorial/tutorial-burn-a-dvd-on-ubuntu#2
4. Burn the DVD (with Brasero), https://tutorials.ubuntu.com/tutorial/tutorial-burn-a-dvd-on-ubuntu#3

문제
한국어 버전은 5.1GB이고 공 DVD는 4.7GB라고 에러가 뜸.
"빈 디스크 (DVD-R): 빈 공간이 부족합니다"
다른 CD나 DVD를 선택하거나 새 CD나 DVD를 넣으십시오.
데이터 크기가 디스크 용량보다(오버버닝 옵션을 사용하더라도) 큽니다.

해결
(1) October 2018 Update와 (2) April 2018 Update 중 더 오래된 "April 2018 Update"를 선택
파일 사이즈: (1)는 5.1GB, (2)는 4.4GB (DVD-R의 용량은 4.7GB)