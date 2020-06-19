```
$ kubectl get nodes
NAME                                           STATUS   ROLES    AGE   VERSION
ip-123-456-78-90.us-west-2.compute.internal    Ready    <none>   22h   v1.15.10-eks-bac369
ip-123-456-71-234.us-west-2.compute.internal   Ready    <none>   22h   v1.15.10-eks-bac369
$
```

```
$ kubectl -n kube-system get po
NAME                                   READY   STATUS    RESTARTS   AGE
aws-node-csfhg                         1/1     Running   0          22h
aws-node-lgc44                         1/1     Running   0          22h
coredns-86d5cbb4bd-gwbp9               1/1     Running   0          22h
coredns-86d5cbb4bd-qnblq               1/1     Running   0          22h
kube-proxy-jfxb5                       1/1     Running   0          22h
kube-proxy-vqr42                       1/1     Running   0          22h
metrics-server-6bdf64df8c-nqljs        1/1     Running   0          72m
nvidia-device-plugin-daemonset-l28gc   1/1     Running   0          21h
nvidia-device-plugin-daemonset-v4gjt   1/1     Running   0          21h
$
```

