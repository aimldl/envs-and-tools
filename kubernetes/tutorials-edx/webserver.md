* Draft: 2020-08-13 (Thu)

[Exposing an Application I](https://courses.edx.org/courses/course-v1:LinuxFoundationX+LFS158x+2T2019/courseware/77c05d04d7244b9a8fe0183dd0d594d0/bf63d04f285b43bc8726a3a99107282d/?child=first)

```yaml
---
apiVersion: apps/v1
kind: Deployment
metadata:
  name: webserver
  labels:
    app: nginx
spec:
  replicas: 3
  selector:
    matchLabels:
      app: nginx
  template:
    metadata:
      labels:
        app: nginx
    spec:
      containers:
      - name: nginx
        image: nginx:alpine
        ports:
        - containerPort: 80
```



```bash
$ kubectl create -f test_webserver.yaml 
deployment.apps/webserver created
$
```



```bash
$ kubectl get replicasets
NAME                  DESIRED   CURRENT   READY   AGE
webserver-97499b967   3         3         1       15s
$
```



```bash
$ kubectl get pods
NAME                        READY   STATUS             RESTARTS   AGE
webserver-97499b967-25x9l   1/1     Running            0          60s
webserver-97499b967-kxxw9   1/1     Running            0          60s
webserver-97499b967-vgzjl   1/1     Running            0          60s
$
```



This tutorial works.

Q: Where does the image for `nginx:alpine` reside? Docker Hub doesn't have it.

<img src="images/dockerhub-search_results-nginx_alpine.png">

I checked the three page search results, but couldn't find it.