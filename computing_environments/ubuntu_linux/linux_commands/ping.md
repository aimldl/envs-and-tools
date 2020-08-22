##### ping.md

# ping
ping is a classic tool to test the network status. It's light-weight and useful and used nowadays, too. To learn about the basics, refer to [How to Ping in Linux](https://www.wikihow.com/Ping-in-Linux) or [Linux ping Command Tutorial for Beginners (8 Examples)](https://www.howtoforge.com/linux-ping-command/).

## See also
traceroute

## Examples
```bash
$ ping www.facebook.com
$ ping www.google.com
```

### -c or count
The -c option is to specify the count of packets.
```bash
# Send only three packets and stop
$ ping -c 3 www.facebook.com
```
### -i or interval
The -i option to give an interval between ping packets.
```bash
# Three seconds
$ ping -i 3 www.facebook.com
# half a second
$ ping -i 0.5 www.facebook.com
```
Note: only super-user may set interval to values.

## Failures

```bash
$ ping www.google.com
ping: www.google.com: Temporary failure in name resolution
$ ping www.facebook.com
ping: www.facebook.com: Temporary failure in name resolution
$
```
