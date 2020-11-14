* Rev.1: 2020-11-14 (Sat)
* Draft: 2020-06-29 (Mon)
# How to Clone, Pull, and Push My Github Repositories at Once
## Overview
Repeating the same set of commands to clone, pull, and push multiple repositories is not fun. [batch_git_clone](batch_git_clone), [batch_git_pull](batch_git_pull), and [batch_git_push](batch_git_push) are written to run a single command for the repetitive jobs.

## Prerequisites
* Understanding of the basic git commands clone, pull, and push.
  * What clone, pull, and push do to tell which one to run: [batch_git_clone](batch_git_clone), [batch_git_pull](batch_git_pull), or [batch_git_push](batch_git_push)

## Customizing these `batch_git_command` scripts for yourself
These scripts are written for me. 
* My Github ID is `aimldl`
* My target repositories are
  * aimldl.github.io
  * coding
  * environments
  * pytorch
  * tensorflow
  * topics_in
  * projects
  
Take a quick look at my Github repositories at https://github.com/aimldl and compare them to my target repositories above. `projects` are a private repository while the rest of them are public repos. Did you notice `Repositories 7` between the `Overview` and `Projects` tabs? Six public repos are pinned to the main list, but there is one more repository which is private.

<img src='images/github-aimldl-main-repositories.png'>

## How to customize the `batch_git_command` scripts
Say you have Github repositores that you wish to clone, pull, and push. You can easily customize these scripts for yourself by changing:
* `github_user_id` to your Github User ID and
* `target_repositories` to your target repositories.

Say your target repositories are:
* https://github.com/your_id/my_repository_1
* https://github.com/your_id/my_repository_2
*   ...
* https://github.com/your_id/my_repository_n

### Step 1. Download all the scripts
### Step 2. Open [batch_git_clone](batch_git_clone) and change `github_user_id` to your Github ID.
Say `your_id` is your Github ID. Simply edit the value in `github_user_id` from `aimldl` to `your_id'.
```bash
github_user_id='your_id'
```
### Step 3. Change the list of `target_repositories` to YOUR target repositories.

All three scripts ([batch_git_clone](batch_git_clone), [batch_git_pull](batch_git_pull), [batch_git_push](batch_git_push)) have variable `target_repositories`. Simply, change the values of `target_repositories` to:
```bash
target_repositories="my_repository_1 my_repository_2 ... my_repository_n"
```
Note each value in the list is delimited by a white space.

## How to use the `batch_git_command` scripts
### Important
To use [batch_git_pull](batch_git_pull) and [batch_git_push](batch_git_push), the target repositories must be cloned first with the 'git clone' command.

You may 
* run YOUR version of [batch_git_clone](batch_git_clone) or
* run the `git clone` command for all target repositories manually.
Either way works. The following steps are the option to use [batch_git_clone](batch_git_clone).

# TODO
### Step 1. Create directory `github` under the user home directory.
```bash
$ cd
$ mkdir github
$ cd github/
```

### Step 2. The target repositories must be cloned first with the 'git clone' command.
#
Usage
  $ chmod +x batch_git_push
  $ ./batch_git_push
#
Doing it manually
  You have a Github user ID 'your_id' and 
      want to clone everything in your repository "my_repository".
    $ cd ~/github/
    $ cd my_repository/
    $ git add .
    $ git commit -m "Add a new stuff manually"
    $ git push
#



Copy & paste `batch_git_clone`
```bash
$ nano batch_git_clone
```
Run `batch_git_clone`
```bash
$ chmod +x batch_git_clone 
$ ./batch_git_clone 
```
All the repos are cloned to directory `~/github` on a local machine.

```bash
$ cd
$ tree github -d -L 1
github
├── aimldl.github.io
├── non_technical_skills
├── technical_skills
└── topics_in

4 directories
$
```
