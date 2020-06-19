* Draft: 2020-04-21 (Tue)

# Kubernetes 대시보드 설치하기

참고 문서: [자습서: Kubernetes 웹 UI 배포(대시보드)](https://docs.aws.amazon.com/ko_kr/eks/latest/userguide/dashboard-tutorial.html)

## Kubernetes Dashboard

* 쿠버네티스 대시보드는 Kubernetes 관리를 위한 웹UI입니다. 

* 설치하기라고 했지만 정확히는 Kubernetes 클러스터에 배포를 하는 것입니다.
* 커맨드 라인으로 보는 k9s라는 CLI (Command Line Interface)도 있습니다.
* 대시보드와 k9s 모두 설치하면 편리합니다.

## 배포하기

### 준비 사항

* Amazon EKS 클러스터를 생성
* kubectl 설치

#### Kubernetes 지표 서버 (Metrics Server)배포

* Option 1: curl과 jq를 쓰는 방법

* Option 2: Web brower를 쓰는 방법

두가지 방법 중 첫 번째 방법을 이용합니다.

##### metrics-server의 최신 Release를 다운로드하고, 클러스터에 배포

```bash
$ DOWNLOAD_URL=$(curl -Ls "https://api.github.com/repos/kubernetes-sigs/metrics-server/releases/latest" | jq -r .tarball_url)
DOWNLOAD_VERSION=$(grep -o '[^/v]*$' <<< $DOWNLOAD_URL)
$ curl -Ls $DOWNLOAD_URL -o metrics-server-$DOWNLOAD_VERSION.tar.gz
$ mkdir metrics-server-$DOWNLOAD_VERSION
$ tar -xzf metrics-server-$DOWNLOAD_VERSION.tar.gz --directory metrics-server-$DOWNLOAD_VERSION --strip-components 1
$ kubectl apply -f metrics-server-$DOWNLOAD_VERSION/deploy/1.8+/
```

```bash
clusterrole.rbac.authorization.k8s.io/system:aggregated-metrics-reader created
clusterrolebinding.rbac.authorization.k8s.io/metrics-server:system:auth-delegator created
rolebinding.rbac.authorization.k8s.io/metrics-server-auth-reader created
apiservice.apiregistration.k8s.io/v1beta1.metrics.k8s.io created
serviceaccount/metrics-server created
deployment.apps/metrics-server created
service/metrics-server created
clusterrole.rbac.authorization.k8s.io/system:metrics-server created
clusterrolebinding.rbac.authorization.k8s.io/system:metrics-server created
$
```

#### 배포 확인

```
$ kubectl get deployment metrics-server -n kube-system
```

```bash
NAME             READY   UP-TO-DATE   AVAILABLE   AGE
metrics-server   1/1     1            1           24s
$
```

#### 대시보드 배포

```bash
$ kubectl apply -f https://raw.githubusercontent.com/kubernetes/dashboard/v2.0.0-rc7/aio/deploy/recommended.yaml
```

최신 버전을 설치하기 위해선 [GitHub의 Kubernetes Dashboard 페이지](https://github.com/kubernetes/dashboard)의 명령어를 확인하세요. 아래는 Amazon EKS 공식 문서의 명령어인데 업데이트가 되지 않은 것 같네요. 같은 날인데 beta8이니까요.

```
$ kubectl apply -f https://raw.githubusercontent.com/kubernetes/dashboard/v2.0.0-beta8/aio/deploy/recommended.yaml
```

```bash
namespace/kubernetes-dashboard unchanged
serviceaccount/kubernetes-dashboard unchanged
service/kubernetes-dashboard unchanged
secret/kubernetes-dashboard-certs unchanged
secret/kubernetes-dashboard-csrf configured
Warning: kubectl apply should be used on resource created by either kubectl create --save-config or kubectl apply
secret/kubernetes-dashboard-key-holder configured
configmap/kubernetes-dashboard-settings unchanged
role.rbac.authorization.k8s.io/kubernetes-dashboard unchanged
clusterrole.rbac.authorization.k8s.io/kubernetes-dashboard unchanged
rolebinding.rbac.authorization.k8s.io/kubernetes-dashboard unchanged
clusterrolebinding.rbac.authorization.k8s.io/kubernetes-dashboard unchanged
deployment.apps/kubernetes-dashboard configured
service/dashboard-metrics-scraper unchanged
deployment.apps/dashboard-metrics-scraper configured
$
```

#### eks-admin 서비스 계정 및 클러스터 역할 바인딩 생성

기본적으로 제한된 Kubernetes 대시보드 사용자의 권한을 관리자 수준 권한 변경합니다. eks-admin 서비스 계정 및 클러스터 역할 바인딩을 생성하여 대시보드에 안전하게 연결 (securely connect)할 수 있습니다. 

##### `eks-admin-service-account.yaml`파일 생성

이 파일 (정확히는 매니페스트)는 서비스 계정 (`eks-admin`)과 클러스터 역할 바인딩을 정의합니다.

```yaml
apiVersion: v1
kind: ServiceAccount
metadata:
  name: eks-admin
  namespace: kube-system
---
apiVersion: rbac.authorization.k8s.io/v1beta1
kind: ClusterRoleBinding
metadata:
  name: eks-admin
roleRef:
  apiGroup: rbac.authorization.k8s.io
  kind: ClusterRole
  name: cluster-admin
subjects:
- kind: ServiceAccount
  name: eks-admin
  namespace: kube-system
```

##### 배포

매니패스트를 쿠버네티스 클러스터에 적용하여 `서비스 계정과 클러스터 역할 바인딩`을 배포합니다.

```bash
$ kubectl apply -f eks-admin-service-account.yaml
```

```bash
serviceaccount/eks-admin created
clusterrolebinding.rbac.authorization.k8s.io/eks-admin created
$
```



#### 대시보드에 로그인하기

인증 토큰 (Authentication Token)으로 위에서 배포된 대쉬보드에 접속해봅니다. 로그인을 위해 ID와 Password를 쓰는 대신 인증 토큰을 이용합니다.

##### **kubectl proxy**를 시작

```bash
$ kubectl proxy
Starting to serve on 127.0.0.1:8001
```

##### 대시보드에 접속

웹 브라우저의 주소창에 다음 링크를 입력합니다.

```
http://localhost:8001/api/v1/namespaces/kubernetes-dashboard/services/https:kubernetes-dashboard:/proxy/#!/login
```

<img src="images/kubernetes-dashboard-web_browser_access.png">

##### `Token`을 선택하고 인증토큰을 입력 

<img src="images/kubernetes-dashboard-web_browser_access-token.png">

`eks-admin` 서비스 계정에 대한 인증 토큰은 아래 명령어로 조회할 수 있습니다.

```bash
$ kubectl -n kube-system describe secret $(kubectl -n kube-system get secret | grep eks-admin | awk '{print $1}') | grep "token:" | awk '{ print $2 }'
```

결과 예시

```bash
eyJhbGciOiJSUzI1NiIsImtpZCI6IiJ9.eyJpc3MiOiJrdWJlcm5ldGVzL3NlcnZpY2VhY2NvdW50Iiwia3ViZXJuZXRlcy5pby9zZXJ2aWNlYWNjb3VudC9uYW1lc3BhY2UiOiJrdWJlLXN5c3RlbSIsImt1YmVybmV0ZXMuaW8vc2VydmljZWFjY291bnQvc2VjcmV0Lm5hbWUiOiJla3MtYWRtaW4tdG9rZW4tZHE2MmciLCJrdWJlcm5ldGVzLmlvL3NlcnZpY2VhY2NvdW50L3NlcnZpY2UtYWNjb3VudC5uYW1lIjoiZWtzLWFkbWluIiwia3ViZXJuZXRlcy5pby9zZXJ2aWNlYWNjb3VudC9zZXJ2aWNlLWFjY291bnQudWlkIjoiYmI2NDIyNmItODE1ZC00NzNiLTg4ODItZWViMjhlYzUzZDA1Iiwic3ViIjoic3lzdGVtOnNlcnZpY2VhY2NvdW50Omt1YmUtc3lzdGVtOmVrcy1hZG1pbiJ9.T3cwkPK2SY7jVE_38YQMA9rmwb7pIl7v80yzVGHwGX8eiBA1E3WW-SUrzGsuXPKtiHbUpFibFDLhW3U5LfxInp-DVFFP09IwVFVT1DGe5fZd5KQ3cjW7yXtdoL73TJPaEb62zs5U4BZItJAGnxny6Hz7aYkzg78h4W2fswidxm23QhgvcDfoF2qF79ozY2ec11QfcLlnXTzZE9v1FLDbBvac2sZTBU2tMBW0ojjqe2MH7sZVdGeI9S9zZ7OA3YmYmfVtqXJaKBRA3-vp1EIHopK1IH5woA7cTiRddnxlmwVeYtT6PgdU-Ee_LVzZLe0Nd84AnLrS-Fx_VPIRQbMK4w
$
```

참고: 자습서의 명령어를 이용할 경우, 출력 제일 밑의 `token:`의 값을 복사하면 됩니다. 위의 명령어는 `token:`의 값을 자동 추출하므로 조금 더 편리합니다.

```bash
$ kubectl -n kube-system describe secret $(kubectl -n kube-system get secret | grep eks-admin | awk '{print $1}')
Name:         eks-admin-token-b5zv4
Namespace:    kube-system
Labels:       <none>
Annotations:  kubernetes.io/service-account.name=eks-admin
              kubernetes.io/service-account.uid=bcfe66ac-39be-11e8-97e8-026dce96b6e8

Type:  kubernetes.io/service-account-token

Data
====
ca.crt:     1025 bytes
namespace:  11 bytes
token:      <authentication_token>
$
```

조회한 인증 입증 토큰을 `Enter token`창에 복사합니다.

##### `Sign in`을 눌러서 대시보드 시작

`Sign in`버튼을 누르면 대시보드의 메인 화면이 나옵니다. 대시보드 사용에 대한 자세한 내용은 [kubernetes/dashboard의 GitHub 프로젝트 문서](https://github.com/kubernetes/dashboard)를 참고하세요.

<img src="images/kubernetes-dashboard-first_sign_in.png">

