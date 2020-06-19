* Draft: 2020-04-20 (Mon)



## Error



## Problem

A blog on AWS [Kubeflow on Amazon EKS](https://aws.amazon.com/ko/blogs/opensource/kubeflow-amazon-eks/) is one of two tutorials on Kubeflow installation on AWS. The other installation manual is from Kubeflow's official website. The problem with this blog is it's outdated. It's written in Sep. 30, 2018. Additionally, the command fails to work at the early stage of the listed commands. Well, the second command fails! So I started from the official Kubeflow installation manual.

The official manual is better than this blog, but the quality of writing and information are far from, well, great. It's better than nothing. So I've studied and studied it. I had to fill in the large gap missing in the manual. Anyways the installation succeeded, but the next step in the official website fails! I'm supposed to create the Jupyter Server, but the creation is pended for a long time. I've tried this and that. In other words, I've taken all possible paths to get to the Jupyter Server creation. To expedite this process, I've written a Bash script to automate the installation process which saved me from despair and waste of enter in reading and typing all those command over and over again.

Anyways, I thought I've put enough effort on this manual. Nothing can be gained from it. So I've decided to move onto the blog. At least, the blog's got other piece of information. With hope of getting out of the 



```
$ eksctl create cluster eks-kubeflow --node-type=p3.8xlarge --nodes 2 --region us-west-2 --timeout=40m
```



```
$ kubectl create -f https://raw.githubusercontent.com/NVIDIA/k8s-device-plugin/v1.10/nvidia-device-plugin.yml
error: unable to read URL "https://raw.githubusercontent.com/NVIDIA/k8s-device-plugin/v1.10/nvidia-device-plugin.yml", server reported 404 Not Found, status code=404
$
```

404 Not Found error. The link is invalid. 

> https://raw.githubusercontent.com/NVIDIA/k8s-device-plugin
>
> https://raw.githubusercontent.com/NVIDIA
>
> https://raw.githubusercontent.com

## Hint

Google search: kubectl Nvidia Kubernetes device plugin for aws yaml

I've found a page [NVIDIA device plugin for Kubernetes](https://github.com/NVIDIA/k8s-device-plugin). This is likely the source of the failed command because of the following comand.

> ### Enabling GPU Support in Kubernetes
>
> Once you have enabled this option on *all* the GPU nodes you wish to use, you can then enable GPU support in your cluster by deploying the following Daemonset:
>
> ```
> $ kubectl create -f https://raw.githubusercontent.com/NVIDIA/k8s-device-plugin/1.0.0-beta5/nvidia-device-plugin.
> ```

This command itself is identical to that of the blog. Well, the command in the source fails! Dang! But I didn't give up because these are only two most reliable and relevant documents. Other documents are worse than these two.

There exists a link on this github repository.

https://github.com/NVIDIA/k8s-device-plugin/blob/master/nvidia-device-plugin.yml

With hope this is the correct link to the yml file, I ran the following command.

```
$ kubectl create -f https://github.com/NVIDIA/k8s-device-plugin/blob/master/nvidia-device-plugin.yml
error: error parsing https://github.com/NVIDIA/k8s-device-plugin/blob/master/nvidia-device-plugin.yml: error converting YAML to JSON: yaml: line 115: mapping values are not allowed in this context
$
```

Well, even the YAML file in the source repository fails. Dang! I had to take a rest (mentally). After coming back, I read through the document instead of giving up. 

 An alternative method is explained in this page. The alternative doesn't work for me, but gives a clue.

```
$ kubectl create -f nvidia-device-plugin.yml
```

I've saved the YAML file locally and ran the following command.

## Solution

```
$ kubectl create -f nvidia-device-plugin.yaml 
daemonset.apps/nvidia-device-plugin-daemonset created
#
```

Yes! It worked! If this fails, I was going to go deeper. Do study this document until I find more clues.

## TODO?

In the YAML file, 

image: nvidia/k8s-device-plugin:1.0.0-beta5

Is there a newer version?