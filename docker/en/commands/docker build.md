* Draft: 2020-05-29 (Fri)
# Docker build
`Docker build` builds a Docker image from a `Dockerfile`. The usage is:
```bash
docker build [OPTIONS] PATH | URL | -
```
For details, refer to [docker build](https://docs.docker.com/engine/reference/commandline/build/).
## The basic command
Make sure a `Dockerfile` is in the current directory and run:
```bash
$ docker build .
# or
$ docker build - < Dockerfile
```
## If the file name is long,
### Use the -f option to specify the file name
```bash
$ docker build -f /path/to/a/Dockerfile .
```
For example,
```bash
$ docker build -f Dockerfile-kubeflow_h20_openm_python3 .
```
### Change the file name and run `docker build .`
For example,
```bash
$ mv Dockerfile-kubeflow_h20_openm_python3 Dockerfile
$ docker build .
```
### Use the `export` command to save the Docker file name into a variable
```bash
$ export DOCKERFILE=Dockerfile-kubeflow_h20_openm_python3
$ docker build - < $DOCKERFILE
```

## If the tag or image name is long,
Use the `export` command to save the image name in a variable
For example,
```bash
$ export IMAGE_NAME=aimldl/baseimage-kubeflow-h203.30.0.3_openml0.10.2_python3_ubuntu18.04
$ docker build -t $IMAGE_NAME .
```
Instead of 
```bash
$ docker build -t aimldl/baseimage-kubeflow-h203.30.0.3_openml0.10.2_python3_ubuntu18.04 .
```
Alternatively, you may run `docker build -t $IMAGE_NAME - < Dockerfile`.

## If both the Dockerfile name and tag are long,
applying the above options makes a set of readable commands. Instead of a line of command,
```bash
$ docker build -t aimldl/baseimage-kubeflow-h203.30.0.3_openml0.10.2_python3_ubuntu18.04 - < Dockerfile-kubeflow_h20_openm_python3
```
The readability of the following lines are better than the above one.
```bash
$ mv Dockerfile-kubeflow_h20_openm_python3 Dockerfile
$ export IMAGE_NAME=aimldl/baseimage-kubeflow-h203.30.0.3_openml0.10.2_python3_ubuntu18.04
$ docker build -t $IMAGE_NAME .
```
or
```bash
$ export DOCKERFILE=Dockerfile-kubeflow_h20_openm_python3
$ export IMAGE_NAME=aimldl/baseimage-kubeflow-h203.30.0.3_openml0.10.2_python3_ubuntu18.04
$ docker build -t $IMAGE_NAME - < $DOCKERFILE
```
