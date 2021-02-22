* Rev.1: 2020-04-06 (Mon)
* Draft: 2020-04-02 (Thu)

# Kubernetes

## 설치 환경 준비하기

[Kubeflow releases page](https://github.com/kubeflow/kfctl/releases/tag/v1.0.1).

## [Tutorials](https://kubernetes.io/docs/tutorials/)

* [Using kubectl to Create a Deployment](https://kubernetes.io/docs/tutorials/kubernetes-basics/deploy-app/deploy-intro/)

* [Cluster API: Manage your Kubernetes clusters in a Kubernetes-native way](https://developer.ibm.com/articles/cluster-api-manage-your-kubernetes-cluster-in-a-kubernetes-way/)

* [Itaú Unibanco: How we built a CI/CD Pipeline for machine learning with online training in Kubeflow](https://cloud.google.com/blog/products/ai-machine-learning/itau-unibanco-how-we-built-a-cicd-pipeline-for-machine-learning-with-online-training-in-kubeflow)

<img src="https://storage.googleapis.com/gweb-cloudblog-publish/images/Itau_concrete_architecture.max-700x700.png">





```bash
Kubernetes Bootcamp Terminal

$
$ minikube version
minikube version: v1.8.1
commit: cbda04cf6bbe65e987ae52bb393c10099ab62014
$ minikube start
* minikube v1.8.1 on Ubuntu 18.04
* Using the none driver based on user configuration
* Running on localhost (CPUs=2, Memory=2460MB, Disk=145651MB) ...
* OS release is Ubuntu 18.04.4 LTS
* Preparing Kubernetes v1.17.3 on Docker 19.03.6 ...
  - kubelet.resolv-conf=/run/systemd/resolve/resolv.conf
* Launching Kubernetes ...
* Enabling addons: default-storageclass, storage-provisioner
* Configuring local host environment ...
* Waiting for cluster to come online ...
* Done! kubectl is now configured to use "minikube"
$ minikube version
minikube version: v1.8.1
commit: cbda04cf6bbe65e987ae52bb393c10099ab62014
$ kubectl cluster-info
Kubernetes master is running at https://172.17.0.18:8443
KubeDNS is running at https://172.17.0.18:8443/api/v1/namespaces/kube-system/services/kube-dns:dns/proxy

To further debug and diagnose cluster problems, use 'kubectl cluster-info dump'.
$ kubectl get nodes
NAME       STATUS   ROLES    AGE     VERSION
minikube   Ready    master   2m12s   v1.17.3
$
```



## Selected References

[kubectl](https://kubernetes.io/docs/reference/kubectl/kubectl/)

[Overview of kubectl](https://kubernetes.io/docs/reference/kubectl/overview/)

[kubectl - Cheat Sheet](https://kubernetes.io/docs/reference/kubectl/cheatsheet/)

[kubectl Command Reference](https://kubernetes.io/docs/reference/generated/kubectl/kubectl-commands)

[kubectl for Docker Users](https://kubernetes.io/docs/reference/kubectl/docker-cli-to-kubectl/)

------

다음: [AWS를 이용해서 Kubernetes 설치하기](INSTALL-Amazon_EKS.md)

