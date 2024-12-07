#

# docker rmi

* `docker rmi` removes images while `docker rm` removes containers.

## Example: remove all the old versions

The size of an image is large. So it's a good practice to clean up unused images on the regular basis. I've encountered situations that the disk space became full because I didn't clean up unused images.

```bash
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
```

I see multiple images of "aimldl/python3_base_image" exists. The list is quite long and hard to understand. So let's filter out other images and see only "aimldl/python3_base_image".

```bash
$ docker images | grep "python3_base_image"
REPOSITORY                    TAG     IMAGE ID      CREATED        SIZE
aimldl/python3_base_image     ver0.2  2f569417310b  11 months ago  1.11GB
aimldl/python3_base_image     latest  588f6d18f46e  18 months ago  1.09GB
aimldl/python3_base_image     ver0.1  588f6d18f46e  18 months ago  1.09GB
$



$ docker rmi [TODO]
```

#### Remove the Older Images Right Away?

Can we remove the older images other than the lastest one right away? I think it's a bad idea because valuable information may reside inside them. Unless you're sure, a better practice is to check the content first! So let's check what's inside of ver0.1 and ver0.2.

#### Check What's Inside ver0.1

```bash
$ docker run -it aimldl/python3_base_image:ver0.1 bash 
To run a command as administrator (user "root"), use "sudo <command>".
See "man sudo_root" for details.

user@f819dc09e431:~$ ls
bin  downloads  lib  uploads
user@f819dc09e431:~$ pwd
/home/user
user@f819dc09e431:~$ tree
.
|-- bin
|-- downloads
|-- lib
`-- uploads

4 directories, 0 files
user@f819dc09e431:~$ exit
exit
$ 
```

There is nothing other than directories in ver0.1. So it's fine to delete it.

#### Remove ver0.1

```bash
$ docker images |grep python3_base_image
aimldl/python3_base_image     ver0.2  2f569417310b  11 months ago  1.11GB
aimldl/python3_base_image     latest  588f6d18f46e  18 months ago  1.09GB
aimldl/python3_base_image     ver0.1  588f6d18f46e  18 months ago  1.09GB
$ docker rmi aimldl/python3_base_image:ver0.1
Untagged: aimldl/python3_base_image:ver0.1

# Double-check if ver0.1 is removed.
$ docker images |grep python3_base_image
aimldl/python3_base_image  ver0.2  2f569417310b  11 months ago  1.11GB
aimldl/python3_base_image  latest  588f6d18f46e  18 months ago  1.09GB
$
```

ver0.1 is removed successfully.

#### Check What's Inside ver0.2

```bash
$ docker run -it aimldl/python3_base_image:ver0.2 bash
user@19968a9c5e3d:~$ pwd
/home/user
user@19968a9c5e3d:~$ tree
.
|-- bin
|-- downloads
|-- lib
`-- uploads

4 directories, 0 files
user@19968a9c5e3d:~$ exit
exit
$
```

There's no data in it. So it's fine to delete ver0.2 as well.

#### Remove ver0.2

Unlike ver0.1, removing ver0.2 fails because a container is using the image.

```bash
$ docker rmi aimldl/python3_base_image:ver0.2
Error response from daemon: conflict: unable to remove repository reference "aimldl/python3_base_image:ver0.2" (must force) - container 19968a9c5e3d is using its referenced image 2f569417310b
$
```

Now let's list up containers. "docker ps" lists up active containers, but there's no result.

```bash
$ docker ps | grep python3_base_image
$
```

Let's use "docker ps -a" which shows all containers. I do see the first container with ID 19968a9c5e3d is used by ver0.2.

```bash
$ docker ps -a
CONTAINER ID  IMAGE                             ...  NAMES
19968a9c5e3d  aimldl/python3_base_image:ver0.2  ...  recursing_black
63edc552b5a3  aimldl/python3_base_image         ...  laughing_carson
  ...
b54772653615  hello-world                       ...  stoic_wiles
  ...
$

(base) aimldl@GPU-Desktop:~/github$ docker ps -a | grep python3_base_image
19968a9c5e3d        aimldl/python3_base_image:ver0.2   "bash"              21 minutes ago      Exited (0) 21 minutes ago                        recursing_black
63edc552b5a3        aimldl/python3_base_image          "bash"              22 minutes ago      Exited (0) 21 minutes ago                        laughing_carson
(base) aimldl@GPU-Desktop:~/github$ 
```

Note the list may be long. In that case, the grep command is helpful filtering out only relevant lines.

```bash
# Use any keyword like the image name
$ docker ps -a | grep python3_base_image
19968a9c5e3d  aimldl/python3_base_image:ver0.2  ...  recursing_black
63edc552b5a3  aimldl/python3_base_image         ...  laughing_carson
$

# or Container ID
$ docker ps -a | grep 19968a9c5e3d
19968a9c5e3d  aimldl/python3_base_image:ver0.2  ...  recursing_black
$
```

Let's check if there's any valuable information in this container. First, activate the container with "docker start". Next, check if the container has been started with "docker ps". Lastly, execute the container with "docker exec".

```bash
$ docker start 19968a9c5e3d
$ docker ps
CONTAINER ID  IMAGE                             ...  NAMES
19968a9c5e3d  aimldl/python3_base_image:ver0.2  ...  recursing_black
$ docker exec -it recursing_black bash
user@19968a9c5e3d:~$ pwd
/home/user
user@19968a9c5e3d:~$ tree
.
|-- bin
|-- downloads
|-- lib
`-- uploads

4 directories, 0 files
user@19968a9c5e3d:~$ exit
exit
$
```

Inside the container, no valuable information exists. So it's fine to get rid of it.

To remove the image, the associated container must be removed. 

## TODO

$ docker start 19968a9c5e3d
19968a9c5e3d
$ docker ps
CONTAINER ID        IMAGE                              COMMAND             CREATED             STATUS              PORTS               NAMES
19968a9c5e3d        aimldl/python3_base_image:ver0.2   "bash"              33 minutes ago      Up 37 seconds                           recursing_black
$ docker stop 19968a9c5e3d
19968a9c5e3d
$ docker ps
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
ceadff6f1295        ubuntu              "bash"              4 hours ago         Up 4 hours                              vibrant_jones
$ docker start recursing_black 
recursing_black
$ docker ps
CONTAINER ID        IMAGE                              COMMAND             CREATED             STATUS              PORTS               NAMES
19968a9c5e3d        aimldl/python3_base_image:ver0.2   "bash"              34 minutes ago      Up 3 seconds                            recursing_black
ceadff6f1295        ubuntu                             "bash"              4 hours ago         Up 4 hours                              vibrant_jones
$ docker exec -it recursing_black bash
user@19968a9c5e3d:~$ pwd
/home/user
user@19968a9c5e3d:~$ tree
.
|-- bin
|-- downloads
|-- lib
`-- uploads

4 directories, 0 files


(base) aimldl@GPU-Desktop:~/github$ docker rmi aimldl/python3_base_image:ver0.2
Error response from daemon: conflict: unable to remove repository reference "aimldl/python3_base_image:ver0.2" (must force) - container 19968a9c5e3d is using its referenced image 2f569417310b
(base) aimldl@GPU-Desktop:~/github$ docker rm 19968a9c5e3d
Error response from daemon: You cannot remove a running container 19968a9c5e3dce3a4159e6de07178147163f8a45d4f34727a99daa3a2ec58de2. Stop the container before attempting removal or force remove
(base) aimldl@GPU-Desktop:~/github$ docker stop 19968a9c5e3d
19968a9c5e3d
(base) aimldl@GPU-Desktop:~/github$ docker ps
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
ceadff6f1295        ubuntu              "bash"              4 hours ago         Up 4 hours                              vibrant_jones
(base) aimldl@GPU-Desktop:~/github$ docker ps | grep 19968a9c5e3d
(base) aimldl@GPU-Desktop:~/github$ docker rm 19968a9c5e3d
19968a9c5e3d
(base) aimldl@GPU-Desktop:~/github$ docker ps -a | grep 19968a9c5e3d
$ docker rmi aimldl/python3_base_image:ver0.2 
Untagged: aimldl/python3_base_image:ver0.2
Untagged: aimldl/python3_base_image@sha256:39659004b55832a76f4d6ae27822f8b88d35d4990261f0f817e3ddecbe7ea1f9
Deleted: sha256:2f569417310b79188d647c779a073ee49e21ca9f3117f178bc7ff78b6f4d2e40
Deleted: sha256:ab12e2dbc8ebf3d965fe284fd7bca72763bb60a4e24dbc8d86e2cee3f841bd33
$

$ docker images | grep python3_base_image
aimldl/python3_base_image                  latest              588f6d18f46e        18 months ago       1.09GB