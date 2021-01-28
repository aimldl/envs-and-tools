* Rev.1: 2021-01-28 (Thu)
* Draft: 2020-03-24 (Tue)

# Install nvidia-docker on Ubuntu

## Overview

nvidia-docker is for a computer with NVIDIA GPU card. If the computer doesn't have an NVIDIA GPU card for a General Purpose GPU, install docker. To simply put, install docker for CPU and nvidia-docker for GPU.

## References

* [NVIDIA/nvidia-docker](https://github.com/NVIDIA/nvidia-docker)

> **Getting Started**
>
> Make sure you have installed
>
> *  the [NVIDIA driver](https://github.com/NVIDIA/nvidia-docker/wiki/Frequently-Asked-Questions#how-do-i-install-the-nvidia-driver)
>   * Note that you do not need to install the CUDA Toolkit on the host system, but the NVIDIA driver needs to be installed
> * Docker engine
>
> for your Linux distribution. 

Google search: ubuntu 18.04 how to install nvidia docker

* [How to install Docker and Nvidia-Docker 2.0 on Ubuntu 18.04](https://medium.com/@linhlinhle997/how-to-install-docker-and-nvidia-docker-2-0-on-ubuntu-18-04-da3eac6ec494), 2020-01-15
* 

### Prerequisite

Install

* [NVIDIA driver](https://github.com/NVIDIA/nvidia-docker/wiki/Frequently-Asked-Questions#how-do-i-install-the-nvidia-driver)
  * Note that you do not need to install the CUDA Toolkit on the host system, but the NVIDIA driver needs to be installed
* Docker engine
  * Follow the instructions in [How to Install Docker on Ubuntu](docker_on_ubuntu.md)



#### Install curl

curl is a Linux command necessary to install nvidia-docker. 

```bash
$ sudo apt install -y curl
```

#### Remove nvidia-docker 1.0

```
$ docker volume ls -q -f driver=nvidia-docker | xargs -r -I{} -n1 docker ps -q -a -f volume={} | xargs -r docker rm -f
$ sudo apt-get purge nvidia-docker
```

### Installing version 2.0

The following part is excerpts of [Installation (version 2.0)](https://github.com/nvidia/nvidia-docker/wiki/Installation-(version-2.0)), github/nvidia/nvidia-docker. If you already have nvidia-docker 1.0, you have to remove it first.

#### Ubuntu distributions

##### Step 1. Install the repository for your distribution by following the instructions [here](http://nvidia.github.io/nvidia-docker/). 

If you haven't set up the repository for nvidia-docker, the next step won't work because the apt package manager can't see where nvidia-docker is.

##### Repository configuration

These commands are from [Repository configuration](https://nvidia.github.io/nvidia-docker/) > Debian-based distributions. For details, refer to [Repository configuration](https://nvidia.github.io/nvidia-docker/), nvidia-docker. 

```bash
$ curl -s -L https://nvidia.github.io/nvidia-docker/gpgkey | sudo apt-key add -
OK
$ distribution=$(. /etc/os-release;echo $ID$VERSION_ID)
$ echo $distribution
ubuntu18.04
$ curl -s -L https://nvidia.github.io/nvidia-docker/$distribution/nvidia-docker.list | sudo tee /etc/apt/sources.list.d/nvidia-docker.list
```

```bash
deb https://nvidia.github.io/libnvidia-container/ubuntu18.04/$(ARCH) /
deb https://nvidia.github.io/nvidia-container-runtime/ubuntu18.04/$(ARCH) /
deb https://nvidia.github.io/nvidia-docker/ubuntu18.04/$(ARCH) /
$ sudo apt-get update
  ...
$
```

##### Step 2. Install the `nvidia-docker2` package and reload the Docker daemon configuration.

* 

```bash
$ sudo apt-get install nvidia-docker2
  ...
$ sudo pkill -SIGHUP dockerd
$
```

##### Step 3. Optional — Ensure Docker can run without sudo

For details, refer to [How to install Docker and Nvidia-Docker 2.0 on Ubuntu 18.04](https://medium.com/@linhlinhle997/how-to-install-docker-and-nvidia-docker-2-0-on-ubuntu-18-04-da3eac6ec494) > Optional — Ensure Docker can run without sudo. 

```bash
$ sudo usermod -aG docker ${USER}
$ su - ${USER}
$ id -nG
```

##### Step 4. Verify the installation

Notice the leading `sudo` command is omitted by the set-up at the previous step.

```bash
$ nvidia-docker ps
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
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

If you see the following message, follow step 3 to run Docker without sudo.

```bash
$ nvidia-docker ps
Got permission denied while trying to connect to the Docker daemon socket at unix:///var/run/docker.sock: Get http://%2Fvar%2Frun%2Fdocker.sock/v1.40/containers/json: dial unix /var/run/docker.sock: connect: permission denied
$
```

You may choose to add the `sudo` command in front, but it is more convenient to run Docker without sudo.

```bash
$ sudo nvidia-docker ps
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
$
```



## Basic Usage

```
$ docker run --runtime=nvidia --rm nvidia/cuda nvidia-smi
```
