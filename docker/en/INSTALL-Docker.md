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

> **Docker Engine Overview**
>
> Docker Engine is an open source containerization technology for building and containerizing your applications.
>
> * Docker Engine acts as a client-server application with:
>   * A server with a long-running daemon process dockerd.
>   * APIs which specify interfaces that programs can use to talk to and instruct the Docker daemon.
>   * A command line interface (CLI) client docker.
>
> The CLI uses [Docker APIs](https://docs.docker.com/engine/api/) to control or interact with the Docker daemon through scripting or direct CLI commands. For more details, see [Docker Architecture](https://docs.docker.com/get-started/overview/#docker-architecture).
>
> Source: [Docker Engine overview](https://docs.docker.com/engine/), docker docs

## Documents for

### Ubuntu

* [How to Install Docker on Ubuntu](install/docker_on_ubuntu.md)
  * [How to Install Docker on Ubuntu (verbose version)](install/docker_on_ubuntu-verbose_version.md)
* [How to Install NVIDIA Docker on Ubuntu](install/nvidia-docker_on_Ubuntu.md)

### Windows

* [Install Docker Desktop on Windows](install/docker_desktop_on_windows.md)

## References

* [How to Install Docker On Ubuntu 18.04 Bionic Beaver](https://phoenixnap.com/kb/how-to-install-docker-on-ubuntu-18-04)
  * The instructions in [Get Docker Engine - Community for Ubuntu](https://docs.docker.com/install/linux/docker-ce/ubuntu/) > Install Docker Engine - Community failed with errors.

* [Post-installation steps for Linux](https://docs.docker.com/install/linux/linux-postinstall/#manage-docker-as-a-nonroot-user)
* [How to install Docker and Nvidia-Docker 2.0 on Ubuntu 18.04](https://medium.com/@linhlinhle997/how-to-install-docker-and-nvidia-docker-2-0-on-ubuntu-18-04-da3eac6ec494) > Optional — Ensure Docker can run without sudo

