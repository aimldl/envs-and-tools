* Draft: 2020-08-14 (Fri)

# Errors in Names

To create a pod from an YAML file, you must abide by the Kubernetes naming convention which:

* prevents underscore `_` while
* dot `.` is allowed for metadata name, but prohibited for `spec: containers`'s name

```bash
$ kubectl create -f test_pod-h2o_ai.yaml 
```

## Problem 1: `name: test-h2o_ai`

### Do not use an underscore `_`

```yaml
metadata:
  name: test-h2o_ai
```

is an invalid name with the following error

```bash
The Pod "test-h2o_ai" is invalid: 
* metadata.name: Invalid value: "test-h2o_ai": a DNS-1123 subdomain must consist of lower case alphanumeric characters, '-' or '.', and must start and end with an alphanumeric character (e.g. 'example.com', regex used for validation is '[a-z0-9]([-a-z0-9]*[a-z0-9])?(\.[a-z0-9]([-a-z0-9]*[a-z0-9])?)*')
```

## Solution 1: `test-h2o_ai` →`test-h2o.ai`

### Do use a dash `-` or dot `.`

```yaml
metadata:
  name: test-h2o.ai
```



## Problem 2: `name: h2o3_18_0_2`

### Do not use an underscore `_` or dot `.` for `spec: containers` 

```yaml
spec:
  containers:
    - name: h2o3_18_0_2
```

causes the following error

```bash
* spec.containers[0].name: Invalid value: "h2o3_18_0_2": a DNS-1123 label must consist of lower case alphanumeric characters or '-', and must start and end with an alphanumeric character (e.g. 'my-name',  or '123-abc', regex used for validation is '[a-z0-9]([-a-z0-9]*[a-z0-9])?')
[1]+  Done                    gedit test_webserver.yaml
```

## Solution 2: `h2o3_18_0_2` →`h2o3-18-0-2`

### Do use a dash `-` (only dash)

```bash
$ kubectl create -f test_pod-h2o_ai.yaml 
pod/test-h2o.ai created
$
```

## Next

* [error_status-crashloopbackoff.md](error_status-crashloopbackoff.md)