* Rev.1:
* Draft:
# How to Install Google Chrome on Ubuntu 18.04
## Purpose
The following command used to work:
```bash
$ sudo apt install -y chronium-browser
```
I recently found the above command fails. 
## How to install manually
According to [How to Install Google Chrome Web Browser on Ubuntu 18.04](https://linuxize.com/post/how-to-install-google-chrome-web-browser-on-ubuntu-18-04/), run the following commands.
```bash
$ wget https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
$ sudo apt install -y ./google-chrome-stable_current_amd64.deb
```
To verify, run:
```bash
$ google-chrome
```
<img src="images/google_chrome-initial_launch_window.png">
