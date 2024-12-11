connect_github_with_ssh.md
* Draft: 2019-12-17 (Tue)
#### Situation
Entering the user name and password for each github repository is cumbersome when Github repositories are pulled and/or pushed. "How can I NOT enter the user name and password?"

Google search: git how to set up a credential with ssh key

There are two options: (1) dangerous, but easy, (2) safe, but more difficult.
1. Save the user name and password to a plain text under directory ~/.gitconfig.
 This option is potentially dangerous because anyone can see the user account. 
```bash
$ git config --global credential.helper store
$ git pull
```
saves the user name and password in a plain text. For details, refer to [How to save username and password in Git?](https://stackoverflow.com/questions/35942754/how-to-save-username-and-password-in-git).

2. Connect to GitHub with SSH
* [GitHub.com Authentication Connecting to GitHub with SSH](https://help.github.com/en/github/authenticating-to-github/connecting-to-github-with-ssh)
* [Configuring SSH for git](https://dev.to/idrisrampurawala/configuring-ssh-for-git-2of1)

#### Summary: [Configuring SSH for git](https://dev.to/idrisrampurawala/configuring-ssh-for-git-2of1)
##### About SSH
SSH is a protocol that establishes a secured connection between a client and a server. With SSH keys, a user can log into the server without supplying the username and password. For example, one can log into the GitHub server from the client program or git without entering the username and password.

##### Setting Up SSH Keys
Create a key pair: private key and public key. Private key is saved to a local machine while public key is passed to the server. 
1. Check for existing keys.
If any keys exist, they are listed.
```bash
$ ls -al ~/.ssh
total 4
drwx------ 1 aimldl aimldl 4096 Dec 17 23:14 .
drwxr-xr-x 1 aimldl aimldl 4096 Dec 17 23:14 ..
-rw------- 1 aimldl aimldl 1766 Dec 17 23:14 id_rsa
-rw-r--r-- 1 aimldl aimldl  400 Dec 17 23:14 id_rsa.pub
$ 
```
The following output is when no key exists.
```bash
$ ls -al ~/.ssh
ls: cannot access '/home/aimldl/.ssh': No such file or directory
$ 
```

2. Generate key with ssh-keygen
```bash
$ ssh-keygen
Generating public/private rsa key pair.
Enter file in which to save the key (/home/aimldl/.ssh/id_rsa):
Created directory '/home/aimldl/.ssh'.
Enter passphrase (empty for no passphrase):
Enter same passphrase again:
Your identification has been saved in /home/aimldl/.ssh/id_rsa.
Your public key has been saved in /home/aimldl/.ssh/id_rsa.pub.
The key fingerprint is:
<generated_key_fingerprint>
The key's randomart image is:
+---[RSA 2048]----+
|                 |
|       ...       |
|                 |
+----[SHA256]-----+
```
Check if the identification and public key are generated.
```
$ ls -al ~/.ssh
total 4
drwx------ 1 aimldl aimldl 4096 Dec 17 23:14 .
drwxr-xr-x 1 aimldl aimldl 4096 Dec 17 23:14 ..
-rw------- 1 aimldl aimldl 1766 Dec 17 23:14 id_rsa
-rw-r--r-- 1 aimldl aimldl  400 Dec 17 23:14 id_rsa.pub
$ 
```

##### Add the key to the ssh-agent
Add the key to the ssh-agent in order to avoid typing in the password each time you use the key.
```bash
$ eval `ssh-agent`
Agent pid 199
$ ssh-add ~/.ssh/id_rsa
Enter passphrase for /home/aimldl/.ssh/id_rsa:
Identity added: /home/aimldl/.ssh/id_rsa (/home/aimldl/.ssh/id_rsa)
$ 
```

##### Add the public key to the GitHub server
Get the "public_key" in id_rsa.pub and copy the public key to the GitHub. For details, refer to [Adding a new SSH key to your GitHub account](https://help.github.com/en/github/authenticating-to-github/adding-a-new-ssh-key-to-your-github-account).
```bash
$ cat ~/.ssh/id_rsa.pub
<public_key>
$
```

##### TODO: Start from here.
```bash
$ git add .
(base) aimldl@GPU-DESKTOP:~/aimldl/python3$ git comment -m "test"
git: 'comment' is not a git command. See 'git --help'.

The most similar command is
        commit
(base) aimldl@GPU-DESKTOP:~/aimldl/python3$ git commit -m "test"

*** Please tell me who you are.

Run

  git config --global user.email "you@example.com"
  git config --global user.name "Your Name"

to set your account's default identity.
Omit --global to set the identity only in this repository.

fatal: empty ident name (for <aimldl@GPU-DESKTOP.localdomain>) not allowed
(base) aimldl@GPU-DESKTOP:~/aimldl/python3$
```
