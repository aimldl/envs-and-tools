

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

## Example2

The following commands are run at

* `(base) k8smaster@k8smaster-Alienware-Aurora-R7:~/github/tools/yolo/v3/install`

There was no specific purpose. Cleaning up some unused images is what was done below.

```bash
$ docker images
REPOSITORY                            TAG                          IMAGE ID            CREATED             SIZE
aimldl/darknet                        gpu_cudnn_opencv_version     4b159247967d        3 hours ago         6.51GB
baseimage-darknet                     ver0.4                       3a48bd8567fd        5 days ago          8.36GB
baseimage-darknet                     ver0.3                       9ed3aa90a41c        5 days ago          10.2GB
baseimage-darknet                     ver0.2                       40b7c6a87c86        5 days ago          8.36GB
baseimage-darknet                     latest                       3d0a19184aa9        5 days ago          7.27GB
cuda_with_x11                         latest                       e51cb8db05ff        5 days ago          4.93GB
cuda                                  ver0.1                       13907d3dcb52        5 days ago          4.77GB
nvidia/cuda                           11.2.0-devel-ubuntu20.04     d229b1c49851        10 days ago         4.25GB
nvidia/cuda                           11.2.0-devel-ubuntu18.04     0b7ce4b2aaa4        11 days ago         4.22GB
<none>                                <none>                       67532306e1b6        2 weeks ago         4.23GB
nvcr.io/nvidia/cuda                   11.2.0-runtime-ubuntu18.04   5b3bfc967c6d        4 weeks ago         2.01GB
datamachines/cuda_tensorflow_opencv   10.2_2.3.1_4.5.0-20201204    88ee926b4281        2 months ago        8.32GB
$ docker ps -a
CONTAINER ID  IMAGE                                    COMMAND CREATED             STATUS                     PORTS               NAMES
228b2e12fee0  aimldl/darknet:gpu_cudnn_opencv_version  "bash"  About an hour ago   Up About an hour                               affectionate_shirley
1e6bdeec1030  baseimage-darknet:ver0.2                 "bash"  5 days ago          Exited (255) 2 hours ago                       vibrant_bartik
b865d9c1f5da  baseimage-darknet:ver0.2                 "bash"  5 days ago          Exited (255) 2 hours ago                       quirky_engelbart
f508e9cee903  baseimage-darknet                        "bash"  5 days ago          Exited (255) 2 hours ago                       vibrant_jang
644157d4bceb  3d0a19184aa9                             "/bin/sh -c 'apt-get…"   5 days ago          Exited (100) 5 days ago                        interesting_bose
3fdee107ae16  5b12024f8062                             "bash"  5 days ago          Exited (127) 5 days ago                        mystifying_chandrasekhar
d65596fe9a45  b6ed5359269b                             "bash"  5 days ago          Exited (1) 5 days ago                          pensive_knuth
e65d06c0f9ff  5b12024f8062                             "bash"  5 days ago          Exited (1) 5 days ago                          practical_swartz
f406a53f9197  cuda_with_x11                            "bash"  5 days ago          Exited (127) 5 days ago                        adoring_faraday
303fba46b646  cuda_with_x11                            "bash"  5 days ago          Exited (1) 5 days ago                          wonderful_mahavira
3d504ede6430  cuda_with_x11                            "bash"  5 days ago          Exited (0) 5 days ago                          boring_shirley
64994096281a  cuda_with_x11                            "bash"  5 days ago          Exited (0) 5 days ago                          exciting_haslett
dfd4f2088c7c  cuda_with_x11                            "bash"  5 days ago          Exited (0) 5 days ago                          beautiful_solomon
49fc725be2b7  cuda_with_x11                            "bash"  5 days ago          Exited (1) 5 days ago                          crazy_euler
7e90cc45d542  cuda_with_x11                            "bash"  5 days ago          Exited (1) 5 days ago                          youthful_feistel
6ed110cd2fea  cuda_with_x11                            "bash"  5 days ago          Exited (0) 5 days ago                          goofy_bartik
0f849469a8df  nvcr.io/nvidia/cuda:11.2.0-runtime-ubuntu18.04   "bash"  11 days ago         Exited (0) 5 days ago                          brave_grothendieck
81aae2fef9ac  88ee926b4281                             "bash"  2 weeks ago         Exited (0) 12 days ago                         trusting_rosalind
134efd710933  67532306e1b6                             "bash"  2 weeks ago         Exited (127) 2 weeks ago                       silly_kapitsa
$ docker rm 81aae2fef9ac
81aae2fef9ac
$ docker rmi 88ee926b4281
Untagged: datamachines/cuda_tensorflow_opencv:10.2_2.3.1_4.5.0-20201204
  ...
Deleted: sha256:80580270666742c625aecc56607a806ba343a66a8f5a7fd708e6c4e4c07a3e9b
$ docker rm 0f849469a8df
0f849469a8df
$ docker rmi 5b3bfc967c6d
Error response from daemon: conflict: unable to delete 5b3bfc967c6d (cannot be forced) - image has dependent child images
$ docker rmi -f 5b3bfc967c6d
Error response from daemon: conflict: unable to delete 5b3bfc967c6d (cannot be forced) - image has dependent child images
$ docker rmi d229b1c49851
  ...
Deleted: sha256:d229b1c498519ffa7807118bad911209032d567ed0270d296c04b8b541396de2
$ docker rmi 0b7ce4b2aaa4
Error response from daemon: conflict: unable to delete 0b7ce4b2aaa4 (cannot be forced) - image has dependent child images
$ docker images
REPOSITORY            TAG                          IMAGE ID            CREATED             SIZE
aimldl/darknet        gpu_cudnn_opencv_version     4b159247967d        3 hours ago         6.51GB
baseimage-darknet     ver0.4                       3a48bd8567fd        5 days ago          8.36GB
baseimage-darknet     ver0.3                       9ed3aa90a41c        5 days ago          10.2GB
baseimage-darknet     ver0.2                       40b7c6a87c86        5 days ago          8.36GB
baseimage-darknet     latest                       3d0a19184aa9        5 days ago          7.27GB
cuda_with_x11         latest                       e51cb8db05ff        5 days ago          4.93GB
cuda                  ver0.1                       13907d3dcb52        5 days ago          4.77GB
nvidia/cuda           11.2.0-devel-ubuntu18.04     0b7ce4b2aaa4        11 days ago         4.22GB
<none>                <none>                       67532306e1b6        2 weeks ago         4.23GB
nvcr.io/nvidia/cuda   11.2.0-runtime-ubuntu18.04   5b3bfc967c6d        4 weeks ago         2.01GB
$ docker rmi 67532306e1b6
Error response from daemon: conflict: unable to delete 67532306e1b6 (must be forced) - image is being used by stopped container 134efd710933
$ docker ps
CONTAINER ID        IMAGE                                     COMMAND             CREATED             STATUS              PORTS               NAMES
228b2e12fee0        aimldl/darknet:gpu_cudnn_opencv_version   "bash"              2 hours ago         Up 2 hours                              affectionate_shirley
$ docker ps -a
CONTAINER ID        IMAGE                                     COMMAND                  CREATED             STATUS                     PORTS               NAMES
228b2e12fee0        aimldl/darknet:gpu_cudnn_opencv_version   "bash"                   2 hours ago         Up 2 hours                                     affectionate_shirley
1e6bdeec1030        baseimage-darknet:ver0.2          "bash"  5 days ago          Exited (255) 2 hours ago                       vibrant_bartik
b865d9c1f5da        baseimage-darknet:ver0.2          "bash"  5 days ago          Exited (255) 2 hours ago                       quirky_engelbart
f508e9cee903        baseimage-darknet                 "bash"  5 days ago          Exited (255) 2 hours ago                       vibrant_jang
644157d4bceb        3d0a19184aa9                              "/bin/sh -c 'apt-get…"   5 days ago          Exited (100) 5 days ago                        interesting_bose
3fdee107ae16        5b12024f8062                      "bash"  5 days ago          Exited (127) 5 days ago                        mystifying_chandrasekhar
d65596fe9a45        b6ed5359269b                      "bash"  5 days ago          Exited (1) 5 days ago                          pensive_knuth
e65d06c0f9ff        5b12024f8062                      "bash"  5 days ago          Exited (1) 5 days ago                          practical_swartz
f406a53f9197        cuda_with_x11                     "bash"  5 days ago          Exited (127) 5 days ago                        adoring_faraday
303fba46b646        cuda_with_x11                     "bash"  5 days ago          Exited (1) 5 days ago                          wonderful_mahavira
3d504ede6430        cuda_with_x11                     "bash"  5 days ago          Exited (0) 5 days ago                          boring_shirley
64994096281a        cuda_with_x11                     "bash"  5 days ago          Exited (0) 5 days ago                          exciting_haslett
dfd4f2088c7c        cuda_with_x11                     "bash"  5 days ago          Exited (0) 5 days ago                          beautiful_solomon
49fc725be2b7        cuda_with_x11                     "bash"  5 days ago          Exited (1) 5 days ago                          crazy_euler
7e90cc45d542        cuda_with_x11                     "bash"  5 days ago          Exited (1) 5 days ago                          youthful_feistel
6ed110cd2fea        cuda_with_x11                     "bash"  5 days ago          Exited (0) 5 days ago                          goofy_bartik
134efd710933        67532306e1b6                      "bash"                   2 weeks ago         Exited (127) 2 weeks ago                       silly_kapitsa
$ docker rm 134efd710933
134efd710933
$ docker rmi 67532306e1b6
  ...
Deleted: sha256:1a0d5607d55f3a0907aedc2b312bbceda647f1ad89d2cc14b4eb9fba0d5071c6
$ docker images
REPOSITORY            TAG                          IMAGE ID            CREATED             SIZE
aimldl/darknet        gpu_cudnn_opencv_version     4b159247967d        3 hours ago         6.51GB
baseimage-darknet     ver0.4                       3a48bd8567fd        5 days ago          8.36GB
baseimage-darknet     ver0.3                       9ed3aa90a41c        5 days ago          10.2GB
baseimage-darknet     ver0.2                       40b7c6a87c86        5 days ago          8.36GB
baseimage-darknet     latest                       3d0a19184aa9        5 days ago          7.27GB
cuda_with_x11         latest                       e51cb8db05ff        5 days ago          4.93GB
cuda                  ver0.1                       13907d3dcb52        5 days ago          4.77GB
nvidia/cuda           11.2.0-devel-ubuntu18.04     0b7ce4b2aaa4        11 days ago         4.22GB
nvcr.io/nvidia/cuda   11.2.0-runtime-ubuntu18.04   5b3bfc967c6d        4 weeks ago         2.01GB
$ 
```

