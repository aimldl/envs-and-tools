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

Let's see if the github link is valid. In the YAML file, 

```bash
nickchase/rss-php-nginx:v1
```

The URL should be :

https://github.com/nickchase/rss-php-nginx:v1

<img src="/home/aimldl/github/technical_skills/computing_environments/kubernetes/how_to_troubleshoot_yaml_files/images/github-error-404_this_it_not_the_web_page_you_are_looking_for.png">

Well, the link is broken.
