* Rev.2: 2020-11-09 (Mon)
* Rev.1: 2020-03-16 (Mon)
* Draft: 2019-12-18 (Wed)

# Install Anaconda on Linux
This page summarizes [Installing Anaconda on Linux](https://problemsolvingwithpython.com/01-Orientation/01.05-Installing-Anaconda-on-Linux/). So read [Installing Anaconda on Linux](https://problemsolvingwithpython.com/01-Orientation/01.05-Installing-Anaconda-on-Linux/) for details.

The same topic in Korean is available at:
* [Ubuntu Linux에 Anaconda 설치하기](https://aimldl.blog.me/221581359811?Redirect=Log&from=postView)
* [Windows10에서 Anaconda 환경설정 하기](https://aimldl.blog.me/221570801255?Redirect=Log&from=postView)

## Download the installation file

1. Visit the Anaconda downloads page
[Anaconda.com/downloads](https://www.anaconda.com/distribution/)

2. Select Linux
<img src="https://problemsolvingwithpython.com/01-Orientation/images/Anaconda_download_linux.png">

3. Download the installation file

  ### For Python 3.8 version (Linux)

  ###### Python 3.8

  [64-Bit (x86) Installer (550 MB)](https://repo.anaconda.com/archive/Anaconda3-2020.11-Linux-x86_64.sh)

  [64-Bit (Power8 and Power9) Installer (290 MB)](https://repo.anaconda.com/archive/Anaconda3-2020.07-Linux-ppc64le.sh)

  

  Step 1. Copy the installation file `Anaconda3-2020.11-Linux-x86_64.sh` to the user home

  Step 2. Open terminal and star the installation process by running the installation file:

  ```bash
  $ bash Anaconda3-2020.11-Linux-x86_64.sh
  ```

  Follow the instructions to install Anaconda.~/github/projects/text_summarization_in_korean/project-extraction_of_korean_news

  ```bash
  $ bash Anaconda3-2020.11-Linux-x86_64.sh
  
  Welcome to Anaconda3 2020.07
  
  In order to continue the installation process, please review the license
  agreement.
  Please, press ENTER to continue
  >>> 
  (...)
  Do you accept the license terms? [yes|no]
  [no] >>>   yes
  (...)
  Anaconda3 will now be installed into this location:
  /home/k8smaster/anaconda3
  
    - Press ENTER to confirm the location
    - Press CTRL-C to abort the installation
    - Or specify a different location below
  
  [/home/k8smaster/anaconda3] >>> 
  (...)
  Do you wish the installer to initialize Anaconda3
  by running conda init? [yes|no]
  [no] >>> 
  (...)
  ==> For changes to take effect, close and re-open your current shell. <==
  
  If you'd prefer that conda's base environment not be activated on startup, 
     set the auto_activate_base parameter to false: 
  
  conda config --set auto_activate_base false
  
  Thank you for installing Anaconda3!
  (...)
  $
  ```

  Step 3. Close the existing terminal and open a new one.

  ```
  (base) k8smaster@k8smaster-Alienware-Aurora-R7:~$
  ```

  You will see the leading `(base)` indicating Anaconda is ready to use. For short, the above prompt is abbreviated as follows.

  ```
  (base) $
  ```

  Step 4. Check the python version

  ```bash
  (base) $ python --version
  Python 3.8.5
  (base) $
  ```

  Step 5. Update to the most recent version

  ```bash
  (base) $ conda update --all --yes
  
  ```

  Step 6. Start using Anaconda.

  As an example, run Jupyter Notebook.

  ```bash
  (base) $ jupyter notebook
  ```

  ### For Python 3.6 version

  <img src="https://problemsolvingwithpython.com/01-Orientation/images/anaconda_install_linux_copy_link_address.png">

For example, the link of the red box is https://repo.anaconda.com/archive/Anaconda3-2020.02-Linux-x86_64.sh
<img src="images/anaconda-homepage-download.png">

Step 1. Use wget to download the bash installer

```bash
$ wget https://repo.anaconda.com/archive/Anaconda3-2020.02-Linux-x86_64.sh
```

```bash
$ docker run -it --name anaconda aimldl/baseimage_python3.6.9_ubuntu18.04.4 bash
user@9ec1b217c60a:~$ ls
bin  downloads  lib  uploads
user@9ec1b217c60a:~$ wget https://repo.anaconda.com/archive/Anaconda3-2020.02-Linux-x86_64.sh
--2020-03-16 07:53:12--  https://repo.anaconda.com/archive/Anaconda3-2020.02-Linux-x86_64.sh
Resolving repo.anaconda.com (repo.anaconda.com)... 104.16.131.3, 104.16.130.3, 2606:4700::6810:8303, ...
Connecting to repo.anaconda.com (repo.anaconda.com)|104.16.131.3|:443... connected.
HTTP request sent, awaiting response... 200 OK
Length: 546910666 (522M) [application/x-sh]
Saving to: 'Anaconda3-2020.02-Linux-x86_64.sh'

Anaconda3-2020.02-Linux-x86_64.sh 100%[===========================================================>] 521.57M  11.3MB/s    in 47s

2020-03-16 07:53:59 (11.1 MB/s) - 'Anaconda3-2020.02-Linux-x86_64.sh' saved [546910666/546910666]

user@9ec1b217c60a:~$
```

5. Run the bash script to install Anaconda3
Accept the Licence Agreement and allow Anaconda to be added to your PATH. By adding Anaconda to your PATH, the Anaconda distribution of Python will be called when you type $ python in a terminal.
```bash
user@9ec1b217c60a:~$ ls
Anaconda3-2020.02-Linux-x86_64.sh  bin  downloads  lib  uploads
user@9ec1b217c60a:~$ bash Anaconda3-2020.02-Linux-x86_64.sh

Welcome to Anaconda3 2020.02

In order to continue the installation process, please review the license
agreement.
Please, press ENTER to continue
>>>
   ...
Do you accept the license terms? [yes|no]
[no] >>> yes

Anaconda3 will now be installed into this location:
/home/user/anaconda3

  - Press ENTER to confirm the location
  - Press CTRL-C to abort the installation
  - Or specify a different location below

[/home/user/anaconda3] >>>
PREFIX=/home/user/anaconda3
Unpacking payload ...
  ...
installation finished.
Do you wish the installer to initialize Anaconda3
by running conda init? [yes|no]
[no] >>> yes
no change     /home/user/anaconda3/condabin/conda
no change     /home/user/anaconda3/bin/conda
no change     /home/user/anaconda3/bin/conda-env
no change     /home/user/anaconda3/bin/activate
no change     /home/user/anaconda3/bin/deactivate
no change     /home/user/anaconda3/etc/profile.d/conda.sh
no change     /home/user/anaconda3/etc/fish/conf.d/conda.fish
no change     /home/user/anaconda3/shell/condabin/Conda.psm1
no change     /home/user/anaconda3/shell/condabin/conda-hook.ps1
no change     /home/user/anaconda3/lib/python3.7/site-packages/xontrib/conda.xsh
no change     /home/user/anaconda3/etc/profile.d/conda.csh
modified      /home/user/.bashrc

==> For changes to take effect, close and re-open your current shell. <==

If you'd prefer that conda's base environment not be activated on startup,
   set the auto_activate_base parameter to false:

conda config --set auto_activate_base false

Thank you for installing Anaconda3!

===========================================================================
  ...
user@9ec1b217c60a:~$
```
The package plan is a part of the output message of the following command, but it is omitted for readability. For details, refer to [package_plan.md](https://github.com/aimldl/computing_environments/blob/master/anaconda/package_plan.md).

6. source the .bash-rc file to add Anaconda to your PATH
```bash
$ cd ~
$ source .bashrc
```

```bash
user@9ec1b217c60a:~$ source .bashrc
(base) user@9ec1b217c60a:~$
```

7. Start the Python REPL
```bash
$ python

Python 3.6.5 |Anaconda, Inc.| (default, Mar 29 2018, 18:21:58)
[GCC 7.2.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> exit()
$
```

```bash
(base) user@9ec1b217c60a:~$ python
Python 3.7.6 (default, Jan  8 2020, 19:59:22)
[GCC 7.3.0] :: Anaconda, Inc. on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> exit()
(base) user@9ec1b217c60a:~$
```

