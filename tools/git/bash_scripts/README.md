* Draft: 2020-06-29 (Mon)
# How to Set up My Github Repos on a Local Machine
Create directory `github`.
```bash
$ cd
$ mkdir github
$ cd github/
```
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
