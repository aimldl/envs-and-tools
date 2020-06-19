##### aimldl > computing_environments > ubuntu_linux > packages > atom > Installation.md
* Revision: None
* Draft: 2019-11-03 (Sun)
## 1. Installing Atom and Configuring as a Markdown Editor.
### 1.1. Installation
#### 1.1.1. Installing Atom to Ubuntu Linux
The commands to install Atom are below. For details, refer to [How To Install Atom Text Editor on Ubuntu 18.04](https://linuxize.com/post/how-to-install-atom-text-editor-on-ubuntu-18-04/#starting-atom) or [Installing Atom (Linux)](https://flight-manual.atom.io/getting-started/sections/installing-atom/#platform-linux).
```bash
$ sudo apt update
$ sudo apt install software-properties-common apt-transport-https wget
$ wget -q https://packagecloud.io/AtomEditor/atom/gpgkey -O- | sudo apt-key add -
$ sudo add-apt-repository "deb [arch=amd64] https://packagecloud.io/AtomEditor/atom/any/ any main"
$ sudo apt install atom
```
##### Starting Atom
```bash
$ atom
```
##### Upgrading Atom on Ubuntu Linux
```bash
$ sudo apt update
$ sudo apt upgrade
```
#### 1.1.2. Installing Atom to Windows
Go to https://atom.io/ and click "Download". Your Windows will be automatically detected.

<img src="images/windows-downloads.png" width="450" height="300"/>

For details, refer to [Installing Atom (Windows)](https://flight-manual.atom.io/getting-started/sections/installing-atom/#platform-windows).

#### 1.1.3. Installing Atom to MAC
Refer to [Installing Atom (MAC)](https://flight-manual.atom.io/getting-started/sections/installing-atom/#platform-mac).

(EOF)
