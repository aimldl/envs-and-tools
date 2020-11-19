* Draft: 2020-11-19 (Thu)

# 우분투 리눅스에 구글 드라이브 설치하기

출처: [How to Install Google Drive on Ubuntu 20.04](https://linuxhint.com/google_drive_installation_ubuntu/)

## google-drive-ocamlfuse 설치하기

PPA 설정을 하고 apt-get을 업데이트 합니다.

```bash
$ sudo add-apt-repository ppa:alessandro-strada/ppa
  ...
Press [ENTER] to continue or Ctrl-c to cancel adding it.
  ...
$ sudo apt-get update
```

`google-drive-ocamlfuse`를 설치합니다.

```bash
$ sudo apt-get install -y google-drive-ocamlfuse
```

## google-drive-ocamlfuse 설정하기

`google-drive-ocamlfuse`를 실행하면 웹브라우저가 자동으로 열립니다.

```bash
$ google-drive-ocamlfuse
```

구글 계정을 입력해서 로그인합니다. 

<img src='images/google-drive-ocamlfuse-webbrowser-1.png'>

`Allow`버튼을 누르면 구글 계정에 접근할 수 있도록 수락됩니다.

<img src='images/google-drive-ocamlfuse-webbrowser-2.png'>

<img src='images/google-drive-ocamlfuse-webbrowser-3.png'>

성공적으로 수락되면 아래 메세지가 보여집니다. 웹브라우저를 닫습니다.

<img src='images/google-drive-ocamlfuse-webbrowser-4.png'>

구글 드라이브를 저장할 디렉토리를 생성한 후, 구글 드라이브를 이 디렉토리에 마운트합니다.

```bash
$ mkdir -v ~/GoogleDrive
$ google-drive-ocamlfuse ~/GoogleDrive
```

위에선 디렉토리 이름을 `GoogleDrive`라고 했지만, 원하는 디렉토리로 설정하면 됩니다.

## 설치 확인하기

`df` 명령어로 마운트된 것을 확인합니다. `-h`옵션은 사람이 읽을 수 있는 포맷 (human readable format)으로 용량을 보여줍니다. 아래 경우는 100G가 있음을 알 수 있습니다.

```bash
$ df -h
  ...
google-drive-ocamlfuse       100G  -64Z  -16M 100% /home/aimldl/GoogleDrive
$
```