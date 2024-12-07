* Draft: 2021-02-15 (Mon)

#

Google search: ubuntu how to download a package

* [How to download package not install it with apt-get command?](https://unix.stackexchange.com/questions/408346/how-to-download-package-not-install-it-with-apt-get-command)

> Use `--download-only`:
>
> ```bash
> sudo apt-get install --download-only pppoe
> ```
>
> This will download `pppoe` and any dependencies you need, and place them in `/var/cache/apt/archives`. That way a subsequent `apt-get install pppoe` will be able to complete without any extra downloads.
>
> - Can you think of a way to specify the output directory for the downloaded package? – [Shuzheng](https://unix.stackexchange.com/users/128739/shuzheng) [Dec 19 '19 at 11:37](https://unix.stackexchange.com/questions/408346/how-to-download-package-not-install-it-with-apt-get-command#comment1036896_408348) 
>
> - I've considered `apt-get download <package>`, but it doesn't download dependencies. – [Shuzheng](https://unix.stackexchange.com/users/128739/shuzheng) [Dec 19 '19 at 11:55](https://unix.stackexchange.com/questions/408346/how-to-download-package-not-install-it-with-apt-get-command#comment1036904_408348)
>
> - You should be able to change it by modifying `Dir::Cache` and `Dir::Cache::archives`, with the `-o` option. – [Stephen Kitt](https://unix.stackexchange.com/users/86440/stephen-kitt) [Dec 19 '19 at 17:36](https://unix.stackexchange.com/questions/408346/how-to-download-package-not-install-it-with-apt-get-command#comment1037016_408348)
>
> - Does not seem to work if the package is already installed – [Alexey](https://unix.stackexchange.com/users/54221/alexey) [Jun 26 '20 at 12:53](https://unix.stackexchange.com/questions/408346/how-to-download-package-not-install-it-with-apt-get-command#comment1110775_408348)
>
> - @Alexey yes, see [this answer](https://unix.stackexchange.com/a/313117/86440) for situations where the target package is already installed. – [Stephen Kitt](https://unix.stackexchange.com/users/86440/stephen-kitt) [Jun 26 '20 at 13:03](https://unix.stackexchange.com/questions/408346/how-to-download-package-not-install-it-with-apt-get-command#comment1110779_408348)

> Use this command:
>
> ```bash
> apt-get download pppoe
> ```
>
> This command let you download the package into the current directory.
>
> For accessing installed `.deb` files, you can look in this path:
>
> ```bash
> /var/cache/apt/archives
> ```

> This *doesn’t* download dependencies, it only downloads the packages named in the arguments. – [Stephen Kitt](https://unix.stackexchange.com/users/86440/stephen-kitt) [Dec 2 '17 at 15:09](https://unix.stackexchange.com/questions/408346/how-to-download-package-not-install-it-with-apt-get-command#comment731323_408359)

> To expand on Hamid's answer slightly, any of these three very similar commands will work if your only desire is to only download the specified package, and *nothing else*. (Your use case is not clearly stated, so it's unclear if that is what you want to do.) They all download the Debian binary package file corresponding to the specified binary Debian package to the current directory. Note that these commands will download only the binary package specified, and none of its dependencies. If you want the dependencies as well, use [the answer provided by Stephen Kitt](https://unix.stackexchange.com/a/408348/4671).
>
> ```bash
> apt-get download ppoe
> apt download ppoe
> aptitude download ppoe
> ```

## `x11-xserver-utils` 다운로드 받기

```bash
$ sudo apt install --download-only x11-xserver-utils
[sudo] k8smaster의 암호: 
패키지 목록을 읽는 중입니다... 완료
의존성 트리를 만드는 중입니다       
상태 정보를 읽는 중입니다... 완료
패키지 x11-xserver-utils는 이미 최신 버전입니다 (7.7+7build1).
다음 패키지가 자동으로 설치되었지만 더 이상 필요하지 않습니다:
  libass9 libavdevice57 libavfilter6 libbs2b0 libflite1 libmysofa0 libnorm1 libopenal-data
  libopenal1 libpgm-5.2-0 libpostproc54 librubberband2 libsdl2-2.0-0 libzmq5
Use 'sudo apt autoremove' to remove them.
0개 업그레이드, 0개 새로 설치, 0개 제거 및 10개 업그레이드 안 함.
$
```

```bash
$ ls /var/cache/apt/archives | grep xserver
xserver-xorg-video-nvidia-450_450.102.04-0ubuntu1_amd64.deb
xserver-xorg-video-nvidia-460_460.32.03-0ubuntu1_amd64.deb
$
```



```bash
$ sudo apt download x11-xserver-utils
[sudo] k8smaster의 암호: 
받기:1 http://kr.archive.ubuntu.com/ubuntu bionic/main amd64 x11-xserver-utils amd64 7.7+7build1 [159 kB]
내려받기 159 k바이트, 소요시간 2초 (101 k바이트/초)
W: Download is performed unsandboxed as root as file '/home/k8smaster/github/x11-xserver-utils_7.7+7build1_amd64.deb' couldn't be accessed by user '_apt'. - pkgAcquire::Run (13: 허가 거부)
$
```

```bash
$ sudo apt update
$ sudo apt download -y x11-xserver-utils
$ ls
x11-xserver-utils_7.7+7build1_amd64.deb
$
```

원격 서버에 이 `.deb`파일을 옮겨서 설치해보면

```bash
$ sudo dpkg -i x11-xserver-utils_7.7+7build1_amd64.deb
```



`libxi6 libxrandr2 libxxf86vml` dependencies때문에 설치에러가 발생합니다.

```bash
$ sudo apt update
$ sudo apt download -y libxi6 libxrandr2
$ ls
libxi6_2%3a1.7.9-1_amd64.deb      
libxrandr2_2%3a1.5.1-1_amd64.deb
$
```

첫 2개의 파일은 다운로드 받을 수 있습니다. 마지막 파일는 안 되네요.

```bash
$ sudo apt update
$ sudo apt download -y libxxf86vml
E: libxxf86vml 패키지를 찾을 수 없습니다
$
```

받는다 한 들 설치를 수동으로 진행해야 하는 부분이 있습니다.



Google search: ubuntu download x11-xserver-utils and dependencies

* [x11-xserver-utils_7.7+7build1_armhf.deb 18.04 LTS Download](https://ubuntu.pkgs.org/18.04/ubuntu-main-armhf/x11-xserver-utils_7.7+7build1_armhf.deb.html)

  > Download
  >
  > http://ports.ubuntu.com/pool/main/x/x11-xserver-utils/x11-xserver-utils_7.7+7build1_armhf.deb

```bash

```

```bash
$ wget http://ports.ubuntu.com/pool/main/x/x11-xserver-utils/x11-xserver-utils_7.7+7build1_armhf.deb
--2021-02-15 19:21:24--  http://ports.ubuntu.com/pool/main/x/x11-xserver-utils/x11-xserver-utils_7.7+7build1_armhf.deb
Resolving ports.ubuntu.com (ports.ubuntu.com)... 91.189.88.142, 91.189.88.152, 2001:67c:1360:8001::24, ...
접속 ports.ubuntu.com (ports.ubuntu.com)|91.189.88.142|:80... 접속됨.
HTTP request sent, awaiting response... 200 OK
Length: 144858 (141K) [application/x-debian-package]
Saving to: ‘x11-xserver-utils_7.7+7build1_armhf.deb’

x11-xserver-utils_7.7+7bu 100%[==================================>] 141.46K   136KB/s    in 1.0s    

2021-02-15 19:21:26 (136 KB/s) - ‘x11-xserver-utils_7.7+7build1_armhf.deb’ saved [144858/144858]

(base) k8smaster@k8smaster-Alienware-Aurora-R7:~/다운로드$ ls
cudnn                             usb_memory
libxi6_2%3a1.7.9-1_amd64.deb      x11-xserver-utils_7.7+7build1_amd64.deb
libxrandr2_2%3a1.5.1-1_amd64.deb  x11-xserver-utils_7.7+7build1_armhf.deb
$
```

