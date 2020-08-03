* Draft: 2020-08-03 (Mon)

# How to Remote-Access an On-Premise Kubernetes Cluster
A Kunernetes cluster on my on-premiss computers is set up successfully. The cluster consists of one master and two worker nodes. 
I want to remote-access the cluster from a laptop. But how?

## Background Knowledge
Remote-accessing to a Kubernetes cluster requires two pieces of information:
* the location of the cluster
* the credential to access it.

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

## The recommended approach: `kubectl proxy`
* `kubectl proxy` uses the location and authentication information stored in `~/.kube/config` of the control plane.
* To retrieve the location information, run either:
```bash
$ kubectl config view | grep server | sed -e 's/^[ ]*server:[ ]//'
# or
$ kubectl config view --minify | grep server | cut -f 2- -d ":" | tr -d
```
and the output looks something like:
```bash
https://123.456.7.890:6443
$
```
`https://123.456.7.890` is the IP address and the port number is `6443`.

To see the full message, run:
```bash
$ kubectl config view
```
and you'll get something like:
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
The above two commands extract the location information in: "    server: https://123.456.7.890:6443". 

## The alternative approach: access the REST API with an http client
providing the location and credentials directly to the HTTP client is also possible.
In this case, you can  such as:
* web browser
* curl
* wget

Using kubectl proxy
```bash
$ kubectl proxy --port=8080
Starting to serve on 127.0.0.1:8080
```
Running the above command handles locating the apiserver and authenticating. 
With this command, you can explore the API with a browser, curl, or wget.
