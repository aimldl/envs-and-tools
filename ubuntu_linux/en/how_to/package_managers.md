##### aimldl > computing_environments > os-ubuntu_linux > package_managers.md

# Package Managers
* [dpkg](#dpkg)
* [snap](#snap)

## dpkg <a name="dpkg"></a>
dpkg is a Debian package manger used both for Debian and Ubuntu.

### Uninstalling with dpkg
#### --remove or -r option
To remove the package itself without the configuration files, run dpkg with the -r or --remove option.
```bash
$ sudo dpkg -r package_name
  or
$ sudo dpkg --remove package_name
```

#### --purge or -P option
To purge the package or delete the package completely with configuration files, run dpkg with the -P or --purge option.
```bash
$ sudo dpkg -P package_name
$ sudo dpkg --purge package_name
```
For details, refer to :
* [dpkg tutorial – Package Manager for Ubuntu / Debian](https://linuxprograms.wordpress.com/tag/dpkg-remove/)
* [How to uninstall a .deb installed with dpkg?](https://unix.stackexchange.com/questions/195794/how-to-uninstall-a-deb-installed-with-dpkg)

#### --list or -l option
If you're not sure of package_name, find the correct package name with the -l or --list option.
```bash
$ sudo dpkg -l | grep keyword
  or
$ sudo dpkg --list | grep keyword
```

#### Example
The following example searches the correct package name and then remove the package.

* Situation
```bash
$ sudo dpkg -i remarkable_1.87_all.deb
```
I have tried to install a text editor remarkable and decided to uninstall it because the installation didn't work well. But I wasn't sure the correct package name.
```bash
$ sudo apt-get install python3-markdown
```
remarkable depends on python3-markdown, but python3-markdown didn't install properly, and so on. I could fix this problem, but decided to install Atom text editor instead.

* Task
The .deb file name is remarkable_1.87_all.deb. The correct package name is found by searching the package list with a keyword "remarkable".
```bash
$ dpkg -l | grep remarkable
iU  remarkable                                      1.87                                         all          A free fully featured markdown editor.
```
Remove the package remarkable with the -r option.
```bash
$ sudo dpkg -r remarkable
```

## snap <a name="snap"></a>
Snap is an alternative package manager. The tutorial is available at [Basic snap usage](https://tutorials.ubuntu.com/tutorial/basic-snap-usage#0). To test how the installation process works with snap, install snapd and a toy program "hello" as follows.
```bash
$ sudo apt install snapd
$ snap find hello
Name                           Version                      Publisher           Notes    Summary
hello                          2.10                         canonical✓          -        GNU Hello, the "hello world" snap
hello-world                    6.4                          canonical✓          -        The 'hello-world' of snaps
  ...
hello-sagarvolteo              2.10                         sagasmnoob          -        GNU Hello, the "hello world" snap
$ sudo snap install hello
hello 2.10 from Canonical✓ installed
$ hello
Hello, world!
```
(EOF)
