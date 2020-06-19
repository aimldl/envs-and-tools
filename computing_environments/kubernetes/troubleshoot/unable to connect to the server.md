* Draft: 2020-04-07 (Tue)

# Unable to connect to the server

kube configure에 관한 자세한 내용은 [Configure Access to Multiple Clusters](https://kubernetes.io/docs/tasks/access-application-cluster/configure-access-multiple-clusters/)를 참고하세요.

## Problem

```
$ kubectl get svc
Unable to connect to the server: dial tcp: lookup A532D49D10EE3EC476416F5A8C7C7C97.yl4.ap-northeast-2.eks.amazonaws.com on 127.0.0.53:53: no such host
$
```

## Hints

```
$ kubectl cluster-info
To further debug and diagnose cluster problems, use 'kubectl cluster-info dump'.
Unable to connect to the server: dial tcp: lookup A532D49D10EE3EC476416F5A8C7C7C97.yl4.ap-northeast-2.eks.amazonaws.com on 127.0.0.53:53: no such host
$
```

먼저 "kubectl config view" 명령어로 설정을 보겠습니다. kubectl가 이미 지워진 예전 클러스터에 접속하도록 설정되어 있음을 알 수 있습니다.

```
$ kubectl config view
apiVersion: v1
clusters:
- cluster:
    certificate-authority-data: 
  ...
    server: https://123456789012AB345C6789D012E3FGHI.yl4.ap-northeast-2.eks.amazonaws.com
  name: adorable-creature-1234567890.ap-northeast-2.eksctl.io
- cluster:
    certificate-authority-data: 
  ...
    server: https://A532D49D10EE3EC476416F5A8C7C7C97.yl4.ap-northeast-2.eks.amazonaws.com
  name: ridiculous-painting-1586094342.ap-northeast-2.eksctl.io
  ...
$
```

이 명령어는 ~./kube/config 파일의 내용을 보여줍니다. 이 텍스트 파일을 cat 명령어로 직접 보는 것과 결과가 같습니다.

```
~$ cd .kube/
~/.kube$ ls
cache  config  http-cache
/.kube$ cat config 
apiVersion: v1
clusters:
- cluster:
    certificate-authority-data: 
  ...
    server: https://123456789012AB345C6789D012E3FGHI.yl4.ap-northeast-2.eks.amazonaws.com
  name: adorable-creature-1234567890.ap-northeast-2.eksctl.io
- cluster:
    certificate-authority-data: 
  ...
    server: https://A532D49D10EE3EC476416F5A8C7C7C97.yl4.ap-northeast-2.eks.amazonaws.com
  name: ridiculous-painting-1586094342.ap-northeast-2.eksctl.io
  ...
/.kube$
```

## Solution

~/.kube/configure 파일의 내용을 수정했습니다. 이미 지워진 ridiculous-painting 클러스터의 설정을 모두 지웁니다.

### 주의사항

이 때 current-context를 새로 설정한 이름으로 변경해야 합니다.

>   name: aimldl@adorable-creature-1586077260.ap-northeast-2.eksctl.io
> current-context: aimldl@adorable-creature-1234567890.ap-northeast-2.eksctl.io

만약 아래 처럼 예전 이름으로 남아있을 경우

>   name: aimldl@adorable-creature-1234567890.ap-northeast-2.eksctl.io
> current-context: aimldl@ridiculous-painting-1586094342.ap-northeast-2.eksctl.io

에러 메세지가 발생합니다.

```
$ kubectl cluster-info
Error in configuration: 
* context was not found for spec
$
```

## Results

아래 처럼 kubectl 명령어가 정상적으로 작동합니다.

```
$ kubectl cluster-info
Kubernetes master is running at https://123456789012AB345C6789D012E3FGHI.yl4.ap-northeast-2.eks.amazonaws.com
CoreDNS is running at https://123456789012AB345C6789D012E3FGHI.yl4.ap-northeast-2.eks.amazonaws.com/api/v1/namespaces/kube-system/services/kube-dns:dns/proxy

To further debug and diagnose cluster problems, use 'kubectl cluster-info dump'.
$
```

```
$ kubectl get svc
NAME         TYPE        CLUSTER-IP   EXTERNAL-IP   PORT(S)   AGE
kubernetes   ClusterIP   10.100.0.1   <none>        443/TCP   42h
$
```

