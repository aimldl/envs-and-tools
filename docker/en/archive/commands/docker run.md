* Rev.2: 2020-03-31 (Tue)
* Rev.1: 2020-03-16 (Mon)
* Draft: 2020-03-11 (Wed)
# docker run

##### $ docker run [docker_image] 

```
$ docker run hello-world
Hello from Docker! 
This message shows that your installation appears to be working correctly.

To generate this message, Docker took the following steps:
  1. The Docker client contacted the Docker daemon.
  2. The Docker daemon pulled the "hello-world" image from the Docker Hub.
     (amd64)
  3. The Docker daemon created a new container from that image which runs the
     executable that produces the output you are currently reading.
  4. The Docker daemon streamed that output to the Docker client, which sent it
     to your terminal.

To try something more ambitious, you can run an Ubuntu container with:
 $ docker run -it ubuntu bash

Share images, automate workflows, and more with a free Docker ID:
 https://hub.docker.com/

For more examples and ideas, visit:
 https://docs.docker.com/get-started/\
$
```

##### $ docker run -it [docker_image] bash

'bash' can be replaced to ''/bin/bash'

    $ docker run -it ubuntu bash
    Unable to find image 'ubuntu:latest' locally
    latest: Pulling from library/ubuntu
    423ae2b273f4: Pull complete 
    de83a2304fa1: Pull complete 
      ...
    Status: Downloaded newer image for ubuntu:latest
    root@ceadff6f1295:/#

##### $ docker run -p [docker_image] 

Publish or expose port [-p, --expose]

```
# Expose port 80 of the container
#   without publishing the port to the host system’s interfaces.
$ docker run --expose 80 ubuntu bash
```

```
$ docker run -p 8888:8888 tensorflow/tensorflow
```

### docker run -it --name [container_name] [image_name] bash

```bash
$ docker run -it --name scikit_surprise aimldl/baseimage_python3.6.9_ubuntu18.04.4 bash
user@9ec1b217c60a:~$
```

#### Caution: the --name option must come before "container_name".
If the option comes after the container_name, the following error occurs.
```bash
PS C:\Users\aimldl>docker run -it aimldl/baseimage_python3.6.9_ubuntu18.04.4 --name scikit-surprise bash
C:\Program Files\Docker\Docker\resources\bin\docker.exe: Error response from daemon: OCI runtime create failed: container_linux.go:349: starting container process caused "exec: \"--name\": executable file not found in $PATH": unknown.
PS C:\Users\aimldl> docker run -it aimldl/baseimage_python3.6.9_ubuntu18.04.4 --name scikit_surprise bash
C:\Program Files\Docker\Docker\resources\bin\docker.exe: Error response from daemon: OCI runtime create failed: container_linux.go:349: starting container process caused "exec: \"--name\": executable file not found in $PATH": unknown.
```

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

### Mount volume (-v, --read-only)
For details, refer to [docker run](https://docs.docker.com/engine/reference/commandline/run/) in the "Mount volume (-v, --read-only)" section.

```bash
~/github/VOX/kaggle/Compete/titanic_dataset/data$ ls
gender_submission.csv  test.csv  train.csv
/github/VOX/kaggle/Compete/titanic_dataset/data$ docker images
REPOSITORY                                                     TAG     ...  SIZE
aimldl/baseimage_kaggle_python3.7.6_conda4.8.2_ubuntu18.04.4  latest   ...  8.18GB
  ...
hello-world                                                   latest   ...  1.84kB
/github/VOX/kaggle/Compete/titanic_dataset/data$ docker run -it --name titanic -p 8080:8080 -v ~/github/VOX/kaggle/Compete/titanic_dataset:/home/user/hands-on aimldl/baseimage_kaggle_python3.7.6_conda4.8.2_ubuntu18.04.4 bash
2020-03-31 (Tue) 04:27 (13th week)
Welcome to ubuntu18.04, conda 4.8.3, Python 3.7.6
(base) user@69833fa22777:~$ ls
anaconda3  hands-on  project
(base) user@69833fa22777:~$ cd hands-on/
(base) user@69833fa22777:~/hands-on$ ls
data  notebooks
(base) user@69833fa22777:~/hands-on$ ls data/
gender_submission.csv  test.csv  train.csv
(base) user@69833fa22777:~/hands-on$ 
```
