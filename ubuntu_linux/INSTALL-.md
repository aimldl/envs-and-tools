* Rev.1: 2020-12-01 (Tue)

* Draft: 2020-06-22 (Mon)

## Install some basic packages for Ubuntu

[bash_scripts/install_ubuntu_basic_packages](./bash_scripts/install_ubuntu_basic_packages) is a bash script that automatically installs some basic packages for Ubuntu. 

[bash_scripts/install_ubuntu_productivity_packages](bash_scripts/install_ubuntu_productivity_packages) installs some other packages other than the basic packages.

## (Optional) Set up the language settings

## (Optional) Install the NVIDIA Display Driver

```bash
 $ sudo ubuntu-drivers autoinstall
 $ reboot
```

 Verify the installation.

```bash
 $ nvidia-smi
```

 For details, refer to [Install NVIDIA Graphics Card Driver on Ubuntu Automatically](../technical_skills/computing_environments/gpgpu/how_to/install_nvidia_graphics_card_driver_automatically.md).

### Update & upgrade Ubuntu

You should always update your system first before you do anything else. Run the following commands:

```bash
$ sudo apt-get update && sudo apt-get upgrade -y
```

## Install the required package

```bash
$ sudo apt-get install -y software-properties-common
```

## 