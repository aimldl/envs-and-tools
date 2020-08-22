* Draft: 2020-08-12 (Wed)

TODO: rewrite this when I have chance.

# List the Groups
## Problem
https://github.com/aimldl/technical_skills/blob/master/computing_environments/docker/how_to_install/docker_on_ubuntu.md

Say the previous configuration not to use `sudo` fails after the reboot. Let's check each step one by one to fix the problem.

#### List all the groups
For
```
Step 1. Create the docker group
$ sudo groupadd docker
```
run the `groups` command to list all the groups.
```bash
$ groups
h2o_docker sudo docker
$
```
The `docker` group does exist. For details, refer to [How to List Groups in Linux](https://linuxize.com/post/how-to-list-groups-in-linux/).

#### List the groups that the current user belongs to
For
```
Step 2. Add your user to the `docker` group.
$ sudo usermod -aG docker $USER
```
run the `groups` command with the current user name
```bash
$ groups $USER
h2o_docker : h2o_docker sudo docker
$
```
The user name is `h2o_docker` and this user does belong to the group `docker`. For details, refer to [How to Check the User Group(s) an Ubuntu User Belongs To](https://vitux.com/how-to-check-the-user-groups-an-ubuntu-user-belongs-to/).
