* Draft: 2020-07-16 (Thu)

# Cleaner code

Bash script

```bash
get_docker_version() {
  # Input: "Docker version 19.03.12, build 48a66213fe"
  # Output: "19.03.12"

  # split to get rid of the trailing comma "," in "19.03.12,"
  docker --version | awk '{ split($3, buffer,","); print buffer[1]; }'
}
```

The same result can be obtained directly from the `docker version` command.

```bash
$ sudo docker version --format '{{.Server.Version}}'
19.03.11
$
```

[docker version > Get the server version](https://docs.docker.com/engine/reference/commandline/version/#get-the-server-version)

> ##### docker version
>
> ##### Description: Show the Docker version information
>
> ##### Usage: 
>
> ```bash
> docker version [OPTIONS]
> ```
>
> ##### Options
>
> | Name, shorthand | Default | Description                                   |
> | --------------- | ------- | --------------------------------------------- |
> | `--format , -f` |         | Format the output using the given Go template |
>
> ##### Get the server version
>
> ```bash
> $ docker version --format '{{.Server.Version}}'
> 19.03.8
> ```