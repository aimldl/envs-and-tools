* Rev.2: 2020-05-22 (Fri)
* Rev.1: 2020-03-16 (Mon)
* Draft: 2019-12-18 (Wed)
# Anaconda

## Documents
* [Conda Docs](https://conda.io/projects/conda/en/latest/index.html) » [User guide](https://conda.io/projects/conda/en/latest/user-guide/index.html) » [Getting started with conda](https://conda.io/projects/conda/en/latest/user-guide/getting-started.html)
* [CONDA CHEAT SHEET](https://docs.conda.io/projects/conda/en/4.6.0/_downloads/52a95608c49671267e40c689e0bc00ca/conda-cheatsheet.pdf)

### Create a New Virtual Environment
An example command to create a new virtual environment "pytorch" is below. Make sure to update Anaconda before creating a new virtual environment.
```bash
$ conda update -n base -c defaults -y conda
$ conda create -n pytorch python=3 anaconda
```
For details, refer to [Create virtual environments for python with conda](https://uoa-eresearch.github.io/eresearch-cookbook/recipe/2014/11/20/conda/).
### Install PyTorch
When Cuda 10.0 is used, run:
```bash
$ conda install pytorch torchvision cuda100 -c pytorch
```
To verify, the following lines should run without an error message.
```bash
python
>>> import torch
>>> cpu_tensor = torch.zeros(2,3)
>>> device = torch.device('cuda:0')
>>> gpu_tensor = cpu_tensor.to(device)
>>> print( gpu_tensor )
```
