* Draft: 2021-02-16 (Tue)

# 인터넷이 없는 컴퓨터에 `x11-xserver-utils` 설치하기

## 관련 글

* [`/var/cache/apt/archives/`의 파일을 비우는 방법](clean_var_cache_apt_archive.md)

* [How to Manually Install a Deb Package Using Command Line in Ubuntu](https://linuxhint.com/manual_install_deb_package_cli_ubuntu/)



Google search: how to manually install x11-xserver-utils and dependencies

* [Manually compiling and installing Xorg libraries](https://edzeame.wordpress.com/2012/09/18/112/)

> **How to uninstall/remove x11-xserver-utils from Ubuntu 12.04 LTS?**
>
> Now we will see the commands for uninstalling the x11-xserver-utils from Ubuntu 12.04 LTS. For uninstalling this package you can easily use the apt command and remove the package from Linux Operating System.
>
> To remove the x11-xserver-utils following command is used:
>
> ```
> sudo apt-get remove  x11-xserver-utils
> ```
>
> Following command is used to remove the x11-xserver-utils package along with its dependencies:
>
> ```
> sudo apt-get remove --auto-remove x11-xserver-utils
> ```
>
> This will remove x11-xserver-utils and all its dependent packages which is no longer needed in the system.
>
> **Completely removing x11-xserver-utils with all configuration files:**
>
> Following command should be used with care as it deletes all the configuration files and data:
>
> ```
> sudo apt-get purge x11-xserver-utils
> ```
>
> or you can use following command also:
>
> ```
> sudo apt-get purge --auto-remove x11-xserver-utils
> ```
>
> Above command will remove all the configuration files and data associated with x11-xserver-utils package. You can can't recover the delete data, so, use this command with care.

[Install x11-xserver-utils on Ubuntu: sudo apt-get install x11-xserver-utils](https://www.devmanuals.net/install/ubuntu/ubuntu-12-04-lts-precise-pangolin/install-x11-xserver-utils.html)



```bash
$ sudo apt purge --auto-remove x11-xserver-utils
```

로 이 패키지와 dependencies, 설정 등을 모두 제거합니다.

```bash
[sudo] k8smaster의 암호: 
패키지 목록을 읽는 중입니다... 완료
의존성 트리를 만드는 중입니다       
상태 정보를 읽는 중입니다... 완료
다음 패키지를 지울 것입니다:
  gdm3* libass9* libavdevice57* libavfilter6* libbs2b0* libflite1* libmysofa0* libnorm1*
  libopenal-data* libopenal1* libpgm-5.2-0* libpostproc54* librubberband2* libsdl2-2.0-0* libzmq5*
  ubuntu-desktop* x11-xserver-utils* xorg*
0개 업그레이드, 0개 새로 설치, 18개 제거 및 10개 업그레이드 안 함.
이 작업 후 38.2 M바이트의 디스크 공간이 비워집니다.
W: Target Packages (Packages) is configured multiple times in /etc/apt/sources.list:52 and /etc/apt/sources.list.d/cuda.list:1
W: Target Translations (ko_KR) is configured multiple times in /etc/apt/sources.list:52 and /etc/apt/sources.list.d/cuda.list:1
W: Target Translations (ko) is configured multiple times in /etc/apt/sources.list:52 and /etc/apt/sources.list.d/cuda.list:1
W: Target Translations (en) is configured multiple times in /etc/apt/sources.list:52 and /etc/apt/sources.list.d/cuda.list:1
계속 하시겠습니까? [Y/n] y
(데이터베이스 읽는중 ...현재 254176개의 파일과 디렉터리가 설치되어 있습니다.)
Removing ubuntu-desktop (1.417.5) ...
Removing gdm3 (3.28.3-0ubuntu18.04.6) ...
Removing libavdevice57:amd64 (7:3.4.8-0ubuntu0.2) ...
Removing libavfilter6:amd64 (7:3.4.8-0ubuntu0.2) ...
Removing libass9:amd64 (1:0.14.0-1) ...
Removing libbs2b0:amd64 (3.1.0+dfsg-2.2) ...
Removing libflite1:amd64 (2.1-release-1) ...
Removing libmysofa0:amd64 (0.6~dfsg0-3+deb10u1build1) ...
Removing libzmq5:amd64 (4.2.5-1ubuntu0.2) ...
Removing libnorm1:amd64 (1.5r6+dfsg1-6) ...
Removing libopenal1:amd64 (1:1.18.2-2) ...
Removing libopenal-data (1:1.18.2-2) ...
Removing libpgm-5.2-0:amd64 (5.2.122~dfsg-2) ...
Removing libpostproc54:amd64 (7:3.4.8-0ubuntu0.2) ...
Removing librubberband2:amd64 (1.8.1-7ubuntu2) ...
Removing libsdl2-2.0-0:amd64 (2.0.8+dfsg1-1ubuntu1.18.04.4) ...
Removing xorg (1:7.7+19ubuntu7.1) ...
Removing x11-xserver-utils (7.7+7build1) ...
Processing triggers for man-db (2.8.3-2ubuntu0.1) ...
Processing triggers for hicolor-icon-theme (0.17-2) ...
Processing triggers for libc-bin (2.27-3ubuntu1.4) ...
(데이터베이스 읽는중 ...현재 253902개의 파일과 디렉터리가 설치되어 있습니다.)
Purging configuration files for gdm3 (3.28.3-0ubuntu18.04.6) ...
'gdm' 사용자 제거 중...
경고: 'gdm'그룹이 회원목록에 더이상 없음.
완료.
Purging configuration files for libopenal-data (1:1.18.2-2) ...
Purging configuration files for x11-xserver-utils (7.7+7build1) ...
Processing triggers for systemd (237-3ubuntu10.44) ...
Processing triggers for dbus (1.12.2-1ubuntu1.2) ...
Processing triggers for ureadahead (0.100.0-21) ...
ureadahead will be reprofiled on next reboot
$
```

