* Draft: 2020-08-13 (Thu)

# Error Status - `InvalidImageName`

## InvalidImageName after successful `kubectl create'

 I've replaced the Nickcase's image to the official nginx image and created a new YAML file `test_pod-official_nginx.yaml`. The only change from `test_pod-nickchase.yaml` is 

<img src="images/meld-comparing_two_yaml_files.png">



The following page is the search results with `nginx` in Docker Hub.

<img src="images/dockerhub-search_results_with_ngnix.png">

I tried to replace the broken link in the tutorial by Nickcase with the official nginix image.

A pod is successfully created because the image exists.

```bash
$ kubectl create -f test_pod-official_nginx.yaml 
pod/official-nginx created
$
```

The status is `ContainerCreating` right after the above command.

```bash
$ kubectl get pods
NAME             READY   STATUS              RESTARTS   AGE
official-nginx   0/2     ContainerCreating   0          9s
rss-site         1/2     ImagePullBackOff    0          3m45s
$
```

Soon the status has become `InvalidImageName`. 

```bash
$ kubectl get pods
NAME             READY   STATUS             RESTARTS   AGE
official-nginx   1/2     InvalidImageName   0          17s
rss-site         1/2     ImagePullBackOff   0          3m53s
$
```

So far what has seen is that the status error `ImagePullBackOff` from a broken link of Docker image can be fixed with a valid link (official Nginx).

Now the problem is `InvalidImageName`. In the following part, let's see what happens when the image name is changed to a unique one. Notice the used image is pre-occupied by `rss-site`.

First, let's delete all the existing pods with the `--all` option.

```bash
$ kubectl delete pods --all
pod "official-nginx" deleted
pod "rss-site" deleted
$
```

Let's double-check to see if the existing pods are deleted.

```bash
$ kubectl get pods
No resources found in default namespace.
$
```

Change the file names in `test_pod-official_nginx.yaml`

### Before

```yaml
asdf
```

### After

```yaml
spec:
  containers:
    - name: nginx
  ...
    - name: official-nginx
  ...
```



Let's create a pod.

```bash
$ kubectl create -f test_pod-official_nginx.yaml 
pod/official-nginx created
$
```

A pod is created without a problem because a Docker image exists in the Docker Hub, the public Docker image registry. Checking the pod's status reveals a container is being created from the image (official nginx image).

```bash
$ kubectl get pods
NAME             READY   STATUS              RESTARTS   AGE
official-nginx   0/2     ContainerCreating   0          6s
$
```

Soon after the build process of a container from the image, the status is an error.

```bash
$ kubectl get pods
NAME             READY   STATUS             RESTARTS   AGE
official-nginx   1/2     InvalidImageName   0          60s
$
```

