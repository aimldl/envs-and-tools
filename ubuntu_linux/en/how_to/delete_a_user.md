* Rev.1: 2020-10-16 (Fri)
* Draft: 2020-07-16 (Thu)
# Delete a User on Ubuntu Linux
There are two nice options to delete a user.
* Delete the user account and remove all files
* Delete the user account and remove the home directory.

* To delete the user and all files including the home directory, run:
```bash
$ sudo deluser --remove-all-files USER
```
* To delete the user and the home directory, run:
```bash
$ sudo deluser --remove-home USER
```

To verify the sudoer's priviledge, run
```bash
$ sudo visudo
```
and delete the line starting with USER if the line exists.
```bash
root    ALL=(ALL:ALL) ALL
USER    ALL=(ALL:ALL) ALL
```
## deluser --help
```bash
$ deluser --help
deluser USER
  remove a normal user from the system
  example: deluser mike

  --remove-home             remove the users home directory and mail spool
  --remove-all-files        remove all files owned by user
  --backup                  backup files before removing.
  --backup-to <DIR>         target directory for the backups.
                            Default is the current directory.
  --system                  only remove if system user

delgroup GROUP
deluser --group GROUP
  remove a group from the system
  example: deluser --group students

  --system                  only remove if system group
  --only-if-empty           only remove if no members left

deluser USER GROUP
  remove the user from a group
  example: deluser mike students

general options:
  --quiet | -q      don't give process information to stdout
  --help | -h       usage message
  --version | -v    version number and copyright
  --conf | -c FILE  use FILE as configuration file
$
```

## Example
In this example, the current user is `aimldl`. The user I want to delete is `k8snode`.
```bash
$ whoami
aimldl
$ ls /home
aimldl  k8snode
$ sudo deluser --remove-home k8snode
[sudo] password for aimldl: 
Looking for files to backup/remove ...
Removing files ...
Removing user `k8snode' ...
Warning: group `k8snode' has no more members.
userdel: user k8snode is currently used by process 1118
/usr/sbin/deluser: `/usr/sbin/userdel k8snode' returned error code 8. Exiting.
$ ls /home
aimldl
$ sudo visudo
[sudo] password for aimldl: 
visudo: /etc/sudoers.tmp unchanged
$
```

## Troubleshoot
### Problem1
```bash
$ sudo adduser k8snode
adduser: The user `k8snode' already exists.
$
```
### Hint1
```
Google search: "deluser --remove-home" "adduser: The user"  "already exists"
```

### Problem2
```bash
$ sudo deluser --remove-home h2o_docker/
[sudo] h2o의 암호: 
/usr/sbin/deluser: `h2o_docker/' 사용자가 없습니다.
$
```
### Solution2
The trailing `/` was the problem.
```bash
$ sudo deluser --remove-home h2o_docker
백업/제거할 파일들을 찾는 중...
파일 제거중 ...
'h2o_docker' 사용자 제거 중...
경고: 'h2o_docker'그룹이 회원목록에 더이상 없음.
완료.
$
```

## References
* [How to Add and Delete Users on Ubuntu 16.04](https://www.digitalocean.com/community/tutorials/how-to-add-and-delete-users-on-ubuntu-16-04)
