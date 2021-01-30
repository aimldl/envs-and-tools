##### enter, exit, and re-enter a Docker container.md

* Rev.1: 2020-0324 (Tue)
* Draft: 2020-0312 (Thu)

# Enter, exit, and re-enter an existing container

## How to exit the container's shell

```
$ docker ps
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
ceadff6f1295        ubuntu              "bash"              2 hours ago         Up 2 hours                              vibrant_jones
$ docker exec -it vibrant_jones bash
root@ceadff6f1295:/# ls
bin  boot  dev  etc  home  lib  lib64  media  mnt  opt  proc  root  run  sbin  srv  sys  tmp  usr  var
root@ceadff6f1295:/# 
root@ceadff6f1295:/# read escape sequence

```

To exit the Docker container shell, enter "ctrl+p+q".



## How to enter a container

If there is an existing container, use "docker attach" to enter the container shell. You canno attach to a stopped container. So start it first with "docker start". Enter a container "conda" of which image is "aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4".



```
$ docker images
REPOSITORY                                              TAG     IMAGE ID      ...
aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4  latest  1b5f015ba472  ...
aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4  <none>  562fb67f8f2d  ...
hello-world                                             latest  fce289e99eb9  ...
$ docker ps 
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
$ docker ps -a
CONTAINER ID        IMAGE                                       COMMAND             CREATED             STATUS                      PORTS               NAMES
df4703dbba5f        562fb67f8f2d                                "bash"              42 hours ago        Exited (137) 21 hours ago                       conda
82b83fee10f3        hello-world                                 "/hello"            44 hours ago        Exited (0) 44 hours ago                         reverent_mccarthy
$ docker attach conda
You cannot attach to a stopped container, start it first
$ docker start conda
conda
$ docker ps
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
df4703dbba5f        562fb67f8f2d        "bash"              42 hours ago        Up 3 seconds                            conda
$ docker attach conda
(base) user@df4703dbba5f:~$ 
```

[TODO] This is an excerpt from ../commands/docker run.md. Summarize it for this document.

#### Example: Run and Enable Jupyter Notebook 

* The image name is "aimldl/kaggle_telco_customer_churn" .

* The container is named as "telco" for short with "--name telco".
* Jupyter Notebook is enabled with "-p 8080:8080". For details, refer to [../how_to/use jupyter notebook.md](../how_to/use jupyter notebook.md).

```
$ docker run -it -p 8080:8080 --name telco aimldl/kaggle_telco_customer_churn:ver0.1 bash
(base) user@dddbf9e9b072:~$ 
(base) user@dddbf9e9b072:~$ tree -d -L 2
.
|-- anaconda3
|   |-- bin
  ...
|   `-- x86_64-conda_cos6-linux-gnu
|-- hands-ons
`-- projects
    `-- telco_customer_churn
28 directories
(base) user@dddbf9e9b072:~$ 
```

##### Exit and Re-enter/Dettach and Attach a Docker Container

To exit the current docker shell or dettach from the Docker container, press Ctrl+p+q.

```
aimldl@Home-Laptop:~$ 
```

To list the running Docker containers, type in:

```
aimldl@Home-Laptop:~$ docker ps
CONTAINER ID        IMAGE                                                                  ...  PORTS                               NAMES
dddbf9e9b072        aimldl/kaggle_telco_customer_churn:latest  ...  0.0.0.0:8080->8080/tcp  telco
```

To re-enter the "telco" container shell or attach the "telco" container, type in the "docker attach" command:

```
aimldl@Home-Laptop:~$ docker attach telco
^C
(base) user@dddbf9e9b072:~$ 
```

To understand how it works, refer to [How do you attach and detach from Docker's process?](https://stackoverflow.com/questions/19688314/how-do-you-attach-and-detach-from-dockers-process) and [../lifecycle_of_docker_container.md](../lifecycle_of_docker_container.md). 



[TODO] Reorganize an excerpt from [How do you attach and detach from Docker's process?](https://stackoverflow.com/questions/19688314/how-do-you-attach-and-detach-from-dockers-process).

To detach the tty without exiting the shell, use the escape sequence Ctrl+P followed by Ctrl+Q. More details [here](https://docs.docker.com/engine/reference/commandline/attach/).

Additional info from [this source](https://groups.google.com/forum/#!msg/docker-user/nWXAnyLP9-M/kbv-FZpF4rUJ):

- docker run -t -i → can be detached with `^P^Q`and reattached with docker attach
- docker run -i → cannot be detached with `^P^Q`; will disrupt stdin
- docker run → cannot be detached with `^P^Q`; can SIGKILL client; can reattach with docker attach



[TODO] Read and reorganize [Exiting a Docker Container](https://vsupalov.com/exit-docker-container/).

