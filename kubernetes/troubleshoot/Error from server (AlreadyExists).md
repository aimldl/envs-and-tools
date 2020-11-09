# Error from server (AlreadyExists)

## Error

```bash
Error from server (AlreadyExists): error when creating "STDIN": storageclasses.storage.k8s.io "gp2" already exists
```

When running,

```bash
$ cat <<EOF | kubectl create -f -
> kind: StorageClass
> apiVersion: storage.k8s.io/v1
> metadata:
>   name: gp2
>   annotations:
>     storageclass.beta.kubernetes.io/is-default-class: "true"
> provisioner: kubernetes.io/aws-ebs
> parameters:
>   type: gp2
> reclaimPolicy: Delete
> mountOptions:
>   - debug
> EOF

Error from server (AlreadyExists): error when creating "STDIN": storageclasses.storage.k8s.io "gp2" already exists
$
```

