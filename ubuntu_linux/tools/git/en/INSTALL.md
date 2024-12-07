* Rev.2: 2020-03-03 (Tue)
* Rev.1: 2019-11-10 (Sun)
* Draft: 2019-07-08 (Mon)
* TODO:
1. Convert it rom Korean to English, [Anaconda에 git 설치하기](https://aimldl.blog.me/221580086193)
2. Summarize [git cheat-sheet](https://aimldl.blog.me/221595976136) & [로컬에 리모트를 맞추기](https://aimldl.blog.me/221604661840). And then delete these blogs.

# INSTALL
This note is about installing and configuring the git command.

## Installation
Git is built-in to Ubuntu Linux. But it must be installed for Windows and Mac. Refer to [Installing GitHub Desktop](https://help.github.com/en/desktop/getting-started-with-github-desktop/installing-github-desktop).

### Ubuntu Linux
 To test if it's installed, run:
```bash
$ git
```
Git should be there.

### Windows
1. Go to https://desktop.github.com/ and download the installation file.
2. Run the installation file, e.g. Git-2.23.0-64-bit.exe, and select the default options.
3. Check the programs in the Start Menu: Git Bash, Git GUI, and Git CMD (Deprecated).

### Installing Git to Anaconda
In Korean, [Anaconda에 git 설치하기](https://aimldl.blog.me/221580086193)

## Configuration
Git must be setup to push or pull a github repository. Refer to [1.6 Getting Started - First-Time Git Setup](https://git-scm.com/book/en/v2/Getting-Started-First-Time-Git-Setup) for details.

Run commands like the following example to configure git at first.

```bash
$ git config --global user.name "aimldl"
$ git config --global user.email "my_email@gmail.com"
$ git config --global color.ui auto
$ git config --global merge.conflictstyle diff3
$ git config --global core.editor nano
```
nano is given as the text editor. But you may choose other text editor. Use one of the following lines instead of the last line above. 

```bash
# To use emacs as the text editor,
$ git config --global core.editor emacs

# To use Atom as the text editor,
$ git config --global core.editor "atom --wait"
```

## Error without Configuration
An error will occur without the configuration. For example,
```
$ git add .
fatal: not a git repository (or any of the parent directories): .git
$
```
The above error has happened when an already-setup repository "~/aimldl" is moved to another location "~/github" in the same machine.

## Verify the Configuration
To check the configuration, run "git config -l" or "git config --list".
* On Ubuntu Linux,
```bash
$ git config --list
user.name=aimldl
user.email=my_email@gmail.com
color.ui=auto
core.editor=atom --wait
merge.conflictstyle=diff3
```
* On Windows,
```cmd
C:\Users\aimldl>git config --list
core.symlinks=false
core.autocrlf=true
core.fscache=true
color.diff=auto
color.status=auto
color.branch=auto
color.interactive=true
help.format=html
rebase.autosquash=true
http.sslcainfo=C:/Program Files/Git/mingw64/ssl/certs/ca-bundle.crt
http.sslbackend=openssl
diff.astextplain.textconv=astextplain
filter.lfs.clean=git-lfs clean -- %f
filter.lfs.smudge=git-lfs smudge --skip -- %f
filter.lfs.process=git-lfs filter-process --skip
filter.lfs.required=true
credential.helper=manager
user.name=aimldl
user.email=my_email@gmail.com
color.ui=auto
merge.conflictstyle=diff3
core.editor=atom --wait
```
For details, refer to [Your first time with git and github](https://kbroman.org/github_tutorial/pages/first_time.html).
(EOF)
