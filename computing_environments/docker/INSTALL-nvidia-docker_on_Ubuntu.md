##### aimldl/computing_environments/docker/INSTALL-nvidia-docker_on_Ubuntu.md
* Draft: 2020-0324 (Tue)

# Install nvidia-docker on Ubuntu

nvidia-docker is for a computer with NVIDIA GPU card. If the computer doesn't have an NVIDIA GPU card for a General Purpose GPU, install docker. To simply put, install docker for CPU and nvidia-docker for GPU.

### Prerequisite

#### Install curl

curl is a Linux command necessary to install nvidia-docker. 

```
$ sudo apt install curl
```

#### Remove nvidia-docker 1.0

```
$ docker volume ls -q -f driver=nvidia-docker | xargs -r -I{} -n1 docker ps -q -a -f volume={} | xargs -r docker rm -f
$ sudo apt-get purge nvidia-docker
```

### Installing version 2.0

The following part is excerpts of [Installation (version 2.0)](https://github.com/nvidia/nvidia-docker/wiki/Installation-(version-2.0)), github/nvidia/nvidia-docker. If you already have nvidia-docker 1.0, you have to remove it first.

#### Ubuntu distributions

Step 1. Install the repository for your distribution by following the instructions [here](http://nvidia.github.io/nvidia-docker/). 

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
deb https://nvidia.github.io/libnvidia-container/ubuntu18.04/$(ARCH) /
deb https://nvidia.github.io/nvidia-container-runtime/ubuntu18.04/$(ARCH) /
deb https://nvidia.github.io/nvidia-docker/ubuntu18.04/$(ARCH) /
$ sudo apt-get update
  ...
$
```

Step 2. Install the `nvidia-docker2` package and reload the Docker daemon configuration.

```
$ sudo apt-get install nvidia-docker2
  ...
$ sudo pkill -SIGHUP dockerd
$
```

### Verify the installation

```
$ nvidia-docker ps
Got permission denied while trying to connect to the Docker daemon socket at unix:///var/run/docker.sock: Get http://%2Fvar%2Frun%2Fdocker.sock/v1.40/containers/json: dial unix /var/run/docker.sock: connect: permission denied

$
```

```
$ sudo docker ps
[sudo] aimldl의 암호: 
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
$
```

## Removing version 2.0

```
$ sudo apt-get purge nvidia-docker2

  ...

? [Y/n] y

  ...

$
```

## Basic Usage

```
$ docker run --runtime=nvidia --rm nvidia/cuda nvidia-smi
```
