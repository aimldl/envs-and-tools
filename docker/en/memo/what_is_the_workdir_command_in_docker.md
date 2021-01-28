* Draft: 2021-01-28 (Thu)



[What is the WORKDIR command in Docker?](https://www.educative.io/edpresso/what-is-the-workdir-command-in-docker)

> The WORKDIR command is used to define the working directory of a Docker container at any given time.
>
> <img src='images/docker-workdir-example.png'>
>
> A sample Dockerfile
>
> ```dockerfile
> FROM ubuntu:16.04
> WORKDIR /project
> RUN npm install 
> ```
>
> If the `project` directory does not exist, it will be created. The `RUN` command will be executed inside `project`.
>
> **Reusing WORKDIR**
>
> WORKDIR can be reused to set a new working directory at any stage of the Dockerfile. The path of the new working directory must be given relative to the current working directory.
>
> Another sample Dockerfile
>
> ```dockerfile
> FROM ubuntu:16.04
> 
> WORKDIR /project
> RUN npm install 
> 
> WORKDIR ../project2
> RUN touch file1.cpp
> ```
>
> it is strongly recommended that you use WORKDIR to specify the current directory in which you would like to work as it makes troubleshooting easier.