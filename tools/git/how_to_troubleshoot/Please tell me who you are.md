# How to Fix an Error "*** Please tell me who you are"
* Draft: 2020-0323 (Mon)

## Problem
"./batch_git_push" doesn't work as usual and spitted an error message:
< *** Please tell me who you are.

```bash
bitnami@ip-w-x-y-z:~/github$ ./batch_git_push
cd /home/bitnami/github/VOX
git add . && git commit -m 'Add new stuff by batch_git_push' && git push
*** Please tell me who you are.
Run
  git config --global user.email "you@example.com"
  git config --global user.name "Your Name"
to set your account's default identity.
Omit --global to set the identity only in this repository.

fatal: unable to auto-detect email address (got 'bitnami@ip-172-31-31-215.(none)')
cd /home/bitnami/github/documents
git add . && git commit -m 'Add new stuff by batch_git_push' && git push

*** Please tell me who you are.
Run
  git config --global user.email "you@example.com"
  git config --global user.name "Your Name"
  ...
```  
## Solution  
The solution is straightforward. Just enter the account ID (user.name) and the registered email address (user.email). (An existing github account is required.)
```bash
$ git config --global user.email "aimldl@gmail.com"
$ git config --global user.name "aimldl"
$ ./batch_git_push
```
