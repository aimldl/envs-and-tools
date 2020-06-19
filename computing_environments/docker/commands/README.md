##### aimldl/computing_environments/docker/commands/README.md

* Rev.1: 2020-0311 (Wed)
* Draft: 2019-1115 (Fri)

# Docker Commands

This page selectively summarizes Docker commands. 

| Command                                                      | Description                          |
| ------------------------------------------------------------ | ------------------------------------ |
| [docker](https://docs.docker.com/engine/reference/commandline/docker) | The base command for the Docker CLI. |

For the full list of Docker commands, refer to [The base command for the Docker CLI](https://docs.docker.com/engine/reference/commandline/docker/).

## Docker Command Level

### Commands for Local Machine

| Command                                                      | Description<br />$ Syntax                                    |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [docker version](https://docs.docker.com/engine/reference/commandline/version/) | Show the Docker version information<br />$ docker version [OPTIONS] |
| [docker info](https://docs.docker.com/engine/reference/commandline/info/) | Display system-wide information<br />$ docker info [OPTIONS] |
| [docker ps](https://docs.docker.com/engine/reference/commandline/ps/) | List Docker containers on the local machine<br />$ docker ps [OPTIONS] |
|                                                              | Example<br />  \$ docker ps<br />  \$ docker ps -a           |
| [docker mages](https://docs.docker.com/engine/reference/commandline/images/) | List Docker images on the local machine. (Also shown in Docker Image Level>Image-Level Commands for Local Machine.)<br />$ docker images [OPTIONS] [REPOSITORY[:TAG]] |

## Docker Image Level
Commands to deal with Docker images on [Docker Hub](https://hub.docker.com/) and the local machine.

### Image-Level Commands for Docker Hub

| Command                                                      | Description<br />$ Syntax                                    |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [docker login](https://docs.docker.com/engine/reference/commandline/login/) | Log in to a Docker registry<br />$ docker login [OPTIONS] [SERVER] |
| [docker search](https://docs.docker.com/engine/reference/commandline/search/) | Search and list the Docker images on Docker Hub<br />$ docker search [OPTIONS] TERM |
| [docker pull](https://docs.docker.com/engine/reference/commandline/pull/) | Pull an image or a repository from a registry<br />$ docker pull [OPTIONS] NAME[:TAG\|@DIGEST] |
| [docker push](https://docs.docker.com/engine/reference/commandline/push/) | Push an image or a repository to a registry                  |
| [docker logout](https://docs.docker.com/engine/reference/commandline/logout/) | Log out from a Docker registry<br />$ docker logout [SERVER] |

### Image-Level Commands for Local Machine

| Command                                                      | Description<br />$ Syntax                                    |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [docker images](https://docs.docker.com/engine/reference/commandline/images/) | List Docker images on the local machine. (Also shown in Docker Command Level>Commands for Local Machine.)<br />$ docker images [OPTIONS] [REPOSITORY[:TAG]]<br /> |
| [docker inspect](https://docs.docker.com/engine/reference/commandline/inspect/) | Return low-level information on Docker objects<br />$ docker inspect [OPTIONS] NAME |
|                                                              | Examples:<br />to check the OS (Operating System).<br/>  $ docker inspect --format="{{.Os}}" [Docker image] |
| [docker tag](https://docs.docker.com/engine/reference/commandline/tag/) | Create a tag TARGET_IMAGE that refers to SOURCE_IMAGE. This command names/renames a Docker image. It's like putting a sticky note on an image.<br />$ docker tag SOURCE_IMAGE[:TAG] TARGET_IMAGE[:TAG] |
|                                                              | Examples:<br />Tag an image referenced by ID<br/>  \$ docker tag 0e5574283393 fedora/httpd:version1.0<br/>Tag an image referenced by Name<br/>  \$ docker tag httpd fedora/httpd:version1.0<br/>To tag a local image with name “httpd” and tag “test” into the “fedora” repository with “version1.0.test”:<br/>  \$ docker tag httpd:test fedora/httpd:version1.0.test<br/>Tag an image for a private repository<br/>  \$ docker tag 0e5574283393 myregistryhost:5000/fedora/httpd:version1.0 |
| [docker rmi](https://docs.docker.com/engine/reference/commandline/rmi/) | Remove one or more images (on the local machine).<br />$ docker rmi [OPTIONS] IMAGE [IMAGE...] |
|                                                              | See also [docker build](https://docs.docker.com/engine/reference/commandline/build/), [docker history](https://docs.docker.com/engine/reference/commandline/history/), [docker load](https://docs.docker.com/engine/reference/commandline/load/), [docker save](https://docs.docker.com/engine/reference/commandline/save/), [docker import](https://docs.docker.com/engine/reference/commandline/import/), [docker export](https://docs.docker.com/engine/reference/commandline/export/) |

* [Example to download and prepare a Docker image](Example to download and prepare a Docker image.md)

* [Example to clean up unnecessary Docker images](Example to clean up unnecessary Docker images.md)

## Docker Container Level

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

* [docker run](docker run.md)

[TODO] Add more commands and summary.



### docker commit

##### $ docker commit [docker_container] [docker_image]:[tag]



   ### load/save

   ### import/export

  $ docker exec

  To log in as the root user (id=0), run:
     $ docker exec -u 0 -it [Docker Container] bash
  For more information, refer to "root password inside a docker container" https://stackoverflow.com/questions/28721699/root-password-inside-a-docker-container