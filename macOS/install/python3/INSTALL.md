* 2021-12-30 (Thu)

# How to Install Python3 on MacOS
## Summary

```bash
$ xcode-select --install
$ brew install python
```
Source: [Installing Python](https://cloud.google.com/python/docs/setup#installing_python)

## Python2 is the default Python version on MacOS 
```bash
$ python --version
Python 2.7.18
$
```
## `brew` is prerequisites
A package manager `brew` is not pre-built on macOs. So install `brew` if you haven't installed it yet. 

To double-check the installation, run the following command. If you have `brew` on your machine, you'll see a message like this.
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
$ brew list | grep python
$
```

```bash
$ brew install pyenv
$
```

```bash
$ sudo chown -R $(whoami) /usr/local/bin /usr/local/etc /usr/local/sbin /usr/local/share /usr/local/share/doc
Password: 
$ chmod u+w /usr/local/bin /usr/local/etc /usr/local/sbin /usr/local/share /usr/local/share/doc
```

```bash
$ brew list | grep python
$
```

```bash
$ brew install python
```

```bash
==> Installing python@3.9 dependency: xz
==> Pouring xz--5.2.5.monterey.bottle.tar.gz
🍺  /usr/local/Cellar/xz/5.2.5: 95 files, 1.3MB
==> Installing python@3.9
==> Pouring python@3.9--3.9.9.monterey.bottle.tar.gz
Error: The `brew link` step did not complete successfully
The formula built, but is not symlinked into /usr/local
Could not symlink bin/2to3
Target /usr/local/bin/2to3
already exists. You may want to remove it:
  rm '/usr/local/bin/2to3'

To force the link and overwrite all conflicting files:
  brew link --overwrite python@3.9

To list all files that would be deleted:
  brew link --overwrite --dry-run python@3.9

Possible conflicting files are:
/usr/local/bin/2to3 -> /Library/Frameworks/Python.framework/Versions/3.7/bin/2to3
/usr/local/bin/idle3 -> /Library/Frameworks/Python.framework/Versions/3.7/bin/idle3
/usr/local/bin/pydoc3 -> /Library/Frameworks/Python.framework/Versions/3.7/bin/pydoc3
/usr/local/bin/python3 -> /Library/Frameworks/Python.framework/Versions/3.7/bin/python3
/usr/local/bin/python3-config -> /Library/Frameworks/Python.framework/Versions/3.7/bin/python3-config
==> /usr/local/Cellar/python@3.9/3.9.9/bin/python3 -m ensurepip
==> /usr/local/Cellar/python@3.9/3.9.9/bin/python3 -m pip install -v --no-deps --no-index --upgrade --isolated --target=/usr/local/lib/python3.9/site-packages /usr/local/Cellar/pyth
==> Caveats
Python has been installed as
  /usr/local/bin/python3

Unversioned symlinks `python`, `python-config`, `pip` etc. pointing to
`python3`, `python3-config`, `pip3` etc., respectively, have been installed into
  /usr/local/opt/python@3.9/libexec/bin

You can install Python packages with
  pip3 install <package>
They will install into the site-package directory
  /usr/local/lib/python3.9/site-packages

tkinter is no longer included with this formula, but it is available separately:
  brew install python-tk@3.9

See: https://docs.brew.sh/Homebrew-and-Python
==> Summary
🍺  /usr/local/Cellar/python@3.9/3.9.9: 3,080 files, 54.9MB
==> Running `brew cleanup python@3.9`...
Disable this behaviour by setting HOMEBREW_NO_INSTALL_CLEANUP.
Hide these hints with HOMEBREW_NO_ENV_HINTS (see `man brew`).
==> Caveats
==> python@3.9
Python has been installed as
  /usr/local/bin/python3

Unversioned symlinks `python`, `python-config`, `pip` etc. pointing to
`python3`, `python3-config`, `pip3` etc., respectively, have been installed into
  /usr/local/opt/python@3.9/libexec/bin

You can install Python packages with
  pip3 install <package>
They will install into the site-package directory
  /usr/local/lib/python3.9/site-packages

tkinter is no longer included with this formula, but it is available separately:
  brew install python-tk@3.9

See: https://docs.brew.sh/Homebrew-and-Python
$
```

## Verify the installation
```bash
$ brew list | grep python
python@3.9
$
```

```bash
$ python

WARNING: Python 2.7 is not recommended. 
This version is included in macOS for compatibility with legacy software. 
Future versions of macOS will not include Python 2.7. 
Instead, it is recommended that you transition to using 'python3' from within Terminal.

Python 2.7.18 (default, Oct  2 2021, 04:20:39) 
[GCC Apple LLVM 13.0.0 (clang-1300.0.29.1) [+internal-os, ptrauth-isa=deploymen on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>> exit()
$
```

```bash
$ python3
Python 3.7.9 (v3.7.9:13c94747c7, Aug 15 2020, 01:31:08) 
[Clang 6.0 (clang-600.0.57)] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>> exit()
$
```

## One more time

```bash
$ brew install python
Warning: python@3.9 3.9.9 is already installed, it's just not linked.
To link this version, run:
  brew link python@3.9
$
```

```bash
$ brew link python@3.9
Linking /usr/local/Cellar/python@3.9/3.9.9... 
Error: Could not symlink bin/2to3
Target /usr/local/bin/2to3
already exists. You may want to remove it:
  rm '/usr/local/bin/2to3'

To force the link and overwrite all conflicting files:
  brew link --overwrite python@3.9

To list all files that would be deleted:
  brew link --overwrite --dry-run python@3.9
$
```
Before deling the files, check the list first.

```bash
$ brew link --overwrite --dry-run python@3.9
Would remove:
/usr/local/bin/2to3 -> /Library/Frameworks/Python.framework/Versions/3.7/bin/2to3
/usr/local/bin/idle3 -> /Library/Frameworks/Python.framework/Versions/3.7/bin/idle3
/usr/local/bin/pydoc3 -> /Library/Frameworks/Python.framework/Versions/3.7/bin/pydoc3
/usr/local/bin/python3 -> /Library/Frameworks/Python.framework/Versions/3.7/bin/python3
/usr/local/bin/python3-config -> /Library/Frameworks/Python.framework/Versions/3.7/bin/python3-config
$
```
It looks safe to overwrite everything.

```bash
$ brew link --overwrite python@3.9
Linking /usr/local/Cellar/python@3.9/3.9.9... 24 symlinks created.
$
```

To make sure, 
```bash
$ brew install python
Warning: python@3.9 3.9.9 is already installed and up-to-date.
To reinstall 3.9.9, run:
  brew reinstall python@3.9
$
```


## Reference
* [The right and wrong way to set Python 3 as default on a Mac](https://opensource.com/article/19/5/python-3-default-mac), 2020-12-01, Matthew Broberg (Red Hat), Feed Moshe Zadka (Correspondent), opensource.com
* [Installing Python 3 on Mac OS X](https://docs.python-guide.org/starting/install3/osx/), The Hitchhiker's Guide to Python
