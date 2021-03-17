

# `kubeadm join`의 Full Message

```bash
$ kubeadm join 192.168.0.33:6443 --token 4yeuuf.fuugdz7wmm0gkago  --discovery-token-ca-cert-hash sha256:cc2db7078ea7038b273d3790927e6b79fca307c9151fcb1386ed02ceaa18e354
[preflight] Running pre-flight checks
        [WARNING Service-Docker]: docker service is not active, please run 'systemctl start docker.service'
        [WARNING IsDockerSystemdCheck]: detected "cgroupfs" as the Docker cgroup driver. The recommended driver is "systemd". Please follow the guide at https://kubernetes.io/docs/setup/cri/
        [WARNING FileContent--proc-sys-net-bridge-bridge-nf-call-iptables]: /proc/sys/net/bridge/bridge-nf-call-iptables does not exist
[preflight] The system verification failed. Printing the output from the verification:
KERNEL_VERSION: 4.4.0-197-generic
DOCKER_VERSION: 20.10.1
OS: Linux
CGROUPS_CPU: enabled
CGROUPS_CPUACCT: enabled
CGROUPS_CPUSET: enabled
CGROUPS_DEVICES: enabled
CGROUPS_FREEZER: enabled
CGROUPS_MEMORY: enabled
CGROUPS_PIDS: enabled
CGROUPS_HUGETLB: enabled
        [WARNING SystemVerification]: this Docker version is not on the list of validated versions: 20.10.1. Latest validated version: 19.03
        [WARNING SystemVerification]: failed to parse kernel config: unable to load kernel module: "configs", output: "", err: exit status 1
error execution phase preflight: couldn't validate the identity of the API Server: could not find a JWS signature in the cluster-info ConfigMap for token ID "4yeuuf"
To see the stack trace of this error execute with --v=5 or higher
RTNETLINK answers: File exists
$
```

