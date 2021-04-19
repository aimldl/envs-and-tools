* Rev.1: 2021-01-30 (Sat)
* Draft: 2020-03-24 (Tue)

# How to Install NVIDIA Docker on Ubuntu

## Overview

* If the computer has an NVIDIA GPU card, install `nvidia-docker` AFTER installing `docker` assuming NVIDIA graphics drive has been installed already.
* Otherwise, install `docker` for CPU-only computation

### Prerequisite

On the host system, install 

* Docker engine
  * Follow the instructions in [How to Install Docker on Ubuntu](docker_on_ubuntu.md)
* [NVIDIA driver](https://github.com/NVIDIA/nvidia-docker/wiki/Frequently-Asked-Questions#how-do-i-install-the-nvidia-driver)
  * Note that you do not need to install the CUDA Toolkit , but the NVIDIA driver needs to be installed

### Be aware of some extra work

Google search: "docker run --runtime=nvidia --rm nvidia/cuda nvidia-smi" "Unable to find image 'nvidia/cuda:latest' locally"

> You can find the installation instructions on the `nvidia-docker` [wiki](https://github.com/NVIDIA/nvidia-docker/wiki), but it isn’t that easy unless you are using `docker-ce` for dev and `docker-ee` for production.
>
> Ubuntu ships with the `docker.io` package (it’s all about licensing) and the `nvidia-docker` [FAQ](https://github.com/NVIDIA/nvidia-docker/wiki/Frequently-Asked-Questions#which-docker-packages-are-supported) indicates that `docker.io` is supported, but there’s a catch. The `nvidia-docker2` support for `docker.io` is a bit behind, so we have to do some extra work.
>
> Source: [Installing nvidia-docker2 on Ubuntu 18.04 (January 2019)](https://codepyre.com/2019/01/installing-nvidia-docker2-on-ubuntu-18.0.4/), Code Pyre, Jan 25, 2019

## Summary

Run [install_nvidia_docker_on_ubuntu](../bash_scripts/install_nvidia_docker_on_ubuntu).

```bash
## 1. Uninstall the old version of Docker
sudo apt remove -y docker docker-engine docker.io containerd runc
sudo rm -rf /var/lib/docker
sudo apt autoclean
sudo apt update

## 2. Install and configure Docker CE (Community Edition)
##### How can I check if a program exists from a Bash script?
#####   https://stackoverflow.com/questions/592620/how-can-i-check-if-a-program-exists-from-a-bash-script
COMMAND='docker'
if ! command -v ${COMMAND} &> /dev/null
then
    echo "${COMMAND} could not be found. Installing ..."
    install_docker_on_ubuntu
    configure_docker_on_ubuntu
else
    echo "${COMMAN D} exists. Skipping to install and configure it ..."
fi

## 3. Install NVIDIA Docker
##### Install the prerequisites
sudo apt install -y curl

##### Add a repository for nvidia-docker2
curl -s -L https://nvidia.github.io/nvidia-docker/gpgkey | sudo apt-key add -
distribution=$(. /etc/os-release;echo $ID$VERSION_ID)
curl -s -L https://nvidia.github.io/nvidia-docker/$distribution/nvidia-docker.list | sudo tee /etc/apt/sources.list.d/nvidia-docker.list
sudo apt update

##### Install nvidia-docker2
sudo apt install -y nvidia-docker2

##### Reload the Docker configurations
sudo pkill -SIGHUP dockerd

## 4. Verify
#sudo docker run --runtime=nvidia --rm nvidia/cuda:10.1-base nvidia-smi
sudo docker run --runtime=nvidia --rm nvidia/cuda:11.0-base nvidia-smi
#nvidia-docker ps
```

## 1. Uninstall the old version of Docker

```bash
$ sudo apt remove -y docker docker-engine docker.io containerd runc
$ sudo rm -rf /var/lib/docker
$ sudo apt autoclean
$ sudo apt update
```

Equivalently, the following commands remove `nvidia-docker 1.0`.

```bash
$ docker volume ls -q -f driver=nvidia-docker | xargs -r -I{} -n1 docker ps -q -a -f volume={} | xargs -r docker rm -f
$ sudo apt-get purge nvidia-docker
```

## 2. Install and configure Docker CE (Community Edition)

As a prerequisite to install NVIDIA Docker, Docker engine must be installed. Install either Docker CE or Docker EE (Enterprise Edition). Docker CE is the free version which I have installed.

To do so, either

* run `install_docker_on_ubuntu`, log out and log back in, and run `configure_docker_on_ubuntu`

* or follow the instructions in [How to Install Docker on Ubuntu](docker_on_ubuntu.md).

## 3. Install NVIDIA Docker 2.0

`curl` is a Linux command necessary in the next step. Install this prerequisite package.

```bash
$ sudo apt install -y curl
```

Add a repository for `nvidia-docker2`.

```bash
$ curl -s -L https://nvidia.github.io/nvidia-docker/gpgkey | sudo apt-key add -
$ distribution=$(. /etc/os-release;echo $ID$VERSION_ID)
$ curl -s -L https://nvidia.github.io/nvidia-docker/$distribution/nvidia-docker.list | sudo tee /etc/apt/sources.list.d/nvidia-docker.list
$ sudo apt update
```

An example of `$distribution`  is `ubuntu18.04`. To see it, run `$ echo $distribution` .

> If the repository for `nvidia-docker` has not been set, `apt` package manager doesn't know from where to download `nvidia-docker` and the next step will fail. For details, refer to [nvidia-docker > Repository configuration](https://nvidia.github.io/nvidia-docker/)  > Debian-based distributions. 

Install `nvidia-docker2`

```bash
$ sudo apt install -y nvidia-docker2
```

Reload/restart the Docker configurations.

```bash
$ sudo pkill -SIGHUP dockerd
```

## 3. (Optionally) configure to use `nvidia-docker2` without the `sudo` command.

This step might have been done in the previous step `2. Install and configure Docker CE`. Unless you have skipped this step for the security reason, it will be convenient to run the `docker` command without the `sudo` command. For more details, refer to [How to install Docker and Nvidia-Docker 2.0 on Ubuntu 18.04](https://medium.com/@linhlinhle997/how-to-install-docker-and-nvidia-docker-2-0-on-ubuntu-18-04-da3eac6ec494) > Optional — Ensure Docker can run without sudo. 

```bash
$ sudo usermod -aG docker ${USER}
$ su - ${USER}
$ id -nG
```

Notice the group name is `docker`, not `nvidia-docker2`. After the installation of `nvidia-docker2`, the command `docker` will be used. 

## 5. Verify the installation

### Check if `nvidia-docker`works.

To see if `nvidia-docker`works, run:

```bash
$ sudo nvidia-docker ps
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
$
```

### Check if `nvidia-docker`works without `sudo`

Notice that the leading `sudo` command can be omitted if you have set up to do so.

```bash
$ nvidia-docker ps
CONTAINER ID         IMAGE         COMMAND         CREATED         STATUS         PORTS        NAMES
$
```

If you see the following error message message, you may configure to use `Docker` without `sudo`. You may choose to keep adding the `sudo` command, but it is more convenient without the `sudo` command.

```bash
$ nvidia-docker ps
Got permission denied while trying to connect to the Docker daemon socket at unix:///var/run/docker.sock: Get http://%2Fvar%2Frun%2Fdocker.sock/v1.40/containers/json: dial unix /var/run/docker.sock: connect: permission denied
$
```

### Check to see `docker` works instead of `nvidia-docker`.

Notice that replacing `nvidia-docker` to `docker` shows the same result.

```bash
$ docker ps
CONTAINER ID         IMAGE         COMMAND         CREATED         STATUS         PORTS        NAMES
$
```

### Run `nvidia-smi` in the `nvidia-docker` environment.

```bash
$ docker run --runtime=nvidia --rm nvidia/cuda:10.1-base nvidia-smi
```

The expected message is

```bash
Unable to find image 'nvidia/cuda:10.1-base' locally
10.1-base: Pulling from nvidia/cuda
f22ccc0b8772: Pull complete 
3cf8fb62ba5f: Pull complete 
e80c964ece6a: Pull complete 
a0afc6a19124: Pull complete 
18287e0c259e: Pull complete 
88c0e0db918c: Pull complete 
Digest: sha256:55ca575639ac32178d0425d59b98e9983430245d0ad3da13d66c7431930a66b2
Status: Downloaded newer image for nvidia/cuda:10.1-base
Thu Jan 28 02:28:36 2021       
+-----------------------------------------------------------------------------+
| NVIDIA-SMI 460.32.03    Driver Version: 460.32.03    CUDA Version: 11.2     |
|-------------------------------+----------------------+----------------------+
| GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
|                               |                      |               MIG M. |
|===============================+======================+======================|
|   0  GeForce GTX 1080    On   | 00000000:01:00.0  On |                  N/A |
| 27%   37C    P8     9W / 180W |    267MiB /  8118MiB |      6%      Default |
|                               |                      |                  N/A |
+-------------------------------+----------------------+----------------------+
|   1  GeForce GTX 1080    On   | 00000000:02:00.0 Off |                  N/A |
| 28%   29C    P8     5W / 180W |      2MiB /  8119MiB |      0%      Default |
|                               |                      |                  N/A |
+-------------------------------+----------------------+----------------------+
                                                                               
+-----------------------------------------------------------------------------+
| Processes:                                                                  |
|  GPU   GI   CI        PID   Type   Process name                  GPU Memory |
|        ID   ID                                                   Usage      |
|=============================================================================|
+-----------------------------------------------------------------------------+
$
```

You may also run without the version information. That is, use `nvidia/cuda` instead of `nvidia/cuda:10.1-base`.

```
$ docker run --runtime=nvidia --rm nvidia/cuda nvidia-smi
```

The latest version will be applied automatically.

TODO: Fix this.

```bash
Unable to find image 'nvidia/cuda:latest' locally
docker: Error response from daemon: manifest for nvidia/cuda:latest not found: manifest unknown: manifest unknown.
See 'docker run --help'.
$
```

### Instead of the above commands, I may also use the following commands.

### Check if `nvidia-docker` is installed.

```bash
$ sudo nvidia-docker --version
Docker version 19.03.6, build 369ce74a3c
$
```

### Check if `nvidia-docker`works without `sudo`.

```bash
$ nvidia-docker --version
Docker version 19.03.6, build 369ce74a3c
$
```

### Check to see `docker` works instead of `nvidia-docker`.

Notice that replacing `nvidia-docker` to `docker` shows the same result.

```bash
$ docker --version
Docker version 19.03.6, build 369ce74a3c
$
```

### Check to see if `hello-world` works.

```bash
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
 https://docs.docker.com/get-started/
$
```

If this command has not been executed in the process of installing `docker`, you will see the following message before `Hello from Docker!` which downloads the image to the machine.

```bash
Unable to find image 'hello-world:latest' locally
latest: Pulling from library/hello-world
0e03bdcc26d7: Pull complete 
Digest: sha256:31b9c7d48790f0d8c50ab433d9c3b7e17666d6993084c002c2ff1ca09b96391d
Status: Downloaded newer image for hello-world:latest
```

### Run some docker commands to see the current status. 

The existing images and containers are shown below.

```bash
$ docker images
REPOSITORY    TAG                 IMAGE ID            CREATED             SIZE
nvidia/cuda   10.1-base           6fa731bcd2fd        6 weeks ago         105MB
nvidia/cuda   11.0-base           2ec708416bb8        5 months ago        122MB
hello-world   latest              bf756fb1ae65        13 months ago       13.3kB
$ docker ps 
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
$ docker ps -a
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS                      PORTS               NAMES
2b59554032b3        hello-world         "/hello"            12 seconds ago      Exited (0) 10 seconds ago                       xenodochial_hugle
$
```

## References

Google search: ubuntu 18.04 how to install nvidia docker

* [How to install Docker and Nvidia-Docker 2.0 on Ubuntu 18.04](https://medium.com/@linhlinhle997/how-to-install-docker-and-nvidia-docker-2-0-on-ubuntu-18-04-da3eac6ec494), 2020-01-15
* [Installing nvidia-docker2 on Ubuntu 18.04 (January 2019)](https://codepyre.com/2019/01/installing-nvidia-docker2-on-ubuntu-18.0.4/), Code Pyre, Jan 25, 2019
* [NVIDIA/nvidia-docker](https://github.com/NVIDIA/nvidia-docker)