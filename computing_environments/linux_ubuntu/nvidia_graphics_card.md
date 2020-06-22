(base) aimldl@GPU-Desktop:~$ !774
echo $LD_LIBRARY_PATH
/usr/local/cuda-10.1/lib64
(base) aimldl@GPU-Desktop:~$ cd /usr/local/cuda-10.1/
(base) aimldl@GPU-Desktop:/usr/local/cuda-10.1$ ls
LICENSE  bin  include  nvvm     targets
README   doc  lib64    samples  version.txt
(base) aimldl@GPU-Desktop:/usr/local/cuda-10.1$ lshw -c display
WARNING: you should run this program as super-user.
  *-display UNCLAIMED       
       description: VGA compatible controller
       product: GP102 [GeForce GTX 1080 Ti]
       vendor: NVIDIA Corporation
       physical id: 0
       bus info: pci@0000:01:00.0
       version: a1
       width: 64 bits
       clock: 33MHz
       capabilities: vga_controller bus_master cap_list
       configuration: latency=0
       resources: memory:de000000-deffffff memory:c0000000-cfffffff memory:d0000000-d1ffffff ioport:e000(size=128) memory:c0000-dffff
  *-display UNCLAIMED
       description: VGA compatible controller
       product: GP102 [GeForce GTX 1080 Ti]
       vendor: NVIDIA Corporation
       physical id: 0
       bus info: pci@0000:02:00.0
       version: a1
       width: 64 bits
       clock: 33MHz
       capabilities: vga_controller cap_list
       configuration: latency=0
       resources: memory:dc000000-dcffffff memory:a0000000-afffffff memory:b0000000-b1ffffff ioport:d000(size=128) memory:dd000000-dd07ffff
  *-display UNCLAIMED
       description: Display controller
       product: HD Graphics 630
       vendor: Intel Corporation
       physical id: 2
       bus info: pci@0000:00:02.0
       version: 04
       width: 64 bits
       clock: 33MHz
       capabilities: bus_master cap_list
       configuration: latency=0
       resources: memory:db000000-dbffffff memory:90000000-9fffffff ioport:f000(size=64)
WARNING: output may be incomplete or inaccurate, you should run this program as super-user.
(base) aimldl@GPU-Desktop:/usr/local/cuda-10.1$ lshw -c displaysudo ubuntu-drivers devices
Hardware Lister (lshw) - B.02.18
usage: lshw [-format] [-options ...]
       lshw -version

	-version        print program version (B.02.18)

format can be
	-html           output hardware tree as HTML
	-xml            output hardware tree as XML
	-json           output hardware tree as a JSON object
	-short          output hardware paths
	-businfo        output bus information

options can be
	-class CLASS    only show a certain class of hardware
	-C CLASS        same as '-class CLASS'
	-c CLASS        same as '-class CLASS'
	-disable TEST   disable a test (like pci, isapnp, cpuid, etc. )
	-enable TEST    enable a test (like pci, isapnp, cpuid, etc. )
	-quiet          don't display status
	-sanitize       sanitize output (remove sensitive information like serial numbers, etc.)
	-numeric        output numeric IDs (for PCI, USB, etc.)
	-notime         exclude volatile attributes (timestamps) from output

(base) aimldl@GPU-Desktop:/usr/local/cuda-10.1$ 
(base) aimldl@GPU-Desktop:/usr/local/cuda-10.1$ sudo ubuntu-drivers devices
[sudo] password for aimldl: 
== /sys/devices/pci0000:00/0000:00:01.1/0000:02:00.0 ==
modalias : pci:v000010DEd00001B06sv00001028sd00003600bc03sc00i00
vendor   : NVIDIA Corporation
model    : GP102 [GeForce GTX 1080 Ti]
driver   : nvidia-driver-418 - third-party free recommended
driver   : nvidia-driver-390 - distro non-free
driver   : xserver-xorg-video-nouveau - distro free builtin

(base) aimldl@GPU-Desktop:/usr/local/cuda-10.1$ grep -i "nvidia" /var/log/Xorg.0.log
[     4.421] (II) LoadModule: "nvidia"
[     4.421] (II) Loading /usr/lib/xorg/modules/drivers/nvidia_drv.so
[     4.424] (II) Module nvidia: vendor="NVIDIA Corporation"
[     4.425] (II) NVIDIA dlloader X Driver  440.31  Sun Oct 27 02:16:54 UTC 2019
[     4.425] (II) NVIDIA Unified Driver for all Supported NVIDIA GPUs
[     4.446] (EE) NVIDIA: Failed to initialize the NVIDIA kernel module. Please see the
[     4.446] (EE) NVIDIA:     system's kernel log for additional error messages and
[     4.446] (EE) NVIDIA:     consult the NVIDIA README for details.
[     4.449] (EE) NVIDIA: Failed to initialize the NVIDIA kernel module. Please see the
[     4.449] (EE) NVIDIA:     system's kernel log for additional error messages and
[     4.449] (EE) NVIDIA:     consult the NVIDIA README for details.
[     4.451] (EE) NVIDIA: Failed to initialize the NVIDIA kernel module. Please see the
[     4.451] (EE) NVIDIA:     system's kernel log for additional error messages and
[     4.451] (EE) NVIDIA:     consult the NVIDIA README for details.
[     4.453] (EE) NVIDIA: Failed to initialize the NVIDIA kernel module. Please see the
[     4.453] (EE) NVIDIA:     system's kernel log for additional error messages and
[     4.453] (EE) NVIDIA:     consult the NVIDIA README for details.
[     4.456] (II) NVIDIA dlloader X Driver  440.31  Sun Oct 27 02:16:54 UTC 2019
[     4.456] (II) NVIDIA Unified Driver for all Supported NVIDIA GPUs
[     4.456] (II) NOUVEAU driver for NVIDIA chipset families :
[     4.836] (II) config/udev: Adding input device HDA NVidia HDMI/DP,pcm=3 (/dev/input/event21)
[     4.837] (II) config/udev: Adding input device HDA NVidia HDMI/DP,pcm=7 (/dev/input/event22)
[     4.837] (II) config/udev: Adding input device HDA NVidia HDMI/DP,pcm=8 (/dev/input/event23)
[     4.837] (II) config/udev: Adding input device HDA NVidia HDMI/DP,pcm=9 (/dev/input/event24)
[     4.837] (II) config/udev: Adding input device HDA NVidia HDMI/DP,pcm=3 (/dev/input/event17)
[     4.838] (II) config/udev: Adding input device HDA NVidia HDMI/DP,pcm=7 (/dev/input/event18)
[     4.838] (II) config/udev: Adding input device HDA NVidia HDMI/DP,pcm=8 (/dev/input/event19)
[     4.838] (II) config/udev: Adding input device HDA NVidia HDMI/DP,pcm=9 (/dev/input/event20)
[     5.150] (II) config/udev: Adding input device HDA NVidia HDMI/DP,pcm=9 (/dev/input/event20)
[     5.150] (II) config/udev: Adding input device HDA NVidia HDMI/DP,pcm=7 (/dev/input/event22)
[     5.150] (II) config/udev: Adding input device HDA NVidia HDMI/DP,pcm=3 (/dev/input/event21)
[     5.150] (II) config/udev: Adding input device HDA NVidia HDMI/DP,pcm=7 (/dev/input/event18)
[     5.150] (II) config/udev: Adding input device HDA NVidia HDMI/DP,pcm=8 (/dev/input/event23)
[     5.151] (II) config/udev: Adding input device HDA NVidia HDMI/DP,pcm=8 (/dev/input/event19)
[     5.151] (II) config/udev: Adding input device HDA NVidia HDMI/DP,pcm=9 (/dev/input/event24)
[     5.151] (II) config/udev: Adding input device HDA NVidia HDMI/DP,pcm=3 (/dev/input/event17)
(base) aimldl@GPU-Desktop:/usr/local/cuda-10.1$ lspci
00:00.0 Host bridge: Intel Corporation Xeon E3-1200 v6/7th Gen Core Processor Host Bridge/DRAM Registers (rev 05)
00:01.0 PCI bridge: Intel Corporation Xeon E3-1200 v5/E3-1500 v5/6th Gen Core Processor PCIe Controller (x16) (rev 05)
00:01.1 PCI bridge: Intel Corporation Xeon E3-1200 v5/E3-1500 v5/6th Gen Core Processor PCIe Controller (x8) (rev 05)
00:02.0 Display controller: Intel Corporation HD Graphics 630 (rev 04)
00:14.0 USB controller: Intel Corporation 200 Series/Z370 Chipset Family USB 3.0 xHCI Controller
00:15.0 Signal processing controller: Intel Corporation 200 Series PCH Serial IO I2C Controller #0
00:15.1 Signal processing controller: Intel Corporation 200 Series PCH Serial IO I2C Controller #1
00:16.0 Communication controller: Intel Corporation 200 Series PCH CSME HECI #1
00:17.0 RAID bus controller: Intel Corporation SATA Controller [RAID mode]
00:1b.0 PCI bridge: Intel Corporation 200 Series PCH PCI Express Root Port #17 (rev f0)
00:1c.0 PCI bridge: Intel Corporation 200 Series PCH PCI Express Root Port #2 (rev f0)
00:1c.2 PCI bridge: Intel Corporation 200 Series PCH PCI Express Root Port #3 (rev f0)
00:1c.3 PCI bridge: Intel Corporation 200 Series PCH PCI Express Root Port #4 (rev f0)
00:1e.0 Signal processing controller: Intel Corporation 200 Series/Z370 Chipset Family Serial IO UART Controller #0
00:1f.0 ISA bridge: Intel Corporation 200 Series PCH LPC Controller (Z270)
00:1f.2 Memory controller: Intel Corporation 200 Series/Z370 Chipset Family Power Management Controller
00:1f.3 Audio device: Intel Corporation 200 Series PCH HD Audio
00:1f.4 SMBus: Intel Corporation 200 Series/Z370 Chipset Family SMBus Controller
01:00.0 VGA compatible controller: NVIDIA Corporation GP102 [GeForce GTX 1080 Ti] (rev a1)
01:00.1 Audio device: NVIDIA Corporation GP102 HDMI Audio Controller (rev a1)
02:00.0 VGA compatible controller: NVIDIA Corporation GP102 [GeForce GTX 1080 Ti] (rev a1)
02:00.1 Audio device: NVIDIA Corporation GP102 HDMI Audio Controller (rev a1)
03:00.0 Non-Volatile memory controller: Sandisk Corp WD Black NVMe SSD
04:00.0 USB controller: ASMedia Technology Inc. ASM1142 USB 3.1 Host Controller
05:00.0 Network controller: Qualcomm Atheros QCA6174 802.11ac Wireless Network Adapter (rev 32)
06:00.0 Ethernet controller: Qualcomm Atheros Killer E2400 Gigabit Ethernet Controller (rev 10)
(base) aimldl@GPU-Desktop:/usr/local/cuda-10.1$ ls /var/log/packages/nvidia*
ls: cannot access '/var/log/packages/nvidia*': No such file or directory
(base) aimldl@GPU-Desktop:/usr/local/cuda-10.1$ cd /var
(base) aimldl@GPU-Desktop:/var$ ls
backups                               local    run
cache                                 lock     snap
crash                                 log      spool
cuda-repo-10-1-local-10.1.105-418.39  mail     tmp
cuda-repo-10-1-local-10.1.168-418.67  metrics
lib                                   opt
(base) aimldl@GPU-Desktop:/var$ cd log
(base) aimldl@GPU-Desktop:/var/log$ ls
Xorg.0.log              auth.log.2.gz           journal
Xorg.0.log.old          auth.log.3.gz           kern.log
Xorg.1.log              auth.log.4.gz           kern.log.1
Xorg.1.log.old          boot.log                kern.log.2.gz
Xorg.2.log              bootstrap.log           kern.log.3.gz
alternatives.log        btmp                    kern.log.4.gz
alternatives.log.1      btmp.1                  lastlog
alternatives.log.10.gz  cups                    lightdm
alternatives.log.2.gz   dist-upgrade            mysql
alternatives.log.3.gz   dpkg.log                nvidia-installer.log
alternatives.log.4.gz   dpkg.log.1              nvidia-uninstall.log
alternatives.log.5.gz   dpkg.log.10.gz          prime-offload.log
alternatives.log.6.gz   dpkg.log.2.gz           prime-supported.log
alternatives.log.7.gz   dpkg.log.3.gz           speech-dispatcher
alternatives.log.8.gz   dpkg.log.4.gz           syslog
alternatives.log.9.gz   dpkg.log.5.gz           syslog.1
apport.log              dpkg.log.6.gz           syslog.2.gz
apport.log.1            dpkg.log.7.gz           syslog.3.gz
apport.log.2.gz         dpkg.log.8.gz           syslog.4.gz
apport.log.3.gz         dpkg.log.9.gz           syslog.5.gz
apport.log.4.gz         faillog                 syslog.6.gz
apport.log.5.gz         fontconfig.log          syslog.7.gz
apport.log.6.gz         gdm3                    tallylog
apport.log.7.gz         gpu-manager-switch.log  unattended-upgrades
apt                     gpu-manager.log         wtmp
auth.log                hp                      wtmp.1
auth.log.1              installer
(base) aimldl@GPU-Desktop:/var/log$ ls p*
prime-offload.log  prime-supported.log
(base) aimldl@GPU-Desktop:/var/log$ gedit /etc/X11/xorg.conf &
[1] 19143
(base) aimldl@GPU-Desktop:/var/log$ 
