* Rev.1: 2020-05-25 (Mon)
* Draft: 2018-10-28 (Sun)
# ssh (SSH client)
* ssh is a program to log into a remote machine and run commands on it.
  * ssh connects and logs into the specified hostname (with optional username). 
  * The user must prove his/her identity to the remote machine using one of several methods.
  * If command is specified, it is executed on the remote host instead of a login shell.
* It is intended to provide secure encrypted communications between two untrusted hosts over an insecure network.
* X11 connections, arbitrary TCP ports and UNIX-domain sockets can also be forwarded over the secure channel.

## Usage
```bash
$ ssh [user@]hostname [command]
```
For example,
```bash
$ ssh ubuntu@12.345.67.89
```
