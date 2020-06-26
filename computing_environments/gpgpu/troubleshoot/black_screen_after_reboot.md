* Draft: 2020-06-26 (Fri)

# Black Screen after Reboot



First, press the `ESC` key to enter the GRUB menu.





I tried to reinstall the graphics card driver.

```bash
$ sudo apt-get -y install cuda
Reading package lists... Done
Building dependency tree       
Reading state information... Done
cuda is already the newest version (11.0.1-1).
You might want to run 'apt --fix-broken install' to correct these.
The following packages have unmet dependencies:
 cuda-drivers-450 : Depends: libnvidia-compute-450 (>= 450.36.06) but it is not going to be installed
 libnvidia-decode-450 : Depends: libnvidia-compute-450 (= 450.36.06-0ubuntu1) but it is not going to be installed
 nvidia-compute-utils-450 : Depends: libnvidia-compute-450 but it is not going to be installed
 nvidia-driver-450 : Depends: libnvidia-compute-450 (= 450.36.06-0ubuntu1) but it is not going to be installed
                     Recommends: libnvidia-compute-450:i386 (= 450.36.06-0ubuntu1) but it is not installable
                     Recommends: libnvidia-decode-450:i386 (= 450.36.06-0ubuntu1) but it is not installable
                     Recommends: libnvidia-encode-450:i386 (= 450.36.06-0ubuntu1) but it is not installable
                     Recommends: libnvidia-ifr1-450:i386 (= 450.36.06-0ubuntu1) but it is not installable
                     Recommends: libnvidia-fbc1-450:i386 (= 450.36.06-0ubuntu1) but it is not installable
                     Recommends: libnvidia-gl-450:i386 (= 450.36.06-0ubuntu1) but it is not installable
 nvidia-utils-450 : Depends: libnvidia-compute-450 but it is not going to be installed
E: Unmet dependencies. Try 'apt --fix-broken install' with no packages (or specify a solution).
$
```



```bash
$ sudo apt --fix-broken install
Reading package lists... Done
Building dependency tree       
Reading state information... Done
Correcting dependencies... Done
The following packages were automatically installed and are no longer required:
  libatomic1:i386 libbsd0:i386 libdrm-amdgpu1:i386 libdrm-intel1:i386 libdrm-nouveau2:i386
  libdrm-radeon1:i386 libdrm2:i386 libedit2:i386 libelf1:i386 libexpat1:i386 libffi6:i386 libgl1:i386
  libgl1-mesa-dri:i386 libglapi-mesa:i386 libglvnd0:i386 libglx-mesa0:i386 libglx0:i386 libllvm9:i386
  libnvidia-common-440 libnvidia-extra-440 libpciaccess0:i386 libsensors4:i386 libstdc++6:i386
  libx11-6:i386 libx11-xcb1:i386 libxau6:i386 libxcb-dri2-0:i386 libxcb-dri3-0:i386 libxcb-glx0:i386
  libxcb-present0:i386 libxcb-sync1:i386 libxcb1:i386 libxdamage1:i386 libxdmcp6:i386 libxext6:i386
  libxfixes3:i386 libxshmfence1:i386 libxxf86vm1:i386
Use 'sudo apt autoremove' to remove them.
The following additional packages will be installed:
  libnvidia-compute-450
The following NEW packages will be installed:
  libnvidia-compute-450
0 upgraded, 1 newly installed, 0 to remove and 10 not upgraded.
124 not fully installed or removed.
Need to get 0 B/21.8 MB of archives.
After this operation, 115 MB of additional disk space will be used.
Do you want to continue? [Y/n] y
Get:1 file:/var/cuda-repo-ubuntu1804-11-0-local  libnvidia-compute-450 450.36.06-0ubuntu1 [21.8 MB]
(Reading database ... 220201 files and directories currently installed.)
Preparing to unpack .../libnvidia-compute-450_450.36.06-0ubuntu1_amd64.deb ...
Unpacking libnvidia-compute-450:amd64 (450.36.06-0ubuntu1) ...
dpkg: error processing archive /var/cuda-repo-ubuntu1804-11-0-local/./libnvidia-compute-450_450.36.06-0ubuntu1_amd64.deb (--unpack):
 trying to overwrite '/usr/lib/x86_64-linux-gnu/libnvidia-allocator.so', which is also in package libnvidia-extra-440:amd64 440.82-0ubuntu0~0.18.04.2
Errors were encountered while processing:
 /var/cuda-repo-ubuntu1804-11-0-local/./libnvidia-compute-450_450.36.06-0ubuntu1_amd64.deb
E: Sub-process /usr/bin/dpkg returned an error code (1)
$
```

```bash
$ sudo gedit /etc/default/grub
```

Change

```text
GRUB_CMDLINE_LINUX_DEFAULT="quiet splash"
```

to

```text
GRUB_CMDLINE_LINUX_DEFAULT="quiet splash nomodeset"
```

in

```text
# If you change this file, run 'update-grub' afterwards to update
# /boot/grub/grub.cfg.
# For full documentation of the options in this file, see:
#   info -f grub -n 'Simple configuration'

GRUB_DEFAULT=0
GRUB_TIMEOUT_STYLE=hidden
GRUB_TIMEOUT=10
GRUB_DISTRIBUTOR=`lsb_release -i -s 2> /dev/null || echo Debian`
GRUB_CMDLINE_LINUX_DEFAULT="quiet splash"
GRUB_CMDLINE_LINUX=""

# Uncomment to enable BadRAM filtering, modify to suit your needs
# This works with Linux (no patch required) and with any kernel that obtains
# the memory map information from GRUB (GNU Mach, kernel of FreeBSD ...)
#GRUB_BADRAM="0x01234567,0xfefefefe,0x89abcdef,0xefefefef"

# Uncomment to disable graphical terminal (grub-pc only)
#GRUB_TERMINAL=console

# The resolution used on graphical terminal
# note that you can use only modes which your graphic card supports via VBE
# you can see them in real GRUB with the command `vbeinfo'
#GRUB_GFXMODE=640x480

# Uncomment if you don't want GRUB to pass "root=UUID=xxx" parameter to Linux
#GRUB_DISABLE_LINUX_UUID=true

# Uncomment to disable generation of recovery mode menu entries
#GRUB_DISABLE_RECOVERY="true"

# Uncomment to get a beep at grub start
#GRUB_INIT_TUNE="480 440 1"
```



```bash
$ sudo update-grub
```

