* Draft: 2020-06-12 (Fri)
# lshw

```bash
$ sudo lshw -C display
```
## Sample Results
### My LG laptop
```bash
[sudo] password for aimldl: 
  *-display                 
       description: VGA compatible controller
       product: HD Graphics 620
       vendor: Intel Corporation
       physical id: 2
       bus info: pci@0000:00:02.0
       version: 02
       width: 64 bits
       clock: 33MHz
       capabilities: pciexpress msi pm vga_controller bus_master cap_list rom
       configuration: driver=i915 latency=0
       resources: irq:128 memory:d0000000-d0ffffff memory:c0000000-cfffffff ioport:e000(size=64) memory:c0000-dffff
$
```
### My Work GPU Desktop
```bash
[sudo] password for aimldl: 
  *-display                 
       description: VGA compatible controller
       product: GP102 [GeForce GTX 1080 Ti]
       vendor: NVIDIA Corporation
       physical id: 0
       bus info: pci@0000:01:00.0
       version: a1
       width: 64 bits
       clock: 33MHz
       capabilities: pm msi pciexpress vga_controller bus_master cap_list rom
       configuration: driver=nvidia latency=0
       resources: irq:150 memory:de000000-deffffff memory:c0000000-cfffffff memory:d0000000-d1ffffff ioport:e000(size=128) memory:c0000-dffff
  *-display
       description: VGA compatible controller
       product: GP102 [GeForce GTX 1080 Ti]
       vendor: NVIDIA Corporation
       physical id: 0
       bus info: pci@0000:02:00.0
       version: a1
       width: 64 bits
       clock: 33MHz
       capabilities: pm msi pciexpress vga_controller bus_master cap_list rom
       configuration: driver=nvidia latency=0
       resources: irq:151 memory:dc000000-dcffffff memory:a0000000-afffffff memory:b0000000-b1ffffff ioport:d000(size=128) memory:dd000000-dd07ffff
  *-display UNCLAIMED
       description: Display controller
       product: HD Graphics 630
       vendor: Intel Corporation
       physical id: 2
       bus info: pci@0000:00:02.0
       version: 04
       width: 64 bits
       clock: 33MHz
       capabilities: pciexpress msi pm bus_master cap_list
       configuration: latency=0
       resources: memory:db000000-dbffffff memory:90000000-9fffffff ioport:f000(size=64)
$
```
