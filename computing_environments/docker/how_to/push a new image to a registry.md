##### aimldl/computing_environments/docker/how_to/push a new image to a registry.md
* Rev.1: 2020-04-27 (Mon)
* Draft: 2020-03-12 (Thu)
# How to Push a New Image to a Registry
The example in [docker push](https://docs.docker.com/engine/reference/commandline/push/) is straightforward.
```bash
$ docker commit c16378f943fe rhel-httpd
$ docker tag rhel-httpd registry-host:5000/myadmin/rhel-httpd
$ docker login
$ docker push registry-host:5000/myadmin/rhel-httpd
```
For detaills, refer to [docker push](https://docs.docker.com/engine/reference/commandline/push/).

## [docker push](https://docs.docker.com/engine/reference/commandline/push/)
### Usage
```bash
docker push [OPTIONS] NAME[:TAG]
```
### Help
```bash
docker push --help
```
### Example
Push an image named "aimldl/baseimage_python3.6.9_ubuntu18.04.4" to Docker Hub.
```bash
$ docker push aimldl/baseimage_python3.6.9_ubuntu18.04.4
The push refers to repository [docker.io/aimldl/baseimage_python3.6.9_ubuntu18.04.4]
53f0bdfe8a57: Pushed                                                  
  ...
a30b835850bf: Mounted from aimldl/python3_base_image
latest: digest: sha256:... size: 8712
$
```

A sequence of commands to commit an image and push it to Docker Hub is represented below.
```bash
$ docker images
REPOSITORY                                  TAG     IMAGE ID      CREATED         SIZE
hello-world                                 latest  fce289e99eb9  14 months ago   1.84kB
aimldl/python3_base_image                   latest  588f6d18f46e  18 months ago   1.09GB
$ docker ps
CONTAINER ID  IMAGE                       ... NAMES
0ea530773393  aimldl/python3_base_image   ... flamboyant_bhabha
$ docker commit -a "T.Kim" flamboyant_bhabha aimldl/baseimage_python3.6.9_ubuntu18.04.4
sha256:b237e70d403e009480dcc768f2112103331a011c2c54cf8b5354c5e096112c68
$ docker images
REPOSITORY                                  TAG     IMAGE ID      CREATED         SIZE
aimldl/baseimage_python3.6.9_ubuntu18.04.4  latest  773d27d8765e  52 minutes ago  1.57GB
hello-world                                 latest  fce289e99eb9  14 months ago   1.84kB
aimldl/python3_base_image                   latest  588f6d18f46e  18 months ago   1.09GB
$ docker login
Authenticating with existing credentials...
Login Succeeded
$ docker push aimldl/baseimage_python3.6.9_ubuntu18.04.4
The push refers to repository [docker.io/aimldl/baseimage_python3.6.9_ubuntu18.04.4]
53f0bdfe8a57: Pushed                                                  
  ...
a30b835850bf: Mounted from aimldl/python3_base_image
latest: digest: sha256:... size: 8712
$
```

## Caution
Check the upload with the web browser, not on the Docker CLI.
```bash
$ docker search aimldl
NAME                       DESCRIPTION  STARS  OFFICIAL  AUTOMATED
aimldl/python3_base_image  0
  ...
$  docker logout
Removing login credentials for https://index.docker.io/v1/
$
```
To verify if the upload went well, I've searched Docker Hub, but couldn't find the image. However I was able to find it after logging into the website with a web browser.
<img src="images/dockerhub-homepage-aimldl-baseimage_python3.6.9_ubuntu18.04.4.png">

It's not the first time the Docker CLI doesn't show the uploaded image immediately.
In that case, you may use a web browser to verify the upload.
