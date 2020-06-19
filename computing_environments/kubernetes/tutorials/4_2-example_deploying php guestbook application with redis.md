# 4.2. Example: Deploying PHP Guestbook application with Redis

* [Kubernetes Examples](https://github.com/kubernetes/examples/tree/master/)에는 보다 완성된 애플리케이션에 대한 추가 예제가 있습니다.
  * [guestbook 예제](https://github.com/kubernetes/examples/tree/master/guestbook/)

https://kubernetes.io/docs/tutorials/stateless-application/guestbook/

How to build and deploy a simple, multi-tier web application using Kubernetes and Docker

## Components

- A single-instance [Redis](https://redis.io/) master to store guestbook entries
- Multiple [replicated Redis](https://redis.io/topics/replication) instances to serve reads
- Multiple web frontend instances

## Objectives

- Start up a Redis master
- Start up Redis slaves
- Start up the guestbook frontend
- Expose and view the Frontend Service
- Clean up

### Start up the Redis Master

The guestbook application uses Redis to store its data. It writes its data to a Redis master instance and reads data from multiple Redis slave instances.

> Redis is an open source (BSD licensed), in-memory data structure store, used as a database, cache and message broker. It supports data structures such as strings, hashes, lists, sets, sorted sets with range queries, bitmaps, hyperloglogs, geospatial indexes with radius queries and streams. 

#### Creating the Redis Master Deployment

The manifest file, included below, specifies a Deployment controller that runs a single replica Redis master Pod.

##### application/guestbook/redis-master-deployment.yaml

```
apiVersion: apps/v1 # for versions before 1.9.0 use apps/v1beta2
kind: Deployment
metadata:
  name: redis-master
  labels:
    app: redis
spec:
  selector:
    matchLabels:
      app: redis
      role: master
      tier: backend
  replicas: 1
  template:
    metadata:
      labels:
        app: redis
        role: master
        tier: backend
    spec:
      containers:
      - name: master
        image: k8s.gcr.io/redis:e2e  # or just image: redis
        resources:
          requests:
            cpu: 100m
            memory: 100Mi
        ports:
        - containerPort: 6379
```

```
replicas: 1
- name: master
        image: k8s.gcr.io/redis:e2e  # or just image: redis
```

Apply the Redis Master Deployment from the redis-master-deployment.yaml file

```
$ kubectl apply -f https://k8s.io/examples/application/guestbook/redis-master-deployment.yaml
```

만약 .yaml 파일을 로컬에 저장했다면, 

```
$ kubectl apply -f redis-master-deployment.yaml 
deployment.apps/redis-master created
$
```

```
$ kubectl get deployments
NAME           READY   UP-TO-DATE   AVAILABLE   AGE
redis-master   1/1     1            1           2m23s
$ kubectl get pods
NAME                           READY   STATUS    RESTARTS   AGE
redis-master-596696dd4-62wvr   1/1     Running   0          2m29s
$
```

Run the following command to view the logs from the Redis Master Pod:

```
$ kubectl logs -f POD-NAME
Error from server (NotFound): pods "POD-NAME" not found
$ kubectl logs -f $POD-NAME
Error: unknown shorthand flag: 'N' in -NAME
See 'kubectl logs --help' for usage.
$

$ kubectl logs -f POD_NAME
Error from server (NotFound): pods "POD_NAME" not found
$ kubectl logs -f $POD_NAME
error: expected 'logs [-f] [-p] (POD | TYPE/NAME) [-c CONTAINER]'.
POD or TYPE/NAME is a required argument for the logs command
See 'kubectl logs -h' for help and examples
$
```

> **Note:** Replace POD-NAME with the name of your Pod.

```
$ kubectl logs -f redis-master-596696dd4-62wvr
                _._                                                  
           _.-``__ ''-._                                             
      _.-``    `.  `_.  ''-._           Redis 2.8.19 (00000000/0) 64 bit
  .-`` .-```.  ```\/    _.,_ ''-._                                   
 (    '      ,       .-`  | `,    )     Running in stand alone mode
 |`-._`-...-` __...-.``-._|'` _.-'|     Port: 6379
 |    `-._   `._    /     _.-'    |     PID: 1
  `-._    `-._  `-./  _.-'    _.-'                                   
 |`-._`-._    `-.__.-'    _.-'_.-'|                                  
 |    `-._`-._        _.-'_.-'    |           http://redis.io        
  `-._    `-._`-.__.-'_.-'    _.-'                                   
 |`-._`-._    `-.__.-'    _.-'_.-'|                                  
 |    `-._`-._        _.-'_.-'    |                                  
  `-._    `-._`-.__.-'_.-'    _.-'                                   
      `-._    `-.__.-'    _.-'                                       
          `-._        _.-'                                           
              `-.__.-'                                               

[1] 07 Apr 06:20:25.251 # Server started, Redis version 2.8.19
[1] 07 Apr 06:20:25.251 # WARNING you have Transparent Huge Pages (THP) support enabled in your kernel. This will create latency and memory usage issues with Redis. To fix this issue run the command 'echo never > /sys/kernel/mm/transparent_hugepage/enabled' as root, and add it to your /etc/rc.local in order to retain the setting after a reboot. Redis must be restarted after THP is disabled.
[1] 07 Apr 06:20:25.251 # WARNING: The TCP backlog setting of 511 cannot be enforced because /proc/sys/net/core/somaxconn is set to the lower value of 128.
[1] 07 Apr 06:20:25.251 * The server is now ready to accept connections on port 6379

^C
$
```

### Creating the Redis Master Service

The guestbook application needs to communicate to the Redis master to write its data. You need to apply a Service to proxy the traffic to the Redis master Pod. A Service defines a policy to access the Pods.

##### application/guestbook/redis-master-service.yaml

```
apiVersion: v1
kind: Service
metadata:
  name: redis-master
  labels:
    app: redis
    role: master
    tier: backend
spec:
  ports:
  - port: 6379
    targetPort: 6379
  selector:
    app: redis
    role: master
    tier: backend

```

Apply the Redis Master Service from the .yaml file.

```
$ kubectl apply -f https://k8s.io/examples/application/guestbook/redis-master-service.yaml
service/redis-master created
$ kubectl get service
NAME           TYPE        CLUSTER-IP     EXTERNAL-IP   PORT(S)    AGE
kubernetes     ClusterIP   10.100.0.1     <none>        443/TCP    46h
redis-master   ClusterIP   10.100.0.151   <none>        6379/TCP   11s
$
```

**Note:** This manifest file creates a Service named `redis-master` with a set of labels that match the labels previously defined, so the Service routes network traffic to the Redis master Pod.

### Start up the Redis Slaves

Although the Redis master is a single pod, you can make it highly available to meet traffic demands by adding replica Redis slaves.

#### Creating the Redis Slave Deployment

Deployments scale based off of the configurations set in the manifest file. In this case, the Deployment object specifies two replicas.

If there are not any replicas running, this Deployment would start the two replicas on your container cluster. Conversely, if there are more than two replicas are running, it would scale down until two replicas are running.

##### application/guestbook/redis-slave-deployment.yaml

```
apiVersion: apps/v1 # for versions before 1.9.0 use apps/v1beta2
kind: Deployment
metadata:
  name: redis-slave
  labels:
    app: redis
spec:
  selector:
    matchLabels:
      app: redis
      role: slave
      tier: backend
  replicas: 2
  template:
    metadata:
      labels:
        app: redis
        role: slave
        tier: backend
    spec:
      containers:
      - name: slave
        image: gcr.io/google_samples/gb-redisslave:v3
        resources:
          requests:
            cpu: 100m
            memory: 100Mi
        env:
        - name: GET_HOSTS_FROM
          value: dns
          # Using `GET_HOSTS_FROM=dns` requires your cluster to
          # provide a dns service. As of Kubernetes 1.3, DNS is a built-in
          # service launched automatically. However, if the cluster you are using
          # does not have a built-in DNS service, you can instead
          # access an environment variable to find the master
          # service's host. To do so, comment out the 'value: dns' line above, and
          # uncomment the line below:
          # value: env
        ports:
        - containerPort: 6379

```

Apply the Redis Slave Deployment from the .yaml file.

```
$ kubectl apply -f https://k8s.io/examples/application/guestbook/redis-slave-deployment.yaml
```

```
$ kubectl get pods
NAME                           READY   STATUS    RESTARTS   AGE
redis-master-596696dd4-62wvr   1/1     Running   0          63m
redis-slave-6bb9896d48-cvts4   1/1     Running   0          10s
redis-slave-6bb9896d48-k5lt7   1/1     Running   0          10s
$
```

Now there is a master pod and two slave pods.

#### Creating the Redis Slave Service

##### application/guestbook/redis-slave-service.yaml

```
apiVersion: v1
kind: Service
metadata:
  name: redis-slave
  labels:
    app: redis
    role: slave
    tier: backend
spec:
  ports:
  - port: 6379
  selector:
    app: redis
    role: slave
    tier: backend
```

```
$ kubectl get services
NAME           TYPE        CLUSTER-IP     EXTERNAL-IP   PORT(S)    AGE
kubernetes     ClusterIP   10.100.0.1     <none>        443/TCP    46h
redis-master   ClusterIP   10.100.0.151   <none>        6379/TCP   16m
$ kubectl apply -f https://k8s.io/examples/application/guestbook/redis-slave-service.yaml
service/redis-slave created
$ kubectl get services
NAME           TYPE        CLUSTER-IP      EXTERNAL-IP   PORT(S)    AGE
kubernetes     ClusterIP   10.100.0.1      <none>        443/TCP    46h
redis-master   ClusterIP   10.100.0.151    <none>        6379/TCP   16m
redis-slave    ClusterIP   10.100.0.171    <none>        6379/TCP   16s
$
```

### Set up and Expose the Guestbook Frontend

The guestbook application has a web frontend serving the HTTP requests written in PHP. It is configured to connect to the redis-master Service for write requests and the redis-slave service for Read requests.

#### Creating the Guestbook Frontend Deployment

##### application/guestbook/frontend-deployment.yaml

```
apiVersion: apps/v1 # for versions before 1.9.0 use apps/v1beta2
kind: Deployment
metadata:
  name: frontend
  labels:
    app: guestbook
spec:
  selector:
    matchLabels:
      app: guestbook
      tier: frontend
  replicas: 3
  template:
    metadata:
      labels:
        app: guestbook
        tier: frontend
    spec:
      containers:
      - name: php-redis
        image: gcr.io/google-samples/gb-frontend:v4
        resources:
          requests:
            cpu: 100m
            memory: 100Mi
        env:
        - name: GET_HOSTS_FROM
          value: dns
          # Using `GET_HOSTS_FROM=dns` requires your cluster to
          # provide a dns service. As of Kubernetes 1.3, DNS is a built-in
          # service launched automatically. However, if the cluster you are using
          # does not have a built-in DNS service, you can instead
          # access an environment variable to find the master
          # service's host. To do so, comment out the 'value: dns' line above, and
          # uncomment the line below:
          # value: env
        ports:
        - containerPort: 80

```

```
$ kubectl apply -f https://k8s.io/examples/application/guestbook/frontend-deployment.yaml
deployment.apps/frontend created
$
```

```
$ kubectl get pods 
NAME                           READY   STATUS    RESTARTS   AGE
frontend-69859f6796-782ql      1/1     Running   0          3m21s
frontend-69859f6796-sh6bj      1/1     Running   0          3m21s
frontend-69859f6796-whjss      1/1     Running   0          3m21s
redis-master-596696dd4-62wvr   1/1     Running   0          74m
redis-slave-6bb9896d48-cvts4   1/1     Running   0          10m
redis-slave-6bb9896d48-k5lt7   1/1     Running   0          10m
$ kubectl get pods -l app=guestbook
NAME                        READY   STATUS    RESTARTS   AGE
frontend-69859f6796-782ql   1/1     Running   0          3m39s
frontend-69859f6796-sh6bj   1/1     Running   0          3m39s
frontend-69859f6796-whjss   1/1     Running   0          3m39s
```

Equivalently,

```
$ kubectl get pods -l tier=frontend
NAME                        READY   STATUS    RESTARTS   AGE
frontend-69859f6796-782ql   1/1     Running   0          3m49s
frontend-69859f6796-sh6bj   1/1     Running   0          3m49s
frontend-69859f6796-whjss   1/1     Running   0          3m49s
$ kubectl get pods -l app=guestbook -l tier=frontend
NAME                        READY   STATUS    RESTARTS   AGE
frontend-69859f6796-782ql   1/1     Running   0          3m13s
frontend-69859f6796-sh6bj   1/1     Running   0          3m13s
frontend-69859f6796-whjss   1/1     Running   0          3m13s
$
```

### Creating the Frontend Service

The redis-slave and redis-master Services you applied are only accessible within the container cluster because the default type for a Service is ClusterIP. ClusterIP provides a single IP address for the set of Pods the Service is pointing to. This IP address is accessible only within the cluster.

If you want guests to be able to access your guestbook, you must configure the frontend Service to be externally visible, so a client can request the Service from outside the container cluster. Minikube can only expose Services through NodePort.

Note: Some cloud providers, like Google Compute Engine or Google Kubernetes Engine, support external load balancers. If your cloud provider supports load balancers and you want to use it, simply delete or comment out type: NodePort, and uncomment type: LoadBalancer.

```
$ kubectl get services
NAME           TYPE        CLUSTER-IP      EXTERNAL-IP   PORT(S)    AGE
kubernetes     ClusterIP   10.100.0.1      <none>        443/TCP    46h
redis-master   ClusterIP   10.100.0.151    <none>        6379/TCP   16m
redis-slave    ClusterIP   10.100.0.171    <none>        6379/TCP   16s
$
```

##### application/guestbook/frontend-service.yaml

```
apiVersion: v1
kind: Service
metadata:
  name: frontend
  labels:
    app: guestbook
    tier: frontend
spec:
  # comment or delete the following line if you want to use a LoadBalancer
  type: NodePort 
  # if your cluster supports it, uncomment the following to automatically create
  # an external load-balanced IP for the frontend service.
  # type: LoadBalancer
  ports:
  - port: 80
  selector:
    app: guestbook
    tier: frontend
```

> type: NodePort 

exposes Services through NodePort.

```
$ kubectl apply -f https://k8s.io/examples/application/guestbook/frontend-service.yaml
service/frontend created
$
```

```
$ kubectl get services
NAME           TYPE        CLUSTER-IP      EXTERNAL-IP   PORT(S)       AGE
frontend       NodePort    10.100.0.21     <none>        80:30579/TCP  26s
kubernetes     ClusterIP   10.100.0.1      <none>        443/TCP       46h
redis-master   ClusterIP   10.100.0.151    <none>        6379/TCP      32m
redis-slave    ClusterIP   10.100.0.171    <none>        6379/TCP      15m
$
```



### Viewing the Frontend Service via `NodePort`

> > 1. Run the following command to get the IP address for the frontend Service.
> >
> >    ```shell
> >      minikube service frontend --url
> >    ```
> >
> >    The response should be similar to this:
> >
> >    ```
> >      http://192.168.99.100:31323
> >    ```
> >
> > 2. Copy the IP address, and load the page in your browser to view your guestbook.

TODO: Fix this. 

$ minikube service frontend --url

Command 'minikube' not found, but can be installed with:

sudo snap install minikube

$ kubectl service frontend --url
Error: unknown command "service" for "kubectl"

$

#### Viewing the Frontend Service via LoadBalance

```
$ kubectl get service frontend
NAME       TYPE       CLUSTER-IP      EXTERNAL-IP   PORT(S)        AGE
frontend   NodePort   10.100.0.21     <none>        80:30579/TCP   14m
$
```

Copy the external IP address, and load the page in your browser to view your guestbook.

TODO: Fix this. It doesn't work because frontend is not exposed.

#### Scale the Web Frontend

##### Scale up to 5

```
$ kubectl scale deployment frontend --replicas=5
deployment.extensions/frontend scaled
$ kubectl get pods
NAME                           READY   STATUS    RESTARTS   AGE
frontend-69859f6796-782ql      1/1     Running   0          35m
frontend-69859f6796-h2xgj      1/1     Running   0          11s
frontend-69859f6796-sh6bj      1/1     Running   0          35m
frontend-69859f6796-whjss      1/1     Running   0          35m
frontend-69859f6796-zltk7      1/1     Running   0          11s
redis-master-596696dd4-62wvr   1/1     Running   0          106m
redis-slave-6bb9896d48-cvts4   1/1     Running   0          42m
redis-slave-6bb9896d48-k5lt7   1/1     Running   0          42m
$
```

##### Scale down to 2

```
$ kubectl scale deployment frontend --replicas=2
deployment.extensions/frontend scaled
$ kubectl get deployments
NAME           READY   UP-TO-DATE   AVAILABLE   AGE
frontend       2/2     2            2           36m
redis-master   1/1     1            1           107m
redis-slave    2/2     2            2           43m
$ kubectl get pods
NAME                           READY   STATUS    RESTARTS   AGE
frontend-69859f6796-782ql      1/1     Running   0          36m
frontend-69859f6796-whjss      1/1     Running   0          36m
redis-master-596696dd4-62wvr   1/1     Running   0          107m
redis-slave-6bb9896d48-cvts4   1/1     Running   0          44m
redis-slave-6bb9896d48-k5lt7   1/1     Running   0          44m
$
```

### Cleaning up

Deleting the Deployments and Services also deletes any running Pods. Use labels to delete multiple resources with one command.

Run the following commands to delete all Pods, Deployments, and Services.

```
$ kubectl get deployments
NAME           READY   UP-TO-DATE   AVAILABLE   AGE
frontend       2/2     2            2           39m
redis-master   1/1     1            1           110m
redis-slave    2/2     2            2           46m
$
```

```
$ kubectl get pods
NAME                           READY   STATUS    RESTARTS   AGE
frontend-69859f6796-782ql      1/1     Running   0          39m
frontend-69859f6796-whjss      1/1     Running   0          39m
redis-master-596696dd4-62wvr   1/1     Running   0          110m
redis-slave-6bb9896d48-cvts4   1/1     Running   0          46m
redis-slave-6bb9896d48-k5lt7   1/1     Running   0          46m
$
```

Print all the labels

```
$ kubectl get pods --show-labels
NAME                           ...  LABELS
frontend-69859f6796-782ql      ...  app=guestbook,pod-template-hash=69859f6796,tier=frontend
frontend-69859f6796-whjss      ...  app=guestbook,pod-template-hash=69859f6796,tier=frontend
redis-master-596696dd4-62wvr   ...  app=redis,pod-template-hash=596696dd4,role=master,tier=backend
redis-slave-6bb9896d48-cvts4   ...  app=redis,pod-template-hash=6bb9896d48,role=slave,tier=backend
redis-slave-6bb9896d48-k5lt7   ...  app=redis,pod-template-hash=6bb9896d48,role=slave,tier=backend
$
```

For more information about labels, refer to [Kubernetes labels by example](https://kubernetesbyexample.com/labels/).

```
$ kubectl delete deployment -l tier=frontend
No resources found
$ kubectl delete deployment -l tier=backend
No resources found
$
```

```
$ kubectl get deployments --show-labels
NAME           READY   UP-TO-DATE   AVAILABLE   AGE    LABELS
frontend       2/2     2            2           57m    app=guestbook
redis-master   1/1     1            1           128m   app=redis
redis-slave    2/2     2            2           65m    app=redis
$
```

```
$ kubectl get service --show-labels
NAME           TYPE      ...  LABELS
frontend       NodePort  ...  app=guestbook,tier=frontend
kubernetes     ClusterIP ...  component=apiserver,provider=kubernetes
redis-master   ClusterIP ...  app=redis,role=master,tier=backend
redis-slave    ClusterIP ...  app=redis,role=slave,tier=backend
$
```

```
$ kubectl delete deployment -l app=guestbook
deployment.extensions "frontend" deleted
$ kubectl get deployments --show-labels
NAME           READY   UP-TO-DATE   AVAILABLE   AGE    LABELS
redis-master   1/1     1            1           133m   app=redis
redis-slave    2/2     2            2           70m    app=redis
$ kubectl delete deployment -l app=redis
deployment.extensions "redis-master" deleted
deployment.extensions "redis-slave" deleted
$ kubectl get deployments --show-labels
No resources found in default namespace.
$ kubectl delete service -l app=guestbook
service "frontend" deleted
$ kubectl get service --show-labels
NAME           TYPE        ...   LABELS
kubernetes     ClusterIP   ...   component=apiserver,provider=kubernetes
redis-master   ClusterIP   ...   app=redis,role=master,tier=backend
redis-slave    ClusterIP   ...   app=redis,role=slave,tier=backend
$ kubectl delete service -l app=redis
service "redis-master" deleted
service "redis-slave" deleted
$ kubectl get service --show-labels
NAME         TYPE        ...   LABELS
kubernetes   ClusterIP   ...   component=apiserver,provider=kubernetes
$
```

Verify everything is deleted.

```
$ kubectl get pods
No resources found in default namespace.
$
```

