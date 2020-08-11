* Draft: 2020-08-11 (Tue)

# How to Install Kubernetes Both on the Control Plane and a Node in the Same Machine

## Google search
* kubernetes install control plane and node in the same computer

[Will (can) Kubernetes run Docker containers on the master node(s)?](https://stackoverflow.com/questions/27832984/will-can-kubernetes-run-docker-containers-on-the-master-nodes)

```
There is nothing preventing you from creating a cluster where the same machine (physical or virtual) runs both the kubernetes master software and a kubelet, but the current cluster provisioning scripts separate the master onto a distinct machine. 
```

```
You need to taint your master node to run containers on it, although not recommended.
Run this on your master node:

  kubectl taint nodes --all node-role.kubernetes.io/master-

Courtesy of Alex Ellis' blog post here.
```
