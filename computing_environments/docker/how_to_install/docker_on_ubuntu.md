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
If testing on a virtual machine, it may be necessary to restart the virtual machine for changes to take effect.\n")
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

#### (Optional) To disable the Docker service

$ sudo systemctl disable docker

#### (Optional) To start the Docker service

$  sudo systemctl start docker

#### (Optional) To check the status of docker

Run "sudo systemctl status docker".

##### When docker is active or "Active: active (running)". 

The docker service is running.

```
$ sudo systemctl status docker
● docker.service - Docker Application Container Engine
   Loaded: loaded (/lib/systemd/system/docker.service; disabled; vendor preset: enabled)
   Active: active (running) since Tue 2020-03-24 14:18:10 KST; 1s ago
     Docs: https://docs.docker.com
 Main PID: 9601 (dockerd)
    Tasks: 13
   CGroup: /system.slice/docker.service
           └─9601 /usr/bin/dockerd -H fd:// --containerd=/run/containerd/containerd.sock

 3월 24 14:18:09 Home-Laptop dockerd[9601]: time="2020-03-24T14:18:09.680674624+09:00" level=warning
   ...
3월 24 14:18:10 Home-Laptop systemd[1]: Started Docker Application Container Engine.
```

##### When docker is inactive or "Active: inactive (dead)"

The docker service is not running.

```
$ sudo systemctl status docker
● docker.service - Docker Application Container Engine
   Loaded: loaded (/lib/systemd/system/docker.service; disabled; vendor preset: enabled)
   Active: inactive (dead) since Tue 2020-03-24 14:17:38 KST; 6s ago
     Docs: https://docs.docker.com
  Process: 9324 ExecStart=/usr/bin/dockerd -H fd:// --containerd=/run/containerd/containerd.sock (co
 Main PID: 9324 (code=exited, status=0/SUCCESS)

 3월 24 14:17:25 Home-Laptop dockerd[9324]: time="2020-03-24T14:17:25.245291764+09:00" level=info ms
  ...
 3월 24 14:17:38 Home-Laptop systemd[1]: Stopped Docker Application Container Engine.
```

## Uninstall Docker

This part is an excerpt from [How to completely uninstall docker](https://askubuntu.com/questions/935569/how-to-completely-uninstall-docker).

Step 1. Identify the installed packages

```bash
$ dpkg -l | grep -i docker
ii  docker.io                                  19.03.6-0ubuntu1~18.04.1                         amd64        Linux container runtime
$
```

Step 2. Remove the installed packages.

```bash
$ sudo apt-get purge -y docker-engine docker docker.io docker-ce
$sudo apt-get autoremove -y --purge docker-engine docker docker.io docker-ce
```

Step 3. Remove the remnants. 

The commands in step 2 will not remove images, containers, volumes, or user created configuration files on your host. If you wish to delete all images, containers, and volumes run the following commands:

```bash
$ sudo rm -rf /var/lib/docker /etc/docker
$ sudo rm /etc/apparmor.d/docker
$ sudo groupdel docker
$ sudo rm -rf /var/run/docker.sock
```
