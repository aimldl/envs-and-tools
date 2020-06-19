##### aimldl/computing_environments/anaconda/troubleshoot/deactivate_does_not_accept_arguments.md

## Anaconda deactivate does not accept arguments

### Problem
I can't cd to a directory in the Conda terminal and the Bash terminal.

### Phenomenon
All of a sudden, the following error occurs in my Conda virtual environment on Ubuntu 18.04.
```bash
(base) aimldl@GPU-Desktop:~$ cd aws_keys/
deactivate does not accept arguments
remainder_args: ['Documents//']

2: 명령을 찾을 수 없습니다
(base) aimldl@GPU-Desktop:~$
```

```bash
(base) aimldl@GPU-Desktop:~$ conda deactivate
aimldl@GPU-Desktop:~$ cd Documents/
deactivate does not accept arguments
remainder_args: ['Documents/']

2: 명령을 찾을 수 없습니다
aimldl@GPU-Desktop:~$ ls
```

