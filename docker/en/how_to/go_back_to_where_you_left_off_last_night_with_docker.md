* 2021-01-31 (Sun)

# Go back to Where You Left off Last Night with Docker

## Overview

* Say you had to go to bed last night even though you wanted to finish up your project with a Docker container.
* An example to go back to where you left off last night is shown here.
  * In other words, you can retrieve  the  same  working  environment with a Docker container.
    * When your computer was turned off last night, the Docker container has been stopped.

* After rebooting your computer this morning, you can start the container

```bash
$ docker start [container_id]
  or
$ docker start [container_name]
```

 and attach to it.

```bash
$ docker attach [container_id]
  or
$ docker attach [container_name]
```

## Example

* Check the container ID or name first.
* `docker ps` shows all the active containers. Nothing is shown in the list.
* So see all containers including inactive ones with the `docker ps -a` command.

```bash
$ docker ps
CONTAINER ID  IMAGE                  COMMAND  CREATED  STATUS                  PORTS  NAMES
$ docker ps -a
CONTAINER ID  IMAGE                  COMMAND  CREATED  STATUS                  PORTS  NAMES
c0bffd73888a  nvidia/cuda:11.0-base  "bash"     ...    Exited (1) 7 hours ago         stupefied_cori
bc0b5bae0179  nvidia/cuda:11.0-base  "bash"     ...    Exited (0) 12 hours ago        competent_neumann
2b59554032b3  hello-world            "/hello"   ...    Exited (0) 14 hours ago        xenodochial_hugle
$
```

Say my target container name is `stupefied_cori`.

Start the container by name and 

```bash
$ docker start stupefied_cori
stupefied_cori
$
```

and I can see this container is active

```bash
$ docker ps
CONTAINER ID  IMAGE                  COMMAND  CREATED  STATUS                  PORTS  NAMES
c0bffd73888a  nvidia/cuda:11.0-base  "bash"     ...    Exited (1) 7 hours ago         stupefied_cori
$
```

Let's attach to it and get into this container environment.

```bash
$ docker attach stupefied_cori
root@c0bffd73888a:/#
```

The shell has been changed from `$` to `root@c0bffd73888a:/#` indicating you're in the container environment.

To remind what has been done previously, run `history`.

```bash
root@c0bffd73888a:/# history
    1  ls
    2  cd home
    3  mkdir darknet
    4  ls
    5  cd darknet/
    6  ls
    7  nano install_opencv
    8  apt install -y nano
    9  sudo apt update
   10  apt update
   11  apt upgrade -y
   12  apt install -y nano
   13  nano
   14  nano install_opencv
   15  ls
   16  chmod +x install_opencv 
   17  ./install_opencv 
   18  ls
   19  cd home
   20  cd darknet/
   21  ls
   22  history
root@c0bffd73888a:/#
```

* I've gone back to where I left off and reminded myself what was done last night. 
* Now I'm good to go!