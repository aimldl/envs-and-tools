TROUBLESHOOT.md

## TROUBLESHOOT

### Problem: typora crashes
typora is launched after typing in "typora &", but it crashes with Segmentation fault after clicking here and there in the menu.
```bash
(base) ubuntu@ec2-seoul-aimldl:~$ typora &
[1] 62328
(base) ubuntu@ec2-seoul-aimldl:~$ Gtk-Message: 02:20:41.356: Failed to load module "canberra-gtk-module"
Gtk-Message: 02:20:41.365: Failed to load module "canberra-gtk-module"

[1]+  Segmentation fault      (core dumped) typora
(base) ubuntu@ec2-seoul-aimldl:~$ 
```

### Action 1: Remove the config file and install "canberra-gtk-module" -> didn't work
Google search: ubuntu typora Failed to load module "canberra-gtk-module"
The suggestions in [Typora not working anymore on Ubuntu 17.10 #1069](https://github.com/typora/typora-issues/issues/1069) didn't solve the problem in my case.

```bash
$ sudo rm -fr .config/Typora
$
```

```bash 
$ wget -qO - https://typora.io/linux/public-key.asc | sudo apt-key add -
$ sudo add-apt-repository 'deb https://typora.io/linux ./'
$ sudo apt-get update
$ sudo apt-get install libcanberra-gtk-module
```
#### Example
```bash
(base) ubuntu@ec2-seoul-aimldl:~$ wget -qO - https://typora.io/linux/public-key.asc | sudo apt-key add -
OK
(base) ubuntu@ec2-seoul-aimldl:~$ sudo add-apt-repository 'deb https://typora.io/linux ./'
Get:1 https://typora.io/linux ./ InRelease [793 B]
Hit:2 https://nvidia.github.io/libnvidia-container/ubuntu18.04/amd64  InRelease                         
Hit:3 https://nvidia.github.io/nvidia-container-runtime/ubuntu18.04/amd64  InRelease                    
Hit:4 https://nvidia.github.io/nvidia-docker/ubuntu18.04/amd64  InRelease                               
Get:5 http://security.ubuntu.com/ubuntu bionic-security InRelease [88.7 kB]                             
Hit:6 http://ppa.launchpad.net/openjdk-r/ppa/ubuntu bionic InRelease                                    
Hit:7 http://archive.ubuntu.com/ubuntu bionic InRelease                                                 
Get:8 http://archive.ubuntu.com/ubuntu bionic-updates InRelease [88.7 kB]                               
Hit:9 https://apt.repos.neuron.amazonaws.com bionic InRelease                      
Get:10 http://archive.ubuntu.com/ubuntu bionic-backports InRelease [74.6 kB]       
Fetched 253 kB in 3s (96.8 kB/s)   
Reading package lists... Done
(base) ubuntu@ec2-seoul-aimldl:~$ sudo apt-get update
Hit:1 https://nvidia.github.io/libnvidia-container/ubuntu18.04/amd64  InRelease
Get:2 https://typora.io/linux ./ InRelease [793 B]                                                      
Hit:3 https://nvidia.github.io/nvidia-container-runtime/ubuntu18.04/amd64  InRelease                    
Hit:4 https://nvidia.github.io/nvidia-docker/ubuntu18.04/amd64  InRelease                               
Hit:5 http://archive.ubuntu.com/ubuntu bionic InRelease                                                 
Hit:6 http://ppa.launchpad.net/openjdk-r/ppa/ubuntu bionic InRelease                                    
Get:7 http://security.ubuntu.com/ubuntu bionic-security InRelease [88.7 kB]                             
Get:8 http://archive.ubuntu.com/ubuntu bionic-updates InRelease [88.7 kB]                               
Hit:9 https://apt.repos.neuron.amazonaws.com bionic InRelease                                           
Get:10 http://archive.ubuntu.com/ubuntu bionic-backports InRelease [74.6 kB]
Fetched 253 kB in 2s (124 kB/s)    
Reading package lists... Done
(base) ubuntu@ec2-seoul-aimldl:~$ sudo apt-get install libcanberra-gtk-module
Reading package lists... Done
Building dependency tree       
Reading state information... Done
The following additional packages will be installed:
  libcanberra-gtk0 libcanberra0 libtdb1 sound-theme-freedesktop
Suggested packages:
  libcanberra-pulse
The following NEW packages will be installed:
  libcanberra-gtk-module libcanberra-gtk0 libcanberra0 libtdb1 sound-theme-freedesktop
0 upgraded, 5 newly installed, 0 to remove and 14 not upgraded.
Need to get 480 kB of archives.
After this operation, 871 kB of additional disk space will be used.
Do you want to continue? [Y/n] y
Get:1 http://archive.ubuntu.com/ubuntu bionic/main amd64 libtdb1 amd64 1.3.15-2 [39.7 kB]
Get:2 http://archive.ubuntu.com/ubuntu bionic/main amd64 sound-theme-freedesktop all 0.8-2ubuntu1 [384 kB]
Get:3 http://archive.ubuntu.com/ubuntu bionic/main amd64 libcanberra0 amd64 0.30-5ubuntu1 [38.4 kB]
Get:4 http://archive.ubuntu.com/ubuntu bionic/universe amd64 libcanberra-gtk0 amd64 0.30-5ubuntu1 [7864 B]
Get:5 http://archive.ubuntu.com/ubuntu bionic/universe amd64 libcanberra-gtk-module amd64 0.30-5ubuntu1 [10.0 kB]
Fetched 480 kB in 2s (200 kB/s)                  
Selecting previously unselected package libtdb1:amd64.
(Reading database ... 208340 files and directories currently installed.)
Preparing to unpack .../libtdb1_1.3.15-2_amd64.deb ...
Unpacking libtdb1:amd64 (1.3.15-2) ...
Selecting previously unselected package sound-theme-freedesktop.
Preparing to unpack .../sound-theme-freedesktop_0.8-2ubuntu1_all.deb ...
Unpacking sound-theme-freedesktop (0.8-2ubuntu1) ...
Selecting previously unselected package libcanberra0:amd64.
Preparing to unpack .../libcanberra0_0.30-5ubuntu1_amd64.deb ...
Unpacking libcanberra0:amd64 (0.30-5ubuntu1) ...
Selecting previously unselected package libcanberra-gtk0:amd64.
Preparing to unpack .../libcanberra-gtk0_0.30-5ubuntu1_amd64.deb ...
Unpacking libcanberra-gtk0:amd64 (0.30-5ubuntu1) ...
Selecting previously unselected package libcanberra-gtk-module:amd64.
Preparing to unpack .../libcanberra-gtk-module_0.30-5ubuntu1_amd64.deb ...
Unpacking libcanberra-gtk-module:amd64 (0.30-5ubuntu1) ...
Setting up libtdb1:amd64 (1.3.15-2) ...
Setting up sound-theme-freedesktop (0.8-2ubuntu1) ...
Setting up libcanberra0:amd64 (0.30-5ubuntu1) ...
Setting up libcanberra-gtk0:amd64 (0.30-5ubuntu1) ...
Setting up libcanberra-gtk-module:amd64 (0.30-5ubuntu1) ...
Processing triggers for libc-bin (2.27-3ubuntu1) ...
(base) ubuntu@ec2-seoul-aimldl:~$ 
```

Without the first three commands, an error will occur.
```bash
$ sudo apt-get install libcanberra-gtk-module
Reading package lists... Done
Building dependency tree       
Reading state information... Done
E: Unable to locate package libcancerra-gtk-module
$
```

### Action 2: Uninstall and reinstall typora
Refer to [INSTALL.md](#INSTALL.md). Doing this didn't help.

### Action 3: 
Very few web articles with the first Google search keywords. The search condition is relaxed without Ubuntu.
Google search: Failed to load module "canberra-gtk-module"
[[SOLVED] Gtk-Message: Failed to load module "canberra-gtk-module"](https://www.linuxquestions.org/questions/linux-software-2/gtk-message-failed-to-load-module-canberra-gtk-module-936168/)

> On Ubuntu 12.04 server 64, I had to call:
sudo apt-get install libcanberra-gtk*
In order to remove the warning: Gtk-Message: Failed to load module "canberra-gtk-module"

#### Example
The output is too long to show below.
```bash
$ sudo apt-get install libcanberra-gtk*
   ...
$
```

Typora crashed at the first time I used it. Even the command prompt is messed up. So I reconnected to the EC2 instance and ran typora again. It didn't crash. So let's use typora and see if the problem has been solved.
