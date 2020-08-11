* Draft: 2020-08-11 (Tue)

# How to Install H2O on Docker
* The official installation guide does not cover this topic.
* A trick is to install H2O on an Anaconda virtual environment because the official guide covers it.
* [Downloading & Installing H2O](http://docs.h2o.ai/h2o/latest-stable/h2o-docs/downloading.html) > [Install on Anaconda Cloud](http://docs.h2o.ai/h2o/latest-stable/h2o-docs/downloading.html#install-on-anaconda-cloud)

To install the latest H2O version, run:
```bash
$ conda install -c h2oai h2o
```

To install a specific version of H2O, run:
```bash
$ conda install -c h2oai h2o=3.30.0.6
```

## Create a Docker image with H2O
## Prerequisite
* Docker is prepared.

## Step 1. Prepare a Docker image with Anaconda virtual environment. 
The Docker image is available at `aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4`.

```bash
$ sudo docker login
$ sudo docker pull aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4
```

## Step 2. Run the Docker image to enter the container environment with Conda. 
```bash
$ sudo docker run -it aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4 bash
2020-08-11 (Tue) 08:04 (32th week)
Welcome to ubuntu18.04, conda 4.8.2, Python 3.7.6
(base) user@fe51f813476b:~$
```

## Step 3. Install H2O with the `conda install` command.
```bash
(base) user@fe51f813476b:~$ conda install -c h2oai h2o
```

For details, refer to the official installation guide.
* [Downloading & Installing H2O](http://docs.h2o.ai/h2o/latest-stable/h2o-docs/downloading.html) > [Install on Anaconda Cloud](http://docs.h2o.ai/h2o/latest-stable/h2o-docs/downloading.html#install-on-anaconda-cloud)

The full message is below.
```bash
(base) user@fe51f813476b:~$ conda install -c h2oai h2o
Collecting package metadata (current_repodata.json): done
Solving environment: done

## Package Plan ##

  environment location: /home/user/anaconda3

  added / updated specs:
    - h2o


The following packages will be downloaded:

    package                    |            build
    ---------------------------|-----------------
    conda-4.8.3                |           py37_0         2.8 MB
    h2o-3.18.0.2               |                0       118.2 MB
    openjdk-8.0.152            |       h7b6447c_3        57.4 MB
    ------------------------------------------------------------
                                           Total:       178.4 MB

The following NEW packages will be INSTALLED:

  h2o                pkgs/main/linux-64::h2o-3.18.0.2-0
  openjdk            pkgs/main/linux-64::openjdk-8.0.152-h7b6447c_3

The following packages will be UPDATED:

  conda                                        4.8.2-py37_0 --> 4.8.3-py37_0


Proceed ([y]/n)? y

Downloading and Extracting Packages
h2o-3.18.0.2         | 118.2 MB  | ########################################################## | 100% 
conda-4.8.3          | 2.8 MB    | ########################################################## | 100% 
openjdk-8.0.152      | 57.4 MB   | ########################################################## | 100% 
Preparing transaction: done
Verifying transaction: done
Executing transaction: done
(base) user@fe51f813476b:~$ 
```
