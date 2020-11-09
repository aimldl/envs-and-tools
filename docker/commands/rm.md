rm.md

docker rm
Removing a stopped container
Equivalently $ docker run --rm

Note: --network="host" gives the container full access to local system services such as D-bus and is therefore considered insecure.


Clean up (--rm)
By default a container’s file system persists even after the container exits. This makes debugging a lot easier (since you can inspect the final state) and you retain all your data by default. But if you are running short-term foreground processes, these container file systems can really pile up. If instead you’d like Docker to automatically clean up the container and remove the file system when the container exits, you can add the --rm flag:

--rm=false: Automatically remove the container when it exits
Note: When you set the --rm flag, Docker also removes the anonymous volumes associated with the container when the container is removed. This is similar to running docker rm -v my-container. Only volumes that are specified without a name are removed. For example, with docker run --rm -v /foo -v awesome:/bar busybox top, the volume for /foo will be removed, but the volume for /bar will not. Volumes inherited via --volumes-from will be removed with the same logic -- if the original volume was specified with a name it will not be removed.

```bash
aimldl@GPU-Desktop:~$ docker ps -a
CONTAINER ID        IMAGE                          COMMAND             CREATED             STATUS                      PORTS               NAMES
7393cd651e3a        aimldl/python3_base_image      "/bin/bash"         10 days ago         Exited (0) 26 seconds ago                       nostalgic_mayer
ecc5b142ad2b        hello-world                    "/hello"            5 weeks ago         Exited (0) 5 weeks ago                          wonderful_darwin
e65b977102fb        hello-world                    "/hello"            5 weeks ago         Exited (0) 5 weeks ago                          jolly_ellis
aimldl@GPU-Desktop:~$ docker rm nostalgic_mayer 
nostalgic_mayer
aimldl@GPU-Desktop:~$ docker ps -a
CONTAINER ID        IMAGE                          COMMAND             CREATED             STATUS                     PORTS               NAMES
ecc5b142ad2b        hello-world                    "/hello"            5 weeks ago         Exited (0) 5 weeks ago                         wonderful_darwin
e65b977102fb        hello-world                    "/hello"            5 weeks ago         Exited (0) 5 weeks ago                         jolly_ellis
aimldl@GPU-Desktop:~$ 
```
