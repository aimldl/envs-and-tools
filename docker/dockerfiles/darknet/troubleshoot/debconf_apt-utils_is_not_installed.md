* Draft: 2021-01-28 (Thu)

# `apt-utils` 미설치로 발생하는 경고

## Summary

`Dockerfile`의 초반에 두 라인을 추가하니까 문제가 해결되었습니다.

```dockerfile
ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y apt-utils
```

## Problem 1

```basic
debconf: delaying package configuration, since apt-utils is not installed
```

## Hint 1

Google search: 'debconf: delaying package configuration, since apt-utils is not installed'

* [[16.04] debconf: delaying package configuration, since apt-utils is not installed #319](https://github.com/phusion/baseimage-docker/issues/319)

> My solution is just to put a
>
> ```dockerfile
> RUN apt-get update && apt-get install -y --no-install-recommends apt-utils
> ```
>
> line in the docker file and it fixes the problem.

## Solution 2

`Dockerfile`에서 `apt-utils`를 먼저 설치했더니 `WARNING`이 사라졌습니다.

```dockerfile
RUN apt-get update && apt-get install -y --no-install-recommends apt-utils
```

대신 아래의 문제가 발생했습니다.

## Problem 2

```bash
debconf: unable to initialize frontend: Dialog
debconf: (TERM is not set, so the dialog frontend is not usable.)
debconf: falling back to frontend: Readline
debconf: unable to initialize frontend: Readline
debconf: (Can't locate Term/ReadLine.pm in @INC (you may need to install the Term::ReadLine module) (@INC contains: /etc/perl /usr/local/lib/x86_64-linux-gnu/perl/5.26.1 /usr/local/share/perl/5.26.1 /usr/lib/x86_64-linux-gnu/perl5/5.26 /usr/share/perl5 /usr/lib/x86_64-linux-gnu/perl/5.26 /usr/share/perl/5.26 /usr/local/lib/site_perl /usr/lib/x86_64-linux-gnu/perl-base) at /usr/share/perl5/Debconf/FrontEnd/Readline.pm line 7, <> line 19.)
debconf: falling back to frontend: Teletype
dpkg-preconfigure: unable to re-open stdin:
```

## Hint 2

Google search: dockerfile 'debconf: delaying package configuration, since apt-utils is not installed'

* [Avoid apt-utils warning in Debian Dockerfile](https://serverfault.com/questions/980128/avoid-apt-utils-warning-in-debian-dockerfile)

> It is safe to ignore this warning. It appears because the package you are installing can be configured interactively during installation. This warning means that the interactive configuration has been skipped. The default configuration is used instead, and using the default configuration is usually not an issue.
>
> In order not to have this warning, you have to install `apt-utils` and disable the interactive configuration using the environment variable `DEBIAN_FRONTEND`. You will still get the warning while installing `apt-utils`, but after that, the new installation will be free of those warnings.
>
> This can be done by adding the following lines to your Dockerfile:
>
> ```dockerfile
> ARG DEBIAN_FRONTEND=noninteractive
> RUN apt-get update && apt-get install -y apt-utils
> ```

## Solution 2

`Dockerfile`의 초반에 두 라인을 추가하니까 문제가 해결되었습니다.

```dockerfile
ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y apt-utils
```