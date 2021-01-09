* Rev.1: 2020-05-25 (Mon)
* Draft: 2016-11-30 (Wed)
# Install a `.deb` Package with No Internet

## Problem
The `apt-get install` command fails because of no Internet connection.
```bash
	$ sudo apt-get install tree
```

## Hint
* [E: Package 'guile-1.8-dev' has no installation candidate this is an error i got [duplicate]](https://askubuntu.com/questions/47865/e-package-guile-1-8-dev-has-no-installation-candidate-this-is-an-error-i-got)

## Solution
1. Find the link to .deb package file
```bash
$ apt-get_downloadlist tree http://kr.archive.ubuntu.com/ubuntu/pool/universe/t/tree/tree_1.6.0-1_amd64.deb
```
2. Download the `.deb` file
```bash
$ wget http://kr.archive.ubuntu.com/ubuntu/pool/universe/t/tree/tree_1.6.0-1_amd64.deb
```
or
```bash
$ apt download <package>
$ apt-get download <package>
$ apt-get -d install <packages>
# -d, --download-only
$ aptitude download <package>
```
3. Move the package file to directory `/var/cache/apt/archives/`.
There are lots of `.deb` files are in this directory.
4. Install the package
Run one of 
```bash
$ apt-get install <package>
# or
$ sudo apt-get install -f .
# or
$ sudo dpkg -i /path/to/deb/file
```
