* Draft: 2020-06-05 (Fri)
# Set Up a Local machine for a Private Git Server

## Step 1. Open the config file `~/.ssh/config`
```bash
$ nano ~/.ssh/config 
```
Provide
* the link to the private Git server (12.345.678.901)
* the absolute path to the private key (~/.ssh/my_private_key.pem)

Your link and the file name should be changed appropriately.
```bash
Host 12.345.678.901
    Hostname 12.345.678.901
    User git
    IdentityFile ~/.ssh/my_private_key.pem
```

## Step 2. `git clone` the private repository
If you want to store the private repository in directory `~/github`, cd into `~/github` and run 'git clone'.
```bash
$ cd ~/github/
$ git clone ssh://git@12.345.678.901:/home/git/repos/private_repo.git
Cloning into 'private_repo'...
remote: Counting objects: 3, done.
remote: Total 3 (delta 0), reused 0 (delta 0)
Receiving objects: 100% (3/3), done.
$
```
## Step 3. Check the content of the private repository
A sub-directory `private_repo` is created under `~/github`. Check what's in there.
```bash
$ cd private_repo/
$ ls
README.md
$
```
In this example, `README.md` is the only file in the repository.

## Troubleshooting
### Problem 1
When my `~/.ssh/config` is,
```bash
Host 12.345.678.901
    Hostname private_git_server
    User git
    IdentityFile ~/.ssh/my_private_key.pem
```
the following error occurs.
```bash
$ git clone ssh://git@12.345.678.901:/home/git/repos/private_repo.git
Cloning into 'private_repo'...
ssh: Could not resolve hostname private_git_server: Name or service not known
fatal: Could not read from remote repository.

Please make sure you have the correct access rights
and the repository exists.
$
```
### Hint 1
When no DNS to the IP address is set up, `Hostname` must be the IP address.

### Solution 1
Open the config file `~/.ssh/config`
```bash
$ nano ~/.ssh/config 
```
and change `Hostname` from `private_git_server` to `12.345.678.901`
```bash
Host 12.345.678.901
    Hostname 12.345.678.901
    User git
    IdentityFile ~/.ssh/my_private_key.pem
```

### Problem 2
When my `~/.ssh/config` is,
```bash
Host 12.345.678.901
    Hostname 12.345.678.901
    User git
    IdentifyFile ~/.ssh/my_private_key.pem
```
the following error occurs
```bash
$ git clone ssh://git@12.345.678.901:/home/git/repos/private_repo.git
Cloning into 'private_repo'...
/home/aimldl/.ssh/config: line 4: Bad configuration option: identifyfile
/home/aimldl/.ssh/config: terminating, 1 bad configuration options
fatal: Could not read from remote repository.

Please make sure you have the correct access rights
and the repository exists.
$
```
### Hint 2
Notice the configuration option `identifyfile` is an typo.

### Solution 2
Open the config file `~/.ssh/config`
```bash
$ nano ~/.ssh/config 
```
and fix the typo from `IdentifyFile` to `IdentityFile`
```bash
Host 12.345.678.901
    Hostname 12.345.678.901
    User git
    IdentityFile ~/.ssh/my_private_key.pem
```

### Problem 3

```bash
# On the local-machine,
$ git clone ssh://git@123.456.7.890:/home/git/repos/kt_automl.git
Cloning into 'kt_automl'...
git@123.456.7.890: Permission denied (publickey).
fatal: Could not read from remote repository.

Please make sure you have the correct access rights
and the repository exists.
$
```

### Hint 3

> [Error: Permission denied (publickey)](https://help.github.com/en/github/authenticating-to-github/error-permission-denied-publickey)
> A "Permission denied" error means that the server rejected your connection. There could be several reasons why, and the most common examples are explained below.

```bash
$ sudo git clone ssh://git@123.456.7.890:/home/git/repos/kt_automl.git
[sudo] password for aimldl: 
Cloning into 'kt_automl'...
The authenticity of host '123.456.7.890 (123.456.7.890)' can't be established.
ECDSA key fingerprint is SHA256:RV9g2hsi+BOmispPc1mPiFiH0O3hf2ASIhWG8q6e7Zo.
Are you sure you want to continue connecting (yes/no)? yes
Warning: Permanently added '123.456.7.890' (ECDSA) to the list of known hosts.
git@123.456.7.890: Permission denied (publickey).
fatal: Could not read from remote repository.

Please make sure you have the correct access rights
and the repository exists.
$
```



### Action 3

Make sure you have a key that is being used. The `ssh-add` command *should* print out a long string of numbers and letters. If it does not print anything, you will need to [generate a new SSH key](https://help.github.com/en/articles/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent) and associate it with GitHub.

```bash
$ eval "$(ssh-agent -s)"
Agent pid 17714
$ ssh-add -l -E md5
The agent has no identities.
$
```

Tip: On most systems the default private keys (~/.ssh/id_rsa and ~/.ssh/identity) are automatically added to the SSH authentication agent. You shouldn't need to run ssh-add path/to/key unless you override the file name when you generate a key.



```bash
$ ssh-add /home/aimldl/.ssh/id_rsa
/home/aimldl/.ssh/id_rsa: No such file or directory
$
```

