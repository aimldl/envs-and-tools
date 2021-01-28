  * Rev.3: 2021-01-28 (Thu)
  * Rev.2: 2020-04-27 (Mon)
  * Rev.1: 2018-09-21 (Fri)
  * Draft: 2018-09-10 (Mon)

# Dockerfile: `darknet_base_image`

## Summary

### To build a Docker image, 

Copy the `Dockerfile` (to the current working directory) and run

```bash
$ docker build -t aimldl/darknet_base_image github.com/aimldl/darknet
```

or run

```bash
$ docker build - < Dockerfile
```

## Parent tree

This Dockerfile is based off of the official Python3 image.

* Dockerfile-python3_base_image  https://github.com/aimldl/python3/Dockerfile
* Dockerfile-ubuntu_base_image    https://github.com/aimldl/ubuntu/Dockerfile
* FROM ubuntu:18.04

## Getting Started

### Prerequisites

#### Post-installation steps for Linux

* Follow the steps by https://docs.docker.com/install/linux/linux-postinstall/ and you can run docker without the `sudo` keyword.

* If you don't follow these steps, put the `sudo` keyword for each command started with `docker` in this document. That is,

```bash
$ docker images => $ sudo docker images 
```

### Command to build a Docker image from this Dockerfile.
```bash
$ docker build -t aimldl/darknet_base_image github.com/aimldl/python3
```

### Command to list the Docker images on the local machine after the built.

```bash
$ docker images
REPOSITORY                   TAG                 IMAGE ID            CREATED             SIZE
aimldl/darknet_base_image   latest              c9df18d93ec3        56 seconds ago      512MB
$
```

### Command to run the built Docker image

  Note your log-in ID is `user` and the current working directory is `/home/user`.

```bash
$ docker run -it aimldl/darknet_base_image
user@53e421cf0f92:~$ pwd
/home/user
user@53e421cf0f92:~$ ls
bin  downloads  lib  uploads
user@53e421cf0f92:~$
```

  To exit the current shell, press `Ctrl+P+Q` and you'll be returned to the previous Bash shell.

```bash
$
```

### Command to specify the container name

Use the -t option to tag a name.

```bash
$ docker run -it -t darknet_test aimldl/darknet_base_image
```

The image's name is tagged as darknet_test.

### Command to list the Docker container.
```bash
$ docker ps
CONTAINER ID        IMAGE                        COMMAND                  CREATED             STATUS              PORTS               NAMES
53e421cf0f92        aimldl/darknet_base_image   "/bin/sh -c /bin/bash"   2 minutes ago       Up 2 minutes                            infallible_bell
$
```

  Note the container ID and name are assigned randomly as `53e421cf0f92` and infallible_bell, respectively.

### Log in as the root user

Use the -u option 

```bash
$ docker exec -u root -it [container_id] /bin/bash
$ docker exec -u root -it [container_name] /bin/bash 
```

You may use `-u 0` instead of `-u root` because 0 means the root user.

```bash
$ docker exec -u root -it 53e421cf0f92 /bin/bash
root@53e421cf0f92:~  or
$ docker exec -u root -it infallible_bell /bin/bash
root@53e421cf0f92:~
```

## Options to build this Dockerfile
There are several options to build a base image from this Dockerfile.

* The Internet connection is necessary.

The easiest way is to run: 

#### (1) Build from an URL

Build a Docker image without the repository and tag names (none).

```bash
$ docker build github.com/aimldl/python3
```

```bash
$ docker images
REPOSITORY                   TAG                 IMAGE ID            CREATED             SIZE
<none>                       <none>              9a7c5d774254        44 seconds ago      512MB
$
```

https://github.com/aimldl/python3 is the address of this repository.

Caution: Don't use `https://` in the command or an error will occur.

```bash
$ docker build https://github.com/aimldl/python3
Downloading build context from remote url: https://github.com/aimldl/python3  52.83kB
Sending build context to Docker daemon  54.78kB
Error response from daemon: Dockerfile parse error line 7: unknown instruction: <!DOCTYPE
$
```

#### (2) Build a Docker image and name it as `aimldl/darknet_base_image`

```bash
$ docker build -t aimldl/darknet_base_image github.com/aimldl/python3
$ docker images
REPOSITORY                   TAG                 IMAGE ID            CREATED             SIZE
aimldl/darknet_base_image   latest              fe530e6951ac        44 seconds ago      512MB
$
```

#### (3) Download this Dockerfile and run

```bash
$ docker build .
```

or

```bash
$ docker build - < Dockerfile
```

#### (4) Build by specifying the file name

```bash
$ docker build -f Dockerfile .
```

Use the -t option to tag a name to the built image. For example,
  (1) $ docker build -t aimldl/darknet_base_image github.com/aimldl/python3
  (2) $ docker build -t aimldl/darknet_base_image .
  (3) $ docker build -t aimldl/darknet_base_image - < Dockerfile
  (4) $ docker build -f Dockerfile -t aimldl/darknet_base_image .

## References
* [Nathan Leclaire, 10 Docker Tips and Tricks That Will Make You Sing A Whale Song of Joy](https://nathanleclaire.com/blog/2014/07/12/10-docker-tips-and-tricks-that-will-make-you-sing-a-whale-song-of-joy/), 2014-07-12
* [stackoverflow, How to use sudo inside a docker container?](https://stackoverflow.com/questions/25845538/how-to-use-sudo-inside-a-docker-container) 2018-04-07

## Appendix

Ubuntu Packages for Python3 
  python3, python3-pip, python3-dev
Python Packages

  * Fundamental Packages
    IPython
    IPython or Interactive Python is a command shell for interactive computing.
    It's originally developed for Python, but supports multiple programming languages now.
    https://ipython.org/
      Jupyter Notebook
    Project Jupyter is a nonprofit organization created to "develop open-source software, 
    open-standards, and services for interactive computing across dozens of programming languages.
    https://en.wikipedia.org/wiki/Project_Jupyter
    The Jupyter Notebook is an open-source web application by Project Jupyter that one can create and
    share documents that contain live code, equations, visualizations and narrative text.
    http://jupyter.org/
  * Numerial and Scientific Packages
    NumPy
    is the fundamental package for scientific computing with Python, which supports:
      a powerful N-dimensional array object,
      sophisticated (broadcasting) functions,
      tools for integrating C/C++ and Fortran code, and
      useful linear algebra, Fourier transform, and random number capabilities.
    http://www.numpy.org/ 
      SciPy library
    is a fundamental library for scientific computing.
    https://www.scipy.org/

  Matplotlib 
    is a Python 2D plotting library which produces publication quality figures 
    in a variety of hardcopy formats and interactive environments across platforms. 
    https://matplotlib.org/
  Sympy
    is a Python library for symbolic mathematics. 
    https://www.sympy.org
  Pandas
    provides high-performance, easy-to-use data structures and data analysis tools for Python.
    Pandas is an open source, BSD-licensed library.
    https://pandas.pydata.org/
  Scikit-learn
    is a machine learning library for Python designed to interoperate with NumPy, SciPy, and matplotlib.
    It features various machine learning algorithms for classification, regression and clustering including:
    support vector machines, random forests, gradient boosting, k-means and DBSCAN.
    http://scikit-learn.org/stable/

  * Supplementary Packages
    h5py
    The h5py package is a Pythonic interface to the HDF5 binary data format.
    It lets you store huge amounts of numerical data, and easily manipulate that data from NumPy.
    For example, you can slice into multi-terabyte datasets stored on disk, as if they were real NumPy arrays.
    Thousands of datasets can be stored in a single file, categorized and tagged however you want.
    https://www.h5py.org/
      Pillow
    is the Python Imaging Library. 
    https://pillow.readthedocs.io/en/5.2.x/
      PyDotPlus
    is an improved version of the old pydot project that provides a Python Interface to Graphviz’s Dot language.
    https://pydotplus.readthedocs.io/
      seaboarn
    is a statistical data visualization library based on matplotlib.
    https://seaborn.pydata.org/
      PyYAML
    is a full-featured YAML framework for Python.
    https://pyyaml.org/
    Python Packages Under Consideration
      mkl-service libpython m2w64-toolchain
      dill, six, toolz, scs, multiprocess, fastcache, ecos, cvxcanon, cvxopt, cvxpy
    $ pip install dill-0.2.7.1-py2.py3-none-any.whl six-1.11.0-py2.py3-none-any.whl toolz-0.8.2-py2.py3-none-any.whl scs-1.2.7-cp35-cp35m-win_amd64.whl multiprocess-0.70.5-cp35-cp35m-win_amd64.whl fastcache-1.0.2-cp35-cp35m-win_amd64.whl ecos-2.0.4-cp35-cp35m-win_amd64.whl CVXcanon-0.1.1-cp35-cp35m-win_amd64.whl cvxopt-1.1.9-cp35-cp35m-win_amd64.whl cvxpy-0.4.11-py3-none-any.whl