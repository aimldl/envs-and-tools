* Draft: 2020-07-20 (Mon)

# ... because the public key is not available: NO_PUBKEY

## Problem

When installing Docker, the following command gives an error after running `sudo apt-get update`. 

```bash
The following signatures couldn't be verified because the public key is not available: NO_PUBKEY 
```

The OS is freshly installed and several basic and productivity packages are installed beforehand. 

```bash
$ sudo apt-get update
Get:1 https://download.docker.com/linux/ubuntu bionic InRelease [64.4 kB]
Err:1 https://download.docker.com/linux/ubuntu bionic InRelease
  The following signatures couldn't be verified because the public key is not available: NO_PUBKEY 7EA0A9C3F273FCD8
  ...
Reading package lists... Done        
W: GPG error: https://download.docker.com/linux/ubuntu bionic InRelease: The following signatures couldn't be verified because the public key is not available: NO_PUBKEY 7EA0A9C3F273FCD8
E: The repository 'https://download.docker.com/linux/ubuntu bionic InRelease' is not signed.
N: Updating from such a repository can't be done securely, and is therefore disabled by default.
N: See apt-secure(8) manpage for repository creation and user configuration details.
$
```

## Hint

> Google search: "Err:1 https://download.docker.com/linux/ubuntu bionic InReleaseThe following signatures couldn't be verified because the public key is not available:"
>
> ```bash
> $ sudo apt-get update
>   ...
> W: GPG error: http://security.ubuntu.com trusty-security Release: The following signatures couldn't be verified because the public key is not available: NO_PUBKEY 40976EAF437D05B5 NO_PUBKEY 3B4FE6ACC0B21F32
>   ...
> $
> ```
>
> Looking at the error above, apt is telling us that the following keys are missing: `40976EAF437D05B5` and `3B4FE6ACC0B21F32`. Notice that these are listed multiple times. Each unique key will only need to be added once.
>
> To add these keys, run the following commands:
>
> ```bash
> $ sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 40976EAF437D05B5
>   ...
> $ sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 3B4FE6ACC0B21F32
> Executing: gpg --ignore-time-conflict --no-options --no-default-keyring --homedir /tmp/tmp.77TqYGKU7b --no-auto-check-trustdb --trust-model always --keyring /etc/apt/trusted.gpg --primary-keyring /etc/apt/trusted.gpg --keyserver keyserver.ubuntu.com --recv-keys 3B4FE6ACC0B21F32
> gpg: requesting key C0B21F32 from hkp server keyserver.ubuntu.com
> gpg: key C0B21F32: public key "Ubuntu Archive Automatic Signing Key (2012) " imported
> gpg: Total number processed: 1
> gpg:               imported: 1  (RSA: 1)
> $
> ```
>
> Source: [Fix apt-get update “the following signatures couldn’t be verified because the public key is not available”](https://chrisjean.com/fix-apt-get-update-the-following-signatures-couldnt-be-verified-because-the-public-key-is-not-available/)



## Solution

Run `sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys` followed by the key shown in the error message. My key is `7EA0A9C3F273FCD8`. I had to wait for several seconds because nothing showed up.

```bash
$  sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 7EA0A9C3F273FCD8
[sudo] password for k8smaster: 
Executing: /tmp/apt-key-gpghome.ng3qN8MDRI/gpg.1.sh --keyserver keyserver.ubuntu.com --recv-keys 7EA0A9C3F273FCD8
gpg: key 8D81803C0EBFCD88: 8 signatures not checked due to missing keys
gpg: key 8D81803C0EBFCD88: public key "Docker Release (CE deb) <docker@docker.com>" imported
gpg: Total number processed: 1
gpg:               imported: 1
$
```

The problem has been fixed.

```bash
$ sudo apt update
Get:1 https://download.docker.com/linux/ubuntu bionic InRelease [64.4 kB]
Hit:2 http://dl.google.com/linux/chrome/deb stable InRelease                                        
Get:3 https://download.docker.com/linux/ubuntu bionic/stable amd64 Packages [12.5 kB]               
Get:4 http://security.ubuntu.com/ubuntu bionic-security InRelease [88.7 kB]                         
Hit:6 https://typora.io/linux ./ InRelease                                                          
Hit:7 http://kr.archive.ubuntu.com/ubuntu bionic InRelease                                          
Hit:8 http://ppa.launchpad.net/nomacs/stable/ubuntu bionic InRelease                                
Get:9 http://kr.archive.ubuntu.com/ubuntu bionic-updates InRelease [88.7 kB]                        
Hit:5 https://packages.cloud.google.com/apt kubernetes-xenial InRelease                             
Hit:10 http://ppa.launchpad.net/otto-kesselgulasch/gimp/ubuntu bionic InRelease                     
Get:11 http://kr.archive.ubuntu.com/ubuntu bionic-backports InRelease [74.6 kB]
Fetched 329 kB in 2s (138 kB/s)     
Reading package lists... Done
Building dependency tree       
Reading state information... Done
36 packages can be upgraded. Run 'apt list --upgradable' to see them
$
```

