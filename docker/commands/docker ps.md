# docker ps

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

## 