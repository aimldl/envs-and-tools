```bash
$ conda create -n kf python=3 anaconda
   ...
Proceed ([y]/n)? y

Preparing transaction: done
Verifying transaction: done
Executing transaction: done
#
# To activate this environment, use
#
#     $ conda activate kf
#
# To deactivate an active environment, use
#
#     $ conda deactivate
$
```

```bash
(base) $ conda activate kf
(kf) $
```

```bash
(base) aimldl@local-machine:~$ conda activate kf
(kf) aimldl@local-machine:~$ 
```

예2-1
```
$ sudo snap install kubectl --classic
[sudo] aimldl의 암호: 
kubectl 1.21.1 from Canonical✓ installed
```


예2-3


최신 버전으로 변경

```bash
#export KUBEFLOW_TAG=1.0.1
export KUBEFLOW_TAG=1.2.0
# You can also point this to a different version if you want to try
```

```
$ nano install_kubeflow
$ chmod +x install_kubeflow
```

```bash
--2021-08-09 14:39:54--  https://github.com/kubeflow/kfctl/releases/download/v1.2.0/kfctl_v1.2.0-0-gbc038f9_linux.tar.gz
Resolving github.com (github.com)... 15.164.81.167
접속 github.com (github.com)|15.164.81.167|:443... 접속됨.
HTTP request sent, awaiting response... 302 Found
Location: https://github-releases.githubusercontent.com/198858022/744f3900-2b27-11eb-9aed-ae263fac547c?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAIWNJYAX4CSVEH53A%2F20210809%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Date=20210809T053954Z&X-Amz-Expires=300&X-Amz-Signature=5cba90d785f2785f67994462fa5ec3dbbcef999eed39dede1dc4d0c9a1743d99&X-Amz-SignedHeaders=host&actor_id=0&key_id=0&repo_id=198858022&response-content-disposition=attachment%3B%20filename%3Dkfctl_v1.2.0-0-gbc038f9_linux.tar.gz&response-content-type=application%2Foctet-stream [following]
--2021-08-09 14:39:55--  https://github-releases.githubusercontent.com/198858022/744f3900-2b27-11eb-9aed-ae263fac547c?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAIWNJYAX4CSVEH53A%2F20210809%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Date=20210809T053954Z&X-Amz-Expires=300&X-Amz-Signature=5cba90d785f2785f67994462fa5ec3dbbcef999eed39dede1dc4d0c9a1743d99&X-Amz-SignedHeaders=host&actor_id=0&key_id=0&repo_id=198858022&response-content-disposition=attachment%3B%20filename%3Dkfctl_v1.2.0-0-gbc038f9_linux.tar.gz&response-content-type=application%2Foctet-stream
Resolving github-releases.githubusercontent.com (github-releases.githubusercontent.com)... 185.199.109.154, 185.199.110.154, 185.199.108.154, ...
접속 github-releases.githubusercontent.com (github-releases.githubusercontent.com)|185.199.109.154|:443... 접속됨.
HTTP request sent, awaiting response... 200 OK
Length: 31181024 (30M) [application/octet-stream]
Saving to: ‘kfctl_v1.2.0-0-gbc038f9_linux.tar.gz’

kfctl_v1.2.0-0-gbc038f9 100%[============================>]  29.74M  8.90MB/s    in 3.4s    

2021-08-09 14:39:58 (8.73 MB/s) - ‘kfctl_v1.2.0-0-gbc038f9_linux.tar.gz’ saved [31181024/31181024]

./kfctl
$
```

KFCTL_URL의 URL을 만들어서 해당 파일을 다운로드 합니다. 다운로드 받은 파일의 압축을 해제하면 `kfctl`파일이 생깁니다. 실행 파일을 `~/bin/` 디렉토리로 옮긴 다음 파일을 삭제합니다. 어디에서도 실행할 수 있게 `PATH`에 이 디렉토리를 추가합니다.


```bash
$ ls ~/bin
kfctl
$
```


