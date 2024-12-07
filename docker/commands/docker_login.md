* Rev.1: 2020-0324 (Tue)
* Draft: 2020-0317 (Tue)

# docker login

## When no credential exists.
```bash
$ docker login
Login with your Docker ID to push and pull images from Docker Hub.
If you don't have a Docker ID, head over to https://hub.docker.com to create one.
Username: aimldl
Password: 
WARNING! Your password will be stored unencrypted in /home/aimldl/.docker/config.json.
Configure a credential helper to remove this warning. See
https://docs.docker.com/engine/reference/commandline/login/#credentials-store

Login Succeeded
$
```

## When credentials exists,
```bash
$ docker login
Authenticating with existing credentials...
WARNING! Your password will be stored unencrypted in /home/aimldl/.docker/config.json.
Configure a credential helper to remove this warning. See
https://docs.docker.com/engine/reference/commandline/login/#credentials-store

Login Succeeded
$
```

## Caution: docker daemon must be running.
For Windows, the Docker Desk or docker daemon must be running to log into Docker Hub. Otherwise, the following error may occur.

```powershell
This error may also indicate that the docker daemon is not running.
```
In the following example, the first login attemp fails because Docker Desk has not been launched yet. The second login attemp suceeds because I've waited until Docker Desk launches.

```powershell
PS C:\Users\aimldl> docker login
Authenticating with existing credentials...
Login did not succeed, error: error during connect: Post http://%2F%2F.%2Fpipe%2Fdocker_engine/v1.40/auth: open //./pipe/docker_engine: The system cannot find the file specified. In the default daemon configuration on Windows, the docker client must be run elevated to connect. This error may also indicate that the docker daemon is not running.
Login with your Docker ID to push and pull images from Docker Hub. If you don't have a Docker ID, head over to https://hub.docker.com to create one.
Username (aimldl): aimldl
Password:
error during connect: Post http://%2F%2F.%2Fpipe%2Fdocker_engine/v1.40/auth: open //./pipe/docker_engine: The system cannot find the file specified. In the default daemon configuration on Windows, the docker client must be run elevated to connect. This error may also indicate that the docker daemon is not running.
PS C:\Users\aimldl> docker login
Authenticating with existing credentials...
Login Succeeded
PS C:\Users\aimldl>
```

## Example: login, search, and pull an image from Docker Hub
Assume there is only one existing image "hello-world". After pulling an image "aimldl/kaggle_telco_customer_churn", two images reside in the local computer.
```bash
$ docker images
$ docker login
$ docker search aimldl
$ docker pull aimldl/kaggle_telco_customer_churn
$ docker images
$
```
The full message is below. 
```bash
$ docker images
REPOSITORY                                               TAG     ...
hello-world                                              latest  ...
$ docker login
Login with your Docker ID to push and pull images from Docker Hub. If you don't have a Docker ID, head over to https://hub.docker.com to create one.
Username: aimldl
Password: 
WARNING! Your password will be stored unencrypted in /home/aimldl/.docker/config.json.
Configure a credential helper to remove this warning. See
https://docs.docker.com/engine/reference/commandline/login/#credentials-store

Login Succeeded
$ docker search aimldl
NAME                                                        ...  STARS  OFFICIAL  AUTOMATED
  ...
aimldl/kaggle_telco_customer_churn                               0
aimldl/flask_hello_world                                         0
aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4           0
aimldl/baseimage_python3.6.9_ubuntu18.04.4                       0
aimldl/baseimage_surprise_python3.7.6_conda_4.8.2_ubuntu18.04.4  0
aimldl/snapshot_surprise_python3.7.6_conda_4.8.2_ubuntu18.04.4   0
$ docker pull aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4
Using default tag: latest
  ...
Status: Downloaded newer image for aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4:latest
docker.io/aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4:latest
$ docker pull aimldl/kaggle_telco_customer_churn
latest: Pulling from aimldl/kaggle_telco_customer_churn
124c757242f8: Pull complete 
9d866f8bde2a: Pull complete 
  ...
Digest: sha256: ...
Status: Downloaded newer image for aimldl/kaggle_telco_customer_churn:latest
docker.io/aimldl/kaggle_telco_customer_churn:latest
$ docker images
REPOSITORY                                               TAG     ...
hello-world                                              latest  ...
aimldl/kaggle_telco_customer_churn                       latest  ...
$
```
## Example: login and push an image to Docker Hub
```bash
$ docker images
$ docker push aimldl/kaggle_telco_customer_churn
$
```
The full message is below.
```bash
(base) aimldl@GPU-Desktop:~$ docker images
REPOSITORY                                               TAG                 IMAGE ID            CREATED             SIZE
aimldl/kaggle_telco_customer_churn                       ver0.1              dd174d2687a5        3 minutes ago       5.44GB
aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4   ver0.2              08a29d5e5540        4 hours ago         5.44GB
aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4   latest              562fb67f8f2d        25 hours ago        5.44GB
ubuntu                                                   latest              72300a873c2c        3 weeks ago         64.2MB
ratsgo/embedding-gpu                                     latest              300ccaa009a2        6 months ago        6.84GB
aimldl/r_interface2tensorflow_base_image                 ver0_2              489cdc2965b0        11 months ago       6.88GB
aimldl/r_interface2tensorflow_base_image                 ver0_1              819bc08cff85        11 months ago       6.88GB
nvidia/cuda                                              latest              d9a8427c8dd9        13 months ago       2.35GB
hello-world                                              latest              fce289e99eb9        14 months ago       1.84kB
aimldl/keras_base_image                                  latest              3b9219a43e4d        18 months ago       1.56GB
keras_base_image                                         latest              3b9219a43e4d        18 months ago       1.56GB
aimldl/tensorflow_base_image                             latest              255f88e7c71f        18 months ago       1.55GB
aimldl/python3_base_image                                latest              588f6d18f46e        18 months ago       1.09GB
(base) aimldl@GPU-Desktop:~$ docker push aimldl/kaggle_telco_customer_churn
The push refers to repository [docker.io/aimldl/kaggle_telco_customer_churn]
  ...
a30b835850bf: Mounted from aimldl/r_interface2tensorflow_base_image 
ver0.1: digest: sha256: ... size: 9344
$ 
```

