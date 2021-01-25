* Rev.3: 2021-01-15 (Fri)
* Rev.2: 2020-12-28 (Mon)
* Rev.1: 2020-12-10 (Thu)
* Draft: 2020-07-24 (Fri)

# AUTO-INSTALL
This directory contains several bash scripts which automatically install programs on Linux.

## Summary
Open the terminal and run the following commands in the home directory.
```bash
$ cd AUTO_INSTALL/
~/AUTO_INSTALL$ chmod +x install
~/AUTO_INSTALL$ ./install
```

## Installing Ubuntu packages
Running `./install` will invoke the following options. Enter `1` to install Ubuntu packages.
```bash
What would you like to install?
  1. Ubuntu packages
  2. Kubernetes
  3. Kubeflow
  4. All
1
```
Enter the number of your choice. I will choose 4.
```bash
What would you like to install?
  1. Essential packages
  2. Convenience packages
  3. Productivity packages
  4. All
4
```

A list of commands will be executed automatically by the scripts in the `ubuntu_package` directory.
All you have to do is to enter the sudo password.

```bash
chmod +x ./install_ubuntu_essential_packages
./install_ubuntu_essential_packages
[sudo] aimldl의 암호: 
  ...
Processing triggers for libc-bin (2.27-3ubuntu1.4) ...
~/AUTO_INSTALL$ 
```
It's all done! To verify, run Google Chrome which is installed in the process.
```bash
$ google-chrome
```
