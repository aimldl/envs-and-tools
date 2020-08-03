* Draft: 2020-08-03 (Mon)

# How to Remote-Access an On-Premise Kubernetes Cluster
A Kunernetes cluster on my on-premiss computers is set up successfully. The cluster consists of one master and two worker nodes. 
I want to remote-access the cluster from a laptop. But how?

## Background Knowledge
Remote-accessing to a Kubernetes cluster requires two pieces of information:
* the location of the `apiserver`
* the credential to access it.

Notice the `apiserver` is the front end for the Kubernetes control plane. For details, refer to [Kubernetes Components](https://kubernetes.io/docs/concepts/overview/components/).

<img src="images/components-of-kubernetes.png">

## Remote-accessing to a Kubernetes cluster on a public cloud
* [GKS](https://cloud.google.com/kubernetes-engine) or [Amazon EKS](https://aws.amazon.com/eks/?nc1=h_ls) is relatively easy.
* Everything is configured during the installation process.
* The `kubectl` command handles both the location and credentials. (Assuming `kubectl` is installed and configured on the laptop.)
```bash
$ kubectl config view
```
returns the location and credentials that kubectl knows. For example,
```bash
[TODO: show the example]
```
`kubectl config` modifies kubeconfig files using subcommands like `kubectl config SUBCOMMAND`. For details, refer to [kubectl config](https://kubernetes.io/docs/reference/generated/kubectl/kubectl-commands#config).

## Remote-accessing to a Kubernetes cluster on on-premise computers
* Remote-access is trickier from the laptop to an on-premise Kubernetes than a cluster on public cloud.
* It is simply because no good cookbook tutorial was found on the web.

## Google search: remote-access kubernetes master on-premise
* [Accessing Clusters](https://kubernetes.io/docs/tasks/access-application-cluster/access-cluster/)
  * `kubectl` handles locating and authenticating to the `apiserver`.
  * You should access the `apiserver` in the Kubernetes Control Plane.
* [Directly accessing the REST API](https://kubernetes.io/docs/tasks/access-application-cluster/access-cluster/#directly-accessing-the-rest-api)
  * To locate and authenticate, you may or may not use the `kubectl proxy` command.
    * [Using kubectl proxy](https://kubernetes.io/docs/tasks/access-application-cluster/access-cluster/#using-kubectl-proxy) is the recommended approach.
      * `kubectl proxy` creates a proxy server or application-level gateway between localhost and the Kubernetes API Server.
        * All incoming data enters through one port and gets forwarded to the remote kubernetes API Server port, except for the path matching the static content path.
        * For details, refer to [kubectl proxy](https://kubernetes.io/docs/reference/generated/kubectl/kubectl-commands#proxy).
    * [Without kubectl proxy](https://kubernetes.io/docs/tasks/access-application-cluster/access-cluster/#without-kubectl-proxy) is the alternative approach.
      * Access the REST API with an http client such as `curl`, `wget`, or a web browser.

## The recommended approach: `kubectl proxy --port 8080`
`kubectl proxy` uses the location and authentication information stored in `~/.kube/config` of the control plane.

First, run either:
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

## The alternative approach: `kubectl config view'
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

#### Accessing the apiserver with token
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


