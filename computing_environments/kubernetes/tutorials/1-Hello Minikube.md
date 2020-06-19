# 1. [Hello Minikube](https://kubernetes.io/docs/tutorials/hello-minikube/)

A simple Hello World Node.js app on Kubernetes using [Minikube](https://kubernetes.io/docs/setup/learning-environment/minikube) and Katacoda. Katacoda provides a free, in-browser Kubernetes environment.

- [Objectives](https://kubernetes.io/docs/tutorials/hello-minikube/#objectives)
- [Before you begin](https://kubernetes.io/docs/tutorials/hello-minikube/#before-you-begin)
- [Create a Minikube cluster](https://kubernetes.io/docs/tutorials/hello-minikube/#create-a-minikube-cluster)
- [Create a Deployment](https://kubernetes.io/docs/tutorials/hello-minikube/#create-a-deployment)
- [Create a Service](https://kubernetes.io/docs/tutorials/hello-minikube/#create-a-service)
- [Enable addons](https://kubernetes.io/docs/tutorials/hello-minikube/#enable-addons)
- [Clean up](https://kubernetes.io/docs/tutorials/hello-minikube/#clean-up)

이전: [eksctl로 AWS에 EKS 클러스터 만들기](../how_to/create a kubernetes cluster with eksctl.md)

다음: [TODO] Go all the through 3-Configuration.md

------

[TODO] Summarize what's done.

```
start.sh
$
$ start.sh
Starting Kubernetes...minikube version: v1.8.1
commit: cbda04cf6bbe65e987ae52bb393c10099ab62014

* minikube v1.8.1 on Ubuntu 18.04
* Using the none driver based on user configuration
* Running on localhost (CPUs=2, Memory=2460MB, Disk=145651MB) ...
* OS release is Ubuntu 18.04.4 LTS
* Preparing Kubernetes v1.17.3 on Docker 19.03.6 ...
  - kubelet.resolv-conf=/run/systemd/resolve/resolv.conf
* Launching Kubernetes ...
* Enabling addons: default-storageclass, storage-provisioner
* Configuring local host environment ...
* Done! kubectl is now configured to use "minikube"
* The 'dashboard' addon is enabled
  Kubernetes Started
  $ 
```





$ minikube dashboard

* Verifying dashboard health ...
* Launching proxy ...
* Verifying proxy health ...
  http://127.0.0.1:39933/api/v1/namespaces/kubernetes-dashboard/services/http:kubernetes-dashboard:/proxy/

^C
$ kubectl create deployment hello-node --image=gcr.io/hello-minikube-zero-install/hello-node
deployment.apps/hello-node created
$ kubectl get deployments
NAME         READY   UP-TO-DATE   AVAILABLE   AGE
hello-node   1/1     1            1           14s

$

```
$ kubectl get pods
NAME                          READY   STATUS    RESTARTS   AGE
hello-node-7676b5fb8d-lt4pk   1/1     Running   0          32s
$ kubectl get events
LAST SEEN   TYPE     REASON                    OBJECT                             MESSAGE
54s         Normal   Scheduled                 pod/hello-node-7676b5fb8d-lt4pk    Successfully assigned default/hello-node-7676b5fb8d-lt4pk to minikube
53s         Normal   Pulling                   pod/hello-node-7676b5fb8d-lt4pk    Pulling image "gcr.io/hello-minikube-zero-install/hello-node"
53s         Normal   Pulled                    pod/hello-node-7676b5fb8d-lt4pk    Successfully pulled image "gcr.io/hello-minikube-zero-install/hello-node"
53s         Normal   Created                   pod/hello-node-7676b5fb8d-lt4pk    Created container hello-node
52s         Normal   Started                   pod/hello-node-7676b5fb8d-lt4pk    Started container hello-node
54s         Normal   SuccessfulCreate          replicaset/hello-node-7676b5fb8d   Created pod: hello-node-7676b5fb8d-lt4pk
54s         Normal   ScalingReplicaSet         deployment/hello-node              Scaled up replica set hello-node-7676b5fb8d to 1
4m41s       Normal   NodeHasSufficientMemory   node/minikube                      Node minikube status is now: NodeHasSufficientMemory
4m41s       Normal   NodeHasNoDiskPressure     node/minikube                      Node minikube status is now: NodeHasNoDiskPressure
4m41s       Normal   NodeHasSufficientPID      node/minikube                      Node minikube status is now: NodeHasSufficientPID
4m27s       Normal   Starting                  node/minikube                      Starting kubelet.
4m27s       Normal   NodeHasSufficientMemory   node/minikube                      Node minikube status is now: NodeHasSufficientMemory
4m27s       Normal   NodeHasNoDiskPressure     node/minikube                      Node minikube status is now: NodeHasNoDiskPressure
4m27s       Normal   NodeHasSufficientPID      node/minikube                      Node minikube status is now: NodeHasSufficientPID
4m27s       Normal   NodeAllocatableEnforced   node/minikube                      Updated Node Allocatable limit across pods
4m24s       Normal   RegisteredNode            node/minikube                      Node minikube event: Registered Node minikube in Controller
4m22s       Normal   Starting                  node/minikube                      Starting kube-proxy.
4m17s       Normal   NodeReady                 node/minikube                      Node minikube status is now: NodeReady
$
```

