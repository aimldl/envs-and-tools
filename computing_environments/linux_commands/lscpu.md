* Rev.1: 2020-07-23 (Thu)
* Draft: 2020-06-25 (Thu)

# lscpu
`lscpu` displays information about the CPU architecture. For details, refer to [lscpu(1) - Linux man page](https://linux.die.net/man/1/lscpu). 

## Question:

> Google search: ubuntu how to check the number of cores for cpu
>   or
> Google search: ubuntu linux number of cpu cores
>
> [Check how many CPUs are there in Linux system](https://www.cyberciti.biz/faq/check-how-many-cpus-are-there-in-linux-system/)

## Dell Alienware Aurora R7

```bash
$ lscpu | egrep 'CPU\(s\)|Thread|Socket|NUMA|Model name'
CPU(s):              12
On-line CPU(s) list: 0-11
Thread(s) per core:  2
Socket(s):           1
NUMA node(s):        1
Model name:          Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz
NUMA node0 CPU(s):   0-11
$
```

```bash
$ lscpu -p
# The following is the parsable format, which can be fed to other
# programs. Each different item in every column has an unique ID
# starting from zero.
# CPU,Core,Socket,Node,,L1d,L1i,L2,L3
0,0,0,0,,0,0,0,0
1,1,0,0,,1,1,1,0
2,2,0,0,,2,2,2,0
3,3,0,0,,3,3,3,0
4,4,0,0,,4,4,4,0
5,5,0,0,,5,5,5,0
6,0,0,0,,0,0,0,0
7,1,0,0,,1,1,1,0
8,2,0,0,,2,2,2,0
9,3,0,0,,3,3,3,0
10,4,0,0,,4,4,4,0
11,5,0,0,,5,5,5,0
$
```

```bash
$ lscpu
Architecture:        x86_64
CPU op-mode(s):      32-bit, 64-bit
Byte Order:          Little Endian
CPU(s):              12
On-line CPU(s) list: 0-11
Thread(s) per core:  2
Core(s) per socket:  6
Socket(s):           1
NUMA node(s):        1
Vendor ID:           GenuineIntel
CPU family:          6
Model:               158
Model name:          Intel(R) Core(TM) i7-8700K CPU @ 3.70GHz
Stepping:            10
CPU MHz:             900.035
CPU max MHz:         4600.0000
CPU min MHz:         800.0000
BogoMIPS:            7399.70
Virtualization:      VT-x
L1d cache:           32K
L1i cache:           32K
L2 cache:            256K
L3 cache:            12288K
NUMA node0 CPU(s):   0-11
Flags:               fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc art arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf pni pclmulqdq dtes64 monitor ds_cpl vmx smx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch cpuid_fault epb invpcid_single pti ssbd ibrs ibpb stibp tpr_shadow vnmi flexpriority ept vpid fsgsbase tsc_adjust bmi1 hle avx2 smep bmi2 erms invpcid rtm mpx rdseed adx smap clflushopt intel_pt xsaveopt xsavec xgetbv1 xsaves dtherm ida arat pln pts hwp hwp_notify hwp_act_window hwp_epp md_clear flush_l1d
$
```

Interestingly, the number of CPUs looks different on the same machine. The earlier result on 2020-06-25 (Thu) shows 12 CPUs while that on 2020-07-23 (Thu) shows 8 CPUs. The only difference I can think of is the OS reinstallation. In both cases, Ubuntu 18.04 is installed with less than a month difference.

```bash
$ lscpu
Architecture:        x86_64
CPU op-mode(s):      32-bit, 64-bit
Byte Order:          Little Endian
CPU(s):              8
On-line CPU(s) list: 0-7
Thread(s) per core:  2
Core(s) per socket:  4
Socket(s):           1
NUMA node(s):        1
Vendor ID:           GenuineIntel
CPU family:          6
Model:               158
Model name:          Intel(R) Core(TM) i7-7700K CPU @ 4.20GHz
Stepping:            9
CPU MHz:             1100.017
CPU max MHz:         4400.0000
CPU min MHz:         800.0000
BogoMIPS:            8400.00
Virtualization:      VT-x
L1d cache:           32K
L1i cache:           32K
L2 cache:            256K
L3 cache:            8192K
NUMA node0 CPU(s):   0-7
Flags:               fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc art arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf pni pclmulqdq dtes64 monitor ds_cpl vmx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch cpuid_fault epb invpcid_single pti ssbd ibrs ibpb stibp tpr_shadow vnmi flexpriority ept vpid fsgsbase tsc_adjust bmi1 hle avx2 smep bmi2 erms invpcid rtm mpx rdseed adx smap clflushopt intel_pt xsaveopt xsavec xgetbv1 xsaves dtherm ida arat pln pts hwp hwp_notify hwp_act_window hwp_epp md_clear flush_l1d
```

## References

* [Check how many CPUs are there in Linux system](https://www.cyberciti.biz/faq/check-how-many-cpus-are-there-in-linux-system/)
