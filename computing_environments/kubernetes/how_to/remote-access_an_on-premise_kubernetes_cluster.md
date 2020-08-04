* Draft: 2020-08-03 (Mon)

# How to Remote-Access an On-Premise Kubernetes Cluster
A Kunernetes cluster on the on-premise computers was set up successfully. The cluster consists of one master and two worker nodes. I want to remote-access the cluster from a laptop. But how?

## Summary

Step 1. Copy a file `/etc/kubernetes/admin.conf` from a master to the laptop.

Any directory is fine, but I would save it to the `~/.kube` directory .

Step 2. Specify this file as the configuration file.

For example,

```bash
$ kubectl --kubeconfig ~/.kube/admin.conf get nodes
```

Instead of

```bash
$ kubectl get nodes
```

## Background Knowledge
Remote-access to a Kubernetes cluster requires two pieces of information:
* the location of the `apiserver`
* the credential to access it.

Notice the `apiserver` is the front end for the Kubernetes control plane. So remote-access to the `apiserver` is the same as remote-accessing to the Kubernetes cluster. For details, refer to [Kubernetes Components](https://kubernetes.io/docs/concepts/overview/components/).

<img src="images/components-of-kubernetes.png">

## Remote-accessing to a Kubernetes cluster on a public cloud
* Remote-accessing to a public cloud like [GKS](https://cloud.google.com/kubernetes-engine) or [Amazon EKS](https://aws.amazon.com/eks/?nc1=h_ls) is relatively easy.
* Everything is configured during the installation process.
* The `kubectl` command handles both the location and credentials. (Assuming `kubectl` is installed and configured on the laptop.)
```bash
$ kubectl config view
```
returns the location and credentials that kubectl knows. For example,
```bash
apiVersion: v1
clusters:
- cluster:
    certificate-authority-data: DATA+OMITTED
    server: https://F98EB9AFA2363EC799857C1523C4C0A2.gr7.us-west-2.eks.amazonaws.com
  name: eks-kubeflow.us-west-2.eksctl.io
current-context: aimldl@eks-kubeflow.us-west-2.eksctl.io
kind: Config
preferences: {}
users:
- name: aimldl@eks-kubeflow.us-west-2.eksctl.io
  user:
    exec:
      apiVersion: client.authentication.k8s.io/v1alpha1
      args:
      - token
      - -i
      - eks-kubeflow
      command: aws-iam-authenticator
      env:
      - name: AWS_STS_REGIONAL_ENDPOINTS
        value: regional
      - name: AWS_DEFAULT_REGION
        value: us-west-2
```
The above `config` file is configured to access a cluster named `eks-kubeflow.us-west-2.eksctl.io`. Specifically, the `apiserver` is located at:

https://F98EB9AFA2363EC799857C1523C4C0A2.gr7.us-west-2.eks.amazonaws.com

Note the output consists of several parts. 

```text
apiVersion: v1
clusters:
[cluster information]
current-context: [a name from users]
kind: Config
preferences: {}
users:
[user information]
```

If multiple clusters are set up, multiple `cluster information` and `user information` exist under `clusters` and `users` while the current cluster is specified in `current-context`. Unless removed, those information remain stored in the `~/.kube/config` file.

`kubectl config` modifies kubeconfig files using subcommands like `kubectl config SUBCOMMAND`. For details, refer to [kubectl config](https://kubernetes.io/docs/reference/generated/kubectl/kubectl-commands#config) and [Kubectl Context and Configuration](https://kubernetes.io/docs/reference/kubectl/cheatsheet/#kubectl-context-and-configuration).

```bash
$ kubectl config current-context
aimldl@eks-kubeflow.us-west-2.eksctl.io
$
```

```bash
$ kubectl config get-contexts
CURRENT   NAME                                     CLUSTER                           
          AUTHINFO                                 NAMESPACE
*         aimldl@eks-kubeflow.us-west-2.eksctl.io  eks-kubeflow.us-west-2.eksctl.io  
          aimldl@eks-kubeflow.us-west-2.eksctl.io
$ 
```

## Remote-accessing to a Kubernetes cluster of on-premise computers
* Remote-access to an on-premise Kubernetes is trickier than that to a public cloud.
* It is simply because no good cookbook tutorial was found on the web.
  * Most books on Kubernetes assumes a public cloud: Google GCP, Amazon EKS, Microsoft AKS, etc.
  * The same is true for many web articles.
  * Google search results show parts of Kubernetes official document. I feel it's necessary to reorganize those information.

### Google search: remote-access Kubernetes master on-premise
* [Accessing Clusters](https://kubernetes.io/docs/tasks/access-application-cluster/access-cluster/)
  * `kubectl` handles locating and authenticating to the `apiserver`.
  * You should access the `apiserver` in the Kubernetes Control Plane.
* [Directly accessing the REST API](https://kubernetes.io/docs/tasks/access-application-cluster/access-cluster/#directly-accessing-the-rest-api)
  * To locate and authenticate, you may or may not use the `kubectl proxy` command.
    * [Using kubectl proxy](https://kubernetes.io/docs/tasks/access-application-cluster/access-cluster/#using-kubectl-proxy) is the recommended approach.
      * `kubectl proxy` creates a proxy server or application-level gateway between localhost and the Kubernetes API Server.
        * All incoming data enters through one port and gets forwarded to the remote Kubernetes API Server port, except for the path matching the static content path.
        * For details, refer to [kubectl proxy](https://kubernetes.io/docs/reference/generated/kubectl/kubectl-commands#proxy).
    * [Without kubectl proxy](https://kubernetes.io/docs/tasks/access-application-cluster/access-cluster/#without-kubectl-proxy) is the alternative approach.
      * Access the REST API with an http client such as `curl`, `wget`, or a web browser.

## The recommended approach: `kubectl proxy --port 8080`
`kubectl proxy` uses the location and authentication information stored in `~/.kube/config` of the control plane. First, run either:

```bash
$ kubectl proxy --port=8080
# or
$ kubectl proxy --port 8080
```
and the expected output is
```bash
Starting to serve on 127.0.0.1:8080
```

### Retrieve the location information
#### `kubectl cluster-info`
```bash
$ kubectl cluster-info
Kubernetes master is running at https://123.456.7.890:6443
KubeDNS is running at https://123.456.7.890:6443/api/v1/namespaces/kube-system/services/kube-dns:dns/proxy

To further debug and diagnose cluster problems, use 'kubectl cluster-info dump'.
$
```
For details, refer to [Accessing Dashboard](https://github.com/kubernetes/dashboard/blob/master/docs/user/accessing-dashboard/README.md).

#### With `kubectl proxy` and `curl`
In another terminal, run:
```bash
$ curl http://localhost:8080/api/
```
and the output looks something like:
```bash
{
  "kind": "APIVersions",
  "versions": [
    "v1"
  ],
  "serverAddressByClientCIDRs": [
    {
      "clientCIDR": "0.0.0.0/0",
      "serverAddress": "123.456.7.890:6443"
    }
  ]
}
```
Notice `serverAddress` includes the location information `123.456.7.890:6443`.

## The alternative approach: `kubectl config view`
```bash
$ kubectl config view
```
shows the location and authentication information stored in `~/.kube/config`. For example,
```bash
apiVersion: v1
clusters:
- cluster:
    certificate-authority-data: DATA+OMITTED
    server: https://123.456.7.890:6443
  name: kubernetes
contexts:
- context:
    cluster: kubernetes
    user: kubernetes-admin
  name: kubernetes-admin@kubernetes
current-context: kubernetes-admin@kubernetes
kind: Config
preferences: {}
users:
- name: kubernetes-admin
  user:
    client-certificate-data: REDACTED
    client-key-data: REDACTED
$
```

#### Retrieve the `apiserver` location information from `kubectl config view`
Run either:
  ```bash
  $ kubectl config view | grep server | sed -e 's/^[ ]*server:[ ]//'
  # or
  $ kubectl config view --minify | grep server | cut -f 2- -d ":" | tr -d
  ```
to extract the location information in: "    server: https://123.456.7.890:6443". And the output looks something like `https://123.456.7.890:6443`.
  * `https://123.456.7.890` is the IP address
  * `6443` is the port number.

### Retrieve the credential
To get the token, run either:
```bash
$ kubectl -n kube-system describe $(kubectl -n kube-system get secret -n kube-system -o name | grep namespace) | grep ^token | sed -e 's/^token:[ ]*//'
# or
$ kubectl describe secret $(kubectl get secrets | grep ^default | cut -f1 -d ' ') | grep -E '^token' | cut -f2 -d':' | tr -d " "
```
Equivalently, break down the above commands into:
```bash
$ SECRET_NAME=$(kubectl -n kube-system get secret -n kube-system -o name | grep namespace)
$ kubectl -n kube-system describe $SECRET_NAME | grep ^token | sed -e 's/^token:[ ]*//'
# or 
$ SECRET_NAME=$(kubectl get secrets | grep ^default | cut -f1 -d ' ')
$ kubectl describe secret $SECRET_NAME | grep -E '^token' | cut -f2 -d':' | tr -d " "
```

#### Accessing the `apiserver` with token
The following commands returns the equivalent the output described in "With `kubectl proxy` and `curl`". However the use of the `--insecure` flag leaves it subject to MITM attacks.
```bash
$ APISERVER=$(kubectl config view --minify | grep server | cut -f 2- -d ":" | tr -d " ")
$ SECRET_NAME=$(kubectl get secrets | grep ^default | cut -f1 -d ' ')
$ TOKEN=$(kubectl describe secret $SECRET_NAME | grep -E '^token' | cut -f2 -d':' | tr -d " ")
$ curl $APISERVER/api --header "Authorization: Bearer $TOKEN" --insecure
```
That is,
```bash
{
  "kind": "APIVersions",
  "versions": [
    "v1"
  ],
  "serverAddressByClientCIDRs": [
    {
      "clientCIDR": "0.0.0.0/0",
      "serverAddress": "123.456.7.890:6443"
    }
  ]
}
```


## The alternative approach: access the REST API with an http client
* web browser
* curl
* wget
can be used to provide the location and credentials directly to the HTTP client.

Using kubectl proxy
```bash
$ kubectl proxy --port=8080
Starting to serve on 127.0.0.1:8080
```
Running the above command handles locating the apiserver and authenticating. 
With this command, you can explore the API with a browser, curl, or wget.

## Miscellaneous
Remote-accessing a cluster is possible in Go and Python as Kubernetes officially supports Go and Python client libraries. The following topics in [Accessing Clusters](https://kubernetes.io/docs/tasks/access-application-cluster/access-cluster/) will not be covered in this document. Read the links if necessary.
* [Programmatic access to the API](https://kubernetes.io/docs/tasks/access-application-cluster/access-cluster/#programmatic-access-to-the-api)
* [Accessing the API from a Pod](https://kubernetes.io/docs/tasks/access-application-cluster/access-cluster/#accessing-the-api-from-a-pod)
* [Accessing services running on the cluster](https://kubernetes.io/docs/tasks/access-application-cluster/access-cluster/#accessing-services-running-on-the-cluster)
* [Requesting redirects](https://kubernetes.io/docs/tasks/access-application-cluster/access-cluster/#requesting-redirects)

## Configuration

None of the above articles mentions how to set up a laptop. But a hint was found in [Accessing Clusters](https://kubernetes.io/docs/tasks/access-application-cluster/access-cluster/)

> # [Accessing Clusters](https://kubernetes.io/docs/tasks/access-application-cluster/access-cluster/)
>
> This topic discusses multiple ways to interact with clusters.
>
> ## Accessing for the first time with kubectl
>
> When accessing the Kubernetes API for the first time, we suggest using the Kubernetes CLI, `kubectl`.
>
> To access a cluster, you need to know the location of the cluster and have credentials to access it. Typically, this is automatically set-up when you work through a [Getting started guide](https://kubernetes.io/docs/setup/), or someone else setup the cluster and provided you with credentials and a location.

[Getting started guide](https://kubernetes.io/docs/setup/) has so many documents which I've already "studied" a part of the documents. But I nailed it again. In [Creating a single control-plane cluster with kubeadm](https://kubernetes.io/docs/setup/production-environment/tools/kubeadm/create-cluster-kubeadm/#optional-controlling-your-cluster-from-machines-other-than-the-control-plane-node) > [(Optional) Controlling your cluster from machines other than the control-plane node](https://kubernetes.io/docs/setup/production-environment/tools/kubeadm/create-cluster-kubeadm/#optional-controlling-your-cluster-from-machines-other-than-the-control-plane-node), 

> **[(Optional) Controlling your cluster from machines other than the control-plane node](https://kubernetes.io/docs/setup/production-environment/tools/kubeadm/create-cluster-kubeadm/#optional-controlling-your-cluster-from-machines-other-than-the-control-plane-node)**
> In order to get a kubectl on some other computer (e.g. laptop) to talk to your cluster, you need to copy the administrator kubeconfig file from your control-plane node to your workstation like this:
>
> ```bash
> $ scp root@<control-plane-host>:/etc/kubernetes/admin.conf .
> $ kubectl --kubeconfig ./admin.conf get nodes
> ```

For the first command, `<control-plane-host>` is the IP address of the computer that the control plane is installed. In this example, `123.456.7.890:6443`. Well, the command fails as follows.

```bash
$ scp root@123.456.7.890:6443:/etc/kubernetes/admin.conf .
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@    WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!     @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
IT IS POSSIBLE THAT SOMEONE IS DOING SOMETHING NASTY!
Someone could be eavesdropping on you right now (man-in-the-middle attack)!
It is also possible that a host key has just been changed.
The fingerprint for the ECDSA key sent by the remote host is
SHA256:<key>.
Please contact your system administrator.
Add correct host key in /home/aimldl/.ssh/known_hosts to get rid of this message.
Offending ECDSA key in /home/aimldl/.ssh/known_hosts:5
  remove with:
  ssh-keygen -f "/home/aimldl/.ssh/known_hosts" -R "123.456.7.890"
ECDSA host key for 123.456.7.890 has changed and you have requested strict checking.
Host key verification failed.
$
```

The point of this command is to copy `admin.conf` from the control plane to the laptop. So I manually copied the file to the `~/.kube` directory. 

`/etc/kubernetes/admin.conf` located on the control plane looks like this.

```yaml
apiVersion: v1
clusters:
- cluster:
    certificate-authority-data: a1B2c ... 0Z
    server: https://123.456.7.890:6443
  name: kubernetes
contexts:
- context:
    cluster: kubernetes
    user: kubernetes-admin
  name: kubernetes-admin@kubernetes
current-context: kubernetes-admin@kubernetes
kind: Config
preferences: {}
users:
- name: kubernetes-admin
  user:
    client-certificate-data: a1B2c ... 0Z
    client-key-data: b0C1d ... 9z
```

* `a1B2c ... 0Z` and `b0C1d ... 9z` are lengthy keys.
* `https://123.456.7.890:6443` is the IP address and port number. 

Now running the second command works just fine. Yay!

```bash
$ kubectl --kubeconfig admin.conf get nodes
NAME                            STATUS   ROLES    AGE     VERSION
k8smaster-alienware-aurora-r6   Ready    master   7d20h   v1.18.6
k8snode01-alienware-aurora-r7   Ready    <none>   7d19h   v1.18.6
k8snode02-alienware-aurora-r7   Ready    <none>   7d20h   v1.18.6
$
```

Notice the above command is

```bash
$ kubectl get nodes
```

with the `--kubeconfig` option which specified the configuration file as the copied file `admin.conf`.

To summarize, the key is to copy `/etc/kubernetes/admin.conf` from the control plane to the laptop and use the `kubectl` command with the `--kubeconfig` option which specified the configuration file with the location and credential information. 

## References

* [Kubernetes Components](https://kubernetes.io/docs/concepts/overview/components/)
* [Accessing Clusters](https://kubernetes.io/docs/tasks/access-application-cluster/access-cluster/)
  * [Directly accessing the REST API](https://kubernetes.io/docs/tasks/access-application-cluster/access-cluster/#directly-accessing-the-rest-api)
* [Accessing Dashboard](https://github.com/kubernetes/dashboard/blob/master/docs/user/accessing-dashboard/README.md)
* kubectl
  * [Overview of kubectl](https://kubernetes.io/docs/reference/kubectl/overview/)
  * [kubectl Cheat Sheet](https://kubernetes.io/docs/reference/kubectl/cheatsheet/)
  * [kubectl proxy](https://kubernetes.io/docs/reference/generated/kubectl/kubectl-commands#proxy)
  * [kubectl config](https://kubernetes.io/docs/reference/generated/kubectl/kubectl-commands#config)
  * [Using kubectl proxy](https://kubernetes.io/docs/tasks/access-application-cluster/access-cluster/#using-kubectl-proxy)
  * [Without kubectl proxy](https://kubernetes.io/docs/tasks/access-application-cluster/access-cluster/#without-kubectl-proxy)

