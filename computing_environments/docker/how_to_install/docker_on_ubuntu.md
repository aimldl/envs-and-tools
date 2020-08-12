* Rev.2: 2020-08-12 (Wed)
* Rev.1: 2020-08-11 (Tue)
* Draft: 2020-03-24 (Tue)

# Summary
```bash
# Install
sudo apt-get update
sudo apt-get remove docker docker-engine docker.io
sudo apt install -y docker.io

# verify
docker --version
sudo docker run hello-world

# Configure
sudo groupadd docker           # Create the `docker` group
sudo usermod -aG docker $USER  # Add your user to the `docker` group
sudo systemctl enable docker   # Start Docker on Boot

printf("Log out and log back in so that your group membership is re-evaluated.
Just closing the terminal and re-opening it doesn't work. 
On a virtual machine, restart the virtual machine for changes to take effect.\n")
```

# Install docker on Ubuntu

Install docker for CPU and nvidia-docker for GPU. If the computer has an NVIDIA GPU card for a General Purpose GPU, do install nvidia-docker. Two types of Docker exist: Docker CE (Community Edition) and  Docker EE (Enterprise Edition). Docker CE is the free version.

Note the instructions in [Get Docker Engine - Community for Ubuntu](https://docs.docker.com/install/linux/docker-ce/ubuntu/) to "Install Docker Engine - Community" fail with errors. Instead [How to Install Docker On Ubuntu 18.04 Bionic Beaver](https://phoenixnap.com/kb/how-to-install-docker-on-ubuntu-18-04) is used in this document.

## Install Docker on Ubuntu Using Default Repositories

This part is a summary of [How to Install Docker On Ubuntu 18.04 Bionic Beaver](https://phoenixnap.com/kb/how-to-install-docker-on-ubuntu-18-04). For details, refer to [How to Install Docker On Ubuntu 18.04 Bionic Beaver](https://phoenixnap.com/kb/how-to-install-docker-on-ubuntu-18-04). An alternative method is to install Docker from the official repository.  For details, refer to [How to Install Docker On Ubuntu 18.04 Bionic Beaver](https://phoenixnap.com/kb/how-to-install-docker-on-ubuntu-18-04).

Step 1. Update Software Repositories

```bash
$ sudo apt-get update
  ...
$
```

Step 2. Uninstall Old Versions of Docker

```
$ sudo apt-get remove docker docker-engine docker.io
  ...
$
```

Step 3. Install Docker

```output
$ sudo apt install -y docker.io
```

Step 4. Verify the installation. If the docker command doesn't work, something went wrong in the previous steps.

```
$ docker --version
Docker version 19.03.6, build 369ce74a3c
$
```

> Caution: the installation process is NOT complete. Follow through the post-installation steps to configure the Docker environment.

## Hello, World for Docker

Once docker is successfully installed. Run the "hello-world" image. At first, no image exists on the computer.

```
$ sudo docker images
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
$
```

The "docker run hello-world" command triggers docker to automatically download the image from Docker Hub and runs the image.

```
$ sudo docker run hello-world
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

Check images and the "hello-world" image does exists.

```
$ sudo docker images
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
hello-world         latest              fce289e99eb9        14 months ago       1.84kB
$
```

## Post-installation steps for Linux

This part is excerpts of [Post-installation steps for Linux](https://docs.docker.com/install/linux/linux-postinstall/#manage-docker-as-a-nonroot-user). For details, refer to [Post-installation steps for Linux](https://docs.docker.com/install/linux/linux-postinstall/#manage-docker-as-a-nonroot-user).

### Configuring Linux so that "sudo" is Not Necessary

So far "sudo" is necessary every time the "docker" command is used. Examples include:

```
$ sudo docker images
$ sudo docker run hello-world
```

Running without "sudo" results in the permission denied error.

```
$ docker run hello-world
docker: Got permission denied while trying to connect to the Docker daemon socket at unix:///var/run/docker.sock: Post http://%2Fvar%2Frun%2Fdocker.sock/v1.40/containers/create: dial unix /var/run/docker.sock: connect: permission denied.
See 'docker run --help'.
$
```

In order not to enter "sudo" every single time, create a Unix group called `docker` and add users to it. 

**Warning: The `docker` group grants privileges equivalent to the `root` user. For details on how this impacts security in your system, see [*Docker Daemon Attack Surface*](https://docs.docker.com/engine/security/security/#docker-daemon-attack-surface).**

### How to Configure Linux / Manage Docker as a non-root user

#### Step 1. Create the `docker` group.

```
$ sudo groupadd docker
```

#### Step 2. Add your user to the `docker` group.

```
$ sudo usermod -aG docker $USER
```

#### Step 3. Log out and log back in so that your group membership is re-evaluated.

Just closing the terminal and re-opening it doesn't work. If testing on a virtual machine, it may be necessary to restart the virtual machine for changes to take effect.



### Configure Docker to Start on Boot

The Docker service needs to be setup to run at startup. To do so, type in:

```output
$ sudo systemctl enable docker
Created symlink /etc/systemd/system/multi-user.target.wants/docker.service → /lib/systemd/system/docker.service.
$
```

Most current Linux distributions (RHEL, CentOS, Fedora, Ubuntu 16.04 and higher) use **systemd** to manage which services start when the system boots. For Ubuntu 14.10 and below, use upstart in [the document](https://docs.docker.com/install/linux/linux-postinstall/#manage-docker-as-a-nonroot-user).

### Let's double-check the configuration
Say the previous configuration not to use `sudo` fails after the reboot. Let's check each step one by one to fix the problem.

#### List all the groups
For
```
Step 1. Create the docker group
$ sudo groupadd docker
```
run the `groups` command to list all the groups.
```bash
$ groups
h2o_docker sudo docker
$
```
The `docker` group does exist. For details, refer to [How to List Groups in Linux](https://linuxize.com/post/how-to-list-groups-in-linux/).

#### List the groups that the current user belongs to
For
```
Step 2. Add your user to the `docker` group.
$ sudo usermod -aG docker $USER
```
run the `groups` command with the current user name
```bash
$ groups $USER
h2o_docker : h2o_docker sudo docker
$
```
The user name is `h2o_docker` and this user does belong to the group `docker`. For details, refer to [How to Check the User Group(s) an Ubuntu User Belongs To](https://vitux.com/how-to-check-the-user-groups-an-ubuntu-user-belongs-to/).

#### Check the rest of configurations
For the following two actions, 
```
Step 3. Log out and log back in so that your group membership is re-evaluated.

Configure Docker to Start on Boot
$ sudo systemctl enable docker
```
check the status of docker by running:
```bash
$ sudo systemctl status docker
[sudo] h2o_docker의 암호: 
● docker.service - Docker Application Container Engine
   Loaded: loaded (/lib/systemd/system/docker.service; enabled; vendor preset: enabled)
   Active: active (running) since Wed 2020-08-12 10:08:34 KST; 5min ago
     Docs: https://docs.docker.com
 Main PID: 2006 (dockerd)
    Tasks: 18
   CGroup: /system.slice/docker.service
           └─2006 /usr/bin/dockerd -H fd:// --containerd=/run/containerd/containerd.sock

 8월 12 10:08:33 h2o-Alienware-Aurora-R6 dockerd[2006]: time="2020-08-12T10:08:33.842297158+09:00" le
 8월 12 10:08:33 h2o-Alienware-Aurora-R6 dockerd[2006]: time="2020-08-12T10:08:33.842341908+09:00" le
 8월 12 10:08:33 h2o-Alienware-Aurora-R6 dockerd[2006]: time="2020-08-12T10:08:33.842374838+09:00" le
 8월 12 10:08:33 h2o-Alienware-Aurora-R6 dockerd[2006]: time="2020-08-12T10:08:33.842755445+09:00" le
 8월 12 10:08:34 h2o-Alienware-Aurora-R6 dockerd[2006]: time="2020-08-12T10:08:34.473487034+09:00" le
 8월 12 10:08:34 h2o-Alienware-Aurora-R6 dockerd[2006]: time="2020-08-12T10:08:34.709750212+09:00" le
 8월 12 10:08:34 h2o-Alienware-Aurora-R6 dockerd[2006]: time="2020-08-12T10:08:34.801052395+09:00" le
 8월 12 10:08:34 h2o-Alienware-Aurora-R6 dockerd[2006]: time="2020-08-12T10:08:34.801309762+09:00" le
 8월 12 10:08:34 h2o-Alienware-Aurora-R6 dockerd[2006]: time="2020-08-12T10:08:34.822477454+09:00" le
 8월 12 10:08:34 h2o-Alienware-Aurora-R6 systemd[1]: Started Docker Application Container Engine.
```
Docker is loaded and active. It's fine. Enter `q` to quit and get out of this.

#### What's the problem then?
I don't know.
