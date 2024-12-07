# 4. Stateless Applications

## Exposing an External IP Address to Access an Application in a Cluster

This tutorial creates an external load balancer, which requires a cloud provider.

### Objectives

* Run five instances of a Hello World application
* Create a Service object that exposes an external IP address
* Use the Service object to access the running application

### Creating a service for an application running in five pods

Run a Hello World application in your cluster:

##### service/load-balancer-example.yaml

```
apiVersion: apps/v1
kind: Deployment
metadata:
  labels:
    app.kubernetes.io/name: load-balancer-example
  name: hello-world
spec:
  replicas: 5
  selector:
    matchLabels:
      app.kubernetes.io/name: load-balancer-example
  template:
    metadata:
      labels:
        app.kubernetes.io/name: load-balancer-example
    spec:
      containers:
      - image: gcr.io/google-samples/node-hello:1.0
        name: hello-world
        ports:
        - containerPort: 8080

```

이 yaml 파일을 적용하면 

* "gcr.io/google-samples/node-hello:1.0" 이미지를 가지고 와서
* "hello-world"라는 이름을 가진 pod를 5개 복제합니다. 

```
$ kubectl apply -f https://k8s.io/examples/service/load-balancer-example.yaml
deployment.apps/hello-world created
$
```

결과를 확인해보면

```
$ kubectl get deployments
NAME          READY   UP-TO-DATE   AVAILABLE   AGE
hello-world   4/5     5            4           22s
$ kubectl get pods
NAME                           READY   STATUS    RESTARTS   AGE
hello-world-7dc74ff97c-bcr9k   1/1     Running   0          29s
hello-world-7dc74ff97c-g4rdg   1/1     Running   0          29s
hello-world-7dc74ff97c-nl4nl   1/1     Running   0          29s
hello-world-7dc74ff97c-scs46   1/1     Running   0          29s
hello-world-7dc74ff97c-t89zb   1/1     Running   0          29s
$ kubectl get services
NAME         TYPE        CLUSTER-IP   EXTERNAL-IP   PORT(S)   AGE
kubernetes   ClusterIP   10.100.0.1   <none>        443/TCP   47h
$
```



```
$ kubectl get deployments hello-world
NAME          READY   UP-TO-DATE   AVAILABLE   AGE
hello-world   5/5     5            5           6m45s
$ kubectl describe deployments hello-world
Name:                   hello-world
Namespace:              default
CreationTimestamp:      Tue, 07 Apr 2020 17:55:26 +0900
Labels:                 app.kubernetes.io/name=load-balancer-example
Annotations:            deployment.kubernetes.io/revision: 1
Selector:               app.kubernetes.io/name=load-balancer-example
Replicas:               5 desired | 5 updated | 5 total | 5 available | 0 unavailable
StrategyType:           RollingUpdate
MinReadySeconds:        0
RollingUpdateStrategy:  25% max unavailable, 25% max surge
Pod Template:
  Labels:  app.kubernetes.io/name=load-balancer-example
  Containers:
   hello-world:
    Image:        gcr.io/google-samples/node-hello:1.0
    Port:         8080/TCP
    Host Port:    0/TCP
    Environment:  <none>
    Mounts:       <none>
  Volumes:        <none>
Conditions:
  Type           Status  Reason
  ----           ------  ------
  Available      True    MinimumReplicasAvailable
  Progressing    True    NewReplicaSetAvailable
OldReplicaSets:  <none>
NewReplicaSet:   hello-world-7dc74ff97c (5/5 replicas created)
Events:
  Type    Reason             Age   From                   Message
  ----    ------             ----  ----                   -------
  Normal  ScalingReplicaSet  7m2s  deployment-controller  Scaled up replica set hello-world-7dc74ff97c to 5
$
```

describe를 보면 IP에 관한 정보가 없음을 알 수 있습니다. 여하튼 ReplicaSet에는 5개의 pods가 있고, 각각 Hello World 프로그램을 실행합니다.

```
$ kubectl get replicasets
NAME                     DESIRED   CURRENT   READY   AGE
hello-world-7dc74ff97c   5         5         5       9m22s
$ kubectl describe replicasets
Name:           hello-world-7dc74ff97c
Namespace:      default
Selector:       app.kubernetes.io/name=load-balancer-example,pod-template-hash=7dc74ff97c
Labels:         app.kubernetes.io/name=load-balancer-example
                pod-template-hash=7dc74ff97c
Annotations:    deployment.kubernetes.io/desired-replicas: 5
                deployment.kubernetes.io/max-replicas: 7
                deployment.kubernetes.io/revision: 1
Controlled By:  Deployment/hello-world
Replicas:       5 current / 5 desired
Pods Status:    5 Running / 0 Waiting / 0 Succeeded / 0 Failed
Pod Template:
  Labels:  app.kubernetes.io/name=load-balancer-example
           pod-template-hash=7dc74ff97c
  Containers:
   hello-world:
    Image:        gcr.io/google-samples/node-hello:1.0
    Port:         8080/TCP
    Host Port:    0/TCP
    Environment:  <none>
    Mounts:       <none>Create a Service object that exposes the deployment:
  Volumes:        <none>
Events:
  Type    Reason            Age    From                   Message
  ----    ------            ----   ----                   -------
  Normal  SuccessfulCreate  9m49s  replicaset-controller  Created pod: hello-world-7dc74ff97c-t89zb
  Normal  SuccessfulCreate  9m49s  replicaset-controller  Created pod: hello-world-7dc74ff97c-bcr9k
  Normal  SuccessfulCreate  9m49s  replicaset-controller  Created pod: hello-world-7dc74ff97c-g4rdg
  Normal  SuccessfulCreate  9m49s  replicaset-controller  Created pod: hello-world-7dc74ff97c-scs46
  Normal  SuccessfulCreate  9m49s  replicaset-controller  Created pod: hello-world-7dc74ff97c-nl4nl
$
```

#### Create a Service object that exposes the deployment:

```
$ kubectl expose deployment hello-world --type=LoadBalancer --name=my-service
service/my-service exposed
$ kubectl get services
NAME        TYPE          CLUSTER-IP    EXTERNAL-IP     PORT(S)          AGE
kubernetes  ClusterIP     10.100.0.1    <none>          443/TCP          47h
my-service  LoadBalancer  10.100.0.151  104.198.205.71  8080:32126/TCP   16s
$
```

> **Note:** The `type=LoadBalancer` service is backed by external cloud providers, which is not covered in this example, please refer to [this page](https://kubernetes.io/docs/concepts/services-networking/service/#loadbalancer) for the details.

> **Note:** If the external IP address is shown as <pending>, wait for a minute and enter the same command again.

"kubectl describe deployments hello-world"를 실행해도 IP에 대한 정보는 없습니다. 대신 아래의 명령어를 실행하면 IP주소가 보입니다.

```
$ kubectl describe services my-service
Name:                     my-service
  ...
Type:                     LoadBalancer
IP:                       10.3.245.137
LoadBalancer Ingress:     a1b23cd4567ef89gh12345i123j45k67-890123456lmn.amazonaws.com104.198.205.71
  ...
Port:                     <unset>  8080/TCP
TargetPort:               8080/TCP
NodePort:                 <unset>  32126/TCP
Endpoints:      10.0.0.6:8080,10.0.1.6:8080,10.0.1.7:8080 + 2 more...
  ...
$
```

이 서비스로 노출된 외부 IP주소 (LoadBalancer Ingress), Port, NodePort의 값이 중요합니다. 위의 경우 

| Key                  | Value          |
| -------------------- | -------------- |
| LoadBalancer Ingress | 104.198.205.71 |
| Port                 | 8080           |
| NodePort             | 32126          |

the service has several endpoints: 10.0.0.6:8080,10.0.1.6:8080,10.0.1.7:8080 + 2 more. These are internal addresses of the pods that are running the Hello World application. To verify these are pod addresses, enter this command:

```
$ kubectl get pods --output=wide
NAME                           ...   IP               NODE                                              ...
hello-world-7dc74ff97c-bcr9k   ...   192.168.24.199   ip-123-456-78-90.ap-northeast-2.compute.internal  ...
hello-world-7dc74ff97c-g4rdg   ...   192.168.79.237   ip-234-567-89-01.ap-northeast-2.compute.internal  ...
hello-world-7dc74ff97c-nl4nl   ...   192.168.72.155   ip-345-678-90-12.ap-northeast-2.compute.internal  ...
hello-world-7dc74ff97c-scs46   ...   192.168.25.181   ip-456-789-01-23.ap-northeast-2.compute.internal  ...
hello-world-7dc74ff97c-t89zb   ...   192.168.77.197   ip-567-890-12-23.ap-northeast-2.compute.internal  ...
$
```

Use the external IP address (LoadBalancer Ingress) to access the Hello World application:

curl http://<external-ip>:<port>

where `` is the external IP address (`LoadBalancer Ingress`) of your Service, and `` is the value of `Port` in your Service description.

```
$ curl http://a1b23cd4567ef89gh12345i123j45k67-890123456lmn.amazonaws.com:8080
Hello Kubernetes!(base) 
$
```

Cleaning up

```
$ kubectl get deployments --show-labels
NAME          READY   UP-TO-DATE   AVAILABLE   AGE   LABELS
hello-world   5/5     5            5           51m   app.kubernetes.io/name=load-balancer-example
$ kubectl delete deployment hello-world
deployment.extensions "hello-world" deleted
$
```

