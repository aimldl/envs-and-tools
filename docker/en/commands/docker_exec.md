* Rev.2: 2021-01-30 (Sat)
* Rev.1: 2020-03-12 (Thu)
* Draft: 2019-11-15 (Fri)

   # docker exec

To log in as the root user (id=0), run:

```bash
$ docker exec -u 0 -it [Docker Container] bash
```

For more information, refer to [root password inside a docker container](https://stackoverflow.com/questions/28721699/root-password-inside-a-docker-container).