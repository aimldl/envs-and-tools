

# Install pytorch on anaconda
Check if the pytorch package is installed.
```bash
(pytorch) ubuntu@ec2-seoul-aimldl:~$ python
Python 3.7.6 (default, Jan  8 2020, 19:59:22) 
[GCC 7.3.0] :: Anaconda, Inc. on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> import torch
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
ModuleNotFoundError: No module named 'torch'
>>> exit()
(pytorch) ubuntu@ec2-seoul-aimldl:~$ 
```
Because the package doesn't exist, let's go ahead and install it.

[PyTorch Install - Quick and Easy](https://deeplizard.com/learn/video/UWlFM0R_x6I)
```bash
$ conda install pytorch torchvision cudatoolkit=10.0 -c pytorch
```
To verify the installation, run:
```bash
$ torch.cuda.is_available()
True
$ torch.version.cuda
'10.0'
$
```
#### Install pytorch 
```bash
(pytorch) ubuntu@ec2-seoul-aimldl:~$ conda install pytorch torchvision cudatoolkit=10.0 -c pytorch
Collecting package metadata (current_repodata.json): done
Solving environment: done

## Package Plan ##

  environment location: /home/ubuntu/anaconda3/envs/pytorch

  added / updated specs:
    - cudatoolkit=10.0
    - pytorch
    - torchvision


The following NEW packages will be INSTALLED:

  cudatoolkit        pkgs/main/linux-64::cudatoolkit-10.0.130-0
  ninja              pkgs/main/linux-64::ninja-1.9.0-py37hfd86e86_0
  pytorch            pytorch/linux-64::pytorch-1.4.0-py3.7_cuda10.0.130_cudnn7.6.3_0
  torchvision        pytorch/linux-64::torchvision-0.5.0-py37_cu100


Proceed ([y]/n)? 
   ...
```
To verify the installation, run:
```bash
(pytorch) ubuntu@ec2-seoul-aimldl:~$ python
Python 3.7.6 (default, Jan  8 2020, 19:59:22) 
[GCC 7.3.0] :: Anaconda, Inc. on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> import torch
>>> exit()
(pytorch) ubuntu@ec2-seoul-aimldl:~$
```
Pytorch has been installed successfully!
