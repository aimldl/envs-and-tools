# 2.3. Deploy an App

## 2.3.1. [Using kubectl to Create a Deployment](https://kubernetes.io/docs/tutorials/kubernetes-basics/deploy-app/deploy-intro/)

### Kubernetes Deployments

You can deploy your containerized applications on top of a running Kubernetes cluster. To do so, you create a Kubernetes Deployment configuration. 

The Deployment instructs Kubernetes how to create and update instances of your application. Once you've created a Deployment, the Kubernetes master schedules mentioned application instances onto individual Nodes in the cluster.

In a pre-orchestration world, installation scripts would often be used to start applications, but they did not allow recovery from machine failure. A Kubernetes Deployment Controller continuously monitors those instances. If the Node hosting an instance goes down or is deleted, the Deployment controller replaces the instance with an instance on another Node in the cluster. This provides a self-healing mechanism to address machine failure or maintenance.

### Deploying your first app on Kubernetes

<img src="https://d33wubrfki0l68.cloudfront.net/152c845f25df8e69dd24dd7b0836a289747e258a/4a1d2/docs/tutorials/kubernetes-basics/public/images/module_02_first_app.svg">



When you create a Deployment, you'll need to specify the container image for your application and the number of replicas that you want to run.

For your first Deployment, you'll use a Node.js application packaged in a Docker container. (If you didn't already try creating a Node.js application and deploying it using a container, you can do that first by following the instructions from the Hello Minikube tutorial).

Now that you know what Deployments are, let's go to the online tutorial and deploy our first app!

## Interactive Tutorial - Deploying an App

$ kubectl version --short
Client Version: v1.17.3
Server Version: v1.17.3
$ kubectl get nodes
NAME       STATUS   ROLES    AGE     VERSION
minikube   Ready    master   2m48s   v1.17.3
$ kubectl create deployment kubernetes-bootcamp --image=gcr.io/google-samples/kubernetes-bootcamp:v1
deployment.apps/kubernetes-bootcamp created
$ kubectl get nodes
NAME       STATUS   ROLES    AGE     VERSION
minikube   Ready    master   3m39s   v1.17.3
$ kubectl getdeployments
Error: unknown command "getdeployments" for "kubectl"
Run 'kubectl --help' for usage.
$ kubectl get deployments
NAME                  READY   UP-TO-DATE   AVAILABLE   AGE
kubernetes-bootcamp   1/1     1            1           30s
$ curl http://localhost:8001/version
{
  "major": "1",
  "minor": "17",
  "gitVersion": "v1.17.3",
  "gitCommit": "06ad960bfd03b39c8310aaf92d1e7c12ce618213",
  "gitTreeState": "clean",
  "buildDate": "2020-02-11T18:07:13Z",
  "goVersion": "go1.13.6",
  "compiler": "gc",
  "platform": "linux/amd64"
}$ export POD_NAME=$(kubectl get pods -o go-template --template{{range .items}}{{.metadata.name}}{{"\n"}}{{end}}')
$ echo Name of the Pod: $POD_NAME
Name of the Pod: kubernetes-bootcamp-69fbc6f4cf-9ktd2
$