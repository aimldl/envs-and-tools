* Draft: 2021-02-16 (Tue)

# `/var/cache/apt/archives/`의 파일을 비우는 방법

Google search: how to empty /var/cache/apt/archives

* [Can I delete /var/cache/apt/archives for Ubuntu/Debian Linux?](https://www.cyberciti.biz/faq/can-i-delete-var-cache-apt-archives-for-ubuntu-debian-linux/)

> ### How to clear the APT cache and delete everything from /var/cache/apt/archives/
>
> ```bash
> $ sudo apt clean
> ```
>
> The clean command clears out the local repository of retrieved package files. It removes everything but the lock file from /var/cache/apt/archives/ and /var/cache/apt/archives/partial/. 

### 확인하기

```bash
$ sudo du -ch /var/cache/apt/archives
4.0K	/var/cache/apt/archives/partial
72K	/var/cache/apt/archives
72K	합계
$
```

거의 다 비워졌습니다. 파일을 확인하면 다음과 같습니다.

```bash
$ ls /var/cache/apt/archives
lock  partial
$
```

```bash
$ sudo tree /var/cache/apt/archives
/var/cache/apt/archives
├── lock
└── partial

1 directory, 1 file
$
```

> ### Delete all useless files from the APT cache
>
> ```bash
> $ sudo apt autoclean
> ```
>
> Verify that files are removed from /var/cache/apt/archives/ safely using the du command:
>
> ```bash
> $ sudo du -ch /var/cache/apt/archives/
> ```

### Example

```bash
$ sudo apt autoclean
[sudo] k8smaster의 암호: 
패키지 목록을 읽는 중입니다... 완료
의존성 트리를 만드는 중입니다       
상태 정보를 읽는 중입니다... 완료
Del linux-image-generic 4.15.0.132.119 [2,592 B]
Del firefox-locale-ko 84.0.2+build1-0ubuntu0.18.04.1 [488 kB]
Del firefox-locale-en 84.0.2+build1-0ubuntu0.18.04.1 [671 kB]
Del linux-generic 4.15.0.132.119 [1,864 B]
Del firefox-locale-en 85.0+build1-0ubuntu0.18.04.1 [678 kB]
Del firefox-locale-ko 85.0+build1-0ubuntu0.18.04.1 [490 kB]
Del firefox 85.0+build1-0ubuntu0.18.04.1 [56.1 MB]
Del linux-headers-generic 4.15.0.132.119 [2,492 B]
Del linux-libc-dev 4.15.0-132.136 [987 kB]
$
```

```bash
$ sudo du -ch /var/cache/apt/archives
4.0K	/var/cache/apt/archives/partial
289M	/var/cache/apt/archives
289M	합계
$
```

`sudo apt autoclean`은 `/var/cache/apt/archives`의 파일을 지우지는 않습니다. `autoclean`만 한 상태에서 위처럼 파일이 많이 남았고, `ls`명령어로 확인해보면 아래처럼 많이 남아있습니다.

```bash
$ ls /var/cache/apt/archives
cuda-drivers-460_460.32.03-1_amd64.deb
cuda-drivers_460.32.03-1_amd64.deb
libcurl4-gnutls-dev_7.58.0-2ubuntu3.12_amd64.deb
libmysqlclient-dev_5.7.33-0ubuntu0.18.04.1_amd64.deb
libmysqlclient20_5.7.33-0ubuntu0.18.04.1_amd64.deb
libnss-systemd_237-3ubuntu10.44_amd64.deb
libnvidia-cfg1-450_450.102.04-0ubuntu1_amd64.deb
libnvidia-cfg1-460_460.32.03-0ubuntu1_amd64.deb
libnvidia-common-450_450.102.04-0ubuntu1_all.deb
libnvidia-common-460_460.32.03-0ubuntu1_all.deb
libnvidia-compute-450_450.102.04-0ubuntu1_amd64.deb
libnvidia-compute-460_460.32.03-0ubuntu1_amd64.deb
libnvidia-container-tools_1.3.2-1_amd64.deb
libnvidia-container1_1.3.2-1_amd64.deb
libnvidia-decode-450_450.102.04-0ubuntu1_amd64.deb
libnvidia-decode-460_460.32.03-0ubuntu1_amd64.deb
libnvidia-encode-450_450.102.04-0ubuntu1_amd64.deb
libnvidia-encode-460_460.32.03-0ubuntu1_amd64.deb
libnvidia-extra-450_450.102.04-0ubuntu1_amd64.deb
libnvidia-extra-460_460.32.03-0ubuntu1_amd64.deb
libnvidia-fbc1-450_450.102.04-0ubuntu1_amd64.deb
libnvidia-fbc1-460_460.32.03-0ubuntu1_amd64.deb
libnvidia-gl-450_450.102.04-0ubuntu1_amd64.deb
libnvidia-gl-460_460.32.03-0ubuntu1_amd64.deb
libnvidia-ifr1-450_450.102.04-0ubuntu1_amd64.deb
libnvidia-ifr1-460_460.32.03-0ubuntu1_amd64.deb
libopenexr-dev_2.2.0-11.1ubuntu1.4_amd64.deb
libpam-systemd_237-3ubuntu10.44_amd64.deb
libpoppler-dev_0.62.0-2ubuntu2.12_amd64.deb
libpoppler-private-dev_0.62.0-2ubuntu2.12_amd64.deb
libpq-dev_10.15-0ubuntu0.18.04.1_amd64.deb
libpq5_10.15-0ubuntu0.18.04.1_amd64.deb
libssl-dev_1.1.1-1ubuntu2.1~18.04.7_amd64.deb
libxnvctrl0_460.32.03-0ubuntu1_amd64.deb
linux-headers-4.15.0-132-generic_4.15.0-132.136_amd64.deb
linux-headers-4.15.0-132_4.15.0-132.136_all.deb
linux-image-4.15.0-132-generic_4.15.0-132.136_amd64.deb
linux-modules-4.15.0-132-generic_4.15.0-132.136_amd64.deb
linux-modules-extra-4.15.0-132-generic_4.15.0-132.136_amd64.deb
lock
nvidia-compute-utils-450_450.102.04-0ubuntu1_amd64.deb
nvidia-compute-utils-460_460.32.03-0ubuntu1_amd64.deb
nvidia-container-runtime_3.4.1-1_amd64.deb
nvidia-container-toolkit_1.4.1-1_amd64.deb
nvidia-dkms-450_450.102.04-0ubuntu1_amd64.deb
nvidia-dkms-460_460.32.03-0ubuntu1_amd64.deb
nvidia-docker2_2.5.0-1_all.deb
nvidia-driver-450_450.102.04-0ubuntu1_amd64.deb
nvidia-driver-460_460.32.03-0ubuntu1_amd64.deb
nvidia-kernel-common-450_450.102.04-0ubuntu1_amd64.deb
nvidia-kernel-common-460_460.32.03-0ubuntu1_amd64.deb
nvidia-kernel-source-450_450.102.04-0ubuntu1_amd64.deb
nvidia-kernel-source-460_460.32.03-0ubuntu1_amd64.deb
nvidia-modprobe_460.32.03-0ubuntu1_amd64.deb
nvidia-settings_460.32.03-0ubuntu1_amd64.deb
nvidia-utils-450_450.102.04-0ubuntu1_amd64.deb
nvidia-utils-460_460.32.03-0ubuntu1_amd64.deb
partial
python-pil_5.1.0-1ubuntu0.4_amd64.deb
systemd-sysv_237-3ubuntu10.44_amd64.deb
tar_1.29b-2ubuntu0.2_amd64.deb
xserver-xorg-video-nvidia-450_450.102.04-0ubuntu1_amd64.deb
xserver-xorg-video-nvidia-460_460.32.03-0ubuntu1_amd64.deb
$
```



