

# How to Clean up Unnecessary Docker Images

## Overview

* `docker rmi` removes images while `docker rm` removes containers.
* The size of an image is large. So it's a good practice to clean up unused images on the regular basis.
  * I've encountered situations that the disk space became full because I didn't clean up unused images.

## Example

I see multiple images of `aimldl/python3_base_image` exists.

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

Filter out other images and see only `aimldl/python3_base_image`.

```bash
$ docker images | grep "python3_base_image"
REPOSITORY                    TAG     IMAGE ID      CREATED        SIZE
aimldl/python3_base_image     ver0.2  2f569417310b  11 months ago  1.11GB
aimldl/python3_base_image     latest  588f6d18f46e  18 months ago  1.09GB
aimldl/python3_base_image     ver0.1  588f6d18f46e  18 months ago  1.09GB
$
```

* Remove the older images other than the latest right away?
* It's a bad idea! Valuable information may reside in the older images.
* Unless you're sure, it's better to see what is inside the older images.
* And then remove each unnecessary image with the `docker rmi` one by one.

```bash
$ docker rmi [TODO]
```


