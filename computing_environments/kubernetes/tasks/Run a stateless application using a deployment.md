# 간단한 nginx 예제

## AWS EC2에서 쿠버네티스 실행하기

* [Production environment/Turnkey Clous Solutions > Running Kubernetes on AWS EC2](https://kubernetes.io/docs/setup/production-environment/turnkey/aws/)

이 예제는 쿠버네티스 공식 홈페이지의 Getting started 메뉴에 있는 "AWS EC2에서 쿠버네티스 실행하기"에서 소개하는 두 개의 예제 중 하나입니다. eksctl로 생성한 신규 클러스터를 이 예제로 테스트해볼 수 있습니다. 

쿠버네티스 공식 홈페이지의 Tasks메뉴에는 "Deployment를 써서 Statelsss application 실행하기"라는 제목으로 나옵니다.

* [Run Applications > Run a Stateless Application Using a Deployment](https://kubernetes.io/docs/tasks/run-application/run-stateless-application-deployment/)

-----

다음 [PHP guestbook 예제](tutorials/4_2-example_deploying php guestbook application with redis.md)

----

## 간단한 nginx 예제: Deployment를 써서 Statelsss application 실행

### nginx deployment 생성

```
$ kubectl apply -f https://k8s.io/examples/application/deployment.yaml
deployment.apps/nginx-deployment created
$
```

>       - - application/deployment.yaml 
>         
>           apiVersion: apps/v1 # for versions before 1.9.0 use apps/v1beta2
>           kind: Deployment
>           metadata:
>             name: nginx-deployment
>           spec:
>             selector:
>               matchLabels:
>                 app: nginx
>             replicas: 2 # tells deployment to run 2 pods matching the template
>             template:
>               metadata:
>                 labels:
>                   app: nginx
>               spec:
>                 containers:
>                 - name: nginx
>                   image: nginx:1.14.2
>                   ports:
>                   - containerPort: 80

### Display information about the Deployment:

```
$ kubectl describe deployment nginx-deployment
Name:                   nginx-deployment
Namespace:              default
CreationTimestamp:      Tue, 07 Apr 2020 13:41:08 +0900
Labels:                 <none>
Annotations:            deployment.kubernetes.io/revision: 1
Selector:               app=nginx
Replicas:               2 desired | 2 updated | 2 total | 2 available | 0 unavailable
StrategyType:           RollingUpdate
MinReadySeconds:        0
RollingUpdateStrategy:  25% max unavailable, 25% max surge
Pod Template:
  Labels:  app=nginx
  Containers:
   nginx:
    Image:        nginx:1.14.2
    Port:         80/TCP
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
NewReplicaSet:   nginx-deployment-756d9fd5f9 (2/2 replicas created)
Events:
  Type    Reason             Age   From                   Message
  ----    ------             ----  ----                   -------
  Normal  ScalingReplicaSet  84s   deployment-controller  Scaled up replica set nginx-deployment-756d9fd5f9 to 2
$
```

### List the pods created by the deployment:

```
kubectl describe pod <pod-name>
```



```
$ kubectl get pods -l app=nginx
NAME                                READY   STATUS    RESTARTS   AGE
nginx-deployment-756d9fd5f9-ddfrh   1/1     Running   0          8m25s
nginx-deployment-756d9fd5f9-zbdrj   1/1     Running   0          8m25s
$
```

지금은 다른 pods가 없기 때문에 label의 이름을 주지 않아도 출력 결과는 같습니다.

```
$ kubectl get pods
NAME                                READY   STATUS    RESTARTS   AGE
nginx-deployment-756d9fd5f9-ddfrh   1/1     Running   0          8m49s
nginx-deployment-756d9fd5f9-zbdrj   1/1     Running   0          8m49s
$
```

### Display information about a pod:

```
$ kubectl describe pod nginx-deployment-756d9fd5f9-ddfrh 
Name:           nginx-deployment-756d9fd5f9-ddfrh
Namespace:      default
  ...
Labels:         app=nginx
                pod-template-hash=756d9fd5f9
Annotations:    kubernetes.io/psp: eks.privileged
Status:         Running
IP:             123.456.78.90
IPs:            <none>
  ...
    Image:          nginx:1.14.2
    Image ID:       docker-pullable://nginx@sha256:f7988fb6c02e0ce69257d9bd9cf37ae20a60f1df7563c3a2a6abe24160306b8d
    Port:           80/TCP
    Host Port:      0/TCP
    State:          Running
      Started:      Tue, 07 Apr 2020 13:41:15 +0900
    Ready:          True
  ...
$
```

### Updating the deployment

You can update the deployment by applying a new YAML file. This YAML file specifies that the deployment should be updated to use nginx 1.16.1.

> application/deployment-update.yaml 
>
> apiVersion: apps/v1 # for versions before 1.9.0 use apps/v1beta2
> kind: Deployment
> metadata:
>   name: nginx-deployment
> spec:
>   selector:
>     matchLabels:
>       app: nginx
>   replicas: 2
>   template:
>     metadata:
>       labels:
>         app: nginx
>     spec:
>       containers:
>       - name: nginx
>         image: nginx:1.16.1 # Update the version of nginx from 1.14.2 to 1.16.1
>         ports:
>         - containerPort: 80

Apply the new YAML file:

```
$ kubectl apply -f https://k8s.io/examples/application/deployment-update.yaml
deployment.apps/nginx-deployment configured
$
```

Watch the deployment create pods with new names and delete the old pods:

신규 pods의 이름

```
$ kubectl get pods -l app=nginx
NAME                                READY   STATUS    RESTARTS   AGE
nginx-deployment-59777878f8-rq7n7   1/1     Running   0          33s
nginx-deployment-59777878f8-xhtsr   1/1     Running   0          25s
$
```

이전 pods의 이름

```
$ kubectl get pods -l app=nginx
NAME                                READY   STATUS    RESTARTS   AGE
nginx-deployment-756d9fd5f9-ddfrh   1/1     Running   0          8m25s
nginx-deployment-756d9fd5f9-zbdrj   1/1     Running   0          8m25s
$
```

TODO: tutorial에는 없지만 궁금해서 한번 해봄. ngiix 서비스에서 결과값을 리턴 받아보는 것... 

### Scaling the application by increasing the replica count

> application/deployment-scale.yaml 
>
> apiVersion: apps/v1 # for versions before 1.9.0 use apps/v1beta2
> kind: Deployment
> metadata:
>   name: nginx-deployment
> spec:
>   selector:
>     matchLabels:
>       app: nginx
>   replicas: 4 # Update the replicas from 2 to 4
>   template:
>     metadata:
>       labels:
>         app: nginx
>     spec:
>       containers:
>       - name: nginx
>         image: nginx:1.14.2
>         ports:
>         - containerPort: 80

Apply the new YAML file:

```
$ kubectl apply -f https://k8s.io/examples/application/deployment-scale.yaml
deployment.apps/nginx-deployment configured
$
```

Verify that the Deployment has four pods:

```
$ kubectl get pods -l app=nginx
NAME                                READY   STATUS    RESTARTS   AGE
nginx-deployment-756d9fd5f9-22lrb   1/1     Running   0          32s
nginx-deployment-756d9fd5f9-8mvvc   1/1     Running   0          34s
nginx-deployment-756d9fd5f9-9lrwp   1/1     Running   0          34s
nginx-deployment-756d9fd5f9-zdssf   1/1     Running   0          32s
$
```

### Deleting a deployment

Delete the deployment by name:

```
$ kubectl get deployments
NAME               READY   UP-TO-DATE   AVAILABLE   AGE
nginx-deployment   4/4     4            4           34m
$ kubectl delete deployment nginx-deployment
deployment.extensions "nginx-deployment" deleted
$
```

### ReplicationControllers – the Old Way

The preferred way to create a replicated application is to use a Deployment, which in turn uses a ReplicaSet. Before the Deployment and ReplicaSet were added to Kubernetes, replicated applications were configured using a ReplicationController.



------

#### TODO: 예제에 추가하고 싶은 것

> (base) aimldl@Home-Laptop:~$ kubectl get services
> NAME         TYPE        CLUSTER-IP   EXTERNAL-IP   PORT(S)   AGE
> kubernetes   ClusterIP   10.100.0.1   <none>        443/TCP   43h
> (base) aimldl@Home-Laptop:~$ kubectl expose deployment/nginx-deployment --type="NodePort" --port 8080 service/nginx-deployment exposed
> error: there is no need to specify a resource type as a separate argument when passing arguments in resource/name form (e.g. 'kubectl get resource/<resource_name>' instead of 'kubectl get resource resource/<resource_name>'
> See 'kubectl expose -h' for help and examples
> (base) aimldl@Home-Laptop:~$ kubectl expose -h
> Expose a resource as a new Kubernetes service.
>
>  Looks up a deployment, service, replica set, replication controller or pod by name and uses the
> selector for that resource as the selector for a new service on the specified port. A deployment or
> replica set will be exposed as a service only if its selector is convertible to a selector that
> service supports, i.e. when the selector contains only the matchLabels component. Note that if no
> port is specified via --port and the exposed resource has multiple ports, all will be re-used by the
> new service. Also if no labels are specified, the new service will re-use the labels from the
> resource it exposes.
>
>  Possible resources include (case insensitive):
>
>  pod (po), service (svc), replicationcontroller (rc), deployment (deploy), replicaset (rs)
>
> Examples:
>   # Create a service for a replicated nginx, which serves on port 80 and connects to the containers
> on port 8000.
>   kubectl expose rc nginx --port=80 --target-port=8000
>
>   # Create a service for a replication controller identified by type and name specified in
> "nginx-controller.yaml", which serves on port 80 and connects to the containers on port 8000.
>   kubectl expose -f nginx-controller.yaml --port=80 --target-port=8000
>
>   # Create a service for a pod valid-pod, which serves on port 444 with the name "frontend"
>   kubectl expose pod valid-pod --port=444 --name=frontend
>
>   # Create a second service based on the above service, exposing the container port 8443 as port 443
> with the name "nginx-https"
>   kubectl expose service nginx --port=443 --target-port=8443 --name=nginx-https
>
>   # Create a service for a replicated streaming application on port 4100 balancing UDP traffic and
> named 'video-stream'.
>   kubectl expose rc streamer --port=4100 --protocol=UDP --name=video-stream
>
>   # Create a service for a replicated nginx using replica set, which serves on port 80 and connects
> to the containers on port 8000.
>   kubectl expose rs nginx --port=80 --target-port=8000
>
>   # Create a service for an nginx deployment, which serves on port 80 and connects to the containers
> on port 8000.
>   kubectl expose deployment nginx --port=80 --target-port=8000
>
> Options:
>       --allow-missing-template-keys=true: If true, ignore any errors in templates when a field or
> map key is missing in the template. Only applies to golang and jsonpath output formats.
>       --cluster-ip='': ClusterIP to be assigned to the service. Leave empty to auto-allocate, or set
> to 'None' to create a headless service.
>       --dry-run='none': Must be "none", "server", or "client". If client strategy, only print the
> object that would be sent, without sending it. If server strategy, submit server-side request
> without persisting the resource.
>       --external-ip='': Additional external IP address (not managed by Kubernetes) to accept for the
> service. If this IP is routed to a node, the service can be accessed by this IP in addition to its
> generated service IP.
>   -f, --filename=[]: Filename, directory, or URL to files identifying the resource to expose a
> service
>       --generator='service/v2': The name of the API generator to use. There are 2 generators:
> 'service/v1' and 'service/v2'. The only difference between them is that service port in v1 is named
> 'default', while it is left unnamed in v2. Default is 'service/v2'.
>   -k, --kustomize='': Process the kustomization directory. This flag can't be used together with -f
> or -R.
>   -l, --labels='': Labels to apply to the service created by this call.
>       --load-balancer-ip='': IP to assign to the LoadBalancer. If empty, an ephemeral IP will be
> created and used (cloud-provider specific).
>       --name='': The name for the newly created object.
>   -o, --output='': Output format. One of:
> json|yaml|name|go-template|go-template-file|template|templatefile|jsonpath|jsonpath-file.
>       --overrides='': An inline JSON override for the generated object. If this is non-empty, it is
> used to override the generated object. Requires that the object supply a valid apiVersion field.
>       --port='': The port that the service should serve on. Copied from the resource being exposed,
> if unspecified
>       --protocol='': The network protocol for the service to be created. Default is 'TCP'.
>       --record=false: Record current kubectl command in the resource annotation. If set to false, do
> not record the command. If set to true, record the command. If not set, default to updating the
> existing annotation value only if one already exists.
>   -R, --recursive=false: Process the directory used in -f, --filename recursively. Useful when you
> want to manage related manifests organized within the same directory.
>       --save-config=false: If true, the configuration of current object will be saved in its
> annotation. Otherwise, the annotation will be unchanged. This flag is useful when you want to
> perform kubectl apply on this object in the future.
>       --selector='': A label selector to use for this service. Only equality-based selector
> requirements are supported. If empty (the default) infer the selector from the replication
> controller or replica set.)
>       --session-affinity='': If non-empty, set the session affinity for the service to this; legal
> values: 'None', 'ClientIP'
>       --target-port='': Name or number for the port on the container that the service should direct
> traffic to. Optional.
>       --template='': Template string or path to template file to use when -o=go-template,
> -o=go-template-file. The template format is golang templates
> [http://golang.org/pkg/text/template/#pkg-overview].
>       --type='': Type for this service: ClusterIP, NodePort, LoadBalancer, or ExternalName. Default
> is 'ClusterIP'.
>
> Usage:
>   kubectl expose (-f FILENAME | TYPE NAME) [--port=port] [--protocol=TCP|UDP|SCTP]
> [--target-port=number-or-name] [--name=name] [--external-ip=external-ip-of-service] [--type=type]
> [options]
>
> Use "kubectl options" for a list of global command-line options (applies to all commands).
> (base) aimldl@Home-Laptop:~$ 
> (base) aimldl@Home-Laptop:~$ kubectl expose rc nginx --port=80 --target-port=8000
> Error from server (NotFound): replicationcontrollers "nginx" not found
> (base) aimldl@Home-Laptop:~$ kubectl expose rc deployment/nginx-deployment --port=80 --target-port=8000
> error: there is no need to specify a resource type as a separate argument when passing arguments in resource/name form (e.g. 'kubectl get resource/<resource_name>' instead of 'kubectl get resource resource/<resource_name>'
> See 'kubectl expose -h' for help and examples