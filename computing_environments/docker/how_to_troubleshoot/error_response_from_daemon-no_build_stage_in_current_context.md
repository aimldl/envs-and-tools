* Draft: 2020-05-28 (Thu)
# Error response from daemon: No build stage in current context
## Problem
```bash
$ docker build -t aimldl/baseimage-kubeflow-h203.30.0.3_openml0.10.2_python3_ubuntu18.04 - < Dockerfile
Sending build context to Docker daemon  8.192kB
Error response from daemon: No build stage in current context
$

## Hint
* Google search: "Error response from daemon: No build stage in current context"
* [Error response from daemon: No build stage in current context](https://stackoverflow.com/questions/50452860/error-response-from-daemon-no-build-stage-in-current-context)
  * An excerpt
> Does your dockerfile have a: FROM repo/image
> As the first line? I got this error when I forgot to specify the docker image that I was building from.

## Solution
Fix the old code
```dockerfile
ARG BASE_CONTAINER="python:3"
MAINTAINER "Tae-Hyung T. Kim, Ph.D."
```
by adding `FROM ...`
```dockerfile
ARG BASE_CONTAINER="python:3"
FROM $BASE_CONTAINER
MAINTAINER "Tae-Hyung T. Kim, Ph.D."
```
