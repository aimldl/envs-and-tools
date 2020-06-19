##### aimldl > computing_environments > ubuntu_linux > commands > tree.md
* Draft: 2019-11-10 (Sun)
* TODO: Summarize [Tree command in Linux with examples](https://www.geeksforgeeks.org/tree-command-unixlinux/)

## 1. Overview: tree
"tree" is a linux command which shows the directory and file structure in the tree format. It is a convenient tool to grasp the big picture of an underlying structure at a glance. "tree" increases the productivity dramatically to understand something new. Understanding the overall structure of new source codes or newly installed software.  

## 2. Installation
### 2.1. Check if "tree" is Installed
Type in "tree" to check if tree is installed in your OS.
```bash
$ tree
Command 'tree' not found, but can be installed with:
sudo apt install tree
$
```
"tree" is not installed by default on Ubuntu Linux and Ubuntu Linux on Windows 10.

Installation is easy and smooth both on Ubuntu & RedHat Linux.
### 2.2. Installing "tree" on Ubuntu Linux
```bash
$ sudo apt install tree
[sudo] password for aimldl:
...
$
```
### 2.3. Installing "tree" on RedHat Linux
yum package manager is used by Amazon EC2, SageMaker, and so on.
```bash
$ sudo yum install -y tree
[sudo] password for aimldl:
...
$
```
## 3. Tutorials
* [Tree command in Linux with examples](https://www.geeksforgeeks.org/tree-command-unixlinux/), GeeksforGeeks.

## 4. Selected Examples
### 4.1. tree -d
shows directories (under the current directory).
```bash
$ tree -d
$
```
### 4.2. tree -L n
shows up to level n (from the current directory). For example, limit the tree up to the 2nd level.
```bash
$ tree -L 2
$
```

### 4.3. tree -d -L n
shows only directories up to level n (from the current directory). For example,
```bash
$ 
~$ tree -d -L 1
.
├── Desktop
├── Documents
├── Downloads
├── Music
├── Pictures
├── Public
├── Templates
└── Videos
$
```
(EOF)
