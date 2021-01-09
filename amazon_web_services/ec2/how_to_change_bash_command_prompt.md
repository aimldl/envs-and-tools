##### aimldl/aws/ec2/how_to_change_bash_command_prompt.md
* Draft: 2019-12-18 (Wed)

### References
Google search: how to change ubuntu command prompt
Google search: how change bash command prompt

* [how i can change AWS ubuntu ec2 shell prompt name](https://serverfault.com/questions/772111/how-i-can-change-aws-ubuntu-ec2-shell-prompt-name)
* [How to Customize your Ubuntu Terminal Prompt](https://vitux.com/how-to-customize-ubuntu-bash-prompt/)

### How to Change the Bash Command Prompt for Amazon EC2

The part to configure the command prompt in .bashrc is:
```bash
if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\$
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
```
#### Remove @ip-xx-x-x-xxx by Removing @\h
Remove @\h to remove the IP address in the command prompt.
```bash
# From
PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
# To
PS1='${debian_chroot:+($debian_chroot)}\u:\w\$ '
```
Then the command prompt changes as follows.
```bash
# From
username@ip-xx-x-x-xxx:~$
# To
username:~$
```
Note \u displays the user name.

#### Hardcode "aimldl@EC2-Seoul" in the Command Prompt
Hardcoding a string "aimldl@EC2-Seoul" forces to change the command prompt.
```bash
# From
PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
# To
NEW_NAME='aimldl@EC2-Seoul'
PS1='${debian_chroot:+($debian_chroot)}${NEW_NAME}:\w\$ '
```
The command prompt has changed to the new name.
```bash
# From
username@ip-xx-x-x-xxx:~$
# To
aimldl@EC2-Seoul:~$
```
The entire code in the .bashrc is below.
```bash
if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\$
else
    #PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
    #PS1='${debian_chroot:+($debian_chroot)}\u:\w\$ '
    NEW_NAME='aimldl@EC2-Seoul'
    PS1='${debian_chroot:+($debian_chroot)}${NEW_NAME}:\w\$ '
fi
```
