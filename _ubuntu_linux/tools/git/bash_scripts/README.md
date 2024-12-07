* Rev.2: 2022-11-26 (Sat)
* Rev.1: 2020-11-14 (Sat)
* Draft: 2020-06-29 (Mon)
# How to Clone, Pull, and Push My Github Repositories at Once
## Overview
Repeating the same set of commands to clone, pull, and push multiple repositories is not fun. [batch_git_clone](batch_git_clone), [batch_git_pull](batch_git_pull), and [batch_git_push](batch_git_push) are written to run a single command for the repetitive jobs.

## Prerequisites
* Understanding of the basic git commands clone, pull, and push.
  * What clone, pull, and push do to tell which one to run: [batch_git_clone](batch_git_clone), [batch_git_pull](batch_git_pull), or [batch_git_push](batch_git_push)

## Configuration
Change two config files for you:
* github_user_id.cfg should include your GitHub ID.
* target_repositories.cfg should include your target repositories delimited by space.

### Example
Say your target repositories are:
* https://github.com/your_id/my_repository_1
* https://github.com/your_id/my_repository_2
*   ...
* https://github.com/your_id/my_repository_n

github_user_id.cfg
```
your_id
```
target_repositories.cfg
```
my_repository_1 my_repository_2 ... my_repository_n
```
Note each target repo is delimited by space.

## How to use the `batch_git_command` scripts
### Important
To use [batch_git_pull](batch_git_pull) and [batch_git_push](batch_git_push), the target repositories must be cloned first by running the [batch_git_clone](batch_git_clone) command.

### Step 1. Create directory `github` under the user home directory.
```bash
$ cd
$ mkdir github
$ cd github/
```
### Step 2. Download the files in this directory in the github directory.

### Step 3. Clone the target repositories
Run `batch_git_clone`
```bash
$ chmod +x batch_git_clone 
$ ./batch_git_clone 
```
All the target repos will be cloned to directory `~/github` on a your machine.

To double-check, run
```bash
$ cd
$ tree github -d -L 1
github
├── certificates
├── environments
└── tools

3 directories
$
```
### Push or pull as you need it.
batch_git_push 
```bash
  $ chmod +x batch_git_push
  $ ./batch_git_push
```

batch_git_pull
```bash
  $ chmod +x batch_git_pull
  $ ./batch_git_pull
```
Run the `chmod +x your_command` command once to make the file executable. Afterward you can simply run `./your_command`.
