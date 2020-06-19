# docker rm
* "docker rm" removes containers while "docker rmi" removes images.

## Example to clean up unnecessary Docker containers

### Remove All unnecessary containers
```
$  docker ps
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
$  docker ps -a
CONTAINER ID        IMAGE                       COMMAND             CREATED             STATUS                      PORTS               NAMES
0ea530773393        aimldl/python3_base_image   "bash"              3 days ago          Exited (255) 18 hours ago                       flamboyant_bhabha
c0c854755565        aimldl/python3_base_image   "bash"              3 days ago          Exited (0) 3 days ago                           determined_ride
2ba0d76279a4        hello-world                 "/hello"            3 days ago          Exited (0) 3 days ago                           sleepy_mcnulty
f1cfe1653fea        hello-world                 "/hello"            3 days ago          Exited (0) 3 days ago                           vibrant_goldstine
$  docker rm flamboyant_bhabha
flamboyant_bhabha
$  docker ps -a
CONTAINER ID        IMAGE                       COMMAND             CREATED             STATUS                  PORTS               NAMES
c0c854755565        aimldl/python3_base_image   "bash"              3 days ago          Exited (0) 3 days ago                       determined_ride
2ba0d76279a4        hello-world                 "/hello"            3 days ago          Exited (0) 3 days ago                       sleepy_mcnulty
f1cfe1653fea        hello-world                 "/hello"            3 days ago          Exited (0) 3 days ago                       vibrant_goldstine
$  docker rm determined_ride
determined_ride
$  docker rm sleepy_mcnulty vibrant_goldstine
sleepy_mcnulty
vibrant_goldstine
$  docker ps -a
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
$ 
```

