# Anaconda
* Created: 2019-12-18 (Wed)
* Updated: 2025-02-22 (Sat)

## Documents
* [Conda Docs](https://conda.io/projects/conda/en/latest/index.html) » [User guide](https://conda.io/projects/conda/en/latest/user-guide/index.html) » [Getting started with conda](https://conda.io/projects/conda/en/latest/user-guide/getting-started.html)
* [CONDA CHEAT SHEET](https://docs.conda.io/projects/conda/en/4.6.0/_downloads/52a95608c49671267e40c689e0bc00ca/conda-cheatsheet.pdf)

### Create a new Conda environment
An example command to create a new virtual environment "pytorch" is below. Make sure to update Anaconda before creating a new virtual environment.
```bash
$ conda update -n base -c defaults -y conda
$ conda create -n pytorch -y python=3 anaconda
```
For details, refer to [Create virtual environments for python with conda](https://uoa-eresearch.github.io/eresearch-cookbook/recipe/2014/11/20/conda/).

The options `python=3 anaconda` can be skipped to create an empty and clean environment.

### Update all Conda environments

```bash
(base) $ conda update --all -y
```

### Delete the Conda environment
Say `vllm` is the name of the Conda environment to delete.
```bash
(vllm) $ conda deactivate
(base) $ conda env remove -n vllm -y

Remove all packages in environment /home/thekim/anaconda3/envs/vllm:

## Package Plan ##

  environment location: /home/thekim/anaconda3/envs/vllm

The following packages will be REMOVED:
  ...
Preparing transaction: done
Verifying transaction: done
Executing transaction: done
(base) $ 
```
To double-check, run
```bash
(base) $ conda info -e

# conda environments:
#
base                 * /home/thekim/anaconda3
  ...
(base) $
```

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
