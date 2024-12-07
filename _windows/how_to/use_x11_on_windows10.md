* Draft: 2021-02-15 (Mon)

# Windows10에서 X11 사용하기

Google search: windows 10 free x server program

* [Xming X Server for Windows](https://sourceforge.net/projects/xming/)

> Xming is the leading X Window System Server for Microsoft Windows 8/7/Vista/XP (+ server 2012/2008/2003). It is fully featured, small and fast, simple to install and because it is standalone native Microsoft Windows, easily made portable (not needing a machine-specific installation).

홈페이지에서 `Download`를 클릭합니다.

<img src='images/sourceforge-xming_x_server_for_windows-2021-02-15.png'>

다운로드된 `Xmin-6-9-0-31-setup.exe` (2.1MB)를 실행해서 프로그램을 설치합니다.

### SSH Client 프로그램의 설정

`PuTTY Configuration`> `Connection` > `SSH` > `X11`에서 

`X11 forwarding`의 `Enable X11 forwarding`을 체크합니다.

### SSH로 원격서버에 접속

`Xminx X Server`가 실행된 상태에서 원격서버에서 `xclock`을 실행하면 윈도우즈에서 프로그램의 GUI를 볼 수 있습니다.

```bash
$ xclock
Warning: Missing charsets in String to FontSet conversion
```

팝업된 프로그램의 GUI의 `X`를 클릭하면 창을 닫을 수 있습니다.

```bash
$
```

그러면 `ssh`의 프롬프트도 `$`로 돌아옵니다. 이로써 

### 원격서버의 도커 컨테이너에서 `xclock` 실행하기

도커 컨테이너 환경에서 `xclock`을 에러없이 실행하기 위해서는 도커 컨테이너를 실행할 때 X11이 지원되도록 해야합니다. 그러지 않으면

```bash
# xclock
Error: Can't open display:
#
```

라는 에러 메세지가 발생합니다.





```bash
$ docker attach strange_shockley
# xclock
```

