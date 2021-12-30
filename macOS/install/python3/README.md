* 2021-12-30 (Thu)

# How to Install Python3 on MacOS

## Python2 is the default Python version on MacOS 
```bash
$ python --version
Python 2.7.18
$
```
## Prerequisite
A package manager `brew` is not pre-built on macOs. So install `brew` if you haven't installed it yet. 

To double-check if you've installed it before, run:
```bash
$ brew --version
Homebrew 3.3.9
Homebrew/homebrew-core (git revision b78e51d4078; last commit 2021-12-30)
Homebrew/homebrew-cask (git revision a8b70c8532; last commit 2021-12-30)
$
```
Change the ownership of the following directories to your user.
```bash
$ sudo chown -R $(whoami) /usr/local/bin /usr/local/etc /usr/local/lib/pkgconfig /usr/local/sbin /usr/local/share /usr/local/share/doc /usr/local/share/info /usr/local/share/man/man3 /usr/local/share/man/man5
Password: 
$
```
Add the write permission, too.
```bash
$ chmod u+w /usr/local/bin /usr/local/etc /usr/local/lib/pkgconfig /usr/local/sbin /usr/local/share /usr/local/share/doc /usr/local/share/info /usr/local/share/man/man3 /usr/local/share/man/man5
$
```

Otherwise you will see the following error in the next step.
```bash
$ brew install python
  ...
Error: The following directories are not writable by your user:
/usr/local/bin
  ...
/usr/local/share/man/man5

You should change the ownership of these directories to your user.
  sudo chown -R $(whoami) /usr/local/bin /usr/local/etc /usr/local/lib/pkgconfig /usr/local/sbin /usr/local/share /usr/local/share/doc /usr/local/share/info /usr/local/share/man/man3 /usr/local/share/man/man5

And make sure that your user has write permission.
```bash
  chmod u+w /usr/local/bin /usr/local/etc /usr/local/lib/pkgconfig /usr/local/sbin /usr/local/share /usr/local/share/doc /usr/local/share/info /usr/local/share/man/man3 /usr/local/share/man/man5
$
```
Notice the `sudo` command is blocked.
```bash
$ sudo brew install python
Password: 
Error: Running Homebrew as root is extremely dangerous and no longer supported.
As Homebrew does not drop privileges on installation you would be giving all
build scripts full access to your system.
```
## Install `python3` with `brew`



```bash
$ brew install python
```

