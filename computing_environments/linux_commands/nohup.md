##### aimldl/computing_environments/linux_commands/nohup.md
* Rev.1: 2020-01-15 (Wed)
* Draft: 2019-12-27 (Fri)

## nohup
Run another command, ignoring hangup signals. That is, nohuo means no hangup. Even when the terminal is closed or the session is disconnected, another command keeps running. For example, when you log out or exit the shell, another command keeps running in the background.

### Syntax
Help or version information.
```bash
$ nohup --help
$ nohup --version
```
To run COMMAND with command line argumenta ARG, run:
```bash
$ nohup COMMAND [ARG]...
```
It is customary to use the trailing &.
```bash
$ nohup COMMAND [ARG]... &
```
Then the process ID (PID) is shown.

To stop COMMAND, the process must be killed. For example,
```bash
$ kill -9 PID
```
For example,
```bash
$ kill -9 9719
```
### Examples
When there's nothing in the directory, running ls is as follows.
```bash
$ nohup ls
nohup: ignoring input and appending output to 'nohup.out'
$ ls
nohup.out
$ cat nohup.out
nohup.out
$
```
Use the trailing & and the PID is returned.
```bash
$ nohup ls &
[1] 9719
$ nohup: ignoring input and appending output to 'nohup.out'

[1]+  Done                    nohup ls
$ ls
nohup.out
$ cat nohup.out
nohup.out
$
```
### Using nohup with python
When python is run with nohup, the output file nohup.out doesn't get updated without the -u option.
#### Bad: $ nohup python script.py &
```bash
$ nohup python script.py &
[1] 4225
$ nohup: ignoring input and appending output to 'nohup.out'

$ tail nohup.out
$
$ cat nohup.out
$
```
nohup.out returns nothing.

#### Good: $ nohup python -u script.py &
However using the -u option returns the expected output.
```bash
$ nohup python -u script.py &
[1] 4225
$ nohup: ignoring input and appending output to 'nohup.out'

$ tail nohup.out
The expected output is displayed here.
Whatever it might be.
  ...
$
```
For details, refer to [Nohup for Python script not working when running in the background with &](https://stackoverflow.com/questions/32213565/nohup-for-python-script-not-working-when-running-in-the-background-with).

To observe the log in real time, the -f option can be used.
```bash
$ tail -f nohup.out
The expected output is displayed here.
Whatever it might be.
  ...
```
For details, refer to [4 Ways to Watch or Monitor Log Files in Real Time](https://www.tecmint.com/watch-or-monitor-linux-log-files-in-real-time/).
```
Pass python the -u flag for unbuffering stdout
  nohup python -u test.py &
Python will buffer stdout otherwise. This doesn't require a code change. From the man page:
       -u     Force  stdin,  stdout and stderr to be totally unbuffered.  On systems where it matters, also put stdin, stdout and stderr in binary mode.  Note that there is internal buffering in xreadlines(), readlines() and  file-object iterators ("for line in sys.stdin") which is not influenced by this option.  To work around this, you will want to use "sys.stdin.readline()" inside a "while 1:" loop.
* Fix an error "MemoryError: Unable to allocate array with shape (132400,) and data type float64"
```
(EOF)
