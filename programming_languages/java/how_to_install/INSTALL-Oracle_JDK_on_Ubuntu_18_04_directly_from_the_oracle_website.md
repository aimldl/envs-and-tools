* Rev.2: 2020-08-07 (Fri)
* Rev.1: 2020-08-06 (Thu)
* Rev.1: 2020-05-21 (Thu)
* Draft: 2020-03-25 (Wed)

# Install Oracle JDK on Ubuntu 18.04 

```bash
$ sudo apt install jdk-13.0.2
[sudo] h2o의 암호: 
패키지 목록을 읽는 중입니다... 완료
의존성 트리를 만드는 중입니다       
상태 정보를 읽는 중입니다... 완료
주의, './jdk-13.0.2_linux-x64_bin.deb' 대신에 'jdk-13.0.2' 패키지를 선택합니다
다음 새 패키지를 설치할 것입니다:
  jdk-13.0.2
0개 업그레이드, 1개 새로 설치, 0개 제거 및 3개 업그레이드 안 함.
0 바이트/163 M바이트 아카이브를 받아야 합니다.
이 작업 후 0 바이트의 디스크 공간을 더 사용하게 됩니다.
받기:1 /home/h2o/jdk-13.0.2_linux-x64_bin.deb jdk-13.0.2 amd64 13.0.2-1 [163 MB]
Selecting previously unselected package jdk-13.0.2.
(데이터베이스 읽는중 ...현재 166096개의 파일과 디렉터리가 설치되어 있습니다.)
Preparing to unpack .../jdk-13.0.2_linux-x64_bin.deb ...
Unpacking jdk-13.0.2 (13.0.2-1) ...
jdk-13.0.2 (13.0.2-1) 설정하는 중입니다 ...
$
```

# Install Oracle JDK on Ubuntu 18.04 directly from the Oracle website
## Step 1. Download Oracle JDK directly from Oracle website.

Download "Linux Debian Package" from [Java SE Development Kit 13 Downloads](https://www.oracle.com/java/technologies/javase-jdk13-downloads.html).

Click `jdk-13.0.2_linux-x64_bin.deb`

<img src="images/java_se_development_kit13_0_2.png">

Check `I reviewed ...` and click `Download jdk-13.0.2 ...`.

<img src="images/accept_the_license_and_download_deb_file.png">

Sign into the account. Oracle Account Login is mandatory. To open an account, Oracle asks the company and job title, too.

<img src="images/oracle_account_signin-english.png">

A window pops up. Click `Save File` and then `OK`.

<img src="images/opening_jdk13_0_2_linux-x64_bin_deb.png">

Then the download starts.

### License update

<img src="images/important_oracle_jdk_license_update-2019-04-16.png">

### wget no longer works
wget doesn't work any more. Download it from a web browser after accepting the license. 

```bash
Click the right version, accept the license and download the file.
$ wget https://download.oracle.com/otn-pub/java/jdk/14.0.1+7/664493ef4a6946b186ff29eb326336a2/jdk-14.0.1_linux-x64_bin.deb
$ ls
anaconda3  bin  h2o-3.30.0.3  h2o-3.30.0.3.zip  hands-ons  history.log  jdk-14.0.1_linux-x64_bin.deb  projects
$
```
See the error message. Install the .deb file from a web browser.
```bash
(base) user@d24d8fc9d727:~$ ls -al
  ...
-rw-r--r-- 1 user user      5307 Mar 20  2012 jdk-14.0.1_linux-x64_bin.deb
(base) user@d24d8fc9d727:~$ sudo dpkg -i jdk-14.0.1_linux-x64_bin.deb
dpkg: error processing archive jdk-14.0.1_linux-x64_bin.deb (--install):
 dpkg-deb --control subprocess returned error exit status 2
Errors were encountered while processing:
 jdk-14.0.1_linux-x64_bin.deb
$
```

## Step 2. Install the .deb File

```bash
$ sudo dpkg -i jdk-13.0.2_linux-x64_bin.deb
[sudo] h20의 암호: 
Selecting previously unselected package jdk-13.0.2.
(데이터베이스 읽는중 ...현재 172852개의 파일과 디렉터리가 설치되어 있습니다.)
Preparing to unpack jdk-13.0.2_linux-x64_bin.deb ...
Unpacking jdk-13.0.2 (13.0.2-1) ...
jdk-13.0.2 (13.0.2-1) 설정하는 중입니다 ...
$
```

## Step 3. Check the installation JDK version
```bash
$ sudo dpkg --list | grep -i jdk
ii  jdk-13.0.2                                 13.0.2-1                                         amd64        Java Platform Standard Edition Development Kit
$
```
