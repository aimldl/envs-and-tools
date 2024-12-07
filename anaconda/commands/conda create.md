##### aimldl/computing_environments/anaconda/commands/conda create.md

# [conda create](https://docs.conda.io/projects/conda/en/latest/commands/create.html)

Target Environment Specification
-n, --name Name of environment.
-c, --channel  Channel Customization. 

> Additional channel to search for packages. These are URLs searched in the order
they are given (including file:// for local directories). Then, the defaults or channels from .condarc are searched (unless --override-channels is given). You can use 'defaults' to get the default packages for conda. You can also use any name and the .condarc channel_alias value will be prepended. The default channel_alias is http://conda.anaconda.org/.



```bash
(base) $ python --version
Python 3.8.5
(base) $
```

`korean_news_extraction`라는 프로젝트를 생성하고 싶을 때 아래 명령어로 아나콘다 가상환경을 생성합니다.

```bash
(base) $ conda create -n korean_news_extraction python=3.8.5
```

참고로 `conda create -n korean_news_extraction`와 `conda create --name korean_news_extraction`은 동일한 명령어입니다.

```bash
Collecting package metadata (current_repodata.json): done
Solving environment: done

## Package Plan ##

  environment location: /home/k8smaster/anaconda3/envs/korean_news_extraction

  added / updated specs:
    - python=3.8.5


The following NEW packages will be INSTALLED:

  _libgcc_mutex      pkgs/main/linux-64::_libgcc_mutex-0.1-main
  ca-certificates    pkgs/main/linux-64::ca-certificates-2020.10.14-0
  certifi            pkgs/main/noarch::certifi-2020.6.20-pyhd3eb1b0_3
  ld_impl_linux-64   pkgs/main/linux-64::ld_impl_linux-64-2.33.1-h53a641e_7
  libedit            pkgs/main/linux-64::libedit-3.1.20191231-h14c3975_1
  libffi             pkgs/main/linux-64::libffi-3.3-he6710b0_2
  libgcc-ng          pkgs/main/linux-64::libgcc-ng-9.1.0-hdf63c60_0
  libstdcxx-ng       pkgs/main/linux-64::libstdcxx-ng-9.1.0-hdf63c60_0
  ncurses            pkgs/main/linux-64::ncurses-6.2-he6710b0_1
  openssl            pkgs/main/linux-64::openssl-1.1.1h-h7b6447c_0
  pip                pkgs/main/linux-64::pip-20.2.4-py38h06a4308_0
  python             pkgs/main/linux-64::python-3.8.5-h7579374_1
  readline           pkgs/main/linux-64::readline-8.0-h7b6447c_0
  setuptools         pkgs/main/linux-64::setuptools-50.3.1-py38h06a4308_1
  sqlite             pkgs/main/linux-64::sqlite-3.33.0-h62c20be_0
  tk                 pkgs/main/linux-64::tk-8.6.10-hbc83047_0
  wheel              pkgs/main/noarch::wheel-0.35.1-py_0
  xz                 pkgs/main/linux-64::xz-5.2.5-h7b6447c_0
  zlib               pkgs/main/linux-64::zlib-1.2.11-h7b6447c_3


Proceed ([y]/n)? y
```

`y`를 선택하면 아래와 같이 환경이 생성됩니다.

```bash
Preparing transaction: done
Verifying transaction: done
Executing transaction: done
#
# To activate this environment, use
#
#     $ conda activate korean_news_extraction
#
# To deactivate an active environment, use
#
#     $ conda deactivate
(base) $
```

확인하려면 

```bash
(base) $ conda info -e
# conda environments:
#
base                  *  /home/aimldl/anaconda3
korean_news_extraction     /home/aimldl/anaconda3/envs/korean_news_extraction
(base) $
```

가상환경으로 들어가려면 `conda activate <name>`을 입력합니다.

```bash
(base) $ conda activate korean_news_extraction
(korean_news_extraction) $
```



