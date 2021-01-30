* Rev.2: 2021-01-29 (Fri)
* Rev.1: 2020-08-12 (Wed)
* Draft: 2020-03-24 (Tue)

# How to Install Docker on Ubuntu

* This document is tested on Ubuntu 18.04.
* The verbose version of this document is [How to Install Docker on Ubuntu (verbose version)](docker_on_ubuntu-verbose_version.md).

## Summary

Step 1. Run [install_docker_on_ubuntu](../bash_scripts/install_docker_on_ubuntu).

```bash
# install_docker_on_ubuntu

## 1. Install
#### Install Docker from the `apt` Repository
sudo apt update
sudo apt remove docker docker-engine docker.io
sudo apt install -y docker.io

## 2. Configure
#### Configure to use Docker when the system starts.
sudo systemctl enable docker     # Start Docker on Boot

#### Configure to use Docker without the `sudo` command
##### This step is optional, but recommended for convenience.
##### Be aware of the risk that the docker group grants privileges equivalent to the root user.
##### See Docker Daemon Attack Surface at https://docs.docker.com/engine/security/security/#docker-daemon-attack-surface.
sudo groupadd docker             # Create the `docker` group
sudo usermod -aG docker ${USER}  # Add your user to the `docker` group

## 3. Log out and log back in
printf "Log out and log back in. Your group membership must be re-evaluated. \n \
Closing this terminal and re-opening another terminal will not work. \n \
On a virtual machine, restart the virtual machine for changes to take effect.\n\n \
Run configure_docker_on_ubuntu to continue. \n"
```

Step 2. Log out and log back in.

Step 3. Run [configure_docker_on_ubuntu](bash_scripts/configure_docker_on_ubuntu) to continue.

```bash
# configure_docker_on_ubuntu
## 4. Verify
#### Verify the installation
docker --version
sudo docker run hello-world

#### Verify the configuration
##### Now you should be able to run the `docker` command without the `sudo` command.
docker run hello-world

printf "====================================================================== \n\n"
printf "You must see 'Hello from Docker!' twice.\n"
printf "Check if docker exists in the list by running: \n \
  $ su - \${USER} \n \
  $ id -nG \n"

printf "You may see if the docker status is 'active (running)' by executing: \n \
  $ systemctl status docker \n \
    Press q to quit 'systemctl status'.\n"
```

## 1. Install

Install Docker from the `apt` Repository.

```bash
$ sudo apt update
$ sudo apt remove docker docker-engine docker.io
$ sudo apt install -y docker.io
```

## 2. Configure

Configure to use Docker when the system starts.

```bash
$ sudo systemctl enable docker     # Start Docker on Boot
```

Configure to use Docker without the `sudo` command.

* This step is optional, but recommended for convenience. 

* Be aware of the risk that the docker group grants privileges equivalent to the root user.
  * See Docker Daemon Attack Surface at https://docs.docker.com/engine/security/security/#docker-daemon-attack-surface.

```bash
$ sudo groupadd docker             # Create the `docker` group
$ sudo usermod -aG docker ${USER}  # Add your user to the `docker` group
```

## 3. Log out and log back in

* Log out and log back in.
* Open a terminal and run `configure_docker_on_ubuntu` to continue.

This is a guide for the following steps.

```bash
Log out and log back in. Your group membership must be re-evaluated. 
 Closing this terminal and re-opening another terminal will not work. 
 On a virtual machine, restart the virtual machine for changes to take effect.

 Run configure_docker_on_ubuntu to continue. 
```

## 4. Verify

### Verify the installation.

```bash
$ docker --version
$ sudo docker run hello-world
```

> Previously, the `sudo` command must precede the `docker` command. Examples include:
>
> ```
> $ sudo docker run hello-world
> $ sudo docker images
> ```
>
> Running without `sudo` results in the permission denied error.
>
> ```bash
> $ docker run hello-world
> docker: Got permission denied while trying to connect to the Docker daemon socket at unix:///var/run/docker.sock: Post http://%2Fvar%2Frun%2Fdocker.sock/v1.40/containers/create: dial unix /var/run/docker.sock: connect: permission denied.
> See 'docker run --help'.
> $
> ```
>

### Verify the configuration.

Now you should be able to run the `docker` command without the `sudo` command.

```bash
$ docker run hello-world
```

So you must see 'Hello from Docker!' twice. If not, log out and log back in. 

The expected output is:

```bash

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

### Verify

Check if `docker` exists in the list by running: 

```bash
$ su - ${USER}
$ id -nG
```

You may see if the docker status is 'active (running)' by executing: 

```bash
$ systemctl status docker
```

Press q to quit 'systemctl status'.

### 5. (Optionally) Run a Docker image

```bash
$ sudo docker run -it ubuntu bash
```

will download the latest Ubuntu Docker image

```bash
Unable to find image 'ubuntu:latest' locally
latest: Pulling from library/ubuntu
83ee3a23efb7: Pull complete 
db98fc6f11f0: Pull complete 
f611acd52c6c: Pull complete 
Digest: sha256:703218c0465075f4425e58fac086e09e1de5c340b12976ab9eb8ad26615c3715
Status: Downloaded newer image for ubuntu:latest
```

and start a container environment of Ubuntu.

```bash
root@bc0273012750:/# 
```

The following command shows the information on the OS release.

```bash
root@bc0273012750:/# cat /etc/os-release
```

You will see something like:

```bash
NAME="Ubuntu"
VERSION="20.04.1 LTS (Focal Fossa)"
ID=ubuntu
ID_LIKE=debian
PRETTY_NAME="Ubuntu 20.04.1 LTS"
VERSION_ID="20.04"
HOME_URL="https://www.ubuntu.com/"
SUPPORT_URL="https://help.ubuntu.com/"
BUG_REPORT_URL="https://bugs.launchpad.net/ubuntu/"
PRIVACY_POLICY_URL="https://www.ubuntu.com/legal/terms-and-policies/privacy-policy"
VERSION_CODENAME=focal
UBUNTU_CODENAME=focal
root@bc0273012750:/# 
```

To exit the container, enter `exit`.

```bash
root@bc0273012750:/# exit
exit
$
```

Notice the prompt is changed from `#` to `$`. 

## References

* [How to Install Docker On Ubuntu 18.04 Bionic Beaver](https://phoenixnap.com/kb/how-to-install-docker-on-ubuntu-18-04)
  * The instructions in [Get Docker Engine - Community for Ubuntu](https://docs.docker.com/install/linux/docker-ce/ubuntu/) > Install Docker Engine - Community failed with errors.

* [Post-installation steps for Linux](https://docs.docker.com/install/linux/linux-postinstall/#manage-docker-as-a-nonroot-user)
* [How to install Docker and Nvidia-Docker 2.0 on Ubuntu 18.04](https://medium.com/@linhlinhle997/how-to-install-docker-and-nvidia-docker-2-0-on-ubuntu-18-04-da3eac6ec494) > Optional — Ensure Docker can run without sudo