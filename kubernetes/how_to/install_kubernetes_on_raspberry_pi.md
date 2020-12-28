* Draft: 2020-12-28 (Mon)

# How to Install Kubernetes on Raspberry Pi

## Overview

[Kubernetes](https://kubernetes.io/) is an open source system for automating deployment, scaling, and management for containerized applications. If a production-grade back-end system with ease of management must be developed, consider [Kubernetes](https://kubernetes.io/) as an option. 

One of the hurdles to build such a system is the learning curve.  The purpose of this article is to alleviate the pain in the process of building such a system. One of the pain (in my experience) is web articles which do not help toward the working system. I will find the promising web articles, do the hands-on by myself, and provide the summary in the course of making a working system in order for you to save some time.

As the first step, a toy system with Raspberry Pi will be built to gain some experience in Kubernetes. The gained experience can be easily extensible to NVIDIA Jetson Nano, another lightweight edge device with GPU support.

## Prerequisites

* Experience with Linux
* Understanding of Docker
* Basics on Kubernetes

## Referred articles

Google search: How to install k3s on Raspberry Pi

[1] [Run Kubernetes on Your Raspberry Pi Cluster With K3s](https://medium.com/@ikarus/run-kubernetes-on-your-raspberry-pi-cluster-with-k3s-ac3687d6eb1a)

* Some basic knowledge on Kubernetes is covered in this article.
* Compatibility between Kubernetes and Raspberry Pi is discussed. 

## Compatibility of Kubernetes on Raspberry Pi

After deciding to install Kubernetes on Raspberry Pi, the question raised in my mind is "Is it possible to install Kubernetes on Raspberry Pi 4?". Raspberry Pi is a low cost, low performance computer. Kubernetes has the minimum requirements. The answer is "Yes." The follow-up question is "What about the older version of Raspberry Pi I have?". The answer is "Raspberry Pi2 and above." According to [1], Raspberry Pi 2 and above with memory size of 8GB+ is the bare minimum to install Kubernetes on Raspberry Pi.

### Minimum requirements of Kubernetes

Ubuntu 16.04+, 2GB+ RAM, 2+ CPUs, network connectivity, unique hostname, MAC address, and product_uuid, certain ports are open, and swap disabled.

For details, refer to [Installing kubeadm](https://kubernetes.io/docs/setup/production-environment/tools/kubeadm/install-kubeadm/)

### Raspberry Pi

#### Hardwares

> As of 2020-07-29, Kubernetes will only work on the Raspberry Pi 2 and newer models because of the supported ARM architectures. For details, refer to the `Compatibility issues` section in [Run Kubernetes on Your Raspberry Pi Cluster With K3s](https://medium.com/@ikarus/run-kubernetes-on-your-raspberry-pi-cluster-with-k3s-ac3687d6eb1a). 

#### Memory requirements

2GB+ RAM is the minimum requirements for Kubernetes while 8GB+ is recommended to run `etcd` the database for Kubernetes.

## Choice of Kubernetes flavor

Flavors of Kubernetes are available for Raspberry Pi.

* The vanilla Kubernetes (denoted as k8s)
* [k3s](https://k3s.io/): lightweight Kubernetes for resource-constrained edge devices

Instead of the full k8s, a lightweight k3s will be used. 

### [k3s](https://k3s.io/)

* capable of using a datastore other than `etcd`
* Embedded SQLite database in the main node (by default)
  * SQLite database may corrupt due to power loss.
* PostgreSQL, MySQL, MariaDB (with multi-master setups)

#### Terminologies

|        | k8s    | k3s    |
| ------ | ------ | ------ |
| master | master | server |
| slave  | worker | agent  |

<img src='https://k3s.io/images/how-it-works-k3s.svg'>

Source: https://k3s.io/

## Installing k3s

There are two ways to install k3s: manual installation vs. installation with Ansible. k3s will be installed manually in this article because the purpose is to gain some experience with k8s.

### Manual installation of k3s

Step 1. Install k3s on the server(s)

Step 2. Install k3s on the agent(s).

Step 3. Connect the cluster from your computer.

#### Step 1. Install k3s on the server(s)

```bash
(base) $ conda deactivate
```

```bash
$ curl -sfL https://get.k3s.io | sh -
```

Make k3s as close as vanilla k8s by deploying your own ingress controller and load balancer.

```bash
$ curl -sfL https://get.k3s.io | sh - --no-deploy traefik --no-deploy servicelb
```

