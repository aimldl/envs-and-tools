* Draft: 2021-02-15 (Mon)

# [docker load](https://docs.docker.com/engine/reference/commandline/load/)



## Examples

```bash
$ docker image ls
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
$ docker load < busybox.tar.gz
Loaded image: busybox:latest
$ docker images
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
busybox             latest              769b9341d937        7 weeks ago         2.489 MB

$ docker load --input fedora.tar
Loaded image: fedora:rawhide
Loaded image: fedora:20
$ docker images
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
busybox             latest              769b9341d937        7 weeks ago         2.489 MB
fedora              rawhide             0d20aec6529d        7 weeks ago         387 MB
fedora              20                  58394af37342        7 weeks ago         385.5 MB
fedora              heisenbug           58394af37342        7 weeks ago         385.5 MB
fedora              latest              58394af37342        7 weeks ago         385.5 MB
$
```



## My examples



```bash
$ docker load < darknet_gpu_cudnn_opencv_version.tar
Error processing tar file(exit status 1): archive/tar: invalid tar header
$
```

