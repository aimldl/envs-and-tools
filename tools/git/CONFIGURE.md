* Draft: 2020-06-24 (Wed)
# Configure
On the local machine, configure the local git repositories with the `git config` command.

## Prerequisite
Before pushing data to your git repository, you should configure git with your account information. Otherwise, the following warning message is given.
```bash
$ git add . && git commit -m 'Add new stuff to my git repo' && git push

*** Please tell me who you are.

Run

  git config --global user.email "you@example.com"
  git config --global user.name "Your Name"

to set your account's default identity.
Omit --global to set the identity only in this repository.
  ...
$
```

## Example
```bash
$ git config --global user.email my_id@email.com
$ git config --global user.name aimldl
```
You should be able to push to your repo after the above commands. The password will be asked whenever you run 'git push'.
