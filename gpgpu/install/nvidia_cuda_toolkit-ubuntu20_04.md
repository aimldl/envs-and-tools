

* Rev.2: 2021-01-08 (Thu)
* Rev.1: 2020-06-25 (Thu)
* Draft: 2019-07-23 (Tue)

# Install NVIDIA CUDA Toolkit for Ubuntu 20.04

## Summary

Step 1. Pre-installation actions

```bash
$ lspci | grep -i nvidia
$ uname -m && cat /etc/*release
$ gcc --version
```

Step 2. Update/upgrade the system and install dependencies

```bash
$ sudo apt-get update && sudo apt-get upgrade -y
$ sudo apt install -y build-essential
$ sudo apt-get install -y python-dev python3-dev python-pip python3-pip
#$ sudo apt-get install linux-headers-$(uname -r)
```

Step 3. Clean the existing NVIDIA driver.

```bash
# TODO: include -y to remove automatically
$ sudo apt-get purge nvidia*
$ sudo apt-get autoremove
$ sudo apt-get autoclean
$ sudo rm -rf /usr/local/cuda*
```

Step 4. Install the latest NVIDIA CUDA

* cuda 11.2 is the latest version (as of 2021-01-08). 
* You may change the version name in the following command.
* These commands are from ***Installation instructions: deb (network)*** below. 

```bash
$ wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2004/x86_64/cuda-ubuntu2004.pin
$ sudo mv cuda-ubuntu2004.pin /etc/apt/preferences.d/cuda-repository-pin-600
$ wget https://developer.download.nvidia.com/compute/cuda/11.2.0/local_installers/cuda-repo-ubuntu2004-11-2-local_11.2.0-460.27.04-1_amd64.deb
$ sudo dpkg -i cuda-repo-ubuntu2004-11-2-local_11.2.0-460.27.04-1_amd64.deb
$ sudo apt-key add /var/cuda-repo-ubuntu2004-11-2-local/7fa2af80.pub
$ sudo apt-get update -y
$ sudo apt-get -y install cuda
```

Step 5. Reboot the system

```bash
$ reboot
```

For the full detail of this document, refer to [NVIDIA CUDA Installation Guide for Linux](https://docs.nvidia.com/cuda/cuda-installation-guide-linux/index.html#abstract). A more general guideline is available at [NVIDIA CUDA GETTING STARTED GUIDE FOR LINUX](http://developer.download.nvidia.com/compute/cuda/7_0/Prod/doc/CUDA_Getting_Started_Linux.pdf). [Verify CUDA Installation](https://xcat-docs.readthedocs.io/en/stable/advanced/gpu/nvidia/verify_cuda_install.html)

Step 6. Post-installation actions

TODO: check the command & update the output at the bottom.

```bash
# Double-check the directory name
$ ls /usr/local/ | grep "cuda-"
$ ls /usr/local/

# Add the PATH variable at the end of `.bashrc`
$ echo 'export PATH=/usr/local/cuda-11.0/bin${PATH:+:${PATH}}' >> ~/.bashrc
$ echo 'export LD_LIBRARY_PATH=/usr/local/cuda-11.0/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}' >> ~/.bashrc

# Reload the bash
$ source ~/.bashrc

# Check 
$ sudo ldconfig
$ nvidia-smi
$ echo $PATH
/usr/local/cuda-11.0/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
$
```

## Bash script: `install_nvidia_cuda_libraries-ubuntu20_04`

```basic
#!/bin/bash
# install_nvidia_cuda_libraries-ubuntu20_04

# Update, upgrade the system and install dependencies
sudo apt-get update && sudo apt-get upgrade -y
sudo apt install -y build-essential
sudo apt-get install -y python-dev python3-dev python-pip python3-pip

# Clean the existing NVIDIA driver.
# TODO: include -y to remove automatically
sudo apt-get purge nvidia*
sudo apt-get autoremove
sudo apt-get autoclean
sudo rm -rf /usr/local/cuda*

# Install the latest NVIDIA CUDA
wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2004/x86_64/cuda-ubuntu2004.pin
sudo mv cuda-ubuntu2004.pin /etc/apt/preferences.d/cuda-repository-pin-600
wget https://developer.download.nvidia.com/compute/cuda/11.2.0/local_installers/cuda-repo-ubuntu2004-11-2-local_11.2.0-460.27.04-1_amd64.deb
sudo dpkg -i cuda-repo-ubuntu2004-11-2-local_11.2.0-460.27.04-1_amd64.deb
sudo apt-key add /var/cuda-repo-ubuntu2004-11-2-local/7fa2af80.pub
sudo apt-get update -y
sudo apt-get -y install cuda

# Reboot the system
read -p 'Reboot? (y/n): ') REPLY
if [ $REPLY == "[Yy]" ]; then
  echo "Rebooting..."
  reboot
fi

echo "Exiting..."
exit 0
```

## Pre-installation actions

```bash
$ lspci | grep -i nvidia
01:00.0 VGA compatible controller: NVIDIA Corporation GP104 [GeForce GTX 1080] (rev a1)
01:00.1 Audio device: NVIDIA Corporation GP104 High Definition Audio Controller (rev a1)
02:00.0 VGA compatible controller: NVIDIA Corporation GP104 [GeForce GTX 1080] (rev a1)
02:00.1 Audio device: NVIDIA Corporation GP104 High Definition Audio Controller (rev a1)
$ uname -m && cat /etc/*release
x86_64
DISTRIB_ID=Ubuntu
DISTRIB_RELEASE=20.04
DISTRIB_CODENAME=focal
DISTRIB_DESCRIPTION="Ubuntu 20.04.1 LTS"
NAME="Ubuntu"
VERSION="20.04.1 LTS (Focal Fossa)"
ID=ubuntu
ID_LIKE=debian
PRETTY_NAME="Ubuntu 20.04.1 LTS"
VERSION_ID="20.04"
HOME_URL="https://www.ubuntu.com/"
SUPPORT_URL="https://help.ubuntu.com/"
BUG_REPORT_URL="https://bugs.launchpad.net/ubuntu/"
PRIVACY_POLICY_URL="https://www.ubuntu.com/legal/terms-and-policies/privacy-policy"
VERSION_CODENAME=focal
UBUNTU_CODENAME=focal
$ gcc --version
gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
Copyright (C) 2019 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

$ uname -r
5.4.0-58-generic
$
```

The above output is for Dell Alienware Aurora R7 with two NVIDIA GPU cards (GeForce GTX 1080) with the recent Ubuntu 20.04.

## Download the NVIDIA CUDA Toolkit

### Select the target platform to install the toolkit

Go to http://developer.nvidia.com/cuda-downloads.

<img src="images/nvidia-cuda_toolkit_11_2_rc_download-select_target_platform.png">

And select the options for the target platform. For Ubuntu 20.04, the selections are presented below. 

<img src="images/nvidia-cuda_toolkit_11_2_rc_download-select_target_platform-selected.png">

The `Installer Type` can be any of the three options while my preference is `deb(local)` in this example. When the selections are made, the installation instructions and some useful links are presented.

<img src="images/nvidia-cuda_toolkit_11_2_rc_download-download_installer_for_linux_ubuntu_20_04_x86_64.png">

### Some useful links presented in this part

[CUDA Quick Start Guide](https://docs.nvidia.com/cuda/cuda-quick-start-guide/index.html): Minimal first-steps instructions to get CUDA running on a standard system.

[CUDA FAQ](https://developer.nvidia.com/cuda-faq)

[CUDA Samples](https://github.com/nvidia/cuda-samples) at https://github.com/nvidia/cuda-samples

[CUDA Toolkit Documentation v11.0.171](https://docs.nvidia.com/cuda/)

[Accelerated Computing - Training](https://developer.nvidia.com/accelerated-computing-training)

[NVIDIA Developer Forums](https://forums.developer.nvidia.com/)

--------

[Open-Source Software for the CUDA Toolkit](http://developer.download.nvidia.com/compute/cuda/opensource/11.0.1/): `cuda_gdb_src-all-all-11.0.172.tar.gz` is the only file in this link.sudo rm -rf /usr/local/cuda*

[Index of /compute/cuda/opensource](https://developer.download.nvidia.com/compute/cuda/opensource/): some more open source packages are available here.

[NVIDIA CUDA Toolkit Release Notes](https://docs.nvidia.com/cuda/cuda-toolkit-release-notes/index.html)

[CUDA Toolkit Archive](https://developer.nvidia.com/cuda-toolkit-archive)

### Download Installer for Linux Ubuntu 20.04 x86_64

Recall three options exits for `Installer Type` in `CUDA Toolkit 11.2 RC Download > Select Target Platform`. 

* runfile (local)
* deb (local): this is the option for this example.
* deb (network)

**Memo:** It took about 4 hours to download files for `deb (local)` while 1 and a half hours for `deb (network)`.  For me, `deb (local)` failed and I had to reinstall from the OS all over again. `deb (network)` worked fine and the summary is at the top of this document.

The CUDA Toolkit will be downloaded and installed which contains

* the CUDA driver
* tools needed to create, build and run a CUDA application
* libraries, header files, CUDA samples source code, and other resources.

#### Installation instructions: deb (local)

```bash
$ wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2004/x86_64/cuda-ubuntu2004.pin
$ sudo mv cuda-ubuntu2004.pin /etc/apt/preferences.d/cuda-repository-pin-600
$ wget https://developer.download.nvidia.com/compute/cuda/11.2.0/local_installers/cuda-repo-ubuntu2004-11-2-local_11.2.0-460.27.04-1_amd64.deb
$ sudo dpkg -i cuda-repo-ubuntu2004-11-2-local_11.2.0-460.27.04-1_amd64.deb
$ sudo apt-key add /var/cuda-repo-ubuntu2004-11-2-local/7fa2af80.pub
$ sudo apt-get update -y
$ sudo apt-get -y install cuda
```

## Reboot the system

```bash
$ reboot
```

## Post-installation actions

### Mandatory Actions

Step 1. Double-check the directory name

```bash
$ ls /usr/local/ | grep "cuda-"
cuda-11.0
# or
$ ls /usr/local/
bin  cuda-11.0  etc  games  include  lib  man  sbin  share  src
$
```

Step 2. Add the PATH variable at the end of `.bashrc`

Either run

```bash
$ echo 'export PATH=/usr/local/cuda-11.0/bin${PATH:+:${PATH}}' >> ~/.bashrc
$ echo 'export LD_LIBRARY_PATH=/usr/local/cuda-11.0/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}' >> ~/.bashrc
```

or add the following two variables to `.bashrc` with a text editor.

```bash
export PATH=/usr/local/cuda-11.0/bin${PATH:+:${PATH}}
export LD_LIBRARY_PATH=/usr/local/cuda-11.0/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
```

Step 3. Reload the bash

```bash
$ source ~/.bashrc
```

Step 4. Check 

```bash
$ sudo ldconfig
$ nvidia-smi
$ echo $PATH
/usr/local/cuda-11.0/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
$
```

## Next

* [Install cuDNN](nvidia_cudnn.md)

## References

* [NVIDIA CUDA Installation Guide for Linux](https://docs.nvidia.com/cuda/cuda-installation-guide-linux/index.html#abstract)

```bash
$ nvidia-smi
Mon Jun 29 13:46:18 2020       
+-----------------------------------------------------------------------------+
| NVIDIA-SMI 450.36.06    Driver Version: 450.36.06    CUDA Version: 11.0     |
|-------------------------------+----------------------+----------------------+
| GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
|                               |                      |               MIG M. |
|===============================+======================+======================|
|   0  GeForce GTX 1080    On   | 00000000:01:00.0  On |                  N/A |
| 28%   34C    P8     8W / 180W |    336MiB /  8118MiB |      2%      Default |
|                               |                      |                  N/A |
+-------------------------------+----------------------+----------------------+
|   1  GeForce GTX 1080    On   | 00000000:02:00.0 Off |                  N/A |
| 27%   30C    P8     5W / 180W |      2MiB /  8119MiB |      0%      Default |
|                               |                      |                  N/A |
+-------------------------------+----------------------+----------------------+
                                                                               
+-----------------------------------------------------------------------------+
| Processes:                                                                  |
|  GPU   GI   CI        PID   Type   Process name                  GPU Memory |
|        ID   ID                                                   Usage      |
|=============================================================================|
|    0   N/A  N/A      1146      G   /usr/lib/xorg/Xorg                171MiB |
|    0   N/A  N/A      1259      G   /usr/bin/gnome-shell               88MiB |
|    0   N/A  N/A      1755      G   /proc/self/exe                     34MiB |
|    0   N/A  N/A      2150      G   ...AAAAAAAAA= --shared-files       36MiB |
+-----------------------------------------------------------------------------+
$
```

