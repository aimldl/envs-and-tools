##### aimldl/computing_environments/docker/README.md

* Rev.2: 2020-0324 (Tue)
* Rev.1: 2020-0311 (Wed)
* Draft: 2019-1115 (Fri)

# [Docker](https://www.docker.com/)

## What is Docker?

**Docker** is a set of platform as a service (PaaS) products that uses OS-level virtualization to deliver software in packages called containers. To learn about what is Docker, refer to [Docker (software)](https://en.wikipedia.org/wiki/Docker_(software)), wikipedia. Several images that explain some high level concepts are presented below. Refer to the provided links for details.

### [Docker overview](https://docs.docker.com/engine/docker-overview/)

<img src="https://docs.docker.com/engine/images/engine-components-flow.png">

<img src="https://docs.docker.com/engine/images/architecture.svg">

## What is Docker Hub

**Docker Hub** is a hosted repository service provided by Docker for finding and sharing container images with your team. Key features include:

* Private Repositories
* Push and pull container images
* Automated Builds
  * Automatically build container images from GitHub and Bitbucket and push them to Docker Hub.

For details, refer to [Docker Hub - Container Image Library | Docker](https://www.docker.com/products/docker-hub).

## How to Use Docker Container

A Docker container provides an isolated computing environment. A command line command "docker" is used to use a Docker container. 

While a computer is a machine that exists physically, a container is like a machine that exists virtually or a "virtual machine." Just like a user buys a computer, starts the computer, runs programs on it, pauses or stops the machine, and eventually throw away the beloved machine, a container is created, started, run, paused or stopped, and eventually deleted.

### [Lifecycle of Docker Container](https://medium.com/@nagarwal/lifecycle-of-docker-container-d2da9f85959), medium

Understanding this lifecycle is important to use Docker containers. This topic is summarized at [lifecycle_of_docker_container.md](lifecycle_of_docker_container.md).

<img src="images/docker-lifecycle_of_docker_container.png">

The above figure depicts the comprehensive list of commands to use a Docker container throughout its lifecycle. In other words, these are the must-know commands to use a Docker container. To read about the essential commands listed below, refer to [Lifecycle of Docker Container](https://medium.com/@nagarwal/lifecycle-of-docker-container-d2da9f85959), medium.

### [Docker Commands](commands/README.md)

[commands/README.md](commands/README.md) summarizes some Docker commands serving as a cheat sheet.



## Ubuntu Linux on Windows 10 over Docker Desktop

There are several options to run Linux on Windows. Using Docker Desktop is a wonderful choice because a Docker container provides more or like a native Linux computing environment on Windows! To set up this computing environment, [install Docker Desktop on Windows](INSTALL_Docker_Desktop_on_Windows.md) and then run a Docker container like below.

```powershell
PS C:\Users\aimldl> docker run -it aimldl/python3_base_image bash
To run a command as administrator (user "root"), use "sudo <command>".
See "man sudo_root" for details.

user@c0c854755565:~$ pwd
/home/user
user@c0c854755565:~$ tree
.
|-- bin
|-- downloads
|-- lib
`-- uploads

4 directories, 0 files
user@c0c854755565:~$ exit
exit
PS C:\Users\aimldl>
```

## Hello, World for Docker

Docker has to be installed in order to run the following command.

```
$ docker run hello-world
Unable to find image 'hello-world:latest' locally
latest: Pulling from library/hello-world
1b930d010525: Pull complete 
Digest: sha256:f9dfddf63636d84ef479d645ab5885156ae030f611a56f3a7ac7f2fdd86d7e4e
Status: Downloaded newer image for hello-world:latest

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

