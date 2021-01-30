* Rev.2: 2020-0312 (Thu)
* Rev.1: 2020-0311 (Wed)
* Draft: 2019-1115 (Fri)

# Docker Commands
This page selectively summarizes Docker commands.

## Parent Command
"docker" itself is referred to as the base command for Docker CLI (Command Line Interface) or parent command. The docker command, base command, or parent command takes in child commands such as version and info resulting in commands like "docker version" and "docker info". A combination of the parent command and a child command is referred to as a Docker command or simply command.

| Command                                                      | Description                                                  |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [docker](https://docs.docker.com/engine/reference/commandline/docker) | The base command for the Docker CLI.nvcr.io/nvidia/cuda:11.2.0-runtime-ubuntu18.04 |

For the full list of Docker commands, refer to ***[The base command for the Docker CLI](https://docs.docker.com/engine/reference/commandline/docker/)***.

## Child Commands for Managements
The following child commands list relevant commands to manage container and image, respectively.

| Command                                                      | Description                          |
| ------------------------------------------------------------ | ------------------------------------ |
| [docker container](https://docs.docker.com/engine/reference/commandline/container/) | Manage containers |
| [docker image](https://docs.docker.com/engine/reference/commandline/image/) | Manage images |

Other child commands for managements are listed below.
| Command                                                      | Description                          |
| ------------------------------------------------------------ | ------------------------------------ |
| [docker builder](https://docs.docker.com/engine/reference/commandline/builder/) | Manage builds |
| [docker checkpoint](https://docs.docker.com/engine/reference/commandline/checkpoint/) | Manage checkpoints |
| [docker config](https://docs.docker.com/engine/reference/commandline/config/) | Manage Docker configs |
| [docker context](https://docs.docker.com/engine/reference/commandline/context/) | Manage contexts |
| [docker manifest](https://docs.docker.com/engine/reference/commandline/manifest/) | Manage Docker image manifests and manifest lists |
| [docker network](https://docs.docker.com/engine/reference/commandline/network/) | Manage Docker networks |
| [docker node](https://docs.docker.com/engine/reference/commandline/node/) | Manage Swarm nodes |
| [docker plugin](https://docs.docker.com/engine/reference/commandline/plugin/) | Manage plugins |
| [docker secret](https://docs.docker.com/engine/reference/commandline/secret/) | Manage Docker secrets |
| [docker service](https://docs.docker.com/engine/reference/commandline/service/) | Manage services |
| [docker stack](https://docs.docker.com/engine/reference/commandline/stack/) | Manage Docker stacks |
| [docker swarm](https://docs.docker.com/engine/reference/commandline/plugin/) | Manage Swarm |
| [docker system](https://docs.docker.com/engine/reference/commandline/system/) | Manage Docker |
| [docker trust](https://docs.docker.com/engine/reference/commandline/trust/) | Manage trust on Docker images |
| [docker volume](https://docs.docker.com/engine/reference/commandline/plugin/) | Manage volumes |

### Command: docker container
```bash
$docker container

Usage:  docker container COMMAND

Manage containers

Commands:
  attach      Attach local standard input, output, and error streams to a running container
  commit      Create a new image from a container's changes
  cp          Copy files/folders between a container and the local filesystem
  create      Create a new container
  diff        Inspect changes to files or directories on a container's filesystem
  exec        Run a command in a running container
  export      Export a container's filesystem as a tar archive
  inspect     Display detailed information on one or more containers
  kill        Kill one or more running containers
  logs        Fetch the logs of a container
  ls          List containers
  pause       Pause all processes within one or more containers
  port        List port mappings or a specific mapping for the container
  prune       Remove all stopped containers
  rename      Rename a container
  restart     Restart one or more containers
  rm          Remove one or more containers
  run         Run a command in a new container
  start       Start one or more stopped containers
  stats       Display a live stream of container(s) resource usage statistics
  stop        Stop one or more running containers
  top         Display the running processes of a container
  unpause     Unpause all processes within one or more containers
  update      Update configuration of one or more containers
  wait        Block until one or more containers stop, then print their exit codes

Run 'docker container COMMAND --help' for more information on a command.
$
```

### Command: docker image
```bash
$ docker image

Usage:  docker image COMMAND

Manage imagescomputing_environments/docker/commands/

Commands:
  build       Build an image from a Dockerfile
  history     Show the history of an image
  import      Import the contents from a tarball to create a filesystem image
  inspect     Display detailed information on one or more images
  load        Load an image from a tar archive or STDIN
  ls          List images
  prune       Remove unused images
  pull        Pull an image or a repository from a registry
  push        Push an image or a repository to a registry
  rm          Remove one or more images
  save        Save one or more images to a tar archive (streamed to STDOUT by default)
  tag         Create a tag TARGET_IMAGE that refers to SOURCE_IMAGE

Run 'docker image COMMAND --help' for more information on a command.
$
```
### Docker Command Level
#### Commands for Local Machine

| Command                                                      | Description<br />$ Syntax                                    |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [docker version](https://docs.docker.com/engine/reference/commandline/version/) | Show the Docker version information<br />$ docker version [OPTIONS] |
| [docker info](https://docs.docker.com/engine/reference/commandline/info/) | Display system-wide information<br />$ docker info [OPTIONS] |
| [docker ps](https://docs.docker.com/engine/reference/commandline/ps/) | List Docker containers on the local machine<br />$ docker ps [OPTIONS] |
|                                                              | Example<br />  \$ docker ps<br />  \$ docker ps -a           |
| [docker mages](https://docs.docker.com/engine/reference/commandline/images/) | List Docker images on the local machine. (Also shown in Docker Image Level>Image-Level Commands for Local Machine.)<br />$ docker images [OPTIONS] [REPOSITORY[:TAG]] |


```
$ docker version
Client: Docker Engine - Community
 Version:           19.03.5
 API version:       1.40
 Go version:        go1.12.12
   ...
$
```

```
$ docker info
Client:
 Debug Mode: false

Server:
 Containers: 3
  Running: 0
  Paused: 0
  Stopped: 3
 Images: 8Basic
 Server Version: 19.03.5
 Storage Driver: overlay2
  Backing Filesystem: extfs
  Supports d_type: true
  Native Overlay Diff: true
 Logging Driver: json-file

  ...
$
```

When no container has been started,

```
$ docker ps
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
```

When there is a container,

```
$ docker ps
CONTAINER ID  IMAGE        COMMAND  CREATED      STATUS                 PORTS  NAMES
ceadff6f1295  ubuntu       "bash"   2 hours ago  Up About an hour              vibrant_jones
$
```

The -a option shows all containers in the local machine.

```
$ docker ps -a
CONTAINER ID  IMAGE        COMMAND  CREATED      STATUS                 PORTS  NAMES
ceadff6f1295  ubuntu       "bash"   2 hours ago  Up About an hour              vibrant_jones
b54772653615  hello-world  "/hello" 3 hours ago  Exited (0) 2 hours ago        stoic_wiles
  ...
$

$ docker images
REPOSITORY                    TAG     IMAGE ID      CREATED        SIZE
hello-world                   latest  fce289e99eb9  14 months ago  1.84kB
aimldl/python3_base_image     ver0.2  2f569417310b  11 months ago  1.11GB
aimldl/tensorflow_base_image  latest  255f88e7c71f  18 months ago  1.55GB
  ...
$

```

### Docker Image Level
Commands to deal with Docker images on [Docker Hub](https://hub.docker.com/) and the local machine.

#### Image-Level Commands for Docker Hub

| Command                                                      | Description<br />$ Syntax                                    |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [docker login](https://docs.docker.com/engine/reference/commandline/login/) | Log in to a Docker registry<br />$ docker login [OPTIONS] [SERVER] |
| [docker search](https://docs.docker.com/engine/reference/commandline/search/) | Search and list the Docker images on Docker Hub<br />$ docker search [OPTIONS] TERM |
| [docker pull](https://docs.docker.com/engine/reference/commandline/pull/) | Pull an image or a repository from a registry<br />$ docker pull [OPTIONS] NAME[:TAG\|@DIGEST] |
| [docker push](https://docs.docker.com/engine/reference/commandline/push/) | Push an image or a repository to a registry                  |
| [docker logout](https://docs.docker.com/engine/reference/commandline/logout/) | Log out from a Docker registry<br />$ docker logout [SERVER] |

#### Image-Level Commands for Local Machine

| Command                                                      | Description<br />$ Syntax                                    |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [docker images](https://docs.docker.com/engine/reference/commandline/images/) | List Docker images on the local machine. (Also shown in Docker Command Level>Commands for Local Machine.)<br />$ docker images [OPTIONS] [REPOSITORY[:TAG]]<br /> |
| [docker inspect](https://docs.docker.com/engine/reference/commandline/inspect/) | Return low-level information on Docker objects<br />$ docker inspect [OPTIONS] NAME |
|                                                              | Examples:<br />to check the OS (Operating System).<br/>  $ docker inspect --format="{{.Os}}" [Docker image] |
| [docker tag](https://docs.docker.com/engine/reference/commandline/tag/) | Create a tag TARGET_IMAGE that refers to SOURCE_IMAGE. This command names/renames a Docker image. It's like putting a sticky note on an image.<br />$ docker tag SOURCE_IMAGE[:TAG] TARGET_IMAGE[:TAG] |
|                                                              | Examples:<br />Tag an image referenced by ID<br/>  \$ docker tag 0e5574283393 fedora/httpd:version1.0<br/>Tag an image referenced by Name<br/>  \$ docker tag httpd fedora/httpd:version1.0<br/>To tag a local image with name “httpd” and tag “test” into the “fedora” repository with “version1.0.test”:<br/>  \$ docker tag httpd:test fedora/httpd:version1.0.test<br/>Tag an image for a private repository<br/>  \$ docker tag 0e5574283393 myregistryhost:5000/fedora/httpd:version1.0 |
| [docker rmi](https://docs.docker.com/engine/reference/commandline/rmi/) | Remove one or more images (on the local machine).<br />$ docker rmi [OPTIONS] IMAGE [IMAGE...] |
|                                                              | See also [docker build](https://docs.docker.com/engine/reference/commandline/build/), [docker history](https://docs.docker.com/engine/reference/commandline/history/), [docker load](https://docs.docker.com/engine/reference/commandline/load/), [docker save](https://docs.docker.com/engine/reference/commandline/save/), [docker import](https://docs.docker.com/engine/reference/commandline/import/), [docker export](https://docs.docker.com/engine/reference/commandline/export/) |

#### Example to download and prepare a Docker image

```
# Let's use a command line command to log into Docker Hub.
# The login credentials have already been set up in this example.
$ docker login
Authenticating with existing credentials...
WARNING! Your password will be stored unencrypted in /home/userid/.docker/config.json.
Configure a credential helper to remove this warning. See
https://docs.docker.com/engine/reference/commandline/login/#credentials-store

Login Succeeded

# My Docker Hub ID is aimldl. Search the uploaded Docker images by me.
$ docker search aimldl
NAME                      DESCRIPTION     STARS     OFFICIAL     AUTOMATED
aimldl/python3_base_image                 0                               
aimldl/keras_base_image                   0             
aimldl/tensorflow_base_image              0                 
aimldl/flask_was_base_image               0               
aimldl/flask_hello_world                  0         
aimldl/ubuntu_base_image                  0               
  ...
$

# List up the Docker images downloaded to my local machine.
$ docker images
REPOSITORY                    TAG     IMAGE ID      CREATED        SIZE
hello-world                   latest  fce289e99eb9  14 months ago  1.84kB
aimldl/python3_base_image     ver0.2  2f569417310b  11 months ago  1.11GB
aimldl/tensorflow_base_image  latest  255f88e7c71f  18 months ago  1.55GB
  ...
$

# aimldl/keras_base_image doesn't exist on the local machine.
# So let's download the image from Docker Hub to the local machine.
$ docker pull aimldl/keras_base_image
Using default tag: latest
latest: Pulling from aimldl/keras_base_image
124c757242f8: Already exists 
9d866f8bde2a: Already exists 
  ...
f296ef3d9b89: Pull complete 
8c6adc173361: Pull complete 
  ...
Status: Downloaded newer image for aimldl/keras_base_image:latest
docker.io/aimldl/keras_base_image:latest
$

# Verify if the target Docker image "keras_base_image" is downloaded.
$ docker images
REPOSITORY                    TAG     IMAGE ID      CREATED        SIZE
hello-world                   latest  fce289e99eb9  14 months ago  1.84kB
  ...
aimldl/keras_base_image       latest  3b9219a43e4d  18 months ago  1.56GB
  ...
$

# Check the OS in the downloaded image to see if I got the right one.
$ docker inspect --format="{{.Os}}" aimldl/keras_base_image
linux
$

# Rename the image for convenience. I know all images are from aimldl.
$ docker tag aimldl/keras_base_image keras_base_image

# Double-check the result. The same IMAGE ID 3b9219a43e4d has two names!
$ docker images
REPOSITORY                    TAG     IMAGE ID      CREATED        SIZE
hello-world                   latest  fce289e99eb9  14 months ago  1.84kB
  ...
aimldl/keras_base_image       latest  3b9219a43e4d  18 months ago  1.56GB
keras_base_image              latest  3b9219a43e4d  18 months ago  1.56GB

  ...
$

# I could've logged out earlier right after downloading the Docker image.
# But I'm logging out after all the relevant tasks are finished.
# In case the Docker image must be downloaded again.
$ docker logout
Removing login credentials for https://index.docker.io/v1/
$
```

#### Example to clean up unnecessary Docker images

* "docker rmi" removes images while "docker rm" removes containers.
* The size of an image is large. So it's a good practice to clean up unused images on the regular basis. I've encountered situations that the disk space became full because I didn't clean up unused images.

```
# I see multiple images of "aimldl/python3_base_image" exists.
$ docker images
REPOSITORY                    TAG     IMAGE ID      CREATED        SIZE
hello-world                   latest  fce289e99eb9  14 months ago  1.84kB
aimldl/python3_base_image     ver0.2  2f569417310b  11 months ago  1.11GB
  ...
aimldl/python3_base_image     latest  588f6d18f46e  18 months ago  1.09GB
  ...
aimldl/python3_base_image     ver0.1  588f6d18f46e  18 months ago  1.09GB
  ...
$

# Filter out other images and see only "aimldl/python3_base_image".
$ docker images | grep "python3_base_image"
REPOSITORY                    TAG     IMAGE ID      CREATED        SIZE
aimldl/python3_base_image     ver0.2  2f569417310b  11 months ago  1.11GB
aimldl/python3_base_image     latest  588f6d18f46e  18 months ago  1.09GB
aimldl/python3_base_image     ver0.1  588f6d18f46e  18 months ago  1.09GB
$

# Remove the older images other than the lastest one right away?
# It's a bad idea! Valuable information may reside in the older images.
# Unless you're sure, a better practice is to check the content first!
$ [TODO]
$ docker rmi [TODO]
```

### Docker Container Level

| Command                                                      | Description<br />$ Syntax                                    |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [docker create](https://docs.docker.com/engine/reference/commandline/create/) | Create a new container                                       |
| [docker run](https://docs.docker.com/engine/reference/commandline/run/) | Run a command in a new container                             |
| [docker exec](https://docs.docker.com/engine/reference/commandline/exec/) | Run a command in a running container                         |
| [docker start](https://docs.docker.com/engine/reference/commandline/start/) | Start one or more stopped containers                         |
| [docker stop](https://docs.docker.com/engine/reference/commandline/stop/) | Stop one or more running containers                          |
|                                                              | To stop all the running docker containers,<br />  \$ docker stop $(docker ps -a -q) |
| [docker restart](https://docs.docker.com/engine/reference/commandline/restart/) | Restart one or more containers                               |
| [docker rename](https://docs.docker.com/engine/reference/commandline/rename/) | Rename a container                                           |
| [docker top](https://docs.docker.com/engine/reference/commandline/top/) | Display the running processes of a container                 |
| [docker rm](https://docs.docker.com/engine/reference/commandline/rm/) | Remove one or more containers                                |
|                                                              | To destroy all the running docker containers,<br />  \$ docker rm $(docker ps -q -f status=exited) |
| [docker commit](https://docs.docker.com/engine/reference/commandline/commit/) | Create a new image from a container’s changes                |
|                                                              |                                                              |

#### docker run

##### $ docker run [docker_image] 

```
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
 https://docs.docker.com/get-started/\
$
```

##### $ docker run -it [docker_image] bash

'bash' can be replaced to ''/bin/bash'

    $ docker run -it ubuntu bash
    Unable to find image 'ubuntu:latest' locally
    latest: Pulling from library/ubuntu
    423ae2b273f4: Pull complete 
    de83a2304fa1: Pull complete 
      ...
    Status: Downloaded newer image for ubuntu:latest
    root@ceadff6f1295:/#

##### $ docker run -p [docker_image] 

Publish or expose port [-p, --expose]

```
# Expose port 80 of the container
#   without publishing the port to the host system’s interfaces.
$ docker run --expose 80 ubuntu bash
```

```
$ docker run -p 8888:8888 tensorflow/tensorflow
```

#### docker commit

##### $ docker commit [docker_container] [docker_image]:[tag]



   ### load/save

   ### import/export

  $ docker exec

  To log in as the root user (id=0), run:
     $ docker exec -u 0 -it [Docker Container] bash
  For more information, refer to "root password inside a docker container" https://stackoverflow.com/questions/28721699/root-password-inside-a-docker-container
