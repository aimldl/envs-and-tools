

# X11 proxy: Unsupported authorisation protocol.
## Problem
On an AWS EC2 instance, an error message occurs. 
```bash
/usr/bin/xauth:  timeout in locking authority file /home/ubuntu/.Xauthority
ubuntu@ip-w-x-y-z:~$
ubuntu@ip-w-x-y-z:~$ xclock
PuTTY X11 proxy: Unsupported authorisation protocol
Error: Can't open display: localhost:12.0
ubuntu@ip-172-31-30-116:~$ /usr/bin/xauth:  timeout in locking authority file /home/ubuntu/.Xauthority
-bash: /usr/bin/xauth:: No such file or directory
ubuntu@ip-w-x-y-z:~$
```

```bash
ubuntu@ip-w-x-y-z:/etc/X11$ cat /etc/ssh/sshd_config  | grep X11
X11Forwarding yes
X11DisplayOffset 10
ubuntu@ip-w-x-y-z:/etc/X11$ service ssh restart
==== AUTHENTICATING FOR org.freedesktop.systemd1.manage-units ===
Authentication is required to restart 'ssh.service'.
Authenticating as: Ubuntu (ubuntu)
Password:
ubuntu@ip-w-x-y-z:/etc/X11$ echo $DISPLAY
localhost:12.0
ubuntu@ip-w-x-y-z:/etc/X11$ sudo service ssh restart
ubuntu@ip-w-x-y-z:/etc/X11$ xhost +root
PuTTY X11 proxy: Unsupported authorisation protocol
xhost:  unable to open display "localhost:12.0"
ubuntu@ip-w-x-y-z:/etc/X11$ sudo xhost +root
PuTTY X11 proxy: Unsupported authorisation protocol
xhost:  unable to open display "localhost:12.0"
ubuntu@ip-w-x-y-z:/etc/X11$ xhost
PuTTY X11 proxy: Unsupported authorisation protocol
xhost:  unable to open display "localhost:12.0"
ubuntu@ip-w-x-y-z:/etc/X11$ cp /home/ubuntu/.Xauthority /root/
cp: cannot stat '/root/.Xauthority': Permission denied
ubuntu@ip-w-x-y-z:/etc/X11$ sudo cp /home/ubuntu/.Xauthority /root/
ubuntu@ip-w-x-y-z:/etc/X11$ xauth list
xauth:  timeout in locking authority file /home/ubuntu/.Xauthority
ubuntu@ip-w-x-y-z:/etc/X11$
$ sudo chown ubuntu /home/ubuntu/.Xauthority
```

I've tested with a new EC2 instance and found something weird.
```bash
  ...
/usr/bin/xauth:  timeout in locking authority file /home/ubuntu/.Xauthority
ubuntu@ip-w-x-y-z:/etc/X11$
```
The error from .Xauthority should not happen.
Google search: how to set up x11 on ec2 ubuntu

[Setting up X11 for use on an EC2 host · GitHub](https://gist.github.com/jay-johnson/9184a4e9df277dd2d518eaa4343ece53)
```bash
$ cat /etc/ssh/sshd_config  | grep X11
X11Forwarding yes 
X11DisplayOffset 10
$ sudo service ssh restart
$ xhost +root
$ cp /home/ubuntu/.Xauthority /root/
$ xauth list
xauth:  timeout in locking authority file /home/ubuntu/.Xauthority
$
```
Expected output is
> <Internal Host Name>/unix:10  MIT-MAGIC-COOKIE-1  A_STRING_OF_CHARACTERS

Something is weird. 


sudo cp /home/ubuntu/.Xauthority /root/
xauth list
```bash
sudo chown ubuntu /home/ubuntu/.Xauthority
exit
```
xclock
It works!

