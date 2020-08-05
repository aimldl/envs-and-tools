* Draft: 2020-08-05 (Wed)

# Use an On-Premise Kubernetes Cluster

## Overview

In the following parts, the `kubectl` command is the key command to control the Kubernetes cluster as the name of the command indicates.

> Kubernetes control → kubectl

Assuming the Kubernetes cluster is installed and configured properly, a computer is configured and used to remote-access the cluster. In other words, this computer you are using to read this tutorial is configured and used to remote-access the cluster.

[TODO: add a figure with a computer and a cluster]

## The major difference in the `kubectl` command

The major difference in the `kubectl` command is to

​	**use the `--kubeconfig` option to specify the location of `admin.conf`**

Instead of,

```bash
$ kubectl get nodes
```

use

```bash
$ kubectl get nodes --kubeconfig ~/.kube/admin.conf
```

Equivalently,

```bash
$ kubectl --kubeconfig ~/.kube/admin.conf get nodes 
```

## Configure to remote-access from your computer

The configuration process of the remote-accessing computer is summarized into two steps.

**Step 1. Install `kubectl` in your computer.**

**Step 2. Copy `admin.conf` from a master to your computer.**

Copy `/etc/kubernetes/admin.conf` in the control plane (or master) of the cluster to your computer. Say copy `admin.conf` to the `~/.kube` directory resulting in `~/.kube/admin.conf`.

`admin.conf` contains the information necessary to access the cluster.

## How not to use the `--kubeconfig` option

It is cumbersome to add `--kubeconfig ~/.kube/admin.conf` in every  `kubectl`  command. It is possible to omit this option if you put the information of  `admin.conf` to the default `config` file.

After the change, the `kubectl` command works without the `--kubeconfig` option. Yay!

```bash
$ kubectl get nodes
NAME                            STATUS   ROLES    AGE   VERSION
k8smaster-alienware-aurora-r6   Ready    master   8d    v1.18.6
k8snode01-alienware-aurora-r7   Ready    <none>   8d    v1.18.6
k8snode02-alienware-aurora-r7   Ready    <none>   8d    v1.18.6
$
```

When a `kubectl` command is executed, the default configuration is read in the background. In the following part, let's edit the default `config` file.

### Case 1: If the `config` file does not exit.

```bash
$ ls ~/.kube
admin.conf
$
```

Use `admin.conf` as the `config` file.

```bash
$ cp admin.conf config
$ ls ~/.kube
admin.conf  config
$
```

Then `kubectl` can access the cluster. To check the nodes in the cluster, run:

```bash
$ kubectl get nodes
NAME                            STATUS   ROLES    AGE   VERSION
k8smaster-alienware-aurora-r6   Ready    master   9d    v1.18.6
k8snode01-alienware-aurora-r7   Ready    <none>   8d    v1.18.6
k8snode02-alienware-aurora-r7   Ready    <none>   9d    v1.18.6
$
```

### Case 2: The existing `config` file is empty.

```bash
$ ls ~/.kube
admin.conf  config
$
```

Let's say the `config` file exists, but it's either empty or meaningless. Simply, overwrite the existing `config` file.

#### Step 1. Back up the existing `config` file to `config.backup`

```bash
$ mv config config.backup
```

#### Step 2. Use `admin.conf` as the `config` file. 

```bash
$ cp admin.conf config
$ ls ~/.kube
admin.conf  config
$
```

This is the same as case 1. The `kubectl` command works just as good as case 1.

```bash
$ kubectl get nodes
NAME                            STATUS   ROLES    AGE   VERSION
k8smaster-alienware-aurora-r6   Ready    master   9d    v1.18.6
k8snode01-alienware-aurora-r7   Ready    <none>   8d    v1.18.6
k8snode02-alienware-aurora-r7   Ready    <none>   9d    v1.18.6
$
```

### Case 3: The existing `config` file has multiple cluster information.

When multiple clusters with corresponding context and user information exist in the `config` file, the `config` file looks like below. The following example has a cluster named `adorable-creature-1586077260.ap-northeast-2.eksctl.io`. 

```yaml
apiVersion: v1
clusters:
- cluster:
  certificate-authority-data: ...
    server: https://864506417098CA502E6771E934C9BCCC.yl4.ap-northeast-2.eks.amazonaws.com
  name: adorable-creature-1586077260.ap-northeast-2.eksctl.io
    ...
contexts:
- contexts:
  - context:
    cluster: ...
      ...
current-context: aimldl@wonderful-painting-1587560462.us-west-2.eksctl.io
kind: Config
preferences: {}
users:
- name: aimldl@adorable-creature-1586077260.ap-northeast-2.eksctl.io
  user:
    exec:
      apiVersion: client.authentication.k8s.io/v1alpha1
      args:
      - eks
      - get-token
      - --cluster-name
      - adorable-creature-1586077260
      - --region
      - ap-northeast-2
      command: aws
      env: null
  ...
```

In `admin.conf`, the information on cluster, context, and user looks like below.

```yaml
- cluster:
  certificate-authority-data: a1B2c ... 0Z
  server: https://123.456.7.890:6443
  name: kubernetes

- context:
    cluster: kubernetes
    user: kubernetes-admin
  name: kubernetes-admin@kubernetes

- name: kubernetes-admin
  user:
    client-certificate-data: b0C1 ... =a
    client-key-data: C1d2 ... 0B
```

Add these information to the `config` file and change `current-context` to `kubernetes-admin@kubernetes` which is the context name in `admin.conf`. The new `config` file looks like below.

```yaml
apiVersion: v1
clusters:
- cluster:
  certificate-authority-data: a1B2c ... 0Z
  server: https://123.456.7.890:6443
  name: kubernetes
- cluster:
  certificate-authority-data: ...
    server: https://864506417098CA502E6771E934C9BCCC.yl4.ap-northeast-2.eks.amazonaws.com
  name: adorable-creature-1586077260.ap-northeast-2.eksctl.io
    ...
contexts:
- context:
    cluster: kubernetes
    user: kubernetes-admin
  name: kubernetes-admin@kubernetes
- contexts:
  - context:
    cluster: ...
      ...
current-context: kubernetes-admin@kubernetes
kind: Config
preferences: {}
users:
- name: kubernetes-admin
  user:
    client-certificate-data: b0C1 ... =a
    client-key-data: C1d2 ... 0B
- name: aimldl@adorable-creature-1586077260.ap-northeast-2.eksctl.io
  user:
    exec:
      apiVersion: client.authentication.k8s.io/v1alpha1
      args:
      - eks
      - get-token
      - --cluster-name
      - adorable-creature-1586077260
      - --region
      - ap-northeast-2
      command: aws
      env: null
  ...
```

Notice `current-context` has been changed from the old context name `aimldl@wonderful-painting-1587560462.us-west-2.eksctl.io` to a new one `kubernetes-admin@kubernetes`. This part is important because `current-context` can be used to switch from cluster to cluster specified in the `config` file.

Again, run a `kubectl` command to verify the access to the cluster.

```bash
$ kubectl get nodes
NAME                            STATUS   ROLES    AGE   VERSION
k8smaster-alienware-aurora-r6   Ready    master   9d    v1.18.6
k8snode01-alienware-aurora-r7   Ready    <none>   8d    v1.18.6
k8snode02-alienware-aurora-r7   Ready    <none>   9d    v1.18.6
$
```

