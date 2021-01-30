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
    echo "${COMMAND} exists. Skipping to install and configure it ..."
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

Reload the Docker configurations.

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

### Run `nvidia-smi` in the nvidia-docker environment.

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

## References

Google search: ubuntu 18.04 how to install nvidia docker

* [How to install Docker and Nvidia-Docker 2.0 on Ubuntu 18.04](https://medium.com/@linhlinhle997/how-to-install-docker-and-nvidia-docker-2-0-on-ubuntu-18-04-da3eac6ec494), 2020-01-15

* [NVIDIA/nvidia-docker](https://github.com/NVIDIA/nvidia-docker)