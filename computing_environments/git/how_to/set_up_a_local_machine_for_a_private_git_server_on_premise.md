* Draft: 2020-06-08 (Mon)

## [Generating a new SSH key and adding it to the ssh-agent](https://help.github.com/en/github/authenticating-to-github/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent)

## [Generating a new SSH key](https://help.github.com/en/github/authenticating-to-github/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent#generating-a-new-ssh-key)

```bash
$ ssh-keygen -t rsa -b 4096 -C "your_email@example.com"
```

### [Adding your SSH key to the ssh-agent](https://help.github.com/en/github/authenticating-to-github/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent#adding-your-ssh-key-to-the-ssh-agent)

```bash
$ eval "$(ssh-agent -s)"
$ ssh-add ~/.ssh/id_rsa
```

Add the SSH key to your GitHub account. 

For a private Git server, a different action must be taken.

## [Create a Public/Private Key Pair](../../linux_commands/ssh/how_to/create_a_public_prive_key_pair_on_ubuntu.md)

### Step 1-1. Create the RSA key pair

```bash
# On the local machine,
$ ssh-keygen
```

### Step 1-2. Change the permission of the private key

```bash
$ chmod 400 ~/.ssh/id_rsa
```

### Step 2. Copy the public key to the remote server

Copy the public key using `ssh-copy-id`

```bash
# On the local machine,
$ ssh-copy-id username@remote_host
```

### Step 3. Authenticate to the remote server using SSH keys

```bash
# On the local machine,
$ ssh username@remote_host
```

Step 4 — Disable Password Authentication on your Server



## Hands-on

### Generating a new SSH key

```bash
$ ssh-keygen
```

```bash
$ ssh-keygen -t rsa -b 4096
Generating public/private rsa key pair.
Enter file in which to save the key (/home/aimldl/.ssh/id_rsa): 
Enter passphrase (empty for no passphrase): 
Enter same passphrase again: 
Your identification has been saved in /home/aimldl/.ssh/id_rsa.
Your public key has been saved in /home/aimldl/.ssh/id_rsa.pub.
The key fingerprint is:
SHA256:x8vybYqzDFre6gtD8WaRWAUQsVloKJI3YVcnTDVuvjM aimldl@Home-Laptop
The key's randomart image is:
+---[RSA 4096]----+
| .oo=OB+=        |
|+.+.o*.= .       |
|.o o= o o        |
|     o + .       |
|    . + S o      |
|   . o   + .     |
|    o o E o      |
|     * +.* ..    |
|    ..=o=ooo.    |
+----[SHA256]-----+
$
```

If there is an existing key, you'll be asked.

```bash
/home/aimldl/.ssh/id_rsa already exists.
Overwrite (y/n)? y
```

### Adding your SSH key to the ssh-agent

```bash
$ eval "$(ssh-agent -s)"
Agent pid 21041
$ ssh-add ~/.ssh/id_rsa
Identity added: /home/aimldl/.ssh/id_rsa (/home/aimldl/.ssh/id_rsa)
$
```

### Change the permission of the private key

```bash
$ chmod 400 ~/.ssh/id_rsa
$ ls -al ~/.ssh/id_rsa
-r-------- 1 aimldl aimldl 3243 Jun  8 17:24 /home/aimldl/.ssh/id_rsa
$
```

#### Troubleshooting

As `id_rsa` is changed to read only, an error will occur if an overwrite attempt is made.

```bash
Saving key "/home/aimldl/.ssh/id_rsa" failed: Permission denied
```

If you intend to make a change to the file or remove it, change the permission.

```bash
$ chmod +700 ~/.ssh/id_rsa
$ ls -al ~/.ssh/id_rsa
-rwx------ 1 aimldl aimldl 3247 Jun  8 17:51 /home/aimldl/.ssh/id_rsa
$
```

### Copy the public key to the remote server

Say the IP address to the remove server is `123.456.7.890`.

```bash
# On the local machine,
$ cat ~/.ssh/config
Host 123.456.7.890
    Hostname 123.456.7.890
    User git
    IdentityFile ~/.ssh/id_rsa
$
```

Run `ssh-copy-id`. If the password is asked, you're half-way through.

```bash
$ ssh-copy-id git@123.456.7.890
/usr/bin/ssh-copy-id: INFO: attempting to log in with the new key(s), to filter out any that are already installed
/usr/bin/ssh-copy-id: INFO: 1 key(s) remain to be installed -- if you are prompted now it is to install the new keys
git@123.456.7.890's password: 
```

```bash
Number of key(s) added: 1

Now try logging into the machine, with:   "ssh 'git@123.456.7.890'"
and check to make sure that only the key(s) you wanted were added.

(base) aimldl@Home-Laptop:~/.ssh$
```

#### Troubleshooting

If you have already set up the remote server, you may encounter error message(s).

##### Problem: Permission denied (publickey)

If an permission error occurs instead of the passwords, 

```bash
$ ssh-copy-id git@123.456.7.890
/usr/bin/ssh-copy-id: INFO: attempting to log in with the new key(s), to filter out any that are already installed
/usr/bin/ssh-copy-id: INFO: 1 key(s) remain to be installed -- if you are prompted now it is to install the new keys
git@123.456.7.890: Permission denied (publickey).
$
```

you fell into the state that you can't ssh into the remote host.

```bash
$ ssh git@123.456.7.890
git@123.456.7.890: Permission denied (publickey).
$
```

##### Solution: Turn on `PasswordAuthentication` and restart ssh daemon

It's because the password authentication is turned off. To turn it back on, open `/etc/ssh/sshd_config`

```bash
$ sudo nano /etc/ssh/sshd_config
```

and comment out `PasswordAuthentication no`

* Before

```text
PasswordAuthentication no
```

* After

```text
#PasswordAuthentication no
```

This change is not enough. Restart `ssh` to make the change effective to the current ssh daemon.

```bash
$ sudo systemctl restart ssh
$ exit
logout
Connection to 123.456.7.890 closed.
```

The `ssh-copy-id` command should work by now and the passwords will be asked.

```bash
$ ssh-copy-id git@123.456.7.890
/usr/bin/ssh-copy-id: INFO: attempting to log in with the new key(s), to filter out any that are already installed
/usr/bin/ssh-copy-id: INFO: 1 key(s) remain to be installed -- if you are prompted now it is to install the new keys
git@123.456.7.890's password: 
```

### Authenticate to the remote server using SSH keys

```bash
$ ssh git@123.456.7.890
Welcome to Ubuntu 18.04.2 LTS (GNU/Linux 4.15.0-99-generic x86_64)
  ...
git@remote-host:~$ hostname
remote-host
git@remote-host:~$ exit
logout
Connection to 123.456.7.890 closed.
$
```

Now `ssh` works just fine!

### `git clone` the private repository

Say `~/github` is the directory to save the repositories.

```bash
$ mkdir ~/github
$ cd ~/github
```

`git clone` will create a directory `private_repo_on_premise`.

```bash
$ git clone ssh://123.456.7.890:/home/git/repos/private_repo_on_premise.git
Cloning into 'private_repo_on_premise'...
warning: You appear to have cloned an empty repository.
$
```

### Disable Password Authentication on your Server

Open `/etc/ssh/sshd_config` 

```bash
$ sudo nano /etc/ssh/sshd_config
```

and set `PasswordAuthentication no`

```text
PasswordAuthentication no
```

Restart `ssh` to make the change effective to the current ssh daemon.

```bash
$ sudo systemctl restart ssh
```

### Test the private repository

Add a file in the repository.

```bash
$ cd ~/github/private_repo_on_premise
$ echo "#Hello" > README.md
$ cat README.md 
#Hello
$
```

`git push` to the private repository

```bash
$ git add .
$ git commit -m "Test the private git repository"
[master (root-commit) de24485] Test the private git repository
 1 file changed, 1 insertion(+)
 create mode 100644 README.md
$ git push
Counting objects: 3, done.
Writing objects: 100% (3/3), 231 bytes | 231.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0)
To ssh://192.168.0.109:/home/git/repos/kt_automl.git
 * [new branch]      master -> master
$
```

Yay! It works just fine.