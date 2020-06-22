##### > ubuntu_linux > japanese_ime.md

### how to set up Japanese input IME

Google search: ubuntu linux japanese input
[Writing Japanese with Ubuntu 18.04 LTS Bionic Beaver](https://moritzmolch.com/2404)

[Japanese Input on Ubuntu 16.04 LTS Xenial Xerus](http://www.localizingjapan.com/blog/2017/08/20/japanese-input-on-ubuntu-16-04-lts-xenial-xerus/)

### Install Japanese character sets

[Help:Installing Japanese character sets](https://en.wikipedia.org/wiki/Help:Installing_Japanese_character_sets#Debian_and_Ubuntu)


 To display Japanese text in Debian or Ubuntu, run:
 ```bash
$ sudo apt-get install fonts-takao-mincho
# More fonts
$ sudo apt-get install fonts-takao
```

Google search: ubuntu 18.04 japanese "Failed to fetch http://"

> The default Japanese Input Method is now Mozc (the open-source component of Google's Japanese IME, which is used in Android and Chrome OS) instead of Anthy.
[Writing Japanese with Ubuntu 16.04 LTS Xenial Xerus, 07/2016](https://moritzmolch.com/2287)

#### Troubleshooting
Google search: ubuntu 18.04 "Manage installed languages" "Failed to fetch http://"

Done it - I downloaded the package files from https://packages.ubuntu.com/bionic/language-pack-de, and went through the Settings procedure outlined in the first post again. This time they installed correctly, presumably because it read them from my desktop. :)
[Can't install German language, Jun 28, 2019.](https://forum.parallels.com/threads/cant-install-german-language.347465/)

[Ubuntu » Packages » bionic (18.04LTS) » translations » language-pack-ja](https://packages.ubuntu.com/bionic/language-pack-ja)

[Download Page for language-pack-ja_18.04+20180423_all.deb](https://packages.ubuntu.com/bionic/all/language-pack-ja/download)

http://kr.archive.ubuntu.com/ubuntu/pool/main/l/language-pack-ja/language-pack-ja_18.04+20180423_all.deb

```bash
$ sudo dpkg -i language-pack-ja_18.04+20180423_all.deb
Selecting previously unselected package language-pack-ja.
(Reading database ... 277835 files and directories currently installed.)
Preparing to unpack language-pack-ja_18.04+20180423_all.deb ...
Unpacking language-pack-ja (1:18.04+20180423) ...
dpkg: dependency problems prevent configuration of language-pack-ja:
 language-pack-ja depends on language-pack-ja-base (>= 1:18.04+20180423); however:
  Package language-pack-ja-base is not installed.

dpkg: error processing package language-pack-ja (--install):
 dependency problems - leaving unconfigured
Errors were encountered while processing:
 language-pack-ja
```

```bash
$ sudo apt-get install -f
Reading package lists... Done
Building dependency tree
Reading state information... Done
Correcting dependencies... Done
The following packages were automatically installed and are no longer required:
  cuda-command-line-tools-10-1 cuda-compiler-10-1 cuda-cuobjdump-10-1 cuda-cupti-10-1
  cuda-documentation-10-1 cuda-gdb-10-1 cuda-gpu-library-advisor-10-1 cuda-libraries-10-1
  cuda-libraries-dev-10-1 cuda-memcheck-10-1 cuda-nsight-10-1 cuda-nsight-compute-10-1
  cuda-nsight-systems-10-1 cuda-nvdisasm-10-1 cuda-nvml-dev-10-1 cuda-nvprof-10-1 cuda-nvprune-10-1
  cuda-nvtx-10-1 cuda-nvvp-10-1 cuda-sanitizer-api-10-1 cuda-toolkit-10-1 cuda-tools-10-1
  cuda-visual-tools-10-1 dkms libnvidia-cfg1-418 libnvidia-common-418 libnvidia-compute-418
  libnvidia-container-tools libnvidia-container1 libnvidia-decode-418 libnvidia-encode-418
  libnvidia-fbc1-418 libnvidia-gl-418 libnvidia-ifr1-418 libpango1.0-0 libpangox-1.0-0
  xserver-xorg-video-nvidia-418
Use 'sudo apt autoremove' to remove them.
The following additional packages will be installed:
  language-pack-ja-base
The following NEW packages will be installed:
  language-pack-ja-base
0 upgraded, 1 newly installed, 0 to remove and 84 not upgraded.
1 not fully installed or removed.
Need to get 0 B/1,643 kB of archives.
After this operation, 7,567 kB of additional disk space will be used.
Do you want to continue? [Y/n] y
Selecting previously unselected package language-pack-ja-base.
(Reading database ... 277838 files and directories currently installed.)
Preparing to unpack .../language-pack-ja-base_1%3a18.04+20180423_all.deb ...
Unpacking language-pack-ja-base (1:18.04+20180423) ...
Setting up language-pack-ja (1:18.04+20180423) ...
Setting up language-pack-ja-base (1:18.04+20180423) ...
Generating locales (this might take a while)...
  ja_JP.UTF-8... done
Generation complete.
$
```

<img src="소프트웨어 데이터베이스가 망가졌습니다.png">

Fcitx is the default framework in Ubuntu for Chinese, Japanese, Korean and Vietnamese.
[Use alternative input sources](https://help.ubuntu.com/16.04/ubuntu-help/keyboard-layouts.html#complex)
Updated again.

Complex input methods
Recommended frameworks for input methods are IBus and Fcitx. The latter is the default framework in Ubuntu for Chinese, Japanese, Korean and Vietnamese.

Input source options with input methods are only available if respective input method (IM) engine is installed. When you install a language, a suitable IM engine is automatically installed if applicable.

For example, to prepare for typing Korean (Hangul) on an English system, follow these steps:

Install Korean. One of the installed packages is fcitx-hangul, the Hangul IM engine for Fcitx.

Close Language Support and open it again.

Select fcitx as the Keyboard input method system.

Log out and log in again.

Click the icon at the very right of the menu bar and select System Settings.

In the Personal section, click Text Entry.

Click the + button, select Hangul (Fcitx), and click Add.

This will make Hangul available in the Fcitx input source indicator in the menu bar. (The design differs from the IBus equivalent.)

If you prefer some other IM engine than the one which is installed automatically when you install a language, you can install the IBus or Fcitx IM engine of your choice separately.


Troubleshooting

<img src='images/전체 언어 지원을 설치하지 못 했습니다.png'>

The problem is reportedly the missing packages have already been installed!

```bash
$ sudo apt-get install gnome-getting-started-docs gnome-user-docs
[sudo] password for aimldl:
Reading package lists... Done
Building dependency tree
Reading state information... Done
gnome-user-docs is already the newest version (3.28.2+git20180715-0ubuntu0.1).
gnome-getting-started-docs is already the newest version (3.28.2-0ubuntu0.1).
The following packages were automatically installed and are no longer required:
  cuda-command-line-tools-10-1 cuda-compiler-10-1 cuda-cuobjdump-10-1 cuda-cupti-10-1
  cuda-documentation-10-1 cuda-gdb-10-1 cuda-gpu-library-advisor-10-1 cuda-libraries-10-1
  cuda-libraries-dev-10-1 cuda-memcheck-10-1 cuda-nsight-10-1 cuda-nsight-compute-10-1
  cuda-nsight-systems-10-1 cuda-nvdisasm-10-1 cuda-nvml-dev-10-1 cuda-nvprof-10-1 cuda-nvprune-10-1
  cuda-nvtx-10-1 cuda-nvvp-10-1 cuda-sanitizer-api-10-1 cuda-toolkit-10-1 cuda-tools-10-1
  cuda-visual-tools-10-1 dkms libheif1 libnvidia-cfg1-418 libnvidia-common-418 libnvidia-compute-418
  libnvidia-container-tools libnvidia-container1 libnvidia-decode-418 libnvidia-encode-418
  libnvidia-fbc1-418 libnvidia-gl-418 libnvidia-ifr1-418 libpango1.0-0 libpangox-1.0-0
  linux-headers-4.15.0-65 linux-headers-4.15.0-65-generic linux-image-4.15.0-65-generic
  linux-modules-4.15.0-65-generic linux-modules-extra-4.15.0-65-generic xserver-xorg-video-nvidia-418
Use 'sudo apt autoremove' to remove them.
0 upgraded, 0 newly installed, 0 to remove and 2 not upgraded.
$
```

To remove Japanese, the correct password fails.

<img src="images/Authentication_required.png">
