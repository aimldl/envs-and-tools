# 2.6. Scale Your App

## [Running Multiple Instances of Your App](https://kubernetes.io/docs/tutorials/kubernetes-basics/scale/scale-intro/)

### Scaling an application

Scaling is accomplished by changing the number of replicas in a Deployment

In the previous modules we created a Deployment, and then exposed it publicly via a Service. The Deployment created only one Pod for running our application. When traffic increases, we will need to scale the application to keep up with user demand.

<img src="https://d33wubrfki0l68.cloudfront.net/043eb67914e9474e30a303553d5a4c6c7301f378/0d8f6/docs/tutorials/kubernetes-basics/public/images/module_05_scaling1.svg">

<img src="https://d33wubrfki0l68.cloudfront.net/30f75140a581110443397192d70a4cdb37df7bfc/b5f56/docs/tutorials/kubernetes-basics/public/images/module_05_scaling2.svg">

Scaling out a Deployment will ensure new Pods are created and scheduled to Nodes with available resources. Scaling will increase the number of Pods to the new desired state. Kubernetes also supports [autoscaling](https://kubernetes.io/docs/user-guide/horizontal-pod-autoscaling/) of Pods, but it is outside of the scope of this tutorial. Scaling to zero is also possible, and it will terminate all Pods of the specified Deployment.

Running multiple instances of an application will require a way to distribute the traffic to all of them. Services have an integrated load-balancer that will distribute network traffic to all Pods of an exposed Deployment. Services will monitor continuously the running Pods using endpoints, to ensure the traffic is sent only to available Pods.

## [Interactive Tutorial - Scaling Your App](https://kubernetes.io/docs/tutorials/kubernetes-basics/scale/scale-interactive/)

First, let's get NODE_PORT.

```
$ export NODE_PORT=$(kubectl get services/kubernetes-bootcamp -o go-template='{{(index .spec.ports 0).nodePort}}')
$ echo NODE_PORT=$NODE_PORT
NODE_PORT=30003
$
```

Next, we’ll do a `curl` to the exposed IP and port. Execute the command multiple times:

```
$ curl $(minikube ip):$NODE_PORT
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-765bf4c7b4-5gzdb | v=1
$ curl $(minikube ip):$NODE_PORT
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-765bf4c7b4-5gzdb | v=1
$ curl $(minikube ip):$NODE_PORT
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-765bf4c7b4-5gzdb | v=1
$ curl $(minikube ip):$NODE_PORT
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-765bf4c7b4-5gzdb | v=1
$
```

We hit the same Pod with every request. The load-balancing is NOT working because there's only one Pod.

```
$ kubectl get rs
NAME                             DESIRED   CURRENT   READY   AGE
kubernetes-bootcamp-765bf4c7b4   1         1         1     57s
$
```

Let's scale up and see what happens.

#### Step 1: Scaling a deployment

```
$ kubectl get deployments
NAME                  READY   UP-TO-DATE   AVAILABLE   AGE
kubernetes-bootcamp   1/1     1            1           59s
$
```

We should have 1 Pod. If not, run the command again. This shows:

- *NAME* lists the names of the Deployments in the cluster.
- *READY* shows the ratio of CURRENT/DESIRED replicas
- *UP-TO-DATE* displays the number of replicas that have been updated to achieve the desired state.
- *AVAILABLE* displays how many replicas of the application are available to your users.
- *AGE* displays the amount of time that the application has been running.

Let’s scale the Deployment to 4 replicas. 

```
$ kubectl scale deployments/kubernetes-bootcamp --replicas=4
deployment.apps/kubernetes-bootcamp scaled
$ kubectl get rs
NAME                             DESIRED   CURRENT   READY   AGE
kubernetes-bootcamp-765bf4c7b4   4         4         4     80s
$ kubectl get deployments
NAME                  READY   UP-TO-DATE   AVAILABLE   AGE
kubernetes-bootcamp   4/4     4            4           99s
$ kubectl get pods -o wide
NAME                                   READY   STATUS RESTARTS   AGE    IP           NODE       NOMINATED NODE   READINESS GATES
kubernetes-bootcamp-765bf4c7b4-cnlfp   1/1     Running 0          30s    172.18.0.7   minikube   <none>    <none>
kubernetes-bootcamp-765bf4c7b4-fk98k   1/1     Running 0          30s    172.18.0.8   minikube   <none>    <none>
kubernetes-bootcamp-765bf4c7b4-mf95n   1/1     Running 0          30s    172.18.0.9   minikube   <none>    <none>
kubernetes-bootcamp-765bf4c7b4-vp569   1/1     Running 0          103s   172.18.0.3   minikube   <none>    <none>
$ kubectl describe deployments/kubernetes-bootcamp
Name:                   kubernetes-bootcamp
  ...
Replicas:               4 desired | 4 updated | 4 total| 4 available | 0 unavailable
  ...
NewReplicaSet:   kubernetes-bootcamp-765bf4c7b4 (4/4 replicas created)
Events:
  Type    Reason             Age    From   Message
  ----    ------             ----   ----   -------
  Normal  ScalingReplicaSet  2m13s  deployment-controller  Scaled up replica set kubernetes-bootcamp-765bf4c7b4to 1
  Normal  ScalingReplicaSet  60s    deployment-controller  Scaled up replica set kubernetes-bootcamp-765bf4c7b4to 4
$

```

There are 4 Pods now, with different IP addresses.

#### Step 2: Load Balancing

Step 1 is summarized by the following two commands.

```
$ kubectl scale deployments/kubernetes-bootcamp --replicas=4
deployment.apps/kubernetes-bootcamp scaled
$ kubectl get deployments
NAME                  READY   UP-TO-DATE   AVAILABLE   AGE
kubernetes-bootcamp   4/4     4            4           6m5s
$
```

Let’s check that the Service is load-balancing the traffic.

```
$ kubectl describe services/kubernetes-bootcamp
Name:                     kubernetes-bootcamp
Namespace:                default
Labels:                   run=kubernetes-bootcamp
Annotations:              <none>
Selector:                 run=kubernetes-bootcamp
Type:                     NodePort
IP:                       10.98.254.57
Port:                     <unset>  8080/TCP
TargetPort:               8080/TCP
NodePort:                 <unset>  30003/TCP
Endpoints:                <none>
Session Affinity:         None
External Traffic Policy:  Cluster
Events:                   <none>
$
```

Execute the command multiple times quickly.

```
$ curl $(minikube ip):$NODE_PORT
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-765bf4c7b4-l4qxm | v=1
$ curl $(minikube ip):$NODE_PORT
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-765bf4c7b4-l4qxm | v=1
$ curl $(minikube ip):$NODE_PORT
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-765bf4c7b4-5gzdb | v=1
$ curl $(minikube ip):$NODE_PORT
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-765bf4c7b4-btmml | v=1
$ curl $(minikube ip):$NODE_PORT
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-765bf4c7b4-btmml | v=1
$ curl $(minikube ip):$NODE_PORT
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-765bf4c7b4-5gzdb | v=1
$
```

We hit different Pods. This demonstrates that the load-balancing is working.

#### Step 3: Scale Down

Let's scale down the Service to 2 replicas. 

```
$ kubectl scale deployments/kubernetes-bootcamp --replicas=2
deployment.apps/kubernetes-bootcamp scaled
$ kubectl get deployments
NAME                  READY   UP-TO-DATE   AVAILABLE   AGE
kubernetes-bootcamp   2/2     2            2           10m
$ kubectl get pods -o wide
NAME                                   READY   STATUS    RESTARTS   AGE IP           NODE       NOMINATED NODE   READINESS GATES
kubernetes-bootcamp-765bf4c7b4-5gzdb   1/1     Running   0          11m 172.18.0.5   minikube   <none>           <none>
kubernetes-bootcamp-765bf4c7b4-swm69   1/1     Running   0          5m29s 172.18.0.8   minikube   <none>           <none>
$
```

The number of replicas decreased to 2. This confirms that 2 Pods were terminated.