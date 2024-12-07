* Draft: 2021-06-10 (Thu)

# lsof (LiSt Open Files)

## References

* [lsof](https://en.wikipedia.org/wiki/Lsof), Wikipedia
  * Some phrases and examples are from Wikipedia.

> ## What is lsof?
>
> * lsof reports a list of all open files and the processes that opened them in many Unix-like systems.
> * Open files in the system include disk files, named pipes, network sockets and devices opened by all processes. 
> * For example,
>
> ```bash
> $ sudo lsof | head
> [sudo] aimldl의 암호:
> COMMAND  PID  TID TASKCMD  USER   FD  TYPE  DEVICE SIZE/OFF      NODE NAME
> systemd  1                 root  cwd  DIR   8,4        4096         2 /
> systemd  1                 root  rtd  DIR   8,4        4096         2 /
> systemd  1                 root  txt  REG   8,4     1620224  22681157 /usr/lib/systemd/systemd
> systemd  1                 root  mem  REG   8,4     1369352  22676733 /usr/lib/x86_64-linux-gnu/libm-2.31.so
> systemd  1                 root  mem  REG   8,4      178528  22676226 /usr/lib/x86_64-linux-gnu/libudev.so.1.6.17
> systemd  1                 root  mem  REG   8,4     1575112  22683845 /usr/lib/x86_64-linux-gnu/libunistring.so.2.1.0
> systemd  1                 root  mem  REG   8,4      137584  22683068 /usr/lib/x86_64-linux-gnu/libgpg-error.so.0.28.0
> systemd  1                 root  mem  REG   8,4       67912  22683281 /usr/lib/x86_64-linux-gnu/libjson-c.so.4.0.0
> systemd  1                 root  mem  REG   8,4       34872  22682599 /usr/lib/x86_64-linux-gnu/libargon2.so.1
> $
> ```
>
> ## Usage examples
>
> * One use for this command is when a disk cannot be unmounted because (unspecified) files are in use. 
>   * For example, the listing of open files can be consulted (suitably filtered if necessary) to identify the process that is using the files.
>
> ```bash
> # lsof /var
> COMMAND     PID     USER   FD   TYPE DEVICE SIZE/OFF   NODE NAME
> syslogd     350     root    5w  VREG  222,5        0 440818 /var/adm/messages
> syslogd     350     root    6w  VREG  222,5   339098   6248 /var/log/syslog
> cron        353     root  cwd   VDIR  222,5      512 254550 /var -- atjobs
> ```
>
> * View the port associated with a daemon `sendmail`. `lsof` shows what `sendmail` is listening on its standard port `25`.
>
> ```bash
> # lsof -i -n -P | grep sendmail
> sendmail  31649    root    4u  IPv4 521738       TCP *:25 (LISTEN)
> ```
>
> -i: Lists IP sockets.
> -n: Do not resolve hostnames (no DNS).
> -P: Do not resolve port names (list port number instead of its name).
>
> * One can also list Unix Sockets by using `lsof -U`.
>
> ```bash
> $ lsof -U
> COMMAND  PID   USER  FD  TYPE   DEVICE SIZE/OFF   NODE NAME
> systemd  836 aimldl  1u  unix 0x0...00      0t0  34415 type=STREAM
> systemd  836 aimldl  2u  unix 0x0...00      0t0  34415 type=STREAM
>   ...
> chrome  9796 aimldl 17u  unix 0x0...00      0t0 197738 type=STREAM
> chrome  9796 aimldl 18u  unix 0x0...00      0t0 166156 type=SEQPACKET
> $
> ```
>
> The above output is edited for better readability. The total number of lines is 1028 on my Ubuntu 18.04 when two Chrome instances opens 16 tabs.

