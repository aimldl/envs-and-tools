* Rev.3: 2020-06-24 (Wed)
* Rev.2: 2020-06-10 (Wed)
* Rev.1: 2019-10-10 (Thu)
* Draft: 2019-03-03 (Sun)

# Install NVIDIA Graphics Driver on Ubuntu

## Summary

Step 1. Download the NVIDIA Graphics Card Driver installation file.

## Download the driver installation file

 `./NVIDIA-Linux-x86_64-440.82.run` is downloaded in the `Downloads` directory on Ubuntu 18.04. 

```bash
$ sudo add-apt-repository ppa:graphics-drivers/ppa
$ sudo apt update
$ sudo apt upgrade -y
```

Google search: nvidia graphics driver download

https://www.nvidia.com/download/index.aspx?lang=en-us

Select the right options for the graphics card. In this example, I need a driver for `GeForce GTC 1080Ti` on Linux.

<img src="images/nvidia_driver_downloads-geforce_gtx_1080ti_linux_64bit.png">

Click the `SEARCH` button.

<img src="images/nvidia-drivers-linux_x64_amd64_em64t_display_driver.png">

Click the DOWNLOAD button and the download confirmation page will show up.

<img src="images/nvidia_home-download_drivers-download_confirmation.png">

Click the DOWNLOAD button. When the pop-up window shows up, click the `Save File` button and the file download begins.

<img src="images/nvidia_home-download_drivers-opening_nvidia-linux-x86_64-440_82_run.png">

When the download is finished, check the downloaded file. The download directory differs from web browser to web browser.

```bash
$ cd ~/Downloads/
$ ls
NVIDIA-Linux-x86_64-440.82.run
$
```

## Check the current graphics driver

Go to `Settings > Details > About` and check `Graphics`. In this example, `NV134` is set up for the graphics card.

<img src="images/ubuntu_18_04-settings-details-about.png">

```bash

```

## Installation

The official driver is manually installed below. For other options, refer to [How to install the NVIDIA drivers on Ubuntu 18.04 Bionic Beaver Linux](https://linuxconfig.org/how-to-install-the-nvidia-drivers-on-ubuntu-18-04-bionic-beaver-linux).

### Step 1. Switch to TTY2 by entering `Ctrl+Alt+F2` and log in.

```bash
Ubuntu 18.04.02 LTS GPU-Dektop tty2
GPU-Desktop login: aimldl
Password:
  ...
$
```

### Step 2. Exit X Windows system or the GUI

```bash
$ sudo service lightdm stop
[sudo] password for aimldl:
$
```

If you skip this step and proceed to the next step, the installation will fail at any rate. In other words, you do not exit X Windows sytem and try to install the driver. The following error message will be shown and you can not proceed.

<img src="images/nvidia_accelerated_graphics_driver_for_linux-x86_64-the_distribution-provided_pre-install_script_failed.png">

When `Abort installation` is selected, the following message shows up.

<img src="images/nvidia_accelerated_graphics_driver_for_linux-x86_64-the_distribution-provided_pre-install_script_failed-warning.png">

### Step 3. Install NVIDIA Graphics Driver.

```bash
$ cd Downloads/
$ chmod +x ./NVIDIA-Linux-x86_64-440.82.run
$ sudo ./NVIDIA-Linux-x86_64-440.82.run
[sudo] password for aimldl:
```

```bash
There appears to already be a driver installed on your system (version:
440.44). As part of installing this driver (version: 440.82), the existing
driver will be uninstalled. Are you sure you want to continue?

               Continue installation      Abort installation
```

Select `Continue installation`.

```bash
The distribution-provided pre-install script failed! Are you sure you want
to continue?
               Continue installation      Abort installation
```

Select `Continue installation` and the installation will start.

```bash
Install NVIDIA's 32-bit compatibility libraries?
                        Yes                      No
```

Select `Yes`(default)

```bash
Would you like to run the nvidia-xconfig utility to automatically update
your X configuration file so that the NVIDIA X driver will be used when you
restart X?  Any pre-existing X configuration file will be backed up.
                        Yes                       No
```

Select `Yes`

## Verification

Run `nvidia-smi` and see if the graphics card(s) is/are properly recognized.

```bash
$ nvidia-smi
```

A sample message is presented below.

```bash
Wed Jun 10 15:00:17 2020       
+-----------------------------------------------------------------------------+
| NVIDIA-SMI 440.82       Driver Version: 440.82       CUDA Version: 10.2     |
|-------------------------------+----------------------+----------------------+
| GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
|===============================+======================+======================|
|   0  GeForce GTX 108...  Off  | 00000000:01:00.0  On |                  N/A |
| 23%   34C    P8    13W / 250W |    174MiB / 11177MiB |      0%      Default |
+-------------------------------+----------------------+----------------------+
|   1  GeForce GTX 108...  Off  | 00000000:02:00.0 Off |                  N/A |
| 23%   29C    P8     7W / 250W |      2MiB / 11178MiB |      0%      Default |
+-------------------------------+----------------------+----------------------+
                                                                               
+-----------------------------------------------------------------------------+
| Processes:                                                       GPU Memory |
|  GPU       PID   Type   Process name                             Usage      |
|=============================================================================|
|    0       994      G   /usr/lib/xorg/Xorg                           105MiB |
|    0      2078      G   /usr/bin/gnome-shell                          66MiB |
+-----------------------------------------------------------------------------+
$
```

There're two GPUs on my machine and they're up and running.

## Solutions to Frequently Occurring Errors

### Problem 1: nvidia-installer must be run as root

```bash
$ ./NVIDIA-Linux-x86_64-440.82.run
#   incurs the following error message

ERROR: nvidia-installer must be run as root
```

NVIDIA graphics driver must be run as a root.

### Solution 1: 

```bash
$ sudo ./NVIDIA-Linux-x86_64-440.82.run
```

### Problem 2: You appear to be running an X server

You must exit the X Server. Otherwise the following error occurs:

```bash
$ sudo ./NVIDIA-Linux-x86_64-440.82.run
#   incurs the following error message

ERROR: You appear to be running an X server; please exit X before
       installing. For further details, please see the section INSTALLING
       THE NVIDIA DRIVER in the README available on the Linux driver
       download page at www.nvidia.com.
```

### Solution 2: 

***Caution: Save all your previous works before following the insturction here.***

#### Step 1. Swith to other TTY terminal

Enter `Ctrl+Alt+F2` and the black background will be switched to a command-line terminal. The new screen looks like:

```bash
Ubuntu 18.04.02 LTS GPU-Dektop tty2
GPU-Desktop login: _
```

Instead of `F2`, you may enter any key between `F2 through F6`. In other words, `Ctrl+Alt+F3` instead of `Ctrl+Alt+F2` or `Ctrl+Alt+F5` instead of `Ctrl+Alt+F2`. There are multiple TTY and you're free to choose any of them. For `Ctrl+Alt+F4`, the last word in the first line is, now, `tty4`.

```bash
Ubuntu 18.04.02 LTS GPU-Dektop tty4
GPU-Desktop login: _
```

In general, `Ctrl+Alt+F7` brings you back to the GUI part. But what's the use of doing so when you see a black screen with a blinking prompt?

#### Step 2. Enter ID and password to log in

```bash
Ubuntu 18.04.02 LTS GPU-Dektop tty2
GPU-Desktop login: aimldl
Password:
  ...
$
```

#### Step 3. Exit the X Windows system or the GUI

```bash
$ sudo service lightdm stop
[sudo] password for aimldl:
$
```

Note the order to run each step is important. If `$ sudo service lightdm stop` is ran before the previous steps, you may get into a trouble. Refer to Problem 3 below for details.

### Problem 3: `$ sudo service lightdm stop` turns everything on the monitor black.

The GUI or X Windows dissapears and everything turns black on the monitor. On the left top corner of the monitor, there is a prompt blinking periodically indicating the Ubuntu is up and running in the background.

Don't panic. It's supposed to be this way if you run this command on the GUI. Only the GUI or X Windows system has been turned off. But the problem in this installation process is you haven't done it in a TTY terminal.

### Solution 3: Switch to a TTY Terminal first and then run `$ sudo service lightdm stop`

* Did you run `$ sudo service lightdm stop` in the "normal" Ubuntu with the GUI or X Windows, not in one of the TTY terminals?
* If so, switch to a TTY terminal by pressing `Ctrl+Alt+F2` and run the command `$ sudo service lightdm stop`.

```bash
Ubuntu 18.04.02 LTS GPU-Dektop tty2
GPU-Desktop login: aimldl
Password:
  ...
$ sudo service lightdm stop
[sudo] password for aimldl:
$
```

All the letters in the monitor should remain as it was.

## References

* [How to install the NVIDIA drivers on Ubuntu 18.04 Bionic Beaver Linux](https://linuxconfig.org/how-to-install-the-nvidia-drivers-on-ubuntu-18-04-bionic-beaver-linux)
* [006. GPGPU 환경 설정](https://m.blog.naver.com/PostView.nhn?blogId=aimldl&logNo=221478837620&referrerCode=0&searchKeyword=linux)