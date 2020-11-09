# 2.7. Update Your App

## [Performing a Rolling Update](https://kubernetes.io/docs/tutorials/kubernetes-basics/update/update-intro/)

### Updating an application

Users expect applications to be available all the time and developers are expected to deploy new versions of them several times a day. In Kubernetes this is done with rolling updates. Rolling updates allow Deployments' update to take place with zero downtime by incrementally updating Pods instances with new ones. The new Pods will be scheduled on Nodes with available resources.

In the previous module we scaled our application to run multiple instances. This is a requirement for performing updates without affecting application availability. By default, the maximum number of Pods that can be unavailable during the update and the maximum number of new Pods that can be created, is one. Both options can be configured to either numbers or percentages (of Pods). In Kubernetes, updates are versioned and any Deployment update can be reverted to a previous (stable) version.

###  Rolling updates overview

<img src="https://d33wubrfki0l68.cloudfront.net/30f75140a581110443397192d70a4cdb37df7bfc/fa906/docs/tutorials/kubernetes-basics/public/images/module_06_rollingupdates1.svg">

<img src="https://d33wubrfki0l68.cloudfront.net/678bcc3281bfcc588e87c73ffdc73c7a8380aca9/703a2/docs/tutorials/kubernetes-basics/public/images/module_06_rollingupdates2.svg">

<img src="https://d33wubrfki0l68.cloudfront.net/9b57c000ea41aca21842da9e1d596cf22f1b9561/91786/docs/tutorials/kubernetes-basics/public/images/module_06_rollingupdates3.svg">

<img src="https://d33wubrfki0l68.cloudfront.net/6d8bc1ebb4dc67051242bc828d3ae849dbeedb93/fbfa8/docs/tutorials/kubernetes-basics/public/images/module_06_rollingupdates4.svg">

Similar to application Scaling, if a Deployment is exposed publicly, the Service will load-balance the traffic only to available Pods during the update. An available Pod is an instance that is available to the users of the application.

Rolling updates allow the following actions:

- Promote an application from one environment to another (via container image updates)
- Rollback to previous versions
- Continuous Integration and Continuous Delivery of applications with zero downtime

Edit This Page

## [Interactive Tutorial - Updating Your App](https://kubernetes.io/docs/tutorials/kubernetes-basics/update/update-interactive/)

we'll update our application to a new version, and also perform a rollback.

### Step 1: Update the version of the app

```
Kubernetes Started
$ kubectl get deployments
NAME                  READY   UP-TO-DATE   AVAILABLE   AGE
kubernetes-bootcamp   4/4     4            4           76s
$ kubectl get pods
NAME                                   READY   STATUS    RESTARTS   AGE
kubernetes-bootcamp-765bf4c7b4-24qdk   1/1     Running   0          78s
kubernetes-bootcamp-765bf4c7b4-4tjf2   1/1     Running   0          78s
kubernetes-bootcamp-765bf4c7b4-tdjq8   1/1     Running   0          78s
kubernetes-bootcamp-765bf4c7b4-xp2gt   1/1     Running   0          78s
$
```



```
$ kubectl describe pods
Name:         kubernetes-bootcamp-765bf4c7b4-24qdk
Namespace:    default
  ...
Labels:       pod-template-hash=765bf4c7b4
              run=kubernetes-bootcamp
  ...
IP:           172.18.0.6
  ...
    Image:          gcr.io/google-samples/kubernetes-bootcamp:v1
    Image ID:       docker-pullable://jocatalin/kubernetes-bootcamp@sha256:0d6b8ee63bb57c5f5b6156f446b3bc3b3c143d233037f3a2f00e279c8fcc64af
  ...
  
Name:         kubernetes-bootcamp-765bf4c7b4-4tjf2
Namespace:    default
  ...
Labels:       pod-template-hash=765bf4c7b4
              run=kubernetes-bootcamp
  ...
IP:           172.18.0.2
  ...
    Image:          gcr.io/google-samples/kubernetes-bootcamp:v1
    Image ID:       docker-pullable://jocatalin/kubernetes-bootcamp@sha256:0d6b8ee63bb57c5f5b6156f446b3bc3b3c143d233037f3a2f00e279c8fcc64af
  ...

Name:         kubernetes-bootcamp-765bf4c7b4-tdjq8
  ...
Labels:       pod-template-hash=765bf4c7b4
              run=kubernetes-bootcamp
  ...
IP:           172.18.0.4
  ...
    Image:          gcr.io/google-samples/kubernetes-bootcamp:v1
    Image ID:       docker-pullable://jocatalin/kubernetes-bootcamp@sha256:0d6b8ee63bb57c5f5b6156f446b3bc3b3c143d233037f3a2f00e279c8fcc64af
  ...
  
Name:         kubernetes-bootcamp-765bf4c7b4-xp2gt
  ...
Labels:       pod-template-hash=765bf4c7b4Step 2: Verify an update
              run=kubernetes-bootcamp
  ...
IP:           172.18.0.7
  ...
    Image:          gcr.io/google-samples/kubernetes-bootcamp:v1
    Image ID:       docker-pullable://jocatalin/kubernetes-bootcamp@sha256:0d6b8ee63bb57c5f5b6156f446b3bc3b3c143d233037f3a2f00e279c8fcc64af
  ...
$
```

To update the image of the application to version 2, use the `set image` command, followed by the deployment name and the new image version:

```
$ kubectl set image deployments/kubernetes-bootcamp kubernetes-bootcamp=jocatalin/kubernetes-bootcamp:v2
deployment.apps/kubernetes-bootcamp image updated
$
```

Check the status of the new Pods, and view the old one terminating with the `get pods` command:

```
$ kubectl get pods
NAME                                   READY   STATUS        RESTARTS   AGE
kubernetes-bootcamp-765bf4c7b4-24qdk   1/1     Terminating   0          9m53s
kubernetes-bootcamp-765bf4c7b4-4tjf2   1/1     Terminating   0          9m53s
kubernetes-bootcamp-765bf4c7b4-tdjq8   1/1     Terminating   0          9m53s
kubernetes-bootcamp-765bf4c7b4-xp2gt   1/1     Terminating   0          9m53s
kubernetes-bootcamp-7d6f8694b6-27sh8   1/1     Running       0          13s
kubernetes-bootcamp-7d6f8694b6-4ngj9   1/1     Running       0          10s
kubernetes-bootcamp-7d6f8694b6-r7j9l   1/1     Running       0          13s
kubernetes-bootcamp-7d6f8694b6-wr9w9   1/1     Running       0          10s
$
```

### Step 2: Verify an update

First, let’s check that the App is running. To find out the exposed IP and Port we can use `describe service`:

```
We see that the deployment is using a stable version of the app (v2). The Rollback was successful.$ kubectl describe services/kubernetes-bootcamp
Name:                     kubernetes-bootcamp
Namespace:                default
Labels:                   run=kubernetes-bootcamp
Annotations:              <none>
Selector:                 run=kubernetes-bootcamp
Type:                     NodePort
IP:                       10.101.251.110
Port:                     <unset>  8080/TCP
TargetPort:               8080/TCP
NodePort:                 <unset>  30488/TCP
Endpoints:                172.18.0.10:8080,172.18.0.11:8080,172.18.0.12:8080 + 1 more...
Session Affinity:         None
External Traffic Policy:  Cluster
Events:                   <none>
$
```

Create an environment variable called NODE_PORT that has the value of the Node port assigned:

```
$ export NODE_PORT=$(kubectl get services/kubernetes-bootcamp -o go-template='{{(index .spec.ports 0).nodePort}}')
$ echo NODE_PORT=$NODE_PORT
NODE_PORT=30488
$
```

Next, we’ll do a `curl` to the the exposed IP and port:

```
$ curl $(minikube ip):$NODE_PORT
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-7d6f8694b6-wr9w9 | v=2
$ curl $(minikube ip):$NODE_PORT
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-7d6f8694b6-27sh8 | v=2
$ curl $(minikube ip):$NODE_PORT
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-7d6f8694b6-wr9w9 | v=2
$ curl $(minikube ip):$NODE_PORT
Hello Kubernetes bootcamp! | Running on: kubernetes-bootcamp-7d6f8694b6-wr9w9 | v=2
$
```

We hit a different Pod with every request and we see that all Pods are running the latest version (v2).

The update can be confirmed also by running a rollout status command:

```
$ kubectl rollout status deployments/kubernetes-bootcamp
deployment "kubernetes-bootcamp" successfully rolled out
$
```

To view the current image version of the app, run a describe command against the Pods:

```
$ kubectl describe pods | grep "Image"
    Image:          jocatalin/kubernetes-bootcamp:v2
    Image ID:       docker-pullable://jocatalin/kubernetes-bootcamp@sha256:fb1a3ced00cecfc1f83f18ab5cd14199e30adc1b49aa4244f5d65ad3f5feb2a5
    Image:          jocatalin/kubernetes-bootcamp:v2
    Image ID:       docker-pullable://jocatalin/kubernetes-bootcamp@sha256:fb1a3ced00cecfc1f83f18ab5cd14199e30adc1b49aa4244f5d65ad3f5feb2a5
    Image:          jocatalin/kubernetes-bootcamp:v2
    Image ID:       docker-pullable://jocatalin/kubernetes-bootcamp@sha256:fb1a3ced00cecfc1f83f18ab5cd14199e30adc1b49aa4244f5d65ad3f5feb2a5
    Image:          jocatalin/kubernetes-bootcamp:v2
    Image ID:       docker-pullable://jocatalin/kubernetes-bootcamp@sha256:fb1a3ced00cecfc1f83f18ab5cd14199e30adc1b49aa4244f5d65ad3f5feb2a5
$
```

### Step 3: Rollback an update

Let’s perform another update, and deploy image tagged as v10 :

```
$ kubectl set image deployments/kubernetes-bootcamp kubernetes-bootcamp=gcr.io/google-samples/kubernetes-bootcamp:v10
deployment.apps/kubernetes-bootcamp image updated
$
```

See the status of the deployment:

```
$ kubectl get deployments
NAME                  READY   UP-TO-DATE   AVAILABLE   AGE
kubernetes-bootcamp   3/4     2            3           19m
$ kubectl rollout status deployments/kubernetes-bootcamp
Waiting for deployment "kubernetes-bootcamp" rollout to finish: 2 out of 4 new replicas have been updated...


^C$
```

**And something is wrong…** We do not have the desired number of Pods available. List the Pods again:

```
$ kubectl get pods
NAME                                   READY   STATUS             RESTARTS   AGE
kubernetes-bootcamp-7d6f8694b6-27sh8   1/1     Running            0   12m
kubernetes-bootcamp-7d6f8694b6-4ngj9   1/1     Running            0   12m
kubernetes-bootcamp-7d6f8694b6-r7j9l   1/1     Running            0   12m
kubernetes-bootcamp-886577c5d-fvl8m    0/1     ImagePullBackOff   0   2m21s
kubernetes-bootcamp-886577c5d-xq5js    0/1     ImagePullBackOff   0   2m21s
$
```

A describe command on the Pods should give more insights. There is no image called `v10` in the repository. 

```bash
$ kubectl describe pods | grep "Image"
    Image:          jocatalin/kubernetes-bootcamp:v2
    Image ID:       docker-pullable://jocatalin/kubernetes-bootcamp@sha256:fb1a3ced00cecfc1f83f18ab5cd14199e30adc1b49aa4244f5d65ad3f5feb2a5
    Image:          jocatalin/kubernetes-bootcamp:v2
    Image ID:       docker-pullable://jocatalin/kubernetes-bootcamp@sha256:fb1a3ced00cecfc1f83f18ab5cd14199e30adc1b49aa4244f5d65ad3f5feb2a5
    Image:          jocatalin/kubernetes-bootcamp:v2
    Image ID:       docker-pullable://jocatalin/kubernetes-bootcamp@sha256:fb1a3ced00cecfc1f83f18ab5cd14199e30adc1b49aa4244f5d65ad3f5feb2a5
    Image:          gcr.io/google-samples/kubernetes-bootcamp:v10
    Image ID:
      Reason:       ImagePullBackOff
  Warning  Failed     3m35s (x4 over 4m52s)  kubelet, minikube  Error: ErrImagePull
  Warning  Failed     2m55s (x7 over 4m52s)  kubelet, minikube  Error: ImagePullBackOff
    Image:          gcr.io/google-samples/kubernetes-bootcamp:v10
    Image ID:
      Reason:       ImagePullBackOff
  Warning  Failed     3m18s (x4 over 4m53s)  kubelet, minikube  Error: ErrImagePull
  Warning  Failed     3m5s (x6 over 4m52s)   kubelet, minikube  Error: ImagePullBackOff
$
```

Let’s roll back to our previously working version. We’ll use the `rollout` undo command:

```
$ kubectl rollout undo deployments/kubernetes-bootcamp
deployment.apps/kubernetes-bootcamp rolled back
$
```

The `rollout` command reverted the deployment to the previous known state (v2 of the image). Updates are versioned and you can revert to any previously know state of a Deployment.

```
$ kubectl get pods
NAME                                   READY   STATUS    RESTARTS   AGE
kubernetes-bootcamp-7d6f8694b6-27sh8   1/1     Running   0          18m
kubernetes-bootcamp-7d6f8694b6-4ngj9   1/1     Running   0          18m
kubernetes-bootcamp-7d6f8694b6-r7j9l   1/1     Running   0          18m
kubernetes-bootcamp-7d6f8694b6-stsb6   1/1     Running   0          37s
$ kubectl describe pods | grep "Image"
    Image:          jocatalin/kubernetes-bootcamp:v2
    Image ID:       docker-pullable://jocatalin/kubernetes-bootcamp@sha256:fb1a3ced00cecfc1f83f18ab5cd14199e30adc1b49aa4244f5d65ad3f5feb2a5
    Image:          jocatalin/kubernetes-bootcamp:v2
    Image ID:       docker-pullable://jocatalin/kubernetes-bootcamp@sha256:fb1a3ced00cecfc1f83f18ab5cd14199e30adc1b49aa4244f5d65ad3f5feb2a5
    Image:          jocatalin/kubernetes-bootcamp:v2
    Image ID:       docker-pullable://jocatalin/kubernetes-bootcamp@sha256:fb1a3ced00cecfc1f83f18ab5cd14199e30adc1b49aa4244f5d65ad3f5feb2a5
    Image:          jocatalin/kubernetes-bootcamp:v2
    Image ID:       docker-pullable://jocatalin/kubernetes-bootcamp@sha256:fb1a3ced00cecfc1f83f18ab5cd14199e30adc1b49aa4244f5d65ad3f5feb2a5
$
```

We see that the deployment is using a stable version of the app (v2). The Rollback was successful.