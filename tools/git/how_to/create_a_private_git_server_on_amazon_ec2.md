* Draft: 2020-06-05 (Fri)

# Create a Private Git Server on Amazon EC2

## Purpose

* Set up a private Git server on an existing Amazon EC2 instance. 
  * Say the link to the EC2 instance is `<link2server>`, e.g. `http://12.345.678.901`
  * /home/git
* You will be able to clone a repository `test` on the private Git server by running:

```bash
$ git clone ssh://git@<link2server>:/home/git/repos/test.git 
```

## Prerequisites

* There is an existing Amazon EC2 instance.
* `Git` is installed on your local machine. EC2 has `Git` by default.

-------------------

Next: [Create a Private Git Repo on Amazon EC2](create_a_private_repo_on_amazon_ec2.md)

--------------------

## Create an user account `git`

Step 1. `ssh` to the Amazon EC2 instance. In other words, log into the remote server.

Step 2. Create an user account `git`

```bash
$ sudo adduser git
Adding user `git' ...
Adding new group `git' (1003) ...
Adding new user `git' (1002) with group `git' ...
Creating home directory `/home/git' ...
Copying files from `/etc/skel' ...
Enter new UNIX password: 
Retype new UNIX password: 
passwd: password updated successfully
Changing the user information for git
Enter the new value, or press ENTER for the default
	Full Name []: aimldl
	Room Number []: 
	Work Phone []: 
	Home Phone []: 
	Other []: 
Is the information correct? [Y/n] y
$
```

In the above messages, a new password is entered twice.

```bash
Enter new UNIX password: 
Retype new UNIX password: 
```

## Switch to the user account `git`

The password will be used to switch user or `su` to the `git` account.

```bash
$ su git
Password: 
git@ip-w-x-y-z:~$ whoami
git
git@ip-w-x-y-z:~$
```

`git@ip-w-x-y-z:~` is the user name followed by an internal IP address of the remove server or EC2 instance. This indicates the user is switched to `git`. 

## Switch back from the account `git`

Conversely, you may switch back to the original user account from `git`. Traditionally, the `su` command switches the user back to the original user account, say `aimldl`, if you enter the password.

```bash
git@ip-w-x-y-z:~$ pwd
/home/git
git@ip-w-x-y-z:~$ su aimldl
Password: 
aimldl@ip-w-x-y-z:~$ whoami
aimldl
aimldl@ip-w-x-y-z:~$
```

However I don't know the password because a private key is used to access the remote server. 

A trick is to exit the `bash` shell launched when `$ su git` has opened. 

```bash
git@ip-w-x-y-z: ~$ exit
exit
aimldl@ip-w-x-y-z:~$
```

To verify, change directory to the user home with the `cd` command and the `pwd` command.

```bash
aimldl@ip-w-x-y-z:~ cd
aimldl@ip-w-x-y-z:~$ pwd
/home/aimldl
aimldl@ip-w-x-y-z:~$
```

In effect, the user has switched back to the original user `aimldl`. 

## Check the public key in this remote server

Let's check the public key in this remove server or EC2 instance. The public key will be used in the later step.

To access the remove server, a private key in the local machine is required. The corresponding public key is stored in the remove server. In other words, a key pair (public key and private key) is used to grant authentication. For details, refer to [Amazon EC2 key pairs and Linux instances](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-key-pairs.html).

The public key is stored in `~/.ssh/authorized_keys` which is a text file. It starts from `ssh-rsa` and ends with the name of the key. That is, `<key_name>` is a string. If I named `<key_name>` as `this_is_my_name`, the file name for the private key is `this_is_my_name.pem`. 

```bash
$ whoami
aimldl
$ cat ~/.ssh/authorized_keys
ssh-rsa ...
... <key_name>
$
```

Note `aimldl` is the original account. 

## Set up a private Git repository

### Switch user to `git`

Switch user to `git` and move to the user home.

```bash
$ su git
Password: 
git@ip-w-x-y-z:~$ cd
git@ip-w-x-y-z:~$ pwd
/home/aimldl
git@ip-w-x-y-z:~$
```

`git@ip-w-x-y-z:~$` is shown above to indicate the user has been switched to `git`. But `git@ip-w-x-y-z:~` will be omitted and only `$` will be displayed below.

### Make a directory `.ssh`

and make a directory `.ssh` and change mode to `700`. Note there is a leading dot `.` to hide the directory.

```bash
$ mkdir .ssh
$ chmod 700 .ssh
```

### Store the public key to `authorized_keys`

Create a new file `my-ssh-rsa.pub`; copy and paste the public key to create `my-ssh-rsa.pub` on the server. The entire string of

```bash
ssh-rsa ...
... <key_name>
```

must be copied to this file.

Alternatively, upload the file with public key and save the file name as `my-ssh-rsa.pub`. The point is to create a file `my-ssh-rsa.pub` with the public key in it.

Save the public key to `authorized_keys` and change the privilege to `600`. Lastly, remove `my-ssh-rsa.pub` to clean up the hard disk. 

```bash
$ cat my-ssh-rsa.pub >> ~/.ssh/authorized_keys
$ chmod 600 ~/.ssh/authorized_keys
$ rm my-ssh-rsa.pub
$
```

The following lines show the results of the `ls` command for the above commands.

```bash
$ ls -al ~/.ssh/authorized_keys 
-rw-rw-r-- 1 git git 1677 Jun  5 00:21 /home/git/.ssh/authorized_keys
$ chmod 600 ~/.ssh/authorized_keys 
$ ls -al ~/.ssh/authorized_keys 
-rw------- 1 git git 1677 Jun  5 00:21 /home/git/.ssh/authorized_keys
$ ls
my-ssh-rsa.pub
$ rm my-ssh-rsa.pub 
$ ls
$ 
```

## Test if the private git repository works

At this point, it is a good idea to check if the private git server is accessible. `<link2server>` may be a DNS name like `www.mygitserver.com` or an IP address like `12.345.678.901`.

On your local machine, you will eventually run

```bash
$ git clone ssh://git@<link2server>:/home/git/repos/test.git 
```

which will fail with the following messages

```bash
Cloning into 'test'...
git@<link2server>: Permission denied (publickey).
fatal: Could not read from remote repository.

Please make sure you have the correct access rights
and the repository exists.
$
```

because the `ssh` is not configured to use the correct private key for the public key in the remote server. 

## Create a new host entry on the local machine

To fix this problem, create a new host entry to the SSH configuration. On the local machine, use a text editor to open a new file  `~/.ssh/config`

```bash
$ nano ~/.ssh/config
```

and enter the following contents

```text
# ~/.ssh/config
Host <link2server>
    Hostname <any_name>
    User git
    IdentityFile </path/to/my_private_key>
```

`<link2server>` is either an URL or IP address. `<any_name>` is a string. `</path/to/my_private_key>` is the absolute path to the private key. For example,

```text
Host 12.345.678.901
    Hostname my_private_git_server
    User git
    IdentityFile ~/aws_keys/my-ssh-private-key.pem
```

Say the remote server has an URL `http://aimldl.org/git` and the private key is stored in `~/.ssh/my-ssh-private-key.pem`.

```bash
Host aimldl.org/git
    Hostname my_private_git_server
    User git
    IdentityFile ~/.ssh/my-ssh-private-key.pem
```

For your reference, refer to the following article.

> Google search: git clone ssh using a private key
>
> It is not possible to tell Git which SSH credentials to use — strictly speaking. But you can use SSH config to effectively achieve the same result. ... add a new host entry to your SSH config that uses the desired private key.
>
> Source: [How to tell Git which SSH Key to use](https://medium.com/@czarpino/how-to-tell-git-which-ssh-key-to-use-c8574fb243fd)

## Create a Git repository `test`

Up to this point, the remote server and the local machine are configured to connect each other through the `git` command. However it is still early to test the `git clone` command because there is no Git repository on the remote server.

```bash
$ git clone ssh://git@<link2server>:/home/git/repos/test.git
```

Let's create a Git repository on the remote server for a testing purpose.

### Step 1. Access the remote server (if you haven't already)

To recap, you will  `ssh` to the remote server from your local machine. The private key resides in the local machine while the remote server has the public key. These public and private keys must be a pair in order to gain access. This is the standard procedure to access an EC2 instance or remote server.

```bash
$ ssh -i my-ssh-private-key.pem -L 8888:localhost:8888 ubuntu@12.345.678.901
Welcome to Ubuntu 14.04.6 LTS (GNU/Linux 3.13.0-170-generic x86_64)
   ...
Last login: Fri Jun  5 05:13:56 2020 from 234.567.890.123
aimldl@ip-w-x-y-z:~$ 
```

The user name on my remote server is set to be `aimldl`.

### Step 2. Switch user to `git`

```bash
aimldl@ip-w-x-y-z:~$ su git
Password: 
git@ip-w-x-y-z:/home/aimldl$ whoami
git
git@ip-w-x-y-z:/home/aimldl$ 
```

`git@ip-w-x-y-z` is displayed to show the user has been switched. But it will be omitted below.

### Step 3. Create a `test` repository

Change directory to the user home and make directory `repos` which serves as the master directory.

```bash
$ cd
$ mkdir repos
$ cd repos
```

Make a directory to create a repository. By convention, a repository's directory name ends with `.git`

```bash
$ mkdir test.git
$ cd test.git/
$ pwd
/home/git/repos/test.git
$
```

 To create a repository `test` in the local machine, the directory on the Git server becomes `test.git` 

### Step 4. Initialize the repository

If you have an existing repository, provide the `<url>` at the end of the command.

```bash
$ git clone --bare --shared <url>
```

Otherwise, initialize `git` with the `--bare` and `--shared` options. The `--bare` option creates a remote repository and the `--shared` option automatically grants the group write privilege.

```bash
$ git init --bare --shared
Initialized empty shared Git repository in /home/git/repos/test.git/
$
```

The `git init` command creates the following directories and files.

```bash
$ ls
branches  config  description  HEAD  hooks  info  objects  refs
$ tree
.
├── branches
├── config
├── description
├── HEAD
├── hooks
│   ├── applypatch-msg.sample
│   ├── commit-msg.sample
│   ├── post-update.sample
│   ├── pre-applypatch.sample
│   ├── pre-commit.sample
│   ├── prepare-commit-msg.sample
│   ├── pre-push.sample
│   ├── pre-rebase.sample
│   └── update.sample
├── info
│   └── exclude
├── objects
│   ├── info
│   └── pack
└── refs
    ├── heads
    └── tags

9 directories, 13 files
$
```

## Git clone the `test` repository

Now everything is set. On your local machine, run the `git clone` command in the directory where you want to store the Git repository.

```bash
$ git clone ssh://git@<link2server>:/home/git/repos/test.git
Cloning into 'test'...
warning: You appear to have cloned an empty repository.
$ 
```

Say `<link2server>` is `12.345.678.901` and you want to store the repository in `~/github`.

```bash
$ cd
$ pwd
/home/aimldl
$ mkdir github
$ cd github
$ git clone ssh://git@12.345.678.901:/home/git/repos/test.git
```

then a directory `test` is created under `~/github` and the repository is stored under directory `~/github/test`

Notice the exact location of the repository is specified by `git@12.345.678.901:/home/git/repos/test.git`. This command

* accesses a remote server at `12.345.678.901`
* with an ID `git`
* through `ssh` configured with `my-ssh-private-key.pem`

and then

* clone a repository located at directory `/home/git/repos/test.git`

The directory name on the local machine is `test` without `.git`

```bash
$ cd test
$ ls -al
total 12
drwxrwxr-x  3 aimldl aimldl 4096 Jun  5 16:58 .
drwxrwxr-x 10 aimldl aimldl 4096 Jun  5 16:58 ..
drwxrwxr-x  7 aimldl aimldl 4096 Jun  5 16:58 .git
$
```

## Create a file in the local machine

Say `README.md` is created in the `test` directory.

```bash
$ cd ~/github/test
$ pwd
/home/aimldl/github/test
$ echo "# Test Repository" > README.md
```

## Git push to the `test` repository

```bash
$ git add . && git commit -m 'Test the private git server' && git push
[master (root-commit) e42f137] Test the private git server
 1 file changed, 2 insertions(+)
 create mode 100644 README.md
Counting objects: 3, done.
Writing objects: 100% (3/3), 252 bytes | 252.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0)
To ssh://12.345.678.901:/home/git/repos/test_project.git
 * [new branch]      master -> master
 $
```

***Now it is verify that the private Git server is up and running. ***

## Limit the User Privilege

This part is optional, but highly recommended. Let's limit the user privilege in case the new user messes around the server. :-)

First, exit the `git` account to run a command with the `sudo` privilege.

```
git@ip-w-x-y-z: ~$ exit
exit
aimldl@ip-w-x-y-z: ~$
```

Open `/etc/passwd` with your favorite text editor. I use `nano` instead of `vi` or `emacs`.

```bash
sudo nano /etc/passwd
```

The bottom line of this text file `passwd` looks like below.

```bash
git:x:1002:1003:aimldl,,,:/home/git:/bin/bash
```

Change it to below and save the file.

```bash
git:x:1001:1001:aimldl,,,:/home/git:/usr/bin/git-shell
```

The bash shell `/bin/bash` is changed to the Git shell `/usr/bin/git-shell` in order to limit the user's shell scope.

Notice `ssh` access has been denied if you try to access the server.

```bash
$ su git
Password: 
fatal: Interactive git shell is not enabled.
hint: ~/git-shell-commands should exist and have read and execute access.
$
```

If you intend to switch user to `git` and run `bash`, revert `passwd` to the previous configuration.

```bash
git:x:1002:1003:aimldl,,,:/home/git:/bin/bash
```

## References

* [[Ubuntu\] 우분투 Git 서버 구축](https://webdir.tistory.com/220), 흉내쟁이
* [How to tell Git which SSH Key to use](https://medium.com/@czarpino/how-to-tell-git-which-ssh-key-to-use-c8574fb243fd)

-------------------

Next: [Create a Private Git Repo on Amazon EC2](create_a_private_repo_on_amazon_ec2.md)