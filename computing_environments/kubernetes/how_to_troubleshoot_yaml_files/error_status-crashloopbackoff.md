* Draft: 2020-08-14 (Fri)

# Error Status - `CrashLoopBackoff`

## Previous

* [errors_in_names.md](errors_in_names.md)

## Situation

* I want to run H2O.ai on a Kubernetes cluster.
* A Docker image is created. This image runs properly on a local machine.
* The image is pushed to Docker Hub and readily available at
  * [aimldl/baseimage_h2o3.18.0.2_openjdk8.0.152_python3.7.6_conda4.8.3_ubuntu18.04.5](https://hub.docker.com/repository/docker/aimldl/baseimage_h2o3.18.0.2_openjdk8.0.152_python3.7.6_conda4.8.3_ubuntu18.04.5)

## YAML File

* The syntax error in the YAML file has been fixed. For details, refer to [errors_in_names.md](errors_in_names.md).

* The following YAML file includes no syntax error.

```yaml
# test_pod-h2o_ai.yaml
#  * Draft: 2020-08-14 (Fri)
#
# Usage:
#   $ kubectl create -f test_pod-h2o_ai.yaml
#   pod/rss-site created
#   $
---
apiVersion: v1
kind: Pod
metadata:
  name: test-h2o.ai
  labels:
    app: automl
spec:
  containers:
    - name: h2o3-18-0-2
      image: aimldl/baseimage_h2o3.18.0.2_openjdk8.0.152_python3.7.6_conda4.8.3_ubuntu18.04.5
      ports:
        - containerPort: 54321
# The above lines will cause the CrashLoopBackOff error.
# Uncomment the following two lines as a quick fix to the error.
#      command: ["/bin/sh"]
#      args: ["-c", "while true; do echo hello; sleep 10;done"]
```

## Pod is created

```bash
$ kubectl create -f test_pod-h2o_ai.yaml 
pod/test-h2o.ai created
$
```

## Problem: `CrashLoopBackOff`

```bash
$ kubectl get pods
NAME                        READY   STATUS             RESTARTS   AGE
test-h2o.ai                 0/1     CrashLoopBackOff   4          6m8s
  ...
$
```

As `RESTARTS` indicates, restart has been attempted four times. And six times below.

```bash
$ kubectl get pods
NAME                        READY   STATUS             RESTARTS   AGE
test-h2o.ai                 0/1     CrashLoopBackOff   6          11m
  ...
$
```

A restart attempt has no meaning. Let's delete the pod.

```bash
$ kubectl delete -f test_pod-h2o_ai.yaml 
pod "test-h2o.ai" deleted
$
```

## Questions

Q: What does this status mean?

Q: Why does `CrashLoopBackOff` occur?

Q: What might be wrong?

* The Docker image itself?
* The YAML file?
* The `kubectl` command?
* or something else?

Q: How can I fix this error?

## Hint

### `kubectl describe pod <pod_name>` 

The `kubectl describe pod <pod_name>` command shows the detailed information about the pod.

```bash
$ kubectl describe pod test-h2o.ai
  ...
Events:
  Type     Reason     Age                From                                    Message
  ----     ------     ----               ----                                    -------
  Normal   Scheduled  <unknown>          default-scheduler                       Successfully assigned default/test-h2o.ai to k8snode01-alienware-aurora-r7
  Normal   Pulling    10s (x3 over 32s)  kubelet, k8snode01-alienware-aurora-r7  Pulling image "aimldl/baseimage_h2o3.18.0.2_openjdk8.0.152_python3.7.6_conda4.8.3_ubuntu18.04.5"
  Normal   Pulled     7s (x3 over 29s)   kubelet, k8snode01-alienware-aurora-r7  Successfully pulled image "aimldl/baseimage_h2o3.18.0.2_openjdk8.0.152_python3.7.6_conda4.8.3_ubuntu18.04.5"
  Normal   Created    6s (x3 over 29s)   kubelet, k8snode01-alienware-aurora-r7  Created container h2o3-18-0-2
  Normal   Started    6s (x3 over 29s)   kubelet, k8snode01-alienware-aurora-r7  Started container h2o3-18-0-2
  Warning  BackOff    5s (x3 over 24s)   kubelet, k8snode01-alienware-aurora-r7  Back-off restarting failed container
$
```

As `Events` shows, a resource is assigned to a node, the Docker image is successfully pulled and the corresponding container is created, too. `Back-off restarting failed container` is an issue at the moment.

### `kubectl logs <pod_name>`

To obtain another hint, the log is checked.

```bash
$ kubectl logs test-h2o.ai
$
```

There is no log at all which is normal and expected. For details, refer to [My kubernetes pods keep crashing with “CrashLoopBackOff” but I can't find any log](https://stackoverflow.com/questions/41604499/my-kubernetes-pods-keep-crashing-with-crashloopbackoff-but-i-cant-find-any-lo)

## Answers to the questions

### Q: What does this status  `CrashLoopBackOff` mean?

### A:

> A CrashloopBackOff means that you have a pod starting, crashing, starting again, and then crashing again. [...] 
>
> Source: [What is a CrashLoopBackOff? How to alert, debug / troubleshoot, and fix Kubernetes CrashLoopBackOff events](https://sysdig.com/blog/debug-kubernetes-crashloopbackoff/), Knox Anderson, 2018-03-27

More detailed information excerpted from  [What is a CrashLoopBackOff? How to alert, debug / troubleshoot, and fix Kubernetes CrashLoopBackOff events is below.

> As all veteran Kubernetes users know, Kubernetes CrashLoopBackOff events are a way of life. It’s happened to all of us at least once and normally we’re stuck scratching our heads with no access to troubleshooting tools inside the container.

`restartPolicy` applies to all containers in a pod.

* `Always` (default)
* `OnFailure`
* `Never`

For example,

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: dummy-pod
spec:
  containers:
    - name: dummy-pod
      image: ubuntu
  restartPolicy: Always
```

> Failed containers are restarted by `kubelet` with an exponential back-off delay (10s, 20s, 40s …) capped at five minutes, and is reset after ten minutes of successful execution.

### Q: Why does `CrashLoopBackOff` occur?

> - The application inside the container keeps crashing
> - [Some type of parameters of the pod or container have been configured incorrectly](https://stackoverflow.com/questions/41604499/my-kubernetes-pods-keep-crashing-with-crashloopbackoff-but-i-cant-find-any-lo)
> - [An error has been made when deploying Kubernetes](https://stackoverflow.com/questions/35537834/debugging-a-container-in-a-crash-loop-on-kubernetes)



> This most likely means that Kubernetes started your container, then the  container subsequently exited.  As we all know, the Docker container  should hold and keep pid 1 running or the container exits.  When the  container exits, Kubernetes will try to restart it.  After restarting it a few times, it will declare this `BackOff` state.  However, Kubernetes will keep on trying to restart it.
>
> Source: [Kubernetes Troubleshooting Walkthrough - Pod Failure CrashLoopBackOff](https://managedkube.com/kubernetes/pod/failure/crashloopbackoff/k8sbot/troubleshooting/2019/02/12/pod-failure-crashloopbackoff.html)

### Q: What might be wrong?

* The Docker image itself?
  * No. The container from the image runs properly on a local machine. As the `kubectl describe` command shows, a container is created from the image.

```bash
$ kubectl describe pod test-h2o.ai
  ...
Normal   Created ... kubelet, k8snode01-alienware-aurora-r7  Created container h2o3-18-0-2
Normal   Started ... kubelet, k8snode01-alienware-aurora-r7  Started container h2o3-18-0-2
  ...
$
```

* The `kubectl` command?
  * Nope. There is nothing wrong with the command itself.
* The YAML file?
  * No syntax error exists in the YAML. Otherwise a pod cannot be created.
  * But possibly yes! 
    * A small change in the YAML file can fix the problem.

> I observed the same issue, and added the command and args block in yaml file. 
>
> ```yaml
>     command: ["/bin/sh"]
>     args: ["-c", "while true; do echo hello; sleep 10;done"]
> ```
> The full YAML file is below.
>
> ```yaml
>  apiVersion: v1
>     kind: Pod
>     metadata:
>       labels:
>         run: ubuntu
>       name: ubuntu
>       namespace: default
>     spec:
>       containers:
>       - image: gcr.io/ow/hellokubernetes/ubuntu
>         imagePullPolicy: Never
>         name: ubuntu
>         resources:
>           requests:
>             cpu: 100m
>         command: ["/bin/sh"]
>         args: ["-c", "while true; do echo hello; sleep 10;done"]
>       dnsPolicy: ClusterFirst
>       enableServiceLinks: true
> ```
>
> Source: [My kubernetes pods keep crashing with “CrashLoopBackOff” but I can't find any log](https://stackoverflow.com/questions/41604499/my-kubernetes-pods-keep-crashing-with-crashloopbackoff-but-i-cant-find-any-lo)

* or something else?

### Q: How can I fix this error?

[Kubernetes Troubleshooting Walkthrough - Pod Failure CrashLoopBackOff](https://managedkube.com/kubernetes/pod/failure/crashloopbackoff/k8sbot/troubleshooting/2019/02/12/pod-failure-crashloopbackoff.html) explains the topic quite nicely.

* Introduction: troubleshooting CrashLoopBackOff
  * Step One: Describe the pod for more information
    * Look at `Events` first.

```bash
$ kubectl describe pod <pod_name>
  ...
Events:
  Type     Reason     Age               From                                     Message
  ----     ------     ----              ----    
  ...
$
```

* Step Two: Get the logs of the pod

```bash
$ kubectl logs <pod_name>
```

* Step Three: Look at the Liveness probe
* [?}] I have no idea what "'"liveness probe" is.

## A quick fix is to run a command

A command must be run after a container starts in a pod. A quick fix to the `CrashLoopBackOff` error is to add a command to the YAML file. Adding the following command removes the error anyways.

```yaml
    command: ["/bin/sh"]
    args: ["-c", "while true; do echo hello; sleep 10;done"]
```

Create a pod with the new YAML file with the above lines in the container spec.

```bash
$ kubectl create -f test_pod-h2o_ai.yaml 
pod/test-h2o.ai created
$
```

Checking the status in six second shows a container is being created.

```bash
$ kubectl get pods
NAME                        READY   STATUS              RESTARTS   AGE
test-h2o.ai                 0/1     ContainerCreating   0          6s
  ...
$
```

Soon after (at nine second), the container is running.

```bash
$ kubectl get pods
NAME                        READY   STATUS    RESTARTS   AGE
test-h2o.ai                 1/1     Running   0          9s
  ...
$
```

 Yay! The cause of the error is identified. The reason is because a command is not ran after starting the pod. The added command iteratively prints out "hello" at every 10 seconds. Let's check the output as an exercise.

```bash
$ kubectl logs test-h2o.ai
hello
hello
  ...
hello
$
```

### The full YAML file with the quick fix

```yaml
# test_pod-h2o_ai.yaml
#  * Draft: 2020-08-14 (Fri)
#
# Usage:
#   $ kubectl create -f test_pod-h2o_ai.yaml
#   pod/rss-site created
#   $
---
apiVersion: v1
kind: Pod
metadata:
  name: test-h2o.ai
  labels:
    app: automl
spec:
  containers:
    - name: h2o3-18-0-2
      image: aimldl/baseimage_h2o3.18.0.2_openjdk8.0.152_python3.7.6_conda4.8.3_ubuntu18.04.5
      ports:
        - containerPort: 54321
      command: ["/bin/sh"]
      args: ["-c", "while true; do echo hello; sleep 10;done"]
```

Notice this is just a quick fix, not a permanent solution. My target is to use H2O running on a Kubernetes cluster. So delete the pod as "hello" is being printed every 10 seconds.

```bash
$ kubectl delete -f test_pod-h2o_ai.yaml 
pod "test-h2o.ai" deleted
$
```





```
$ docker pull aimldl/baseimage_h2o3.18.0.2_openjdk8.0.152_python3.7.6_conda4.8.3_ubuntu18.04.5
Using default tag: latest
latest: Pulling from aimldl/baseimage_h2o3.18.0.2_openjdk8.0.152_python3.7.6_conda4.8.3_ubuntu18.04.5
  ...
Status: Downloaded newer image for aimldl/baseimage_h2o3.18.0.2_openjdk8.0.152_python3.7.6_conda4.8.3_ubuntu18.04.5:latest
docker.io/aimldl/baseimage_h2o3.18.0.2_openjdk8.0.152_python3.7.6_conda4.8.3_ubuntu18.04.5:latest
$ 
```



```
$ docker run -it -p 54321:54321 aimldl/baseimage_h2o3.18.0.2_openjdk8.0.152_python3.7.6_conda4.8.3_ubuntu18.04.5
2020-08-14 (Fri) 07:16 (32th week)
Welcome to ubuntu18.04, conda 4.8.3, Python 3.7.6
(base) user@5b3d8a21928a:~$ 
```



```
(base) user@5b3d8a21928a:~$ java -jar anaconda3/h2o_jar/h2o.jar 
08-14 07:16:51.695 172.17.0.2:54321      43     main      INFO: Found XGBoost backend with library: xgboost4j_gpu
08-14 07:16:51.712 172.17.0.2:54321      43     main      INFO: XGBoost supported backends: [WITH_GPU, WITH_OMP]
08-14 07:16:51.713 172.17.0.2:54321      43     main      INFO: ----- H2O started  -----
08-14 07:16:51.713 172.17.0.2:54321      43     main      INFO: Build git branch: (HEAD detached from jenkins-3.18.0.2)
  ...
```



http://localhost:54321/



To quit H2O Flow, enter `Ctrl+C`. To exit the container, enter `exit`.

```bash
  ...
08-14 07:17:39.990 172.17.0.2:54321      43     #73041-16 INFO: GET /flow/fonts/fontawesome-webfont.woff, parms: {v=4.2.0}
^C(base) user@5b3d8a21928a:~$ ^C
(base) user@5b3d8a21928a:~$ exit
exit
$
```



Add this.

```yaml
       command: ["/bin/sh"]
       args: ["-p 54321:54321", "-c", "java -jar anaconda3/h2o_jar/h2o.jar"]
```



```bash
$ kubectl create -f test_pod-h2o_ai.yaml
pod/test-h2o.ai created
$
```



```bash
$ kubectl get pods
NAME                        READY   STATUS             RESTARTS   AGE
test-h2o.ai                 0/1     CrashLoopBackOff   1          26s
  ...
$
```

