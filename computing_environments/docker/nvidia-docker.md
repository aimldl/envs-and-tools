

* [NVIDIA / nvidia-docker > Usage](https://github.com/NVIDIA/nvidia-docker/wiki/Usage)
* [nvidia-container-runtime](https://github.com/NVIDIA/nvidia-container-runtime)
* [Upgrading to the NVIDIA Container Runtime for Docker](https://docs.nvidia.com/dgx/nvidia-container-runtime-upgrade/index.html)

### About the NVIDIA Container Runtime for Docker
The NVIDIA Container Runtime for Docker is an improved mechanism for allowing the Docker Engine to support NVIDIA GPUs used by GPU-accelerated containers. This new runtime replaces the Docker Engine Utility for NVIDIA GPUs.

The Docker Engine Utility for NVIDIA GPUs is implemented with the installation of the nvidia-docker package. To upgrade your DGX system environment to use the NVIDIA Container Runtime for Docker, you must install the nvidia-docker2 package.

```bash
$ sudo apt install nvidia-docker2
```
For details, refer to [Upgrading to the NVIDIA Container Runtime for Docker](https://docs.nvidia.com/dgx/nvidia-container-runtime-upgrade/index.html).

### Using the NVIDIA Container Runtime for Docker
Run GPU-accelerated containers in one of the following ways:
1. Use docker run and specify runtime=nvidia.
```bash
$ docker run --runtime=nvidia ...
```
2. Use nvidia-docker run.
```bash
$ nvidia-docker run ...
```

### To check if nvidia-docker is installed.
```bash
$ docker run --runtime=nvidia --rm nvidia/cuda nvidia-smi
```
For details, refer to [TensorFlow > Install > Docker](https://www.tensorflow.org/install/docker)

### Clean up (--rm)
TODO: Summarize
> By default a container’s file system persists even after the container exits. This makes debugging a lot easier (since you can inspect the final state) and you retain all your data by default. But if you are running short-term foreground processes, these container file systems can really pile up. If instead you’d like Docker to automatically clean up the container and remove the file system when the container exits, you can add the --rm flag:

> --rm=false: Automatically remove the container when it exits
Note: When you set the --rm flag, Docker also removes the anonymous volumes associated with the container when the container is removed. This is similar to running docker rm -v my-container. Only volumes that are specified without a name are removed. For example, with docker run --rm -v /foo -v awesome:/bar busybox top, the volume for /foo will be removed, but the volume for /bar will not. Volumes inherited via --volumes-from will be removed with the same logic -- if the original volume was specified with a name it will not be removed.

For details, refer to [Docker docs > Docker run reference](https://docs.docker.com/engine/reference/run/#clean-up---rm)

### NVIDIA runtime
nvidia-docker registers a new container runtime to the Docker daemon.
You must select the nvidia runtime when using docker run:
```bash
docker run --runtime=nvidia --rm nvidia/cuda nvidia-smi
```

GPU isolation
Set the environment variable NVIDIA_VISIBLE_DEVICES in the container:

docker run --runtime=nvidia -e NVIDIA_VISIBLE_DEVICES=0 --rm nvidia/cuda nvidia-smi

NVIDIA_VISIBLE_DEVICES
This variable controls which GPUs will be made accessible inside the container.

Possible values
0,1,2, GPU-fef8089b …: a comma-separated list of GPU UUID(s) or index(es).
all: all GPUs will be accessible, this is the default value in our container images.
none: no GPU will be accessible, but driver capabilities will be enabled.
void or empty or unset: nvidia-container-runtime will have the same behavior as runc.


Non-CUDA image
Setting NVIDIA_VISIBLE_DEVICES will enable GPU support for any container image:

docker run --runtime=nvidia -e NVIDIA_VISIBLE_DEVICES=all --rm debian:stretch nvidia-smi
Dockerfiles
If the environment variables are set inside the Dockerfile, you don't need to set them on the docker run command-line.

For instance, if you are creating your own custom CUDA container, you should use the following:

ENV NVIDIA_VISIBLE_DEVICES all
ENV NVIDIA_DRIVER_CAPABILITIES compute,utility
These environment variables are already set in our official images pushed to Docker Hub.

For a Dockerfile using the NVIDIA Video Codec SDK, you should use:

ENV NVIDIA_VISIBLE_DEVICES all
ENV NVIDIA_DRIVER_CAPABILITIES compute,video,utility

##### Further Reading
* [Enabling GPUs in the Container Runtime Ecosystem](https://devblogs.nvidia.com/gpu-containers-runtime/)
*
