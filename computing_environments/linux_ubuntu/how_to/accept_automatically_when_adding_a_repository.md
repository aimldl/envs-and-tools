* Draft: 2020-07-16 (Thu)
# How to Accept Automatically when adding a repository

## Situation
* I wrote two bash scripts to install several Ubuntu packages.
* The first script installs all the packages till the end.

## Problem
* The second script waits for my input to press "ENTER". Twice! This is the problem.
```bash
$ ./install_ubuntu_productivity_packages
  ...
 More info: https://launchpad.net/~otto-kesselgulasch/+archive/ubuntu/gimp
Press [ENTER] to continue or Ctrl-c to cancel adding it.
  ...
 More info: https://launchpad.net/~nomacs/+archive/ubuntu/stable
Press [ENTER] to continue or Ctrl-c to cancel adding it.
  ...
$
```
## Question
How can I press ENTER automatically given the "Press [ENTER] ..." message?

## Hint
* Use the -y option to accept automatically.
```
Google search: "Press [ENTER] to continue or Ctrl-c to cancel adding it."
* [automaticallly accept when adding a repository?](https://unix.stackexchange.com/questions/238293/how-to-automaticallly-accept-when-adding-a-repository/238294)
Add the --yes option. As described in [the manual page](http://manpages.ubuntu.com/manpages/focal/en/man1/add-apt-repository.1.html):
    -y, --yes: Assume yes to all queries
```
More specifically, 
```
SYNOPSIS
       add-apt-repository [OPTIONS] REPOSITORY
DESCRIPTION
The options supported by add-apt-repository are:
 -y, --yes Assume yes to all queries
Source: [Ubuntu Manpage: add-apt-repository](http://manpages.ubuntu.com/manpages/focal/en/man1/add-apt-repository.1.html)
```

## Solution
Adding the -y option after the `add-apt-repository` command solves the problem.

Before
```bash
#!/bin/bash
#  install_ubuntu_productivity_packages
  ...
sudo add-apt-repository ppa:otto-kesselgulasch/gimp
  ...
sudo add-apt-repository ppa:nomacs/stable
   ...
```
After
```bash
#!/bin/bash
#  install_ubuntu_productivity_packages
   ...
sudo add-apt-repository -y ppa:otto-kesselgulasch/gimp
   ...
sudo add-apt-repository -y ppa:nomacs/stable
   ...
```
