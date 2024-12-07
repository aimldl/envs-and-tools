* Draft: 2020-08-03 (Mon)

# Connect to a Cluster Node via SSH

[Using SSH to connect to a cluster node](https://cloud.google.com/anthos/gke/docs/on-prem/how-to/ssh-cluster-node#before_you_begin)

Let's try to understand this command.
[Using SSH to connect to an admin cluster node](https://cloud.google.com/anthos/gke/docs/on-prem/how-to/ssh-cluster-node#admin)
```
kubectl --kubeconfig [ADMIN_CLUSTER_KUBECONFIG] get secrets -n kube-system sshkeys \
-o jsonpath='{.data.vsphere_tmp}' | base64 -d > \
~/.ssh/admin-cluster.key && chmod 600 ~/.ssh/admin-cluster.key
```

```bash
$ ADMIN_CLUSTER_KUBECONFIG='/home/k8smaster/.kube/config'
$ kubectl --kubeconfig $ADMIN_CLUSTER_KUBECONFIG get secretsNAME                  TYPE                                  DATA   AGE
default-token-j2vpf   kubernetes.io/service-account-token   3      7d
$
```

```bash
$ kubectl --kubeconfig $ADMIN_CLUSTER_KUBECONFIG get secrets -n kube-system
NAME                                             TYPE                                  DATA   AGE
attachdetach-controller-token-f6bdv              kubernetes.io/service-account-token   3      7d1h
bootstrap-signer-token-zwxmq                     kubernetes.io/service-account-token   3      7d1h
calico-kube-controllers-token-2xxk8              kubernetes.io/service-account-token   3      7d1h
calico-node-token-4jzvg                          kubernetes.io/service-account-token   3      7d1h
certificate-controller-token-v9zsl               kubernetes.io/service-account-token   3      7d1h
clusterrole-aggregation-controller-token-wcb97   kubernetes.io/service-account-token   3      7d1h
coredns-token-tpns8                              kubernetes.io/service-account-token   3      7d1h
cronjob-controller-token-jspjk                   kubernetes.io/service-account-token   3      7d1h
daemon-set-controller-token-257fh                kubernetes.io/service-account-token   3      7d1h
default-token-7ctb6                              kubernetes.io/service-account-token   3      7d1h
deployment-controller-token-5lck4                kubernetes.io/service-account-token   3      7d1h
disruption-controller-token-z222b                kubernetes.io/service-account-token   3      7d1h
endpoint-controller-token-977l4                  kubernetes.io/service-account-token   3      7d1h
endpointslice-controller-token-7fdrk             kubernetes.io/service-account-token   3      7d1h
expand-controller-token-nshvc                    kubernetes.io/service-account-token   3      7d1h
generic-garbage-collector-token-vf4q6            kubernetes.io/service-account-token   3      7d1h
horizontal-pod-autoscaler-token-wbfkd            kubernetes.io/service-account-token   3      7d1h
job-controller-token-nb5zl                       kubernetes.io/service-account-token   3      7d1h
kube-proxy-token-p78t9                           kubernetes.io/service-account-token   3      7d1h
namespace-controller-token-9mkr6                 kubernetes.io/service-account-token   3      7d1h
node-controller-token-zmhmj                      kubernetes.io/service-account-token   3      7d1h
persistent-volume-binder-token-w7g9d             kubernetes.io/service-account-token   3      7d1h
pod-garbage-collector-token-hsxk2                kubernetes.io/service-account-token   3      7d1h
pv-protection-controller-token-tdk2t             kubernetes.io/service-account-token   3      7d1h
pvc-protection-controller-token-zz8t4            kubernetes.io/service-account-token   3      7d1h
replicaset-controller-token-ff2sb                kubernetes.io/service-account-token   3      7d1h
replication-controller-token-fmz2h               kubernetes.io/service-account-token   3      7d1h
resourcequota-controller-token-49zjt             kubernetes.io/service-account-token   3      7d1h
service-account-controller-token-lmfr8           kubernetes.io/service-account-token   3      7d1h
service-controller-token-6rrrk                   kubernetes.io/service-account-token   3      7d1h
statefulset-controller-token-vg2js               kubernetes.io/service-account-token   3      7d1h
token-cleaner-token-rfbk5                        kubernetes.io/service-account-token   3      7d1h
ttl-controller-token-rt26k                       kubernetes.io/service-account-token   3      7d1h
$
```
```bash
$ kubectl --kubeconfig $ADMIN_CLUSTER_KUBECONFIG get secrets -n kube-system sshkeys
Error from server (NotFound): secrets "sshkeys" not found
$ 
```
