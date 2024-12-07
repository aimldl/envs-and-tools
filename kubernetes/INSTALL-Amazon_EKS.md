* Rev.2: 2020-04-16 (Thu)
* Rev.1: 2020-04-06 (Mon)
* Draft: 2020-04-05 (Sun)

# AWS를 이용해서 Kubernetes 설치하기

AWS를 이용해서 Kubernetes환경을 구축할 때 AWS EKS (Elastic Kubernetes Service)를 쓰면 편리합니다. 아래의 설치 과정에서는 설치 명령어를 실행하기 위한 준비를 하고, "$ eksctl create cluster" 명령어를 실행합니다.

## 설치 과정 요약

> Python → AWS CLI (+ AWS IAM의 자격 증명) →eksctl →kubectl

* Python 설치 (버전 2.7.9 이상)
* AWS CLI 설치
  * (버전 1.18.10 이상)
    * 최신 버전 설치 명령어: $ pip install awscli --upgrade --user
    * AWS CLI 자격 증명 구성 명령어: $ aws configure
  * (버전 1.18.10 이하)
    * AWS IAM Authenticator가 필요

* [Amazon EKS 클러스터 생성](https://docs.aws.amazon.com/ko_kr/eks/latest/userguide/create-cluster.html)
  * 자동 생성: eksctl 설치 후 "eksctl create cluster" 명령어로 생성
  * 수동 생성
    * AWS Management Console로 생성
    * AWS CLI로 생성

## 주의사항

AWS CLI 설치 부분을 제외한 부분은 상당히 스무즈하게 진행이 됩니다. 다양한 웹문서를 참고했을 때 혼돈이 되는 부분이 있으므로 이부분에 대한 부연설명이 필요합니다. AWS CLI 버전 1.18.10 이상에서 사용할 수 있는 **aws eks get-token** 명령으로 클라이언트 보안 토큰을 생성해야 합니다. 이 명령어를 지원하지 않는 이전 버전에서 클라이언트 보안 토큰을 위해 AWS IAM Authenticator가 필요한 것입니다. 

반대로 말하면 이전 버전의 AWS CLI가 설치된 상황에서 최신 버전 업데이트 없이 진행할 경우, 다음 단계인 EKS 클러스터 생성부분에서 에러가 발생합니다. 

```
$ eksctl create cluster
[ℹ]  eksctl version 0.16.0
  ...
[✔]  all EKS cluster resources for "adorable-lagomorph-1234567890" have been created
[✔]  saved kubeconfig as "/home/aimldl/.kube/config"
  ...    server: https://864506417098CA502E6771E934C9BCCC.yl4.ap-northeast-2.eks.amazonaws.com
[✖]  unable to use kubectl with the EKS cluster (check 'kubectl version'): /usr/lib/python3/dist-packages/requests/__init__.py:80: RequestsDependencyWarning: urllib3 (1.25.5) or chardet (3.0.4) doesn't match a supported version!
  RequestsDependencyWarning)
usage: aws [options] <command> <subcommand> [<subcommand> ...] [parameters]
  ...
Unable to connect to the server: getting credentials: exec: exit status 2

[ℹ]  cluster should be functional despite missing (or misconfigured) client binaries
[✔]  EKS cluster "adorable-lagomorph-1234567890" in "ap-northeast-2" region is ready
$
```

이 문제는 AWS IAM Authenticator를 설치하면 해결됩니다. 혹은 AWS CLI를 최신 버전으로 업데이트 해도 해결됩니다. 에러를 해결한 후 다시 "eksctl create cluster" 명령어를 실행하게 되면 새로운 EKS클러스터를 생성합니다. 

여기서 주의가 필요합니다. 왜냐하면 앞에서 만들어진 Amazon EC2 Instance가 "Running" 상태로 남아있기 때문입니다. 앞에서 만들다 남은 AWS 지원들을 치우지 않으면 계속 과금이 됩니다.

## Prerequisites

### 가상환경 만들기

AWS EKS 공식 문서에서는 요구하지 않지만, 편의상 가상환경을 만들어서 설치를 진행해봅니다. Anaconda가 설치되었다고 가정하고 "e2e_automl"라는 이름을 가진 가상환경을 만듭니다. 

```
(base) $ conda update -n base -c defaults conda
(base) $ conda create -n e2e_automl python=3 anaconda
  ...
(base) ~$
```

#### 설치 확인

```
(base) ~$ conda info -e
# conda environments:
#
e2e_automl               /home/aimldl/anaconda3/envs/e2e_automl
(base) ~$
```

#### 가상환경으로 들어가기

```
(base) ~$ conda activate e2e_automl
(e2e_automl) ~$
```

### AWS 관련 설치 및 설정

#### AWS CLI 설치하기

AWS CLI 설치 과정에서 IAM를 설정하게 됩니다. (터미널로 AWS에 접속 시 크레덴셜이 필요)  자세한 설치  과정은 [aws/cli/INSTLL.md](../../aws/cli/INSTLL.md)을 참고하세요. 

##### 신규 설치

```
$ sudo python get-pip.py
$ sudo pip install awscli
```

##### IAM 설정[eksctl 명령줄 유틸리티](https://docs.aws.amazon.com/ko_kr/eks/latest/userguide/eksctl.html)

```
$ aws configure
AWS Access Key ID [None]: AKIAIOSFODNN7EXAMPLE
AWS Secret Access Key [None]: wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY
Default region name [None]: us-west-2
Default output format [None]: json
$
```

##### (이미 있는 경우) 업그레이드

AWS CLI가 이미 설치된 경우, 최신 버전으로 업그레이드 합니다. 

```
$ pip install awscli --upgrade --user
```

##### AWS IAM Authenticator: Amazon EKS를 위한 IAM 설치하기

시스템에 AWS CLI 버전 1.18.10 이상을 설치할 수 없는 경우, Kubernetes용 AWS IAM Authenticator인 AWS IAM Authenticator를 설치해야 합니다. 자세한 내용은 [aws-iam-authenticator 설치](https://docs.aws.amazon.com/ko_kr/eks/latest/userguide/install-aws-iam-authenticator.html)를 참고하세요.

##### (업그레이드 안 될 때) AWS IAM Authenticator 설치하기

Step 1. aws-iam-authnticator 실행파일을 다운로드

Step 2. 실행권한을 부여

Step 3. User Home 디렉토리에 bin 디렉토리를 생성, 실행파일을 복사한 후, 어디서든 실행될 수 있도록 PATH를 설정

Step 4. 재부팅 후에도 PATH 설정이 적용되도록 .bashrc에 복사

```bash
$ curl -o aws-iam-authenticator https://amazon-eks.s3-us-west-2.amazonaws.com/1.14.6/2019-08-22/bin/linux/amd64/aws-iam-authenticator
$ chmod +x ./aws-iam-authenticator
$ mkdir -p $HOME/bin && cp ./aws-iam-authenticator $HOME/bin/aws-iam-authenticator && export PATH=$PATH:$HOME/bin
$ echo 'export PATH=$PATH:$HOME/bin' >> ~/.bashrc
```

Step 5. 설치 확인.

```bash
$ aws-iam-authenticator version
{"Version":"v0.4.0","Commit":"c141eda34ad1b6b4d71056810951801348f8c367"}
$
```

> Q: aws-iam-authenticator를 설치하게 되면, AWS CLI 설치할 때 실행하는 "aws configure"를 굳히 설정해야 하는가? 둘 다 IAM (Identity and Access Management)이므로 왠지 겹치는 것 같은데...
>
> A:  

##### 참고. AWS IAM Authenticator의 help

```bash
$ aws-iam-authenticator help
A tool to authenticate to Kubernetes using AWS IAM credentials

Usage:
  aws-iam-authenticator [command]

Available Commands:
  help        Help about any command
  init        Pre-generate certificate, private key, and kubeconfig files for the server.
  server      Run a webhook validation server suitable that validates tokens using AWS IAM
  token       Authenticate using AWS IAM and get token for Kubernetes
  verify      Verify a token for debugging purpose
  version     Version will output the current build information

Flags:
  -i, --cluster-id ID       Specify the cluster ID, a unique-per-cluster identifier for your aws-iam-authenticator installation.
  -c, --config filename     Load configuration from filename
  -h, --help                help for aws-iam-authenticator
  -l, --log-format string   Specify log format to use when logging to stderr [text or json] (default "text")

Use "aws-iam-authenticator [command] --help" for more information about a command.
$
```

### Amazon EKS 관련 설정

Amazon EKS는 AWS에 Kubernetes 환경을 손쉽게 만들기 위한 서비스입니다. 새로운 Kubernetes 클러스터를 만들고 관리하기 위해서 필요한 것을 설치해봅니다. 두 가지 옵션이 있습니다.

* 자동 설치를 위해 eksctl (EKS Control)을 사용. 
* 수동 설치를 위해 AWS management Console을 사용. 

#### 참고 문서

* 자동 설치: [eksctl 시작하기 (공식 문서)](https://docs.aws.amazon.com/ko_kr/eks/latest/userguide/getting-started-eksctl.html), [eksctl 명령줄 유틸리티](https://docs.aws.amazon.com/ko_kr/eks/latest/userguide/eksctl.html)

* 수동 설치: [AWS Management 콘솔 시작하기 (공식 문서)](https://docs.aws.amazon.com/ko_kr/eks/latest/userguide/getting-started-console.html)

#### eksctl로 Amazon EKS 시작하기

eksctl은 EKS에 Kubernetes 클러스터를 간편하게 만들기 위한 CLI 툴입니다. (조건만 맞다면) "eksctl create cluster" 명령어 하나로 EKS 클러스터 만들 수 있습니다. 자세한 내용은 [eksctl 명령줄 유틸리티](https://docs.aws.amazon.com/ko_kr/eks/latest/userguide/eksctl.html)와 [eksctl 시작하기 (공식 문서)](https://docs.aws.amazon.com/ko_kr/eks/latest/userguide/getting-started-eksctl.html)를 참고하세요.

#### 사전 조건

eksctl을 설치하기 위한사전 조건은 앞절에서 충족 시켰습니다. 하지만 다른 문서 등을 참고하다보면 혼란이 오기 때문에 아래에 정리합니다.

* Python 설치 (버전 2.7.9 이상)
* AWS CLI 설치
  * AWS CLI를 쓸려면 버전 1.18.10 이상이 필요
    * 최신 버전 설치 명령어: $ pip install awscli --upgrade --user
    * AWS CLI 자격 증명 구성 명령어: $ aws configure
  * 1.18.10 이상 설치가 안 될 때
    * AWS IAM Authenticator가 필요

AWS CLI 버전 1.18.10 이상에서 사용할 수 있는 **aws eks get-token** 명령으로 클라이언트 보안 토큰을 생성해야 합니다.

#### eksctl 설치하기

```
$ curl --silent --location "https://github.com/weaveworks/eksctl/releases/latest/download/eksctl_$(uname -s)_amd64.tar.gz" | tar xz -C /tmp
$ sudo mv /tmp/eksctl /usr/local/bin
```

#### 설치 확인하기

```
$ eksctl version
```

#### 참고: eksctl help

```bash
$ eksctl help
The official CLI for Amazon EKS

Usage: eksctl [command] [flags]

Commands:
  eksctl create                  Create resource(s)
  eksctl get                     Get resource(s)
  eksctl update                  Update resource(s)
  eksctl upgrade                 Upgrade resource(s)
  eksctl delete                  Delete resource(s)
  eksctl set                     Set values
  eksctl unset                   Unset values
  eksctl scale                   Scale resources(s)
  eksctl drain                   Drain resource(s)
  eksctl utils                   Various utils
  eksctl completion              Generates shell completion scripts
  eksctl version                 Output the version of eksctl
  eksctl help                    Help about any command

Common flags:
  -C, --color string   toggle colorized logs (valid options: true, false, fabulous) (default "true")
  -h, --help           help for this command
  -v, --verbose int    set log level, use 0 to silence, 4 for debugging and 5 for debugging with AWS debug logging (default 3)

Use 'eksctl [command] --help' for more information about a command.

$ eksctl
The official CLI for Amazon EKS

Usage: eksctl [command] [flags]

Commands:
  eksctl create                  Create resource(s)
  eksctl get                     Get resource(s)
  eksctl update                  Update resource(s)
  eksctl upgrade                 Upgrade resource(s)
  eksctl delete                  Delete resource(s)
  eksctl set                     Set values
  eksctl unset                   Unset values
  eksctl scale                   Scale resources(s)
  eksctl drain                   Drain resource(s)
  eksctl utils                   Various utils
  eksctl completion              Generates shell completion scripts
  eksctl version                 Output the version of eksctl
  eksctl help                    Help about any command

Common flags:
  -C, --color string   toggle colorized logs (valid options: true, false, fabulous) (default "true")
  -h, --help           help for this command
  -v, --verbose int    set log level, use 0 to silence, 4 for debugging and 5 for debugging with AWS debug logging (default 3)

Use 'eksctl [command] --help' for more information about a command.

$
```

#### 로컬 컴퓨터에 kubectl을 설치하고 구성하기

##### kubectl은 무엇인가?

eksctl로 AWS 클라우드 상에 Kubernetes환경이 구축되었을 때, 원격으로 접속해서 이 환경을 쓰기 위해서는 Kubernetes를 컨트롤 (Control)할 수 있는 프로그램인 kubectl (Kube Control)이 내 로컬 컴퓨터에 설치되어 있어야 합니다. 

##### kubectl 설치하기

kubectl은 Linux, Windows, macOS 모두 지원합니다. 상세한 내용은 [kubectl 설치 (AWS 공식 문서}](https://docs.aws.amazon.com/ko_kr/eks/latest/userguide/install-kubectl.html), [Install and Set Up kubectl (kubernetes 공식 문서)](https://kubernetes.io/docs/tasks/tools/install-kubectl/)를 참고하세요.

```bash
$ sudo apt-get update && sudo apt-get install -y apt-transport-https
$ curl -s https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add -
$ echo "deb https://apt.kubernetes.io/ kubernetes-xenial main" | sudo tee -a /etc/apt/sources.list.d/kubernetes.list
$ sudo apt-get update
$ sudo apt-get install -y kubectl
```

##### 설치 확인하기

```
$ kubectl version --short --client
Client Version: v1.18.0
$
```

##### 주의사항

* Amazon EKS 클러스터 제어 플레인과 마이너 버전이 하나 정도 다른 `kubectl` 버전을 사용
* 예: 1.12 `kubectl` 클라이언트는 Kubernetes 1.11, 1.12 및 1.13 클러스터로 작업해야 합니다.

##### 설정 확인하기

```
$ kubectl cluster-infokubectl cluster-info
Kubernetes master is running at https://A532D49D10EE3EC476416F5A8C7C7C97.yl4.ap-northeast-2.eks.amazonaws.com
CoreDNS is running at https://A123B45C67DE8FG901234H5I6J7K8L90.ab1.ap-northeast-2.eks.amazonaws.com/api/v1/namespaces/kube-system/services/kube-dns:dns/proxy

To further debug and diagnose cluster problems, use 'kubectl cluster-info dump'.
$ 
```

만약 아래와 같은 메세지가 나온다면 앞부분의 설치/설정이 잘못 되었습니다.

```
$ kubectl cluster-info
error: Missing or incomplete configuration info.  Please point to an existing, complete config file:

    1. Via the command-line flag --kubeconfig
    2. Via the KUBECONFIG environment variable
    3. In your home directory as ~/.kube/config

To view or setup config directly use the 'config' command.
$
```

```
$ kubectl cluster-info
To further debug and diagnose cluster problems, use 'kubectl cluster-info dump'.
Unable to connect to the server: dial tcp: lookup A532D49D10EE3EC476416F5A8C7C7C97.yl4.ap-northeast-2.eks.amazonaws.com on 127.0.0.53:53: no such host
$
```

다음: [eksctl로 AWS에 Kubernetes 클러스터 만들기](create a kubernetes cluster with eksctl.md)

이전: [Kubeflow README](README.md)