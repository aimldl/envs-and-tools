* Rev.1: 2020-06-10 (Mon)
* Draft: 2020-06-05 (Fri)

# Create a Private Git Repo on Amazon EC2

## Prerequisites

* There is an existing Amazon EC2 instance.
* `Git` is installed on your local machine.
* A private Git server is created on Amazon EC2.
  * If you haven't created one yet, refer to [Create a Private Git Server on Amazon EC2](create_a_private_git_server_on_amazon_ec2.md).

## Purpose

* Assuming a private Git sever is created, this document shows the process of creating a private Git repository in a more compact way than [Create a Private Git Server on Amazon EC2](create_a_private_git_server_on_amazon_ec2.md). 

* While the previous document creates a repository named `test.git`, this document uses a different name `private_repo` to create a new repository.
* This document, hopefully, serves as a cook book manual while the previous document explains how to set up a private Git server and create a new repository.

-----------------

Previous: [Create a Private Git Server on Amazon EC2](create_a_private_git_server_on_amazon_ec2.md)

---------------

## On the Remote Server

### Step 1. Access the remote server

Assuming the remote server is at `12.345.678.901`, ssh into the server with a private key, say `my-ssh-private-key.pem`. 

```bash
$ ssh -i my-ssh-private-key.pem -L 8888:localhost:8888 ubuntu@12.345.678.901
Welcome to Ubuntu 14.04.6 LTS (GNU/Linux 3.13.0-170-generic x86_64)
   ...
Last login: Fri Jun  5 05:13:56 2020 from 234.567.890.123
aimldl@ip-w-x-y-z:~$ 
```
### Step 2. Add a new user `git`
```bash
$ sudo adduser git
[sudo] password for aimldl: 
Adding user `git' ...
Adding new group `git' (1001) ...
Adding new user `git' (1001) with group `git' ...
Creating home directory `/home/git' ...
Copying files from `/etc/skel' ...
Enter new UNIX password: 
Retype new UNIX password: 
passwd: password updated successfully
Changing the user information for git
Enter the new value, or press ENTER for the default
	Full Name []: this is my project name
	Room Number []: 
	Work Phone []: 
	Home Phone []: 
	Other []: 
Is the information correct? [Y/n] y
$
```
### Step 3. Switch user to `git`

```bash
$ su git
Password: 
$ whoami
git
$ 
```
### Step 4. Make a directory to store all git repositories
Change directory to the user home `/home/git/`.
```bash
$ cd
$ mkdir repos
```

### Step 5. cd to the remote master repository directory `~/repos`

```bash
$ cd ~/repos
```

### Step 6. Make directory for the private repository

For example, my private repository name is `private_repo`. By convention, a repository's directory name ends with `.git`

```bash
$ mkdir private_repo.git
$ cd private_repo.git/
```

### Step 7. Initialize a Git repository

```bash
$ git init --bare --shared
Initialized empty shared Git repository in /home/git/repos/private_repo.git/
$
```

The directory looks like below.

```bash
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

If you don't have the `tree` command, you may use the `ls` command.

```bash
$ ls
branches  config  description  HEAD  hooks  info  objects  refs
$
```

Now your remote server is ready.

## On your local machine

### Step 1. Open a new terminal

The `$` sign is an abbreviation of the bash shell terminal.

```bash
$
```

In this example, it is assumed directory `github` is the master repository directory where all the Git repositories are stored. If you don't have one already, create one.

### Step 2. cd into the local master repository directory `~/github`

```bash
$ cd ~/github
```

### Step 3. `git clone` the repository from the specified location

Recall the remote server is at `12.345.678.901` and the directory of our repository is at `/home/git/repos/private_repo.git` 

```bash
$ git clone ssh://git@12.345.678.901:/home/git/repos/private_repo.git
```

If the `clone` job is done, a new directory `private_repo` is created.

### Step 4. cd into the cloned private repository

```bash
$ cd private_repo
```

### Step 5. (To test the repository), create `README.md`

```bash
$ echo "# Private Repository" > README.md
$ cat README.md
# Private Repository
$
```

### Step 6. `git push` the change to the remote private Git server

```bash
$ git add .
$ git commit -m "Test the private git repository"
[master (root-commit) 37efe33] Test the private git repository
 1 file changed, 1 insertion(+)
 create mode 100644 README.md
$ git push
Counting objects: 3, done.
Writing objects: 100% (3/3), 244 bytes | 244.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0)
To ssh://12.345.678.901:/home/git/repos/private_repo.git
 * [new branch]      master -> master
$ 
```

