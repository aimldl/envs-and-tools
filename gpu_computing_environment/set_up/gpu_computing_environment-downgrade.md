



[Downgrade CUDA for Tensorflow-GPU](https://medium.com/@praveenkrishna/downgrade-cuda-for-tensorflow-gpu-17831db59099), Medium, Praveen Krishna Murthy, Apr 20, 2020

> This short guide helps to understand how to downgrade the `CUDA` version in Ubuntu 18.04 OS. No background knowledge is required for this. The following operations are carried on `distribution : 18.04` and `architecture : x86_64.`
>
> In order to use the `tensorflow-gpu` for training, the `CUDA` version should be compatible with following setups:
>
> - `Python Version`
> - `Compiler (GCC)`
> - `Build Tools (Bazel)`
> - `cuDNN` `(CUDA Deep Neural Network library)`

기존에 있는/이전 버전의 `CUDA`를 제거합니다.

```bash
$ sudo apt --purge remove -y "cublas*" "cuda*"
$ sudo apt --purge remove -y "nvidia*"
$ sudo rm -rf /usr/local/cuda*
$ sudo apt-get autoremove -y && sudo apt-get autoclean -y
$ reboot
```

`CUDA10.0`을 다운로드 받고 설치합니다.

```bash
$ sudo apt-get install -y g++ freeglut3-dev build-essential libx11-dev libxmu-dev libxi-dev libglu1-mesa libglu1-mesa-dev
$ wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/cuda-repo-ubuntu1804_10.0.130-1_amd64.deb
$ sudo apt-key adv-fetch-keys https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/7fa2af80.pub
$ sudo dpkg -i cuda-repo-ubuntu1804_10.0.130-1_amd64.deb
```

다음 명령어를 실행하는데 꽤 많은 시간이 소요됩니다.

```bash
$ sudo apt install -y cuda-10.0
```



환경 변수 설정하기

> ```bash
> echo 'export PATH=/usr/local/cuda-10.0/bin:$PATH' >> ~/.bashrc
> echo 'export LD_LIBRARY_PATH=/usr/local/cuda-10.0/lib64:$LD_LIBRARY_PATH' >> ~/.bashrc
> reboot
> ```

응용

* 제 경우는 `.bashrc`는 기본대로 두고 `.bash_custom`을 불러와서 수정합니다. 그러므로 `.bash_custom`을 수정합니다만 위와 같은 작업입니다.
* `/usr/local/cuda-10.0`가 아닌 `/usr/local/cuda`으로 궁극적으로는 바꿔야하겠지만, 현 단계에서는 다른 버전을 가르키면 안 되기 때문에 명시적으로 버전을 그대로 쓰기로 합니다.
* `source`명령어로 `.bashrc`를 업데이트하는 것 만으로 `PATH`와 `LD_LIBRARY_PATH`를 업데이트할 수 있습니다.

```bash
$ echo 'export PATH=/usr/local/cuda-10.0/bin:$PATH' >> ~/.bash_custom
$ echo 'export LD_LIBRARY_PATH=/usr/local/cuda-10.0/lib64:$LD_LIBRARY_PATH' >> ~/.bash_custom
$ reboot
```



내용을 확인합니다.

```bash
$ tail -n 5 ~/.bash_custom

# TensorFlow 2.0
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda/lib64
export PATH=/usr/local/cuda-10.0/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/cuda-10.0/lib64:$LD_LIBRARY_PATH
$
```



```bash
$ echo $PATH
/home/aimldl/anaconda3/bin:/home/aimldl/anaconda3/condabin:/home/aimldl/.local/bin:/home/aimldl/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:~/.ruby/bin
$ echo $LD_LIBRARY_PATH
:/usr/local/cuda/lib64
$
```



```bash
$ source ~/.bashrc
2021-02-10 (수) 12:50 (06th week)
  ...
$
```



```bash
$ echo $LD_LIBRARY_PATH
/usr/local/cuda-10.0/lib64::/usr/local/cuda/lib64
$ echo $PATH
/usr/local/cuda-10.0/bin:/home/aimldl/anaconda3/bin:/home/aimldl/anaconda3/condabin:/home/aimldl/.local/bin:/home/aimldl/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:~/.ruby/bin:~/.ruby/bin
$ 
```



> The steps that are to be taken to remove and install the required version of CUDA is finished. Now we will head towards installing the CuDNN version. These are again libraries to support Deep Neural Network architecture computations on GPU.

### cuDNN 다운로드 및 설치

#### 다운로드

https://developer.nvidia.com/rdp/cudnn-archive

너무 많은 것이 있습니다. 웹브라우저의 찾기 기능으로 `7.4.2`을 찾습니다.



Download cuDNN v7.4.2 (Dec 14, 2018), for CUDA 10.0



[cuDNN Runtime Library for Ubuntu18.04 (Deb)](https://developer.nvidia.com/compute/machine-learning/cudnn/secure/v7.4.2/prod/10.0_20181213/Ubuntu18_04-x64/libcudnn7_7.4.2.24-1%2Bcuda10.0_amd64.deb)

[cuDNN Developer Library for Ubuntu18.04 (Deb)](https://developer.nvidia.com/compute/machine-learning/cudnn/secure/v7.4.2/prod/10.0_20181213/Ubuntu18_04-x64/libcudnn7-dev_7.4.2.24-1%2Bcuda10.0_amd64.deb)

[cuDNN Code Samples and User Guide for Ubuntu18.04 (Deb)](https://developer.nvidia.com/compute/machine-learning/cudnn/secure/v7.4.2/prod/10.0_20181213/Ubuntu18_04-x64/libcudnn7-doc_7.4.2.24-1%2Bcuda10.0_amd64.deb)





```bash
$ tar -xzvf cudnn-10.0-linux-x64-v7.4.2.24.tgz
$ sudo cp -P cuda/include/cudnn.h /usr/local/cuda-10.0/include
$ sudo cp -P cuda/lib64/libcudnn* /usr/local/cuda-10.0/lib64/
$ sudo chmod a+r /usr/local/cuda-10.0/lib64/libcudnn*
```



테스트 하기

```bash
$ nvcc -V
$ cat /usr/local/cuda/version.txt
$ cat /usr/local/cuda/include/cudnn.h | grep CUDNN_MAJOR -A 2
$ cat /usr/include/cudnn.h | grep CUDNN_MAJOR -A 2
```



> NOTE:
>
> After downgrading the CUDA, the system should never be upgraded or updated when the Linux-Ubuntu system prompts. If it is upgraded, then the system automatically removes `CUDA-10.0` and installs the highest available drivers for GPU.