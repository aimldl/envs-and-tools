* Rev.2: 2021-01-29 (Fri)
* Rev.1: 2020-08-12 (Wed)
* Draft: 2020-03-24 (Tue)

# How to Install Docker

## Overview

Two types of Docker exist:

* Docker CE (Community Edition)
* Docker EE (Enterprise Edition).

 Docker CE is the free version. The free version will do.

If the computer has an NVIDIA GPU card, install `nvidia-docker` AFTER installing `docker`. 

* Install
  * `docker` for CPU-only computation
  * `nvidia-docker` for General Purpuse GPU computing.

## Documents for

### Ubuntu

* [How to Install Docker on Ubuntu](install/docker_on_ubuntu.md)
  * [How to Install Docker on Ubuntu (verbose version)](install/docker_on_ubuntu-verbose_version.md)
* 

#### References

* [How to Install Docker On Ubuntu 18.04 Bionic Beaver](https://phoenixnap.com/kb/how-to-install-docker-on-ubuntu-18-04)
  * The instructions in [Get Docker Engine - Community for Ubuntu](https://docs.docker.com/install/linux/docker-ce/ubuntu/) > Install Docker Engine - Community failed with errors.

* [Post-installation steps for Linux](https://docs.docker.com/install/linux/linux-postinstall/#manage-docker-as-a-nonroot-user)
* [How to install Docker and Nvidia-Docker 2.0 on Ubuntu 18.04](https://medium.com/@linhlinhle997/how-to-install-docker-and-nvidia-docker-2-0-on-ubuntu-18-04-da3eac6ec494) > Optional — Ensure Docker can run without sudo

