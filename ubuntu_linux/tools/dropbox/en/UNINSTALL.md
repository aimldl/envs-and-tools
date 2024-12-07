* Draft: 2020-11-30 (Mon)

# 설치된 Dropbox 제거하기

## 요약 (Summary)

우분투 리눅스 (예: 18.04)에서 이미 설치된 드롭박스를 제거하려면, 터미널에서 아래의 명령어를 입력하면 됩니다. 

[How to Uninstall Dropbox](https://help.dropbox.com/installs-integrations/desktop/uninstall-dropbox)

> Uninstall the desktop app on Linux
>
> ```bash
> $ dropbox stop
> $ dropbox status  # Should report "not running"
> $ rm -rf ~/.dropbox-dist
> $ rm -rf /var/lib/dropbox
> $ rm -rf ~/.dropbox*
> $ sudo apt-get remove nautilus-dropbox
> $ sudo apt-get remove dropbox
> $ rm /etc/apt/source.d/dropbox
> ```
>
> Remove the files in your Dropbox Folder
>
> ```bash
> $ rm -rv ~/Dropbox
> ```

