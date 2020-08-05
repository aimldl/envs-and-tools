* Draft: 2020-08-05 (Wed)

# How to Monitor Resources (CPU & Memory)

## Google search

```text
kubernetes cpu memory usage
how to monitor kubernetes cpu memory
```

[Tools for Monitoring Resources](cloud.google.com/tpu), Official Kubernetes Documentation

[Managing Resources for Containers](https://kubernetes.io/docs/concepts/configuration/manage-resources-containers/), Official Kubernetes Documentation

[How To Monitor Kubernetes With Prometheus](https://phoenixnap.com/kb/prometheus-kubernetes-monitoring), 2020-02-24, phoenixNAP

[Kubernetes Metrics Server](https://github.com/kubernetes-sigs/metrics-server), github repository

[Checking kubernetes pod CPU and memory](https://stackoverflow.com/questions/54531646/checking-kubernetes-pod-cpu-and-memory), stackoverflow



(base) aimldl@Home-Laptop:~/github/private/k8s_cluster/auto_ml$ cat monitor_k8s_cluster_nodes 

```bash
#!/bin/bash
# monitor_k8s_cluster_nodes
# 
# * Draft: 2020-07-30 (Thu)
#
# k8s_cluster_nodes.list
#   is a text file with a list of target IP addresses
#   An IP address is stored each line.
#
# fping send ICMP (Internet Control Message Protocol) echo request to network hosts
#   and returns either alive or unreachable.

FILE_NODES_LIST='k8s_cluster_nodes.list'

fping < $FILE_NODES_LIST
```

