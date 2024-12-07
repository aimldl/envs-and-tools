* Draft: 2020-12-22 (Tue)

# 줌 설치하기 (Installing Zoom)

다운로드 센터: https://zoom.us/download

## 리눅스 (Linux)

### 우분투 리눅스 (20.02)

Step 1. 설치 파일을 다운로드 합니다.

```bash
$ wget https://zoom.us/client/latest/zoom_amd64.deb
```

Step 2. 설치 파일을 실행합니다.

```bash
$ sudo apt install ./zoom_amd64.deb
```

에러가 발생한다면 `--fix-broken`옵션을 추가해서 실행합니다.

```bash
$ sudo apt --fix-broken install ./zoom_amd64.deb
```

Step 3. 줌을 실행해서 설치를 확인합니다.

```bash
$ zoom &
```

