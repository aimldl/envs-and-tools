* Rev.2: 2021-01-30 (Sat)
* Rev.1: 2020-03-12 (Thu)
* Draft: 2019-11-15 (Fri)

# docker ps

When no container has been started,

```bash
$ docker ps
CONTAINER ID  IMAGE        COMMAND  CREATED      STATUS                 PORTS  NAMES
$
```

When there is a container,

```bash
$ docker ps
CONTAINER ID  IMAGE        COMMAND  CREATED      STATUS                 PORTS  NAMES
ceadff6f1295  ubuntu       "bash"   2 hours ago  Up About an hour              vibrant_jones
$
```

The -a option shows all containers in the local machine.

```bash
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

