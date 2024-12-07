
* Version Control System (VCS) = Source Code Manager (SCM)
* Synonyms
Version Control = Revision Control = Source Control  = Source Code Management

```
Version Control Softwares
├── Centralized: CVS, Subversion, ...
└── Distributed: Git, Mercurial, ...
```
<img src="https://github.com/aimldl/ubuntu/blob/master/packages/github/images/Version_Control_Software.png" width="800" height="400">
Source: [Version control](https://en.wikipedia.org/wiki/Version_control)

Terminology
* Commit
* Repository/Repo
* Working Directory
* Checkout
* Staging Area/Staging Index/Index
* SHA (Secure Hash Algorithm)
* Branch

For more terminology, refer to [Version control/Common terminology](https://en.wikipedia.org/wiki/Version_control#Common_terminology).

Commands
```bash
$ git init
$ git clone
$ git status
```
```bash
$ git log
$ git show
```
```bash
$ mkdir working_directory
$ cd working_directory
~/working_directory$ git init
~/working_directory$ tree .git
.git
├── HEAD
├── branches
├── config
├── description
├── hooks
│   ├── applypatch-msg.sample
│   ├── commit-msg.sample
│   ├── fsmonitor-watchman.sample
│   ├── post-update.sample
│   ├── pre-applypatch.sample
│   ├── pre-commit.sample
│   ├── pre-push.sample
│   ├── pre-rebase.sample
│   ├── pre-receive.sample
│   ├── prepare-commit-msg.sample
│   └── update.sample
├── info
│   └── exclude
├── objects
│   ├── info
│   └── pack
└── refs
    ├── heads
    └── tags

9 directories, 15 files
~/working_directory$
```
