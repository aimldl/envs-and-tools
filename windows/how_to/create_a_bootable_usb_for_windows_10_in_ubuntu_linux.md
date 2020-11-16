* Draft: 2020-11-16 (Mon)

# 우분투 리눅스에서 윈도우 10 설치 USB 만들기 (How to Create a Bootable USB for Windows 10 in Ubuntu Linux)
* 참고: [How to Create a Bootable Windows 10 USB in Linux](https://itsfoss.com/bootable-windows-usb-linux/), It's FOSS

## 개요 (Overview)
윈도우 10 설치 USB를 만드는 첫 번째 절차는 윈도우 10 ISO파일을 다운로드 받는 것입니다. USB 메모리를 포맷하고, ISO파일의 내용을 USB 메모리로 옮기면 설치 USB가 완성됩니다.

### 개략적인 절차
#### Step 1. 윈도우 10 ISO파일을 다운로드 받습니다.
* https://www.microsoft.com/en-in/software-download/windows10ISO
* 파일명: Win10_20H2_Korean_x64.iso
#### Step 2. USB 메모리를 포맷합니다.
#### Step 3. ISO파일에 있는 내용을 USB 메모리로 복사합니다.

### 
Ubuntu Linux에서 Disk tool을 사용합니다. 이 때 윈도우/리눅스 모두 사용할 수 있도록 선택합니다.




* https://www.microsoft.com/en-in/software-download/windows10ISO
* 파일명: Win10_20H2_Korean_x64.iso
위 링크에서 파일을 다운로드 받으면 ISO파일이 준비됩니다.

다음 단계는 

### Rufus
Rufus를 쓰면 부팅 USB 디스크를 간단히 만들 수 있지만 .exe파일이므로 우분투에서 사용할 수 없습니다.
* [RUFUS를 이용한 부팅 USB 제작 방법 (윈도우, WINPE, 리눅스 등)](http://korean-daeddo.blogspot.com/2016/01/rufus-usb-winpe.html)

### Disk Image Writer로 ISO파일을 USB 메모리에 쓰기
이 방법은 


네이버 검색: 우분투에서 윈도우10 usb 부팅디스크

https://blog.naver.com/kyy0810/221515930219

https://blog.naver.com/sinjoker/221242863908

https://jimnong.tistory.com/676



우선 ISO파일을 마운트합니다. ISO 우클릭하고 `Open With Disk Image Mounter`를 선택한 후 마운트를 하면, Desktop화면에 마운트됩니다.

<img src='images/ubuntu_linux-win10_iso_mounted.png'>

마운트된 디렉토리를 더블클릭한 후,

<img src='images/ubuntu_linux-win10_iso-directories_and_files.png'>

디렉토리와 파일을 모두 선택 (Ctrl+A)해서 USB 메모리로 복사 (Ctrl+C & Ctrl+v)합니다.

### Step 4. 윈도우10 설치파일이 복사된 USB 메모리를 사용합니다.
복사가 끝나면 윈도우 10 설치 USB가 준비되었습니다.


## Disk Image Writer로 ISO파일을 USB 메모리에 쓰기
ISO파일을 우클릭해서 `Open with Other Application`을 선택한 후, 아래 화면처럼 진행하면 됩니다.

<img src='images/ubuntu_linux-disk_image_writer.png'>

<img src='images/ubuntu_linux-disk_image_writer-restore_disk_image.png'>

<img src='images/ubuntu_linux-disk_image_writer-restore_disk_image-destination_selected.png'>

<img src='images/ubuntu_linux-disk_image_writer-restore_disk_image-destination_selected-are_you_sure.png'>

<img src='images/ubuntu_linux-disk_image_writer-restore_disk_image-destination_selected-are_you_sure-restore.png'>

<img src='images/ubuntu_linux-disk_image_writer-restore_disk_image-destination_selected-are_you_sure-restore-completed.png'>

<img src='images/ubuntu_linux-disk_image_writer-win10_image_mounted.png'>
