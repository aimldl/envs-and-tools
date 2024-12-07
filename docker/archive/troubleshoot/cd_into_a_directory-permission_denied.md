* Draft: 2020-05-29 (Fri)
# cd into a Directory-Permission denied
## Summary
To cd into a directory,
* use WORKDIR directory_name
* do not use RUN cd directory_name

## Problem
I was meant to cd into directory `/home/jovyan` and then unzip a compressed file.
```dockerfile
RUN cd /home/jovyan && unzip h2o-3.30.0.3.zip
```
But the following error occured.
```bash
Step 42/47 : RUN /home/jovyan && unzip h2o-3.30.0.3.zip
 ---> Running in dc0b1cb8bf76
/bin/sh: 1: /home/jovyan: Permission denied
The command '/bin/sh -c /home/jovyan && unzip h2o-3.30.0.3.zip' returned a non-zero code: 126
```

## Hint
[What is the WORKDIR command in Docker?](https://www.educative.io/edpresso/what-is-the-workdir-command-in-docker)
> The WORKDIR command is used to define the working directory of a Docker container at any given time.
> Any RUN, CMD, ADD, COPY, or ENTRYPOINT command will be executed in the specified working directory.

> If the WORKDIR command is not written in the Dockerfile, it will automatically be created by the Docker compiler.
> The command performs mkdir and cd implicitly.

> A sample Dockerfile in which the working directory is set to /project
```bash
FROM ubuntu:16.04
WORKDIR /project
RUN npm install 
```

> If the project directory does not exist, it will be created.
> The RUN command will be executed inside project.

> ***Use a relative path to reuse WORKDIR***

> WORKDIR can be reused to set a new working directory at any stage of the Dockerfile.
> The path of the new working directory must be given relative to the current working directory.
```bash
FROM ubuntu:16.04
WORKDIR /project
RUN npm install 
WORKDIR ../project2
RUN touch file1.cpp
```

## Solution
Use `WORKDIR /home/jovyan` instead of `RUN cd /home/jovyan && some command`.
```dockerfile
WORKDIR /home/jovyan
RUN unzip h2o-3.30.0.3.zip
```
