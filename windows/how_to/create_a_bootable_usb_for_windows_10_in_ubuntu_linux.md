* Draft: 2020-11-16 (Mon)

# 우분투 리눅스에서 윈도우 10 설치 USB 만들기 (How to Create a Bootable USB for Windows 10 in Ubuntu Linux)
* 참고: [How to Create a Bootable Windows 10 USB in Linux](https://itsfoss.com/bootable-windows-usb-linux/), It's FOSS

## 개략적인 절차
### Step 1. 윈도우 10 ISO파일을 다운로드 받습니다.
* https://www.microsoft.com/en-in/software-download/windows10ISO
* 파일명: Win10_20H2_Korean_x64.iso

### Step 2. USB 메모리를 포맷합니다.
Ubuntu Linux에서 Disks tool을 사용합니다. 이 때 윈도우/리눅스 모두 사용할 수 있도록 선택합니다.

### Step 3. ISO파일에 있는 내용을 USB 메모리로 복사합니다.
우선 ISO파일을 마운트합니다. ISO 우클릭하고 `Open With Disk Image Mounter`를 선택한 후 마운트를 하면, Desktop화면에 마운트됩니다.


### Step 4. 복사된 USB
