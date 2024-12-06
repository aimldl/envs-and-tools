* Draft: 2021-06-03 (Thu)

# Redirecting the Standard I/O Streams

## Summary

* To redirect `stdout`, use the `>` constructs.
* To redirect `stderr` and `stdout`, use the `2>&1` or `&>` constructs.

## Reference

Google search: linux standard error redirect

* ### [How to Redirect stderr to stdout in Bash](https://linuxize.com/post/bash-redirect-stderr-stdout/)

> In Bash and other Linux shells, when a program is executed, it uses three standard I/O streams. Each stream is represented by a numeric file descriptor:
>
> - `0` - `stdin`, the standard input stream.
> - `1` - `stdout`, the standard output stream.
> - `2` - `stderr`, the standard error stream.
>
> Streams can be redirected using the `n>` operator, where `n` is the file descriptor number. When n is omitted, it defaults to 1,
>
> #### Examples
>
> Redirect the `command`'s standard output (`stdout`) to the `file`.
>
> ```bash
> # stdout
> $ command > file
> $ command 1> file
> ```
>
> Redirect the `command`'s standard error (`stderr`) to the `file`.
>
> ```bash
> # stderr
> $ command 2> file
> ```
>
> To suppress the error messages, redirect `stderr` to `/dev/null`.
>
> ```bash
> # Suppress stderr
> $ command 2> /dev/null
> ```
>
> #### Redirecting stderr to stdout
>
> It is quite common to redirect `stderr` to `stdout` so that you can have everything in a single file.
>
> ##### `2>&1` redirect or &>
>
> `2>&1` redirects the `stderr` to the current location of `stdout`.
>
> ```bash
> # stdout & stderr are saved to file
> $ command > file 2>&1
> ```
>
> * That is, redirect `stderr` to `stdout` and have error messages sent to the same file as standard output.
>
> * The order of redirection is important.
>
> ##### &> redirect
>
> In Bash `&>` has the same meaning as `2>&1`
>
> ```bash
> $ command &> file
> ```

TODO: Update the following part.

## `2>` redirects the standard error

Example

```bash
$ lss 2> /dev/null
```



## Suppressing the standard error from TensorFlow

```bash
$ python your_tensorflow_code.py
  ...
/home/ubuntu/anaconda3/envs/tensorflow2_latest_p37/lib/python3.7/site-packages/seaborn/_decorators.py:43: FutureWarning: Pass the following variable as a keyword arg: x. From version 0.12, the only valid positional argument will be `data`, and passing other arguments without an explicit keyword will result in an error or misinterpretation.
  FutureWarning
  ...
$
```

For example, the standard I/O can be redirected.

```bash
$ time python ${PY_FILE} > ${DIR_LOG}/${LOG_FILE}
```

the standard error can also be redirected

```bash
$ time python ${PY_FILE} > ${DIR_LOG}/${LOG_FILE} 2> /dev/null
```

The entire Bash script is as follows.

```bash
#!/bin/bash
# batch_run
#   Usage:
#     $ ./batch-time_python_py_file > logs/2021-06-03_09-42.log

NOW=`date +"%Y-%m-%d_%H%M"`
DIR_LOG="logs/${NOW}"

## Array/list of files to iteratively run
PY_FILES=(
2_mnist-mlp-keras.py
2_mnist-simple-cnn-keras.py
3_mnist-cnn-keras.py
4_fashion_mnist-cnn-keras.py
5_cifar10-cnn-keras-tf2.py
6_imdb_movie_review-bidirectional_lstm-keras.py
7_reuters_newswire-mlp-keras-tf2.py
)

## Function Definitions
run() {
  COMMAND=$1
  echo "${COMMAND}"
  #eval "${COMMAND}"
}

# Main
mkdir -p ${DIR_LOG}
for PY_FILE in "${PY_FILES[@]}"; do
  LOG_FILE=`echo ${PY_FILE} | sed 's/\.py/\.log/g'`
  #echo "========== ${PY_FILE} > ${LOG_FILE} =========="
  COMMAND="time python ${PY_FILE} > ${DIR_LOG}/${LOG_FILE} 2> /dev/null"
  run "${COMMAND}"
done
```

When the `>` construct is used, I found out the `time` command outputs are actually `stderr`.

```bash
$ ./run 
mkdir -p logs/2021-06-03_0101
./batch-time_python_py_file > logs/2021-06-03_0101/2021-06-03_0101.log

real	0m28.205s
user	0m22.063s
sys	0m8.206s

real	1m52.405s
user	2m25.466s
sys	0m21.270s

real	0m31.777s
user	0m41.905s
sys	0m11.543s

real	0m32.567s
user	0m42.509s
sys	0m11.433s

real	0m38.113s
user	0m50.171s
sys	0m15.206s

real	4m18.032s
user	7m40.880s
sys	0m29.859s

real	0m10.462s
user	0m11.918s
sys	0m7.465s
$
```

Instead of `>`, `&>` is used to save the output to the log file.

```bash
$ ./run
mkdir -p logs/2021-06-03_0128
./batch-time_python_py_file &> logs/2021-06-03_0128/2021-06-03_0128.log
$
```

