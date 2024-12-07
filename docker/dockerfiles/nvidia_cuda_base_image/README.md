* Draft: 2021-01-28 (Thu)

# NVIDIA CUDA Base Image

## 개요



## NVIDIA CUDA Base Image 소개

[Nvidia CUDA Base Image 2](https://ngc.nvidia.com/catalog/containers/nvidia:cuda)

> You can follow instructions from [here 4](https://github.com/dusty-nv/jetson-containers) to analyze the Dockerfiles so you can build one from scratch and how to download the necessary drivers.
>
> If you use any of the above Base Images, then CUDA will be pre-installed, type `RUN pip3 install opencv-python` (use pip for python2). The documentation for opencv-python is [here](https://pypi.org/project/opencv-python/). If opencv itself does not need GPU support, then that should suffice, else refer to [opencv-python docs 1](https://github.com/skvark/opencv-python#documentation-for-opencv-python) for more info.

[NVIDIA NGC > CATALOG > CUDA](https://ngc.nvidia.com/catalog/containers/nvidia:cuda)

> **Overview of Images**
>
> Three flavors of images are provided:
>
> - `base`: Includes the CUDA runtime (cudart)
> - `runtime`: Builds on the `base` and includes the [CUDA math libraries](https://developer.nvidia.com/gpu-accelerated-libraries), and [NCCL](https://developer.nvidia.com/nccl). A `runtime` image that also includes [cuDNN](https://developer.nvidia.com/cudnn) is available.
> - `devel`: Builds on the `runtime` and includes headers, development tools for building CUDA images. These images are particularly useful for multi-stage builds.
>
> The Dockerfiles for the images are open-source and licensed under 3-clause BSD. For more information see the Supported Tags section below.
>
> **LATEST CUDA 11.2.0**
>
> Ubuntu 20.04
>
> - [`11.2.0-base`, `11.2.0-base-ubuntu20.04` (*11.2.0/ubuntu20.04-x86_64/base/Dockerfile*)](https://gitlab.com/nvidia/container-images/cuda/blob/master/dist/11.2.0/ubuntu20.04-x86_64/base/Dockerfile)
> - [`11.2.0-runtime`, `11.2.0-runtime-ubuntu20.04` (*11.2.0/ubuntu20.04-x86_64/runtime/Dockerfile*)](https://gitlab.com/nvidia/container-images/cuda/blob/master/dist/11.2.0/ubuntu20.04-x86_64/runtime/Dockerfile)
> - [`11.2.0-devel`, `11.2.0-devel-ubuntu20.04` (*11.2.0/ubuntu20.04-x86_64/devel/Dockerfile*)](https://gitlab.com/nvidia/container-images/cuda/blob/master/dist/11.2.0/ubuntu20.04-x86_64/devel/Dockerfile)
>
> Ubuntu 18.04
>
> - [`11.2.0-base-ubuntu18.04` (*11.2.0/ubuntu18.04-x86_64/base/Dockerfile*)](https://gitlab.com/nvidia/container-images/cuda/blob/master/dist/11.2.0/ubuntu18.04-x86_64/base/Dockerfile)
> - [`11.2.0-runtime-ubuntu18.04` (*11.2.0/ubuntu18.04-x86_64/runtime/Dockerfile*)](https://gitlab.com/nvidia/container-images/cuda/blob/master/dist/11.2.0/ubuntu18.04-x86_64/runtime/Dockerfile)
> - [`11.2.0-devel-ubuntu18.04` (*11.2.0/ubuntu18.04-x86_64/devel/Dockerfile*)](https://gitlab.com/nvidia/container-images/cuda/blob/master/dist/11.2.0/ubuntu18.04-x86_64/devel/Dockerfile)
>
> UBI 8
>
> - [`11.2.0-base-ubi8` (*11.2.0/ubuntu18.04-x86_64/base/Dockerfile*)](https://gitlab.com/nvidia/container-images/cuda/blob/master/dist/11.2.0/ubi8-x86_64/base/Dockerfile)
> - [`11.2.0-runtime-ubi8` (*11.2.0/ubuntu18.04-x86_64/runtime/Dockerfile*)](https://gitlab.com/nvidia/container-images/cuda/blob/master/dist/11.2.0/ubi8-x86_64/runtime/Dockerfile)
> - [`11.2.0-devel-ubi8` (*11.2.0/ubuntu18.04-x86_64/devel/Dockerfile*)](https://gitlab.com/nvidia/container-images/cuda/blob/master/dist/11.2.0/ubi8-x86_64/devel/Dockerfile)
>
> UBI 7
>
> - [`11.2.0-base-ubi7` (*11.2.0/ubuntu18.04-x86_64/base/Dockerfile*)](https://gitlab.com/nvidia/container-images/cuda/blob/master/dist/11.2.0/ubi7-x86_64/base/Dockerfile)
> - [`11.2.0-runtime-ubi7` (*11.2.0/ubuntu18.04-x86_64/runtime/Dockerfile*)](https://gitlab.com/nvidia/container-images/cuda/blob/master/dist/11.2.0/ubi7-x86_64/runtime/Dockerfile)
> - [`11.2.0-devel-ubi7` (*11.2.0/ubuntu18.04-x86_64/devel/Dockerfile*)](https://gitlab.com/nvidia/container-images/cuda/blob/master/dist/11.2.0/ubi7-x86_64/devel/Dockerfile)

## NVIDIA CUDA Base Image 생성

우분투 18.04에서 사용할 베이스 이미지를 받아오거나 Dockerfile에서 직접 만드는 방법이 있습니다.

### 1. `docker pull`명령어를 이용한 방법

```dockerfile
$ docker pull nvcr.io/nvidia/cuda:11.2.0-devel-ubuntu18.04
```

### 2. Dockerfile을 이용한 방법

Dockerfile은 [*11.2.0/ubuntu18.04-x86_64/devel/Dockerfile*](https://gitlab.com/nvidia/container-images/cuda/blob/master/dist/11.2.0/ubuntu18.04-x86_64/devel/Dockerfile)를 참고합니다.

```dockerfile
ARG IMAGE_NAME
FROM ${IMAGE_NAME}:11.2.0-runtime-ubuntu18.04

LABEL maintainer "NVIDIA CORPORATION <cudatools@nvidia.com>"

ENV NCCL_VERSION 2.8.3

RUN apt-get update && apt-get install -y --no-install-recommends \
    cuda-cudart-dev-11-2=11.2.72-1 \
    cuda-command-line-tools-11-2=11.2.0-1 \
    cuda-minimal-build-11-2=11.2.0-1 \
    cuda-libraries-dev-11-2=11.2.0-1 \
    cuda-nvml-dev-11-2=11.2.67-1 \
    libnpp-dev-11-2=11.2.1.68-1 \
    libnccl-dev=2.8.3-1+cuda11.2 \
    libcublas-dev-11-2=11.3.1.68-1 \
    libcusparse-11-2=11.3.1.68-1 \
    libcusparse-dev-11-2=11.3.1.68-1 \
    && rm -rf /var/lib/apt/lists/*

# apt from auto upgrading the cublas package. See https://gitlab.com/nvidia/container-images/cuda/-/issues/88
RUN apt-mark hold libcublas-dev-11-2 libnccl-dev
ENV LIBRARY_PATH /usr/local/cuda/lib64/stubs
```

#### Dockerfile의 문제

위의 Dockerfile을 그대로 실행하면 에러 메세지가 발생합니다.

```bash
$ sudo docker build - < Dockerfile
Sending build context to Docker daemon   2.56kB
Step 1/7 : ARG IMAGE_NAME
Step 2/7 : FROM ${IMAGE_NAME}:11.2.0-runtime-ubuntu18.04
invalid reference format
$
```

```dockerfile
ARG IMAGE_NAME
FROM ${IMAGE_NAME}:11.2.0-runtime-ubuntu18.04
```

를 변경하면 실행됩니다.

#### Dockerfile을 수정

에러 수정을 위해 `IMAGE_NAME`을 `nvcr.io/nvidia/cuda`로 변경합니다.

```dockerfile
FROM nvcr.io/nvidia/cuda:11.2.0-runtime-ubuntu18.04
```

#### `docker images`

모든 이미지를 삭제한 상태에서 시작해봅니다.

```bash
$ sudo docker images
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
$
```

#### 수정한 Dockerfile로 이미지를 생성

```bash
$ sudo docker build - < Dockerfile
Sending build context to Docker daemon   2.56kB
Step 1/6 : FROM nvcr.io/nvidia/cuda:11.2.0-runtime-ubuntu18.04
11.2.0-runtime-ubuntu18.04: Pulling from nvidia/cuda
  ...
Step 6/6 : ENV LIBRARY_PATH /usr/local/cuda/lib64/stubs
 ---> Running in 151dd08e2050
Removing intermediate container 151dd08e2050
 ---> 67532306e1b6
Successfully built 67532306e1b6
$
```

#### 이미지 확인

만들었지만 2개의 이미지가 생성되었습니다.

```bash
$ sudo docker images
[sudo] k8smaster의 암호: 
REPOSITORY            TAG                          IMAGE ID            CREATED             SIZE
<none>                <none>                       67532306e1b6        3 minutes ago       4.23GB
nvcr.io/nvidia/cuda   11.2.0-runtime-ubuntu18.04   5b3bfc967c6d        2 weeks ago         2.01GB
$
```

이유는 `nvcr.io/nvidia/cuda:11.2.0-runtime-ubuntu18.04`를 바탕으로 새로운 이미지를 만들기 때문입니다. `sudo docker build - < Dockerfile`명령어를 실행했을 때, `nvcr.io/nvidia/cuda` repository에서 이미지를 pull해서 왔습니다.

```bash
Step 1/6 : FROM nvcr.io/nvidia/cuda:11.2.0-runtime-ubuntu18.04
11.2.0-runtime-ubuntu18.04: Pulling from nvidia/cuda
  ...
```

그러므로 새로 생성된 이미지는 `67532306e1b6`입니다.

#### 컨테이너 동작 확인

이미지에서 컨테이너를 실행해봅니다.

```bash
$ sudo docker run -it 67532306e1b6 bash
root@134efd710933:/#
```



```bash
root@134efd710933:/# ls
bin   dev  home  lib64  mnt  proc  run   srv  tmp  var
boot  etc  lib   media  opt  root  sbin  sys  usr
root@134efd710933:/# nvidia-smi
bash: nvidia-smi: command not found
root@134efd710933:/# exit
exit
$
```

