* Draft: 2021-02-02 (Tue)

# ubuntu-drivers

명령어를 입력해도 없다고 나옵니다.

```bash
$ ubunbtu-drivers devices

Command 'ubunbtu-drivers' not found, did you mean:

  command 'ubuntu-drivers' from deb ubuntu-drivers-common

Try: sudo apt install <deb name>

$
```

`apt` 명령어도 설치도 안 됩니다.

```bash
$ sudo apt install -y ubuntu-drivers
[sudo] aimldl의 암호: 
패키지 목록을 읽는 중입니다... 완료
의존성 트리를 만드는 중입니다       
상태 정보를 읽는 중입니다... 완료
E: ubuntu-drivers 패키지를 찾을 수 없습니다
$
```

`sudo`명령어와 같이 쓰니 됩니다.

```bash
$ sudo ubuntu-drivers devices
== /sys/devices/pci0000:00/0000:00:01.1/0000:02:00.0 ==
modalias : pci:v000010DEd00001B80sv00001028sd00003366bc03sc00i00
vendor   : NVIDIA Corporation
model    : GP104 [GeForce GTX 1080]
driver   : nvidia-driver-455 - third-party free
driver   : nvidia-driver-418 - third-party free
driver   : nvidia-driver-460 - third-party free recommended
driver   : nvidia-driver-450 - third-party free
driver   : nvidia-driver-418-server - distro non-free
driver   : nvidia-driver-450-server - distro non-free
driver   : nvidia-driver-390 - distro non-free
driver   : xserver-xorg-video-nouveau - distro free builtin
$
```

