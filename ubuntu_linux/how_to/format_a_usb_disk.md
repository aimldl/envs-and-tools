* Draft: 2021-02-15 (Mon)

# USB 디스크 포맷하기

* [How to format a USB flash drive on Ubuntu 18.04](https://www.usbmemorydirect.com/blog/how-to-format-flash-drive-on-ubuntu-18-04/)
* 

<img src='https://www.usbmemorydirect.com/blog/wp-content/uploads/2020/02/search_window.jpg'>

<img src='https://www.usbmemorydirect.com/blog/wp-content/uploads/2020/02/disk_utility_selected_device.png'>

터미널에서 `exfat-utils`를 설치합니다.

```bash
$ sudo apt update
$ sudo apt install -y exfat-utils
```

`exfat-utils`가 없으면 아래의 `Format Volume`창에서 Type을 `Others로 선택했을 때 `exFat`이 보이지 않습니다.

<img src='https://www.usbmemorydirect.com/blog/wp-content/uploads/2020/02/disk_manager_navigation.gif'>