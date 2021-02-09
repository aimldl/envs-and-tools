

## Problem

```bash
Error: Can't open display: :0
```

## Hint

Google search: docker can't open x display

Google search: ubuntu docker how to run xclock

* [Is it possible to run Docker container and show its graphical application window on host?](https://askubuntu.com/questions/1161646/is-it-possible-to-run-docker-container-and-show-its-graphical-application-window)

* [Ubuntu – Is it possible to run Docker container and show its graphical application window on host](https://itectec.com/ubuntu/ubuntu-is-it-possible-to-run-docker-container-and-show-its-graphical-application-window-on-host/)



```bash
$ docker run -it -e DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix --user="$(id --user):$(id --group)" cuda_with_x11 bash
groups: cannot find name for group ID 1000
I have no name!@64994096281a:/$ xclock

```

```bash
$ docker run -it -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY cuda_with_x11 bash
root@49fc725be2b7:/# ls
bin   dev  home  lib64  mnt  proc  run   srv  tmp  var
boot  etc  lib   media  opt  root  sbin  sys  usr
root@49fc725be2b7:/# xclock
No protocol specified
Error: Can't open display: :0
root@49fc725be2b7:/# exit
exit
$
```

