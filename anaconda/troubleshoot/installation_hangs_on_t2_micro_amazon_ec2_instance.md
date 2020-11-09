##### aimldl/computing_environments/anaconda/troubleshoot/installation_hangs_on_t2_micro_amazon_ec2_instance.md

## Anaconda Installation Hangs...
* Rev.1: 2020-0323 (Mon)
* Draft: 2019-1219 (Web)

### Summary
* 2019-1219 (Web)
I was trying to install Anaconda on an Amazon EC2 instance. I have enough experience on installing it on other machines. But this phenomenon is weird to me.
* 2020-0323 (Mon)
The same phenomenon happened and I totally forgot this has happened before. I followed the instruction below and Anaconda has installed smoothly! All I had to do is to change the instance type from t2.micro to t2.medium or higher.
  * t2.micro (X)
  * t2.small (X)
  * t2.medium (O)

### Problem
#### Summary
Anaconda installation hangs here and doesn't process on my Amazon EC2 instance (type t2.micro). What's wrong? How can I fix this?
```bash
Unpacking payload ...
  0%|                                                                            | 0/291 [00:00<?, ?it/s]
```
#### Details
The installation file for Linux is downloaded and ran as follows:

```bash
$ cd Downloads/
~/Downloads$ ls
Anaconda3-2019.10-Linux-x86_64.sh
~/Downloads$ bash Anaconda3-2019.10-Linux-x86_64.sh
  ...
Do you accept the license terms? [yes|no]
[no] >>> yes

Anaconda3 will now be installed into this location:
/home/bitnami/anaconda3

  - Press ENTER to confirm the location
  - Press CTRL-C to abort the installation
  - Or specify a different location below

[/home/username/anaconda3] >>>
PREFIX=/home/username/anaconda3
Unpacking payload ...
  0%|                                                                            | 0/291 [00:00<?, ?it/s]
```

### Hint
> go to t2.medium or larger

It looks like something's wrong with the instance type
* [current latest miniconda sh installer for linux hangs on Unpacking payload step #9345](https://github.com/conda/conda/issues/9345)
  > I have tried this now on several different ec2 instances across multiple aws accounts -- it appears to be a problem across ec2, at least within the us-east-1 region.

  > I think this is an issue with smaller EC2 instance types. Anything with a single core seems to experience this issue - if I go to t2.medium or larger, the installation process works. That seems to be a result of the usage of concurrent.futures in our installers and will require more investigation.

### Solution
I have changed the instance type from t2.micro to t2.large. The installation went smooth after the change!
```bash
~/Downloads$ bash Anaconda3-2019.10-Linux-x86_64.sh
  ...
Proceed ([y]/n)? y


Downloading and Extracting Packages
backports.functools_ | 11 KB     | ############################################################## | 100%
conda-4.8.0          | 2.8 MB    | ############################################################## | 100%
Preparing transaction: done
Verifying transaction: done
Executing transaction: done
  ...
  Do you wish the installer to initialize Anaconda3
  by running conda init? [yes|no]
  [no] >>> yes
  ...
  ==> For changes to take effect, close and re-open your current shell. <==

  If you'd prefer that conda's base environment not be activated on startup,
     set the auto_activate_base parameter to false:

  conda config --set auto_activate_base false

  Thank you for installing Anaconda3!
  ...
$
```
Exit the EC2 instance and log back in. Anaconda works just fine!
```bash
(base) username@ip-xx-x-x-xxx:~$
```
