

# docker rm

* `docker rm`
  * removes
    * a stopped container
    * containers while `docker rmi` removes images.
  * is equal to `$ docker run --rm`

## Example: remove a stopped container

```bash
$ docker ps -a
CONTAINER ID  IMAGE                      COMMAND      CREATED      STATUS     PORTS  NAMES
7393cd651e3a  aimldl/python3_base_image  "/bin/bash"  10 days ago   ...              nostalgic_mayer
ecc5b142ad2b  hello-world                "/hello"     5 weeks ago   ...              wonderful_darwin
e65b977102fb  hello-world                "/hello"     5 weeks ago   ...              jolly_ellis
$ docker rm nostalgic_mayer 
nostalgic_mayer
$ docker ps -a
CONTAINER ID  IMAGE                      COMMAND      CREATED      STATUS     PORTS  NAMES
ecc5b142ad2b  hello-world                "/hello"     5 weeks ago   ...              wonderful_darwin
e65b977102fb  hello-world                "/hello"     5 weeks ago   ...              jolly_ellis
$ 
```

## Example: remove all unnecessary containers
```bash
$  docker ps
CONTAINER ID  IMAGE                      COMMAND      CREATED      STATUS     PORTS  NAMES
$  docker ps -a
CONTAINER ID  IMAGE                      COMMAND      CREATED      STATUS     PORTS  NAMES
0ea530773393  aimldl/python3_base_image  "bash"       3 days ago    ...              flamboyant_bhabha
c0c854755565  aimldl/python3_base_image  "bash"       3 days ago    ...              determined_ride
2ba0d76279a4  hello-world                "/hello"     3 days ago    ...              sleepy_mcnulty
f1cfe1653fea  hello-world                "/hello"     3 days ago    ...              vibrant_goldstine
$  docker rm flamboyant_bhabha
flamboyant_bhabha
$  docker ps -a
CONTAINER ID  IMAGE                      COMMAND      CREATED      STATUS     PORTS  NAMES
c0c854755565  aimldl/python3_base_image  "bash"       3 days ago    ...              determined_ride
2ba0d76279a4  hello-world                "/hello"     3 days ago    ...              sleepy_mcnulty
f1cfe1653fea  hello-world                "/hello"     3 days ago    ...              vibrant_goldstine
$  docker rm determined_ride
determined_ride
$  docker rm sleepy_mcnulty vibrant_goldstine
sleepy_mcnulty
vibrant_goldstine
$  docker ps -a
CONTAINER ID  IMAGE                      COMMAND      CREATED      STATUS     PORTS  NAMES
$ 
```



## TODO

Note: --network="host" gives the container full access to local system services such as D-bus and is therefore considered insecure.


Clean up (--rm)
By default a container’s file system persists even after the container exits. This makes debugging a lot easier (since you can inspect the final state) and you retain all your data by default. But if you are running short-term foreground processes, these container file systems can really pile up. If instead you’d like Docker to automatically clean up the container and remove the file system when the container exits, you can add the --rm flag:

--rm=false: Automatically remove the container when it exits
Note: When you set the --rm flag, Docker also removes the anonymous volumes associated with the container when the container is removed. This is similar to running docker rm -v my-container. Only volumes that are specified without a name are removed. For example, with docker run --rm -v /foo -v awesome:/bar busybox top, the volume for /foo will be removed, but the volume for /bar will not. Volumes inherited via --volumes-from will be removed with the same logic -- if the original volume was specified with a name it will not be removed.