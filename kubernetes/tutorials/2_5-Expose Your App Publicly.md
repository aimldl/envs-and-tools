

# 2.5. Expose Your App Publicly

## [Using a Service to Expose Your App](https://kubernetes.io/docs/tutorials/kubernetes-basics/expose/expose-intro/)

### Overview of Kubernetes Services

A Service in Kubernetes is an abstraction which defines a logical set of Pods and a policy by which to access them. Services enable a loose coupling between dependent Pods. Although each Pod has a unique IP address, those IPs are not exposed outside the cluster without a Service. Services allow your applications to receive traffic.

A Service is defined using YAML [(preferred)](https://kubernetes.io/docs/concepts/configuration/overview/#general-configuration-tips) or JSON, like all Kubernetes objects. The set of Pods targeted by a Service is usually determined by a *LabelSelector* (see below for why you might want a Service without including `selector` in the spec).

#### Services and Labels

Services match a set of Pods using [labels and selectors](https://kubernetes.io/docs/concepts/overview/working-with-objects/labels), a grouping primitive that allows logical operation on objects in Kubernetes. 

Labels can be attached to objects at creation time or later on. They can be modified at any time. Labels are key/value pairs attached to objects and can be used in any number of ways:

- Designate objects for development, test, and production
- Embed version tags
- Classify an object using tags

<img src="https://d33wubrfki0l68.cloudfront.net/cc38b0f3c0fd94e66495e3a4198f2096cdecd3d5/ace10/docs/tutorials/kubernetes-basics/public/images/module_04_services.svg">

<img src="https://d33wubrfki0l68.cloudfront.net/b964c59cdc1979dd4e1904c25f43745564ef6bee/f3351/docs/tutorials/kubernetes-basics/public/images/module_04_labels.svg">

Services can be exposed in different ways by specifying a `type` in the ServiceSpec:

- *ClusterIP* (default) - Exposes the Service on an internal IP in the cluster. This type makes the Service only reachable from within the cluster.
- *NodePort* - Exposes the Service on the same port of each selected Node in the cluster using NAT. Makes a Service accessible from outside the cluster using `:`. Superset of ClusterIP.
- *LoadBalancer* - Creates an external load balancer in the current cloud (if supported) and assigns a fixed, external IP to the Service. Superset of NodePort.
- *ExternalName* - Exposes the Service using an arbitrary name (specified by `externalName` in the spec) by returning a CNAME record with the name. No proxy is used. This type requires v1.7 or higher of `kube-dns`.

More information about the different types of Services can be found in the [Using Source IP](https://kubernetes.io/docs/tutorials/services/source-ip/) tutorial. Also see [Connecting Applications with Services](https://kubernetes.io/docs/concepts/services-networking/connect-applications-service).

Kubernetes Pods are mortal. Pods in fact have a lifecycle. When a worker node dies, the Pods running on the Node are also lost. A ReplicaSet might then dynamically drive the cluster back to desired state via creation of new Pods to keep your application running.

As another example, consider an image-processing backend with 3 replicas. Those replicas are exchangeable; the front-end system should not care about backend replicas or even if a Pod is lost and recreated. That said, each Pod in a Kubernetes cluster has a unique IP address, even Pods on the same Node, so there needs to be a way of automatically reconciling changes among Pods so that your applications continue to function.



https://kubernetes.io/docs/tutorials/kubernetes-basics/expose/expose-interactive/

```
Kubernetes Bootcamp Terminal

$
$ sleep 1; launch.sh
Starting Kubernetes. This is expected to take less than a minute......
Kubernetes Started
$ kubectl get pods
NAME                                   READY   STATUS    RESTARTS   AGE
kubernetes-bootcamp-765bf4c7b4-d9rwz   0/1     Pending   0          4s
$ kubectl get services
NAME         TYPE        CLUSTER-IP   EXTERNAL-IP   PORT(S)   AGE
kubernetes   ClusterIP   10.96.0.1    <none>        443/TCP   111s
$
```

```
$ kubectl get deployments
NAME                  READY   UP-TO-DATE   AVAILABLE   AGE
kubernetes-bootcamp   1/1     1            1           3m22s
$ kubectl expose deployment/kubernetes-bootcamp --type="NodePort" --port 8080
service/kubernetes-bootcamp exposed
$
```

To find out what port was opened externally (by the NodePort option) we’ll run the `describe service` command:

```
$ kubectl describe services/kubernetes-bootcamp
Name:                     kubernetes-bootcamp
Namespace:                default
Labels:                   run=kubernetes-bootcamp
Annotations:              <none>
Selector:                 run=kubernetes-bootcamp
Type:                     NodePort
IP:                       10.100.6.130
Port:                     <unset>  8080/TCP
TargetPort:               8080/TCP
NodePort:                 <unset>  31921/TCP
Endpoints:                172.18.0.5:8080
Session Affinity:         None
External Traffic Policy:  Cluster
Events:                   <none>
$
```



```
$ export NODE_PORT=$(kubectl get services/kubernetes-bootcamp -o go-template='{{index.spec.ports0).nodePort}}')
error: error parsing template {{index.spec.ports0).nodePort}}, template: output:1: unexpected ")" in input
$ export NODE_PORT=$(kubectl get services/kubernetes-bootcamp -o go-template='{{(index.spec.ports0).nodePort}}')
error: error executing template "{{(index.spec.ports0).nodePort}}": template: output:1:3: executing "output" at <index>: wrong number of args for index: want at least 1 got 0
$ export NODE_PORT=$(kubectl get services/kubernetes-bootcamp -o go-template='{{(index.spec.ports 0).nodePort}}')
error: error executing template "{{(index.spec.ports 0).nodePort}}": template: output:1:3: executing "output" at <index>: wrongnumber of args for index: want at least 1 got 0
$ export NODE_PORT=$(kubectl get services/kubernetes-bootcamp -o go-template='{{(index .spec.ports 0).nodePort}}')
$ echo NODE_PORT=$NODE_PORT
NODE_PORT=31921
$ export NODE_PORT=$(kubectl get services/kubernetes-bootcamp -o go-template='{{(index .spec.ports 0).nodePort}}')
$ export NODE_PORT=$(kubectl get services/kubernetes-bootcamp -o go-template='{{(index .spec.ports 0).nodePort}}')
$ curl $(minikube ip):$NODE_PORT
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-765bf4c7b4-d9rwz | v=1
$
```

We get a response from the server. The Service is exposed!

The Deployment created automatically a label for our Pod. With `describe deployment` command you can see the name of the label:

```
$ kubectl describe deployment
Name:                   kubernetes-bootcamp
Namespace:              default
CreationTimestamp:      Tue, 07 Apr 2020 00:25:48 +0000
Labels:                 run=kubernetes-bootcamp
Annotations:            deployment.kubernetes.io/revision: 1
Selector:               run=kubernetes-bootcamp
Replicas:               1 desired | 1 updated | 1 total | 1 available | 0 unavailable
StrategyType:           RollingUpdate
MinReadySeconds:        0
RollingUpdateStrategy:  25% max unavailable, 25% max surge
Pod Template:
  Labels:  run=kubernetes-bootcamp
  Containers:
   kubernetes-bootcamp:
    Image:        gcr.io/google-samples/kubernetes-bootcamp:v1
    Port:         8080/TCP
    Host Port:    0/TCP
    Environment:  <none>
    Mounts:       <none>
  Volumes:        <none>
Conditions:
  Type           Status  Reason
  ----           ------  ------
  Available      True    MinimumReplicasAvailable
  Progressing    True    NewReplicaSetAvailable
OldReplicaSets:  <none>
NewReplicaSet:   kubernetes-bootcamp-765bf4c7b4 (1/1 replicas created)
Events:
  Type    Reason             Age   From                   Message
  ----    ------             ----  ----                   -------
  Normal  ScalingReplicaSet  16m   deployment-controller  Scaled up replica set kubernetes-bootcamp-765bf4c7b4 to 1
$
```



> Labels:  run=kubernetes-bootcamp

Let’s use this label to query our list of Pods.

```
$ kubectl get pods -l run=kubernetes-bootcamp
NAME                                   READY   STATUS    RESTARTS   AGE
kubernetes-bootcamp-765bf4c7b4-d9rwz   1/1     Running   0         20m
$
```

```
$ kubectl get services -l run=kubernetes-bootcamp
NAME                  TYPE       CLUSTER-IP     EXTERNAL-IP   PORT(S)          AGE
kubernetes-bootcamp   NodePort   10.100.6.130   <none>   8080:31921/TCP   19m
$
```

Get the name of the Pod and store it in the POD_NAME environment variable:

```
$ kubectl get pods -o go-template --template '{{range .items}} {{.metadata.name}}{{"\n"}}{{end}}'
 kubernetes-bootcamp-765bf4c7b4-d9rwz
$ export POD_NAME=$(kubectl get pods -o go-template --template '{{range .items}} {{.metadata.name}}{{"\n"}}{{end}}')
$ echo POD_NAME: $POD_NAME
POD_NAME: kubernetes-bootcamp-765bf4c7b4-d9rwz
$
```

To apply a new label we use the label command followed by the object type, object name and the new label:

```
$ kubectl label pod $POD_NAME ap=v1  # This is a typo.
$ kubectl label pod $POD_NAME app=v1
pod/kubernetes-bootcamp-765bf4c7b4-d9rwz labeled
$ kubectl describe pods
Name:         kubernetes-bootcamp-765bf4c7b4-d9rwz
Namespace:    default
Priority:     0
Node:         minikube/172.17.0.58
Start Time:   Tue, 07 Apr 2020 00:26:03 +0000
Labels:       ap=v1
              app=v1
              pod-template-hash=765bf4c7b4
              run=kubernetes-bootcamp
  ...
$
```

> Labels:       ap=v1
>               app=v1
>               pod-template-hash=765bf4c7b4
>               run=kubernetes-bootcamp

The same output result with $POD_NAME.

```
$ kubectl describe pods $POD_NAME
$ kubectl label pod $POD_NAME app=v1
pod/kubernetes-bootcamp-765bf4c7b4-d9rwz labeled
$ kubectl describe pods
Name:         kubernetes-bootcamp-765bf4c7b4-d9rwz
Namespace:    default
Priority:     0
Node:         minikube/172.17.0.58
Start Time:   Tue, 07 Apr 2020 00:26:03 +0000
Labels:       ap=v1
              app=v1
              pod-template-hash=765bf4c7b4
              run=kubernetes-bootcamp
  ...
$
```

We see here that the label is attached now to our Pod. And we can query now the list of pods using the new label:

```
$ kubectl get pods -l app=v1
NAME                                   READY   STATUS    RESTARTS   AGE
kubernetes-bootcamp-765bf4c7b4-d9rwz   1/1     Running   0         35m
$
```

And we see the Pod.

To delete Services you can use the `delete service` command. Labels can be used also here:

```
$ kubectl delete service -l run=kubernetes-bootcamp
service "kubernetes-bootcamp" deleted
$ kubectl get services
NAME         TYPE        CLUSTER-IP   EXTERNAL-IP   PORT(S)   AGE
kubernetes   ClusterIP   10.96.0.1    <none>        443/TCP   37m
$
```

```
$ curl $(minikube ip):$NODE_PORT
curl: (7) Failed to connect to 172.17.0.58 port 31921: Connection refused
$
```

This proves that the app is not reachable anymore from outside of the cluster. You can confirm that the app is still running with a curl inside the pod:

```
$ kubectl exec -ti $POD_NAME curl localhost:8080
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-765bf4c7b4-d9rwz | v=1
$
```

