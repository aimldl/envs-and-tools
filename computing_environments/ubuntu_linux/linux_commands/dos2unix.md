##### aimldl > computing_environments > ubuntu_linux > commands > dos2unix.md
* Draft: 2019-11-10 (Sun)
* TODO:

# 1. dos2unix & linux2dos
* dos2unix is a linux command to convert the format from Windows to Unix (or Linux).
```bash
$ dos2unix file_name
```
* linux2dos converts the format from Unix (or Linux) to Windows. 
```bash
$ linux2dos file_name
```
## 2. Installation
### 2.1. Check if "dos2unix" is Installed
Type in "dos2unix" or "linux2dos" to check if it is installed in your OS.
```bash
$ dos2unix test_file
Command 'dos2unix' not found, but can be installed with:
sudo apt install dos2unix
$
```

### 2.2. Installing on Ubuntu Linux
Installation is easy and smooth on Ubuntu.
```bash
$ sudo apt install dos2unix linux2dos
[sudo] password for aimldl:
...
$
```
(EOF)
