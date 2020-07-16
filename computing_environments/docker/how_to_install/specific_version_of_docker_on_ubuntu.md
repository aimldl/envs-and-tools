



[Install Docker Engine on Ubuntu](https://docs.docker.com/engine/install/ubuntu/)



Uninstall old versions

```bash
$ sudo apt-get remove -y docker docker-engine docker.io containerd runc
```

Install using the repository

Set up the repository

```bash
$ sudo apt-get update
$ sudo apt-get install \
    apt-transport-https \
    ca-certificates \
    curl \
    gnupg-agent \
    software-properties-common
```

Add Docker’s official GPG key

```bash
$ curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
$ sudo apt-key fingerprint 0EBFCD88
```

Verify that you now have the key with the fingerprint