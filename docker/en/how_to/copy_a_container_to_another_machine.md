* Draft: 2021-02-09 (Tue)





Google search: docker 이미지 usb로 옮기기

[docker image를 tar 파일로 저장 (export / import / save / load)](https://www.leafcats.com/240)



```bash
$ docker ps
CONTAINER ID        IMAGE                                            COMMAND                              NAMES
0f849469a8df        nvcr.io/nvidia/cuda:11.2.0-runtime-ubuntu18.04   "bash"              ...              brave_grothendieck
$ docker commit 0f849469a8df cuda:ver0.1
sha256:13907d3dcb529bc05a259112e6523304b3eb63bdafa1421e88124b7de15d8855
$ docker images
REPOSITORY                            TAG                          IMAGE ID            CREATED             SIZE
cuda                                  ver0.1                       13907d3dcb52        8 seconds ago       4.77GB
  ...
$ docker save -o cuda_darknet.tar cuda:ver0.1
$ ls
cuda_darknet.tar  ...
$ 
```

