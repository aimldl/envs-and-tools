* Draft: 2020-06-20 (Tue)

# Troubleshoot the Lower Resolution after Upgrading Ubuntu

## Problem

When Ubuntu 18.04 is rebooted after upgrading it with 

```bash
$ sudo apt update && sudo apt upgrade -y
  ...
$ reboot
```

the monitor resolution is lowered to VGA.

<img src="images/ubuntu_18_04-after_login-lower_resolution-vga.png">

## Hint

The graphics card for this computer is that of NVIDIA (GeForce GTX 1080Ti). Running `nvidia-smi` shows the status or the graphics card.

```bash
$ nvidia-smi
NVIDIA-SMI has failed because it couldn't communicate with the NVIDIA driver. Make sure that the latest NVIDIA driver is installed and running.
$
```

The above message indicates that NVIDIA Display Driver is overwritten to Ubuntu's default driver during the upgrade.

## Solution

Reinstall the driver

```bash
$ sudo ubuntu-drivers autoinstall
```

and the monitor resolution is back to normal as follows.

<img src="images/ubuntu_18_04-after_login-full_resolution.png">

Run `nvidia-smi` to check the normal status of the graphics card.

```bash
$ nvidia-smi
Tue Jun 30 16:28:16 2020       
+-----------------------------------------------------------------------------+
| NVIDIA-SMI 440.100      Driver Version: 440.100      CUDA Version: 10.2     |
|-------------------------------+----------------------+----------------------+
| GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
|===============================+======================+======================|
|   0  GeForce GTX 108...  Off  | 00000000:01:00.0  On |                  N/A |
| 24%   46C    P0    59W / 250W |    578MiB / 11177MiB |      5%      Default |
+-------------------------------+----------------------+----------------------+
|   1  GeForce GTX 108...  Off  | 00000000:02:00.0 Off |                  N/A |
| 23%   29C    P8     7W / 250W |      9MiB / 11178MiB |      0%      Default |
+-------------------------------+----------------------+----------------------+
                                                                               
+-----------------------------------------------------------------------------+
| Processes:                                                       GPU Memory |
|  GPU       PID   Type   Process name                             Usage      |
|=============================================================================|
|    0      1096      G   /usr/lib/xorg/Xorg                           232MiB |
|    0      2303      G   /usr/bin/gnome-shell                         130MiB |
|    0      5794      G   ...AAAAAAAAAAAACAAAAAAAAAA= --shared-files   171MiB |
|    0     29005      G   ...AAAAAAAAAAAAAAgAAAAAAAAA --shared-files    39MiB |
|    1      1096      G   /usr/lib/xorg/Xorg                             6MiB |
+-----------------------------------------------------------------------------+
$
```

There are two GeForce GTX 1080Ti graphics cards which are up and running.

For details about setting up NVIDIA Graphics Card, refer to [Install NVIDIA Graphics Card Driver on Ubuntu Automatically](../../gpgpu/how_to_install/nvidia_graphics_card_driver_automatically.md).