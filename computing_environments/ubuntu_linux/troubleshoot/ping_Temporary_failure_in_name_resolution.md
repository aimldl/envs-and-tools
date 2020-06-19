##### channel_setup_fwd_listener_tcpip_cannot_listen_to_port.md
# Network Fails on Ubuntu 18.04.

## Error: channel_setup_fwd_listener_tcpip: cannot listen to port: 8888
My network fails.
```bash
$ ssh -i my.pem -L 8888:localhost:8888 -X ubuntu@w.x.y.z
bind: Address already in use
channel_setup_fwd_listener_tcpip: cannot listen to port: 8888
Could not request local forwarding.

=============================================================================
       __|  __|_  )
       _|  (     /   Deep Learning Base AMI (Ubuntu 18.04) Version 21.0
      ___|\___|___|
=============================================================================

Welcome to Ubuntu 18.04.3 LTS (GNU/Linux 4.15.0-1058-aws x86_64v)
  ...
Failed to connect to https://changelogs.ubuntu.com/meta-release-lts. Check your Internet connection or proxy settings

Last login: Wed Feb 19 04:15:02 2020 from v.w.x.y

$ ping www.google.com
ping: www.google.com: Temporary failure in name resolution
$ ping www.facebook.com
ping: http://www.google.com: Temporary failure in name resolution
$
```
This is the second ssh access to the same EC2 instance. So I closed another connection and retried. The error message is gone.
```bash
$ ssh -i my.pem -L 8888:localhost:8888 -X ubuntu@w.x.y.z
=============================================================================
       __|  __|_  )
       _|  (     /   Deep Learning Base AMI (Ubuntu 18.04) Version 21.0
      ___|\___|___|
=============================================================================

Welcome to Ubuntu 18.04.3 LTS (GNU/Linux 4.15.0-1058-aws x86_64v)
  ...
Failed to connect to https://changelogs.ubuntu.com/meta-release-lts. Check your Internet connection or proxy settings

Last login: Thu Feb 20 01:27:10 2020 from v.w.x.y

$
```
However the ping command fails to work again.
 ```bash
 $ ping www.google.com
ping: www.google.com: Temporary failure in name resolution
$
```
