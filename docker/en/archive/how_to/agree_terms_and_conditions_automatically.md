* Draft: 2020-05-28 (Thu)

# Agree Terms and Conditions Automatically in Dockerfile

## Problem

* A Dockerfile is used to create a Docker image.
* The terms and conditions must be agreed occasionally.
* A problem arises when `yes` must be manually entered.
  * For example, when Java is installed on Ubuntu Linux.
* So an error occurs and the Dockerfile fails to create an image.

```bash
$ docker build -t aimldl/baseimage-kubeflow-h203.30.0.3_openml0.10.2_python3_ubuntu18.04 - < Dockerfile
  ...
Step 12/50 : RUN add-apt-repository ppa:linuxuprising/java
 ---> Running in d12d790daacc
 Oracle Java 11 (LTS) and 14 installer for Ubuntu (20.04, 19.10, 18.04, 16.04 and 14.04), Linux Mint and Debian.
  ...
Exception in thread Thread-1:
Traceback (most recent call last):
  File "/usr/lib/python3.7/threading.py", line 917, in _bootstrap_inner
    self.run()
  ...
FileNotFoundError: [Errno 2] No such file or directory: 'S.gpg-agent.browser'
```

## Hint

> If you want to create a docker image with Java, then there's a problem: it'll ask you manually confirm that you agree to the terms and conditions. To automatically do this, add some `debconf-set-selections` to your script. So the steps are now update, install software properties utils, add the webupd8team repo, set the debconf selections, update again, install java.
>
> ```bash
> apt-get update
> apt-get -y install software-properties-common
> add-apt-repository -y ppa:webupd8team/java
> echo debconf shared/accepted-oracle-license-v1-1 select true | debconf-set-selections
> echo debconf shared/accepted-oracle-license-v1-1 seen true | debconf-set-selections
> apt-get update
> apt-get -y install oracle-java8-installer
> ```
>
> Source: [Docker: install Java8 automatically on ubuntu/debian](https://newfivefour.com/docker-java8-auto-install.html)



But the above command fails at:

```bash
$ sudo echo debconf shared/accepted-oracle-license-v1-1 select true | debconf-set-selections
debconf: DbDriver "passwords" warning: could not open /var/cache/debconf/passwords.dat: Permission denied
debconf: DbDriver "config": could not write /var/cache/debconf/config.dat-new: Permission denied
$
```

The `echo` command prints the subsequent string of commands.

```bash
$ echo debconf shared/accepted-oracle-license-v1-1 select true
debconf shared/accepted-oracle-license-v1-1 select true
$
```

Therefore the pipeline `|` is equal to:

```bash
$ debconf-set-selections debconf shared/accepted-oracle-license-v1-1 select true
```

```

```

> **debconf**-**set**-**selections** can be used to pre-seed the **debconf** database with answers, or to change answers in the database. Each question will be marked as seen to prevent **debconf** from asking the question interactively. Reads from a file if a filename is given, otherwise from stdin.

debconf-set-selections - insert new values into the debconf database

Synopsis

```bash
debconf-set-selections file
debconf-get-selections | ssh newhost debconf-set-selections
```

Examples

```
# Force debconf priority to critical.
debconf debconf/priority select critical

# Override default frontend to readline, but allow user to select.
$ debconf debconf/frontend select readline
$ debconf debconf/frontend seen false
```



Archive

History of commands

```
sudo apt-get install -y software-properties-common
add-apt-repository ppa:linuxuprising/java
sudo add-apt-repository ppa:linuxuprising/java
sudo apt-get update -y
sudo apt-get install oracle-java14-installer
sudo apt-get install -y oracle-java14-installer
java -jar h2o.jar
sudo apt-get -y update
apt-get -y install software-properties-common
sudo apt-get -y install software-properties-common
sudo add-apt-repository -y ppa:webupd8team/java
echo debconf shared/accepted-oracle-license-v1-1 select true | debconf-set-selections
sudo echo debconf shared/accepted-oracle-license-v1-1 select true | debconf-set-selections
echo debconf shared/accepted-oracle-license-v1-1 select true
debconf-set-selections debconf shared/accepted-oracle-license-v1-1 select true
which debconf-set-selections
debconf-set-selections --help
debconf-set-selections "ssdebconf shared/accepted-oracle-license-v1-1 select true"
dpkg-query -S /usr/bin/debconf-set-selections
sudo apt-get install debconf-utils
sudo debconf-get-selections | grep ^iptables-persistent
clear
sudo debconf-get-selections
sudo debconf-get-selections | grep -i "oracle"
debconf-show oracle-java14-installer
sudo debconf-show oracle-java14-installer

```

$ sudo echo debconf shared/present-oracle-license-v1-2 select true | debconf-set-selections
debconf: DbDriver "passwords" warning: could not open /var/cache/debconf/passwords.dat: Permission denied
debconf: DbDriver "config": could not write /var/cache/debconf/config.dat-new: Permission denied

$

$ sudo debconf shared/accepted-oracle-license-v1-2 seen true | debconf-set-selections
debconf: DbDriver "passwords" warning: could not open /var/cache/debconf/passwords.dat: Permission denied
debconf: unable to initialize frontend: Dialog
debconf: (No usable dialog-like program is installed, so the dialog based frontend cannot be used. at /usr/share/perl5/Debconf/FrontEnd/Dialog.pm line 76.)
debconf: falling back to frontend: Readline
Can't exec "shared/accepted-oracle-license-v1-2": No such file or directory at /usr/share/perl/5.26/IPC/Open3.pm line 178.
open2: exec of shared/accepted-oracle-license-v1-2 seen true failed: No such file or directory at /usr/share/perl5/Debconf/ConfModule.pm line 59.

```bash
Processing triggers for dbus (1.12.16-1) ...
gpg: keybox '/tmp/tmp7zfx40a4/pubring.gpg' created
gpg: /tmp/tmp7zfx40a4/trustdb.gpg: trustdb created
gpg: key C2518248EEA14886: public key "Launchpad VLC" imported
gpg: Total number processed: 1
gpg:               imported: 1
Warning: apt-key output should not be parsed (stdout is not a terminal)
gpg: no valid OpenPGP data found.
Exception in thread Thread-1:
Traceback (most recent call last):
  File "/usr/lib/python3.7/threading.py", line 917, in _bootstrap_inner
    self.run()
  File "/usr/lib/python3.7/threading.py", line 865, in run
    self._target(*self._args, **self._kwargs)
  File "/usr/lib/python3/dist-packages/softwareproperties/SoftwareProperties.py", line 688, in addkey_func
    func(**kwargs)
  File "/usr/lib/python3/dist-packages/softwareproperties/ppa.py", line 386, in add_key
    return apsk.add_ppa_signing_key()
  File "/usr/lib/python3/dist-packages/softwareproperties/ppa.py", line 273, in add_ppa_signing_key
    cleanup(tmp_keyring_dir)
  File "/usr/lib/python3/dist-packages/softwareproperties/ppa.py", line 234, in cleanup
    shutil.rmtree(tmp_keyring_dir)
  File "/usr/lib/python3.7/shutil.py", line 491, in rmtree
    _rmtree_safe_fd(fd, path, onerror)
  File "/usr/lib/python3.7/shutil.py", line 449, in _rmtree_safe_fd
    onerror(os.unlink, fullname, sys.exc_info())
  File "/usr/lib/python3.7/shutil.py", line 447, in _rmtree_safe_fd
    os.unlink(entry.name, dir_fd=topfd)
FileNotFoundError: [Errno 2] No such file or directory: 'S.gpg-agent.browser'

Removing intermediate container 90eeb1f6152d
 ---> 16ce66c7eb1c
Step 6/51 : RUN echo debconf shared/present-oracle-license-v1-2 select true | debconf-set-selections
 ---> Running in 401603346efe
Removing intermediate container 401603346efe
 ---> 2c59ed65549e
Step 7/51 : RUN echo debconf shared/accepted-oracle-license-v1-2 seen true | debconf-set-selections
 ---> Running in a73392225c2b
error: Cannot find a question for shared/accepted-oracle-license-v1-2

```

에구 참... 모르겠다 >.<



[How To Install Oracle Java 14 (JDK 14) On Ubuntu, Debian Or Linux Mint From APT PPA Repository](https://www.linuxuprising.com/2020/03/how-to-install-oracle-java-14-jdk14-on.html)

[Creating a Docker Image with Ubuntu and Java](https://dzone.com/articles/creating-a-docker-image-with-ubuntu-and-java)

[How To Install Java on Ubuntu 18.04](https://www.hostinger.com/tutorials/install-java-ubuntu)

