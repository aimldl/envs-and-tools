* Draft: 2020-08-13 (Thu)

# Error Status - `ImagePullBackOff`

## `ImagePullBackOff` after successful `kubectl create`

### Problem

When no syntax error exists, a pod is created as follows.

```bash
$ kubectl create -f test_pod-nickchase.yaml
pod/rss-site created
$
```

However the `STATUS` remains `ImagePullBackOff`. Why?

```bash
$ kubectl get pods
NAME       READY   STATUS             RESTARTS   AGE
rss-site   1/2     ImagePullBackOff   0          2m7s
$
```

### Hint

The `kubectl describe pod <pod_name>` shows the detailed events when the `kubectl create` command ran.

```bash
$ kubectl describe pod rss-site
  ...
Events:
  Type     Reason     Age                From                                    Message
  ----     ------     ----               ----                                    -------
  Normal   Scheduled  <unknown>          default-scheduler                       Successfully assigned default/rss-site to k8snode01-alienware-aurora-r7
  Normal   Pulling    65s                kubelet, k8snode01-alienware-aurora-r7  Pulling image "nginx"
  Normal   Pulled     55s                kubelet, k8snode01-alienware-aurora-r7  Successfully pulled image "nginx"
  Normal   Created    54s                kubelet, k8snode01-alienware-aurora-r7  Created container front-end
  Normal   Started    54s                kubelet, k8snode01-alienware-aurora-r7  Started container front-end
  Normal   BackOff    21s (x2 over 50s)  kubelet, k8snode01-alienware-aurora-r7  Back-off pulling image "nickchase/rss-php-ngnix:v1"
  Warning  Failed     21s (x2 over 50s)  kubelet, k8snode01-alienware-aurora-r7  Error: ImagePullBackOff
  Normal   Pulling    7s (x3 over 54s)   kubelet, k8snode01-alienware-aurora-r7  Pulling image "nickchase/rss-php-ngnix:v1"
  Warning  Failed     4s (x3 over 51s)   kubelet, k8snode01-alienware-aurora-r7  Failed to pull image "nickchase/rss-php-ngnix:v1": rpc error: code = Unknown desc = Error response from daemon: pull access denied for nickchase/rss-php-ngnix, repository does not exist or may require 'docker login': denied: requested access to the resource is denied
  Warning  Failed     4s (x3 over 51s)   kubelet, k8snode01-alienware-aurora-r7  Error: ErrImagePull
$
```

The above output shows `docker login` failed. The lack of log-in credentials is the likely cause.

Let's see if the github link is valid. In the YAML file, 

```bash
nickchase/rss-php-nginx:v1
```

The URL should be :

https://github.com/nickchase/rss-php-nginx:v1

<img src="/home/aimldl/github/technical_skills/computing_environments/kubernetes/how_to_troubleshoot_yaml_files/images/github-error-404_this_it_not_the_web_page_you_are_looking_for.png">

Well, the link is broken. No wonder pulling image has failed. The image itself does not exist.

## Q: Where does kubernetes pull the docker image from?

The following figure shows where Kubernetes pulls an image from. The default Docker registry is Docker Hub.

<img src="https://codefresh.io/docs/images/getting-started/quick-start-k8s/overview.png">

Source: [Accessing a Docker registry from your Kubernetes cluster](https://codefresh.io/docs/docs/deploy-to-kubernetes/access-docker-registry-from-kubernetes/)

For details, read the following links.

* [How Kubernetes Pulls Image from outer respository? Where is the image stored?](https://stackoverflow.com/questions/52666201/how-kubernetes-pulls-image-from-outer-respository-where-is-the-image-stored)

* [Accessing a Docker registry from your Kubernetes cluster](https://codefresh.io/docs/docs/deploy-to-kubernetes/access-docker-registry-from-kubernetes/)
* [Pull an Image from a Private Registry](https://kubernetes.io/docs/tasks/configure-pod-container/pull-image-private-registry/)
* [Pulling Images from Registry during Kubernetes Deployment](https://docs.cloud.oracle.com/en-us/iaas/Content/Registry/Tasks/registrypullingimagesfromocir.htm)

