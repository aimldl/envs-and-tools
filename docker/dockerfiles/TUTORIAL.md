* Rev.1: 2020-05-29 (Fri)
* Draft: 2020-04-27 (Mon)
# Tutorial

## The parent image
A Dockerfile must specify the parent image. For details, refer to:
* [python - Docker Official Images](https://hub.docker.com/_/python)
* [Dockerfile reference](https://docs.docker.com/engine/reference/builder/)

### FROM
Begin with a `FROM` instruction. For example,
```dockerfile
FROM python:3
```
builds from Python Docker official image.

### ARG
The `ARG` command is used to specify a variable `PARENT_IMAGE`.
```dockerfile
ARG PARENT_IMAGE="python:3"
FROM $PARENT_IMAGE
```
The following lines are the same as the above line.

### MAINTAINER
It is customary to provide the information about the maintainer.
```dockerfile
MAINTAINER "Tae-Hyung T. Kim, Ph.D. https://github.com/aimldl"
```
### Summary
A compact way to start a Dockerfile is:
```dockerfile
FROM python:3
```
A verbose version is:
```dockerfile
ARG PARENT_IMAGE="python:3"
FROM $PARENT_IMAGE
MAINTAINER "Tae-Hyung T. Kim, Ph.D. https://github.com/aimldl"
```
## WORKDIR
Change `WORKDIR` so the directory starts from WORKDIR, not from /

# Use two ampersands to merge two commands, e.g. "command 1 && command 2" 
# Install basic packages for Linux
# -q, --quiet

# Quiet. Produces output suitable for logging, omitting progress indicators. More q's will produce more quiet up to a maximum of two. 
# You can also use -q=# to set the quiet level, overriding the # configuration file. Note that quiet level 2 implies -y, 
# you should never use -qq without a no-action modifier such as -d, --print-uris or -s as APT may decided to do something you did not expect.

# It's fine to put all of them together.
# But I prefer to grouping related commands.
# It's a matter of style.
