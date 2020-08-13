* Draft: 2020-08-13 (Thu)

# Errors in a YAML File to Create a Pod

* This page is to fix errors in the YAML file for [Introduction to YAML: Creating a Kubernetes deployment](https://www.mirantis.com/blog/introduction-to-yaml-creating-a-kubernetes-deployment/), Nick Chase, 2020-03-11.
* The YAML file contains several syntax errors and they are fixed.
* The fixed YAML file fails to create a pod, but let's fix the errors.

```yaml
# test_pod.yaml
#  * Draft: 2020-08-13 (Thu)
#
# Introduction to YAML: Creating a Kubernetes deployment, Nick Chase, 2020-03-11
#   https://www.mirantis.com/blog/introduction-to-yaml-creating-a-kubernetes-deployment/
# Usage:
#   $ kubectl create -f test_pod.yaml 

---
apiVersion: v1
kind: Pod
metadata:
  name: rss-site
  labels:
    app: web
  spec:
    containers:
    - name: front-end
      image: nginx
      ports:
        - containerPort: 80
      - name: rss-reader
        image: nickchase/rss-php-ngnix:v1
        ports:
          -containerPort: 88

```

## Problem 1

```bash
$ kubectl create -f test_pod.yaml 
error: error parsing test_pod.yaml: error converting YAML to JSON: yaml: line 12: did not find expected key
$
```

## Solution 1

The wrong indentation was the cause. Two spaces are removed from each line.

### Before

```yaml
  ...
        - containerPort: 80
      - name: rss-reader
        image: nickchase/rss-php-ngnix:v1
        ports:
          -containerPort: 88
```



### After

```yaml
  ...
        - containerPort: 80
    - name: rss-reader
      image: nickchase/rss-php-ngnix:v1
      ports:
        -containerPort: 88
```

### Verification & Problem 2

```bash
$ kubectl create -f test_pod.yaml 
error: error validating "test_pod.yaml": error validating data: ValidationError(Pod.metadata): unknown field "spec" in io.k8s.apimachinery.pkg.apis.meta.v1.ObjectMeta; if you choose to ignore these errors, turn validation off with --validate=false
$
```

```yaml
---
 apiVersion: v1
 kind: Pod
 metadata:
   name: rss-site
   labels:
     app: web
 spec:
```

## Solution

`ValidationError(Pod.metadata): unknown field "spec"` was the hint. I compared the tutorial and found wrong indentation for `spec` which should be at the same level with `metadata`.

### Before

```yaml
  ...
metadata:
  ...
  spec:
    containers:
    - name: front-end
      image: nginx
      ports:
        - containerPort: 80
    - name: rss-reader
      image: nickchase/rss-php-ngnix:v1
      ports:
        -containerPort: 88
```

### After

```yaml
  ...
metadata:
  name: rss-site
  labels:
    app: web
spec:
  containers:
  - name: front-end
    image: nginx
    ports:
      - containerPort: 80
  - name: rss-reader
    image: nickchase/rss-php-ngnix:v1
    ports:
      -containerPort: 88
```

## Verification & Problem 3

```bash
$ kubectl create -f test_pod.yaml 
error: error validating "test_pod.yaml": error validating data: ValidationError(Pod.spec.containers[1].ports): invalid type for io.k8s.api.core.v1.Container.ports: got "map", expected "array"; if you choose to ignore these errors, turn validation off with --validate=false
$
```

## Solution 3

`ValidationError(Pod.spec.containers[1].ports): invalid type for io.k8s.api.core.v1.Container.ports: got "map", expected "array"` was the hint. `array` is expected, but `map` is used in the YAML file.

### Before

```yaml
  ...
spec:
  ...
    ports:
      -containerPort: 88
```

### After

```yaml
  ...
spec:
  ...
    ports:
        - containerPort: 88
```

There is a space between - and containerPort.

## Verification

```bash
$ kubectl create -f test_pod-nickchase.yaml 
pod/rss-site created
$
```

Well, the pod is successfully created after fixing all the syntactical errors.

But the pod is not running anyways. Refer to [errorneous_status-kubectl_create.md](errorneous_status-kubectl_create.md) for details.