* Rev.3: 2020-07-23 (Thu)
* Rev.2: 2020-06-24 (Wed)
* Rev.1: 2020-06-22 (Mon)
* Draft: 2020-

# How to Get the MAC Address on Ubuntu (18.04)

## Summary
* Option 1. Print the MAC address with the `cat` command 
  * `/sys/class/net/<device-name>/address` contains the MAC address of a device `device-name`. 
* Option 2. Use the `ifconfig` command
  * If the `ifconfig` command is available, use it to get the MAC address.

`ifconfig` is not available right after installing Ubuntu Linux (18.04).
```bash
$ ifconfig
Command 'ifconfig' not found, but can be installed with:
sudo apt install net-tools
$
```
  * In general, the Internet is necessary to install `ifconfig`.
  * Say you intend to connect the Internet via a WiFi and the WiFi requires to register your MAC address as a part of authentication method. In this case, `ifconfig` can not be used. So use the first method.

## Web Search

* Google search: "ubuntu how to get mac address"
* You can access the address file for each device on the /sys virtual filesystem. The MAC address should be in /sys/class/net/<device-name>/address. For details, refer to [Output only MAC address on Ubuntu](https://askubuntu.com/questions/628383/output-only-mac-address-on-ubuntu).

## Option 1. Print `/sys/class/net/<device-name>/address` with the `cat` command 

Using the `cat` command gets you the MAC address directly from `/sys/class/net/<device-name>/address`.  There was an occasion when `ifconfig` was not installed because it was right after Ubuntu Linux 18.04 was installed and the Internet was not available yet. To get the Internet access, I had to connect a hidden WiFi network. To register my computer to the hidden WiFi network, the MAC address was required. 

### For all devices

```bash
$ cat /sys/class/net/*/address
34:17:eb:5d:88:7c
00:00:00:00:00:00
64:5a:04:69:50:45
$
```

### When `device-name` is `enp1s0`

```bash
$ cat /sys/class/net/enp1s0/address
34:17:eb:5d:88:7c
```
## Option 2. Use the `ifconfig` command
```bash
$ ifconfig
docker0: flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500
        ether 02:42:72:c0:fc:76  txqueuelen 0  (Ethernet)
           ...
enp6s0: flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500
        ether 14:b3:1f:22:ef:e3  txqueuelen 1000  (Ethernet)
           ...
lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        inet 127.0.0.1  netmask 255.0.0.0
        inet6 ::1  prefixlen 128  scopeid 0x10<host>
        loop  txqueuelen 1000  (Local Loopback)
        RX packets 482  bytes 32896 (32.8 KB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 482  bytes 32896 (32.8 KB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

wlp5s0: flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500
        ether 9c:b6:d0:ea:33:89  txqueuelen 1000  (Ethernet)
          ...
```
