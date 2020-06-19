* Rev.2: 2020-05-29 (Fri)
* Rev.1: 2020-04-27 (Mon)
* Draft: 2020-03-11 (Wed)
# Dockerfiles
## Filename Convention: `Dockerfile-<purpose>`
The file names of the multiple Dockerfiles are changed `Dockerfile-<purpose>`.

## Building a Docker image from a Dockerfile
### Option 1: Use the `-f` option 
Specify the `path to a Dockerfile` and build a Docker image from it.
```bash
$ docker build -f /path/to/a/Dockerfile .
```
### Option 2: Use the default file name of `Dockerfile`
You may change the lengthy file name to `Dockerfile` and then build it. For example,
```bash
$ mv Dockerfile-ubuntu_base_image Dockerfile
$ docker build .
```
For details, refer to [docker build](https://docs.docker.com/engine/reference/commandline/build/).

## Summary
| File Name                     | Purpose                             | Description                      |
|-------------------------------|-------------------------------------|----------------------------------|
| Dockerfile-ubuntu_base_image  | Ubuntu 18.04 base image             | Ubuntu18.04                      |
| Dockerfile-python3_base_image | Python3 base image (on Ubuntu18.04) | Python3,Ubuntu18.04              |
|                               |                                     |                                  |
