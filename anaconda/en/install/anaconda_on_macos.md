* Draft: 2021-12-15 (Wed)

# How to Install Anaconda on macOS

Source: [Installing on macOS](https://docs.anaconda.com/anaconda/install/mac-os/)

## Prerequisite
Install Python3
```bash
$ python --version
Python 2.7.18
$
```

## Download Anaconda Installer for macOS
* Open a web browser and go to [Anaconda macOS installer](https://www.anaconda.com/downloads#macos).
* Scroll down to Anaconda Installers
<img src='images/anaconda_installer_macos_64bit_command_line_installer.png'>

Click `64-Bit Command Line Installer` and download will start.
<img src='images/anaconda_installer_macos_64bit_command_line_installer-downloading.png'>

Open a terminal and check if the downloaded installer exists. Ensure the file extension is `.sh`.
```bash
$ ls ~/Downloads/Ana*
/Users/aimldl/Downloads/Anaconda3-2021.11-MacOSX-x86_64.sh
$
```

Note `64-Bit Graphical Installer` has `.pkg` as the file extension.
```bash
$ ls ~/Downloads/Ana*
/Users/thekim/Downloads/Anaconda3-2021.11-MacOSX-x86_64.pkg
$
```

## [Verify data integrity with SHA-256](https://docs.anaconda.com/anaconda/install/hashes/).
```bash
$ shasum -a 256 ~/Downloads/Anaconda3-2021.11-MacOSX-x86_64.sh 
6a9217d1a08c599f860045d56ef64fc6c3e3112b55cc97f3d07c573d7bbcdb58  /Users/thekim/Downloads/Anaconda3-2021.11-MacOSX-x86_64.sh
$
```

## Install Anaconda
```bash
$ bash ~/Downloads/Anaconda3-2021.11-MacOSX-x86_64.sh
```
In the message, press ENTER

```bash
Welcome to Anaconda3 2021.11

In order to continue the installation process, please review the license
agreement.
Please, press ENTER to continue
>>>
```

Enter `yes`
```bash
  ...
Do you accept the license terms? [yes|no]
[no] >>> 
```
Press ENTER
```bash
Anaconda3 will now be installed into this location:
/Users/thekim/anaconda3

  - Press ENTER to confirm the location
  - Press CTRL-C to abort the installation
  - Or specify a different location below

[/Users/thekim/anaconda3] >>> 
```
