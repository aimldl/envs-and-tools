* Draft: 2020-11-09 (Mon)

# How to Install Jupyter Notebook on Anaconda



## Problem

아나콘다 설치 후 `(base)`에서 Jupyter notebook이 실행되지만, 새로 만든 가상환경 `(new_virtual_environment) `에서 실행하면 아래와 같은 에러가 발생합니다.

```bash
(new_virtual_environment) $ jupyter notebook

Command 'jupyter' not found, but can be installed with:

sudo snap install jupyter       # version 1.0.0, or
sudo apt  install jupyter-core

See 'snap info jupyter' for additional versions.

(new_virtual_environment) $
```

## Hink

Google search: anaconda create a new virtual environment with all packages including jupyter notebook

[Create Virtual Environment using “conda” and add it to Jupyter Notebook](https://medium.com/analytics-vidhya/create-virtual-environment-using-conda-and-add-it-to-jupyter-notebook-d319a81dfd1)

> Part 2: Add Virtual Environment to Jupyter Notebook
>
> Next you can add your virtual environment to Jupyter by typing:
>
> ```bash
> python -m ipykernel install --user --name=<my_env_name>
> ```

```bash
$ python -m ipykernel install --user --name='korean_news_extraction'
Installed kernelspec korean_news_extraction in /home/aimldl/.local/share/jupyter/kernels/korean_news_extraction
$
```

[Installing Jupyter Notebook](https://test-jupyter.readthedocs.io/en/latest/install.html)