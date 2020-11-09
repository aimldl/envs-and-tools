* Draft: 2020-06-09 (Tue)
# Update the Existing Packages in a Docker Container
## Purpose
Given an existing Docker container, update the packages:
* Ubuntu Linux
* Anaconda
* Python's PIP

***Before:*** `Welcome to ubuntu18.04, conda 4.8.2, Python 3.7.6`

***After:*** `Welcome to ubuntu18.04, conda 4.8.3, Python 3.7.6`
## Run a base image 
```bash
$ docker run -it aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4 bash
2020-06-09 (Tue) 06:16 (23th week)
Welcome to ubuntu18.04, conda 4.8.2, Python 3.7.6
(base) user@0ea970718c74:~$
```
## Update and upgrade Ubuntu Linux
```bash
$ sudo apt update
$ sudo apt upgrade
```
## Update Anaconda
```bash
$ conda update --all
```
## Update Python's PIP
```bash
$ pip install -U pip
```
## Check the welcome message
Include the following lines in `.bashrc`
```bash
linux_distribution=$(. /etc/os-release;echo $ID$VERSION_ID)
python_version=`python --version`
anaconda_version=`conda -V`
echo "Welcome to $linux_distribution, $anaconda_version, $python_version"  # ubuntu18.04
```
and sourcing `.bashrc` runs the above commands resulting in:
```bash
$ source .bashrc
2020-06-09 (Tue) 06:25 (23th week)
Welcome to ubuntu18.04, conda 4.8.3, Python 3.7.6
$
```
## Commit the container as a news base image
Exit the container by hitting `Ctrl+p+q`.

```bash
$ docker ps
CONTAINER ID  IMAGE                                                   COMMAND  ...  NAMES
0ea970718c74  aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4  "bash"   ...  cool_visvesvaraya
$
```
Commit the container ID to a new name. Note `conda_4.8.2` has been changed to `conda_4.8.3`.
```bash
$ docker commit 0ea970718c74 aimldl/baseimage_python3.7.6_conda_4.8.3_ubuntu18.04
sha256:73792201feb73e41326ce4497a9a41d44e0558ca8b930eeb725a0c603f739712
$
```
Verify the created image, log into Docker Hub, 
```bash
$ docker images
REPOSITORY                                                                            TAG                 IMAGE ID            CREATED             SIZE
aimldl/baseimage_python3.7.6_conda_4.8.3_ubuntu18.04                                  latest              73792201feb7        9 seconds ago       6.16GB
$ docker login
$ docker push aimldl/baseimage_python3.7.6_conda_4.8.3_ubuntu18.04

$
```
