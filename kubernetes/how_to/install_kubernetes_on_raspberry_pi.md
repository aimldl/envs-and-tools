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

* A server node is defined as a machine running the `k3s server` command. 

* A worker node is defined as a machine running the `k3s agent` command.

Source: [k3s](https://k3s.io/) > [Docs](https://rancher.com/docs/k3s/latest/en/) > [Architecture](https://rancher.com/docs/k3s/latest/en/architecture/)

<img src='https://k3s.io/images/how-it-works-k3s.svg'>

Source: https://k3s.io/



## Installing k3s

There are two ways to install k3s: manual installation vs. installation with Ansible. k3s will be installed manually in this article because the purpose is to gain some experience with k8s. 

For more information, refer to "[k3s](https://k3s.io/) > [Docs](https://rancher.com/docs/k3s/latest/en/) > [Quick-Start Guide](https://rancher.com/docs/k3s/latest/en/quick-start/)" to learn about the installation commands. For more details on installation, refer to "[k3s](https://k3s.io/) > [Docs](https://rancher.com/docs/k3s/latest/en/) > [Installation](https://rancher.com/docs/k3s/latest/en/installation/)". 

### Manual installation of k3s

Step 1. Install k3s on the server(s)

Step 2. Fetch some server information needed by agents.

Step 3. Install k3s on the agent(s).

Step 4. Verify the k3s cluster is up and running.

Step 5. Access the cluster from your computer.

#### Step 1. Install k3s on the server(s)

Power up a computer to use as the server. The computer must not have k8s installed on the machine. Run:

```bash
$ curl -sfL https://get.k3s.io | sh -
```

> - The K3s service will be configured to automatically restart after node reboots or if the process crashes or is killed
> - Additional utilities will be installed, including `kubectl`, `crictl`, `ctr`, `k3s-killall.sh`, and `k3s-uninstall.sh`
> - A [kubeconfig](https://kubernetes.io/docs/concepts/configuration/organize-cluster-access-kubeconfig/) file will be written to `/etc/rancher/k3s/k3s.yaml` and the kubectl installed by K3s will automatically use it
>
> Source:  [k3s](https://k3s.io/) > [Docs](https://rancher.com/docs/k3s/latest/en/) > [Quick-Start Guide](https://rancher.com/docs/k3s/latest/en/quick-start/)

The full message from the above command is in appendix.

Note: **To uninstall, run the `k3s-uninstall.sh` script** generated at the time of installation at `/usr/local/bin/k3s-uninstall.sh`.

```bash
$ cd /usr/local/bin/
$ ls k3s*
k3s  k3s-killall.sh  k3s-uninstall.sh
$
```

Make k3s as close as vanilla k8s by deploying your own ingress controller and load balancer.

```bash
$ curl -sfL https://get.k3s.io | sh - --no-deploy traefik --no-deploy servicelb
```

#### Step 2. Fetch some server information needed by agents.

In the next step, two pieces of information is necessary by agents.

1. `k3s_server_location `

IP address or hostname of the k3s server

```bash
# Get the IP address
$ ifconfig | grep 'inet '
   ...
        inet 192.168.0.118  netmask 255.255.255.0  broadcast 192.168.0.255
$
```

```bash
# Get the hostname
$ hostname
k3sserver-Alienware-Aurora-R7
$
```

2. `k3s_server_node_token`

`node-token` of the k3s server

```bash
$ sudo cat /var/lib/rancher/k3s/server/node-token
[sudo] k3sserver의 암호: 
K1085d9b7fe6396fc4c1426cc44317c31b4692c102247ee645d6c47a400ab6ad29b::server:809170c0a067f84398bbfc473ab5a2d2
$
```

#### Step 3. Install k3s on the agent(s).

Power up the computer to use as an agent. In this case, a Raspberry Pi is the computer. `k3s_server_location ` and `k3s_server_node_token` in the 

```bash
$ curl -sfL https://get.k3s.io | \
  K3S_URL=https://k3s_server_location:6443 \
  K3S_TOKEN=k3s_server_node_token \
  sh -
```

Given the k3s server information in the previous step, an example command is:

```bash
$ curl -sfL https://get.k3s.io | \
  K3S_URL=https://192.168.0.118:6443 \
K3S_TOKEN=K1085d9b7fe6396fc4c1426cc44317c31b4692c102247ee645d6c47a400ab6ad29b::server:809170c0a067f84398bbfc473ab5a2d2 \
  sh -
```

The full message from the above command is in appendix.

Note: **To uninstall, run the `k3s-agent-uninstall.sh` script** generated at the time of installation at `/usr/local/bin/k3s-agent-uninstall.sh`.

```bash
$ cd /usr/local/bin/
$ ls k3s*
k3s  k3s-agent-uninstall.sh  k3s-killall.sh
$
```

#### Step 4. Verify the k3s cluster is up and running.

When a k3s server and a k3s agent are installed, a k3s cluster is launched with default options.

On the k3s server side, run k3s server and verify if the cluster is up and running.

```bash
$ sudo k3s server &
[1] 72766
$ sudo k3s kubectl get node
[sudo] k3sserver의 암호: 
NAME                            STATUS   ROLES    AGE   VERSION
k3sserver-alienware-aurora-r7   Ready    master   71m   v1.19.5+k3s2
pi                              Ready    <none>   42m   v1.19.5+k3s2
$
```

#### Step 5. Access the cluster from your computer.

```

```



## Appendix. Full message to install k3s on the server(s)

When I installed k3s on Ubuntu 20.04 freshly installed, the installation went smooth.

```bash
k3sserver@desktop-1:~$ curl -sfL https://get.k3s.io | sh -
[sudo] k3sserver의 암호: 
[INFO]  Finding release for channel stable
[INFO]  Using v1.19.5+k3s2 as release
[INFO]  Downloading hash https://github.com/rancher/k3s/releases/download/v1.19.5+k3s2/sha256sum-amd64.txt
[INFO]  Downloading binary https://github.com/rancher/k3s/releases/download/v1.19.5+k3s2/k3s
[INFO]  Verifying binary download
[INFO]  Installing k3s to /usr/local/bin/k3s
[INFO]  Creating /usr/local/bin/kubectl symlink to k3s
[INFO]  Creating /usr/local/bin/crictl symlink to k3s
[INFO]  Creating /usr/local/bin/ctr symlink to k3s
[INFO]  Creating killall script /usr/local/bin/k3s-killall.sh
[INFO]  Creating uninstall script /usr/local/bin/k3s-uninstall.sh
[INFO]  env: Creating environment file /etc/systemd/system/k3s.service.env
[INFO]  systemd: Creating service file /etc/systemd/system/k3s.service
[INFO]  systemd: Enabling k3s unit
Created symlink /etc/systemd/system/multi-user.target.wants/k3s.service → /etc/systemd/system/k3s.service.
[INFO]  systemd: Starting k3s
k3sserver@desktop-1:~$
```

When I have installed k3s on an existing k8s master node, the following error message occurs.

```bash
k8smaster@desktop-1:~$ curl -sfL https://get.k3s.io | sh -
[sudo] k8smaster의 암호: 
[INFO]  Finding release for channel stable
[INFO]  Using v1.19.5+k3s2 as release
[INFO]  Downloading hash https://github.com/rancher/k3s/releases/download/v1.19.5+k3s2/sha256sum-amd64.txt
[INFO]  Downloading binary https://github.com/rancher/k3s/releases/download/v1.19.5+k3s2/k3s
[INFO]  Verifying binary download
[INFO]  Installing k3s to /usr/local/bin/k3s
[INFO]  Skipping /usr/local/bin/kubectl symlink to k3s, command exists in PATH at /usr/bin/kubectl
[INFO]  Skipping /usr/local/bin/crictl symlink to k3s, command exists in PATH at /usr/bin/crictl
[INFO]  Skipping /usr/local/bin/ctr symlink to k3s, command exists in PATH at /usr/bin/ctrnstall k3s on the agent(s)
[INFO]  Creating killall script /usr/local/bin/k3s-killall.sh
[INFO]  Creating uninstall script /usr/local/bin/k3s-uninstall.sh
[INFO]  env: Creating environment file /etc/systemd/system/k3s.service.env
[INFO]  systemd: Creating service file /etc/systemd/system/k3s.service
[INFO]  systemd: Enabling k3s unit
Created symlink /etc/systemd/system/multi-user.target.wants/k3s.service → /etc/systemd/system/k3s.service.
[INFO]  systemd: Starting k3s
Job for k3s.service failed because the control process exited with error code.
See "systemctl status k3s.service" and "journalctl -xe" for details.
k8smaster@desktop-1:~$
```

## Appendix. Full message to install k3s on the agent(s)

```bash
pi@pi:~$ curl -sfL https://get.k3s.io | \
  K3S_URL=https://192.168.0.118:6443 \
K3S_TOKEN=K1085d9b7fe6396fc4c1426cc44317c31b4692c102247ee645d6c47a400ab6ad29b::server:809170c0a067f84398bbfc473ab5a2d2 \
  sh -
[INFO]  Finding release for channel stable
[INFO]  Using v1.19.5+k3s2 as release
[INFO]  Downloading hash 
[INFO]  Downloading binary 
[INFO]  Verifying binary download
[INFO]  Installing k3s to /usr/local/bin/k3s
[INFO]  Creating /usr/local/bin/kubectl symlink to k3s
[INFO]  Creating /usr/local/bin/crictl symlink to k3s
[INFO]  Creating /usr/local/bin/ctr symlink to k3s
[INFO]  Creating killall script /usr/local/bin/k3s-killall.sh
[INFO]  Creating uninstall script /usr/local/bin/k3s-agent-uninstall.sh
[INFO]  env: Creating environment file /etc/systemd/system/k3s-agent.service.env
[INFO]  systemd: Creating service file /etc/systemd/system/k3s-agent.service
[INFO]  systemd: Enabling k3s-agent unit
Created symlink /etc/systemd/system/multi-user.target.wants/k3s-agent.service -> /etc/systemd/system/k3s-agent.service.
[INFO]  systemd: Starting k3s-agent
pi@pi:~$
```

