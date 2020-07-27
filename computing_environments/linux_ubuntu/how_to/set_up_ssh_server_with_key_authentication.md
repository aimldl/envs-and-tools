* Draft: 2020-06-08 (Mon)

# Set up a SSH server with Key Authentication

*  OpenSSH consists of the server tool (`sshd`) and client tools (`ssh`,`sftp`, `scp`).

* Authentication methods are either:

  * a password
  * a private key paired with a public key. 


## Double-check the status
If the ssh server is up and running, the status should look like below. Notice ssh.service is "Loaded" and "Active".
```bash
$ service ssh status
● ssh.service - OpenBSD Secure Shell server
   Loaded: loaded (/lib/systemd/system/ssh.service; enabled; vendor preset: enabled)
   Active: active (running) since Tue 2020-07-21 11:53:28 KST; 5min ago
 Main PID: 30966 (sshd)
    Tasks: 1 (limit: 4915)
   CGroup: /system.slice/ssh.service
           └─30966 /usr/sbin/sshd -D

 7월 21 11:53:28 k8snode-01-Alienware-Aurora-R7 systemd[1]: Starting OpenBSD Secure Shell server...
 7월 21 11:53:28 k8snode-01-Alienware-Aurora-R7 sshd[30966]: Server listening on 0.0.0.0 port 22.
 7월 21 11:53:28 k8snode-01-Alienware-Aurora-R7 sshd[30966]: Server listening on :: port 22.
 7월 21 11:53:28 k8snode-01-Alienware-Aurora-R7 systemd[1]: Started OpenBSD Secure Shell server.
 7월 21 11:55:15 k8snode-01-Alienware-Aurora-R7 sshd[32446]: Accepted password for k8snode-01 from 19
 7월 21 11:55:15 k8snode-01-Alienware-Aurora-R7 sshd[32446]: pam_unix(sshd:session): session opened f

$ 
```
If the service is inactive at some reason, start the service with:
```bash
$ service ssh start
```
The list of sub-commands that `service ssh` takes is below.
```bash
$ service ssh
 * Usage: /etc/init.d/ssh {start|stop|reload|force-reload|restart|try-restart|status}
$
```

## References
* [How to SSH Into a Kubernetes Pod From Outside the Cluster](https://medium.com/better-programming/how-to-ssh-into-a-kubernetes-pod-from-outside-the-cluster-354b4056c42b)
