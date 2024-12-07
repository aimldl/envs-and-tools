* Rev.2: 2021-01-30 (Sat)
* Rev.1: 2020-03-12 (Thu)
* Draft: 2019-11-15 (Fri)

# Docker Commands
## Overview

* This page selectively summarizes Docker commands.
  
* For the full list of Docker commands, refer to [The base command for the Docker CLI](https://docs.docker.com/engine/reference/commandline/docker/).
  
* A **Docker command** consists of **the parent command** and **a child command**.

  <u>docker</u> <u>version</u> →Docker command
       |           |
   parent  child

> `docker` itself is referred to as the **base command** for Docker CLI (Command Line Interface) or **parent command**. The `docker` command, base command, or parent command takes in child commands. Examples include `docker version`, `docker info`, and so on. A combination of the parent command and a child command is referred to as a **Docker command** or simply command.

## Parent command

| Command                                                      | Description                         |
| ------------------------------------------------------------ | ----------------------------------- |
| [docker](https://docs.docker.com/engine/reference/commandline/docker) | The base command for the Docker CLI |

## Child commands

### for local machine

| Command                                                      | Description<br />$ Syntax                                    |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [docker version](https://docs.docker.com/engine/reference/commandline/version/) | Show the Docker version information<br />$ docker version [OPTIONS] |
| [docker info](https://docs.docker.com/engine/reference/commandline/info/) | Display system-wide information<br />$ docker info [OPTIONS] |
| [docker ps](https://docs.docker.com/engine/reference/commandline/ps/) | List Docker containers on the local machine<br />$ docker ps [OPTIONS] |
|                                                              | Example<br />  \$ docker ps<br />  \$ docker ps -a           |
| [docker images](https://docs.docker.com/engine/reference/commandline/images/) | List Docker images on the local machine. (Also shown in Docker Image Level>Image-Level Commands for Local Machine.)<br />$ docker images [OPTIONS] [REPOSITORY[:TAG]] |

### for managements

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

### Docker image level commands

Deal with Docker images on [Docker Hub](https://hub.docker.com/) and the local machine.

#### for Docker Hub

| Command                                                      | Description<br />$ Syntax                                    |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [docker login](https://docs.docker.com/engine/reference/commandline/login/) | Log in to a Docker registry<br />$ docker login [OPTIONS] [SERVER] |
| [docker logout](https://docs.docker.com/engine/reference/commandline/logout/) | Log out from a Docker registry<br />$ docker logout [SERVER] |
| [docker search](https://docs.docker.com/engine/reference/commandline/search/) | Search and list the Docker images on Docker Hub<br />$ docker search [OPTIONS] TERM |
| [docker pull](https://docs.docker.com/engine/reference/commandline/pull/) | Pull an image or a repository from a registry<br />$ docker pull [OPTIONS] NAME[:TAG\|@DIGEST] |
| [docker push](https://docs.docker.com/engine/reference/commandline/push/) | Push an image or a repository to a registry                  |

#### for local machine

| Command                                                      | Description<br />$ Syntax                                    |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [docker images](https://docs.docker.com/engine/reference/commandline/images/) | List Docker images on the local machine.<br />$ docker images [OPTIONS] [REPOSITORY[:TAG]] |
| [docker inspect](https://docs.docker.com/engine/reference/commandline/inspect/) | Return low-level information on Docker objects<br />$ docker inspect [OPTIONS] NAME<br />To check the Operating System.<br/> $ docker inspect --format="{{.Os}}" [Docker image] |
| [docker tag](https://docs.docker.com/engine/reference/commandline/tag/) | Create a tag TARGET_IMAGE that refers to SOURCE_IMAGE. <br />$ docker tag SOURCE_IMAGE[:TAG] TARGET_IMAGE[:TAG]<br />This command names/renames a Docker image. It's like putting a sticky note on an image. |
| [docker rmi](https://docs.docker.com/engine/reference/commandline/rmi/) | Remove one or more images (on the local machine).<br />$ docker rmi [OPTIONS] IMAGE [IMAGE...] |

See also [docker build](https://docs.docker.com/engine/reference/commandline/build/), [docker history](https://docs.docker.com/engine/reference/commandline/history/), [docker load](https://docs.docker.com/engine/reference/commandline/load/), [docker save](https://docs.docker.com/engine/reference/commandline/save/), [docker import](https://docs.docker.com/engine/reference/commandline/import/), [docker export](https://docs.docker.com/engine/reference/commandline/export/).

#### Examples

* [How to download and prepare a Docker image](../how_to/download_and_prepare_a_docker_image.md)
* [How to clean up unnecessary Docker images](../how_to/clean_up_unnecessary_docker_images.md)

### Docker container level commands

| Command                                                      | Description<br />$ Syntax                                    |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [docker create](https://docs.docker.com/engine/reference/commandline/create/) | Create a new container                                       |
| [docker run](https://docs.docker.com/engine/reference/commandline/run/) | Run a command in a new container                             |
| [docker exec](https://docs.docker.com/engine/reference/commandline/exec/) | Run a command in a running container                         |
| [docker start](https://docs.docker.com/engine/reference/commandline/start/) | Start one or more stopped containers                         |
| [docker stop](https://docs.docker.com/engine/reference/commandline/stop/) | Stop one or more running containers. <br />To stop all the running docker containers,<br />  \$ docker stop $(docker ps -a -q) |
| [docker restart](https://docs.docker.com/engine/reference/commandline/restart/) | Restart one or more containers                               |
| [docker rename](https://docs.docker.com/engine/reference/commandline/rename/) | Rename a container                                           |
| [docker top](https://docs.docker.com/engine/reference/commandline/top/) | Display the running processes of a container                 |
| [docker rm](https://docs.docker.com/engine/reference/commandline/rm/) | Remove one or more containers                                |
|                                                              | To destroy all the running docker containers,<br />  \$ docker rm $(docker ps -q -f status=exited) |
| [docker commit](https://docs.docker.com/engine/reference/commandline/commit/) | Create a new image from a container’s changes<br />$ docker commit [docker_container] [docker_image]:[tag] |

