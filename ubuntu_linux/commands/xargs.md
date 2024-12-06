* DraftL 2021-07-15 (Thu)

# xargs



## Combine `find` and `xargs` to search a `<pattern>` in files

Find all files  under the current directory and search a `<pattern>` within all the files

```bash
$ find . -name * | xargs egrep -i -n <pattern>
```

As an application of the above set of commands, search a `<pattern>` in all `.py` files under the current directory

```bash
$ find . -name '*.py' | xargs egrep -i -n <pattern>
```

## Use the `arguments` multiple times

Google search: xargs examples use variable multiple times

* [How to repeat variables twice in xargs](https://unix.stackexchange.com/questions/267437/how-to-repeat-variables-twice-in-xargs)

```bash
$ echo test | xargs -I {} echo {} {}
```

### Demo

Create example files

```bash
# Create a directory
$ mkdir test
$ cd test
# Create three empty files
$ touch file1.txt
$ touch file2.txt
$ touch file3.txt
# List the files
$ ls
file1.txt  file2.txt  file3.txt
# Create a dummy directory
$ ls
file1.txt  file2.txt  file3.txt  outputs
# List WITHOUT directories
$ ls -p | grep -v /
file1.txt
file2.txt
file3.txt
$
```

Set the file name as `{}` with the `-I` option and list the file name twice

```bash
$ ls -p | grep -v / | xargs -I {} echo {} {}
file1.txt file1.txt
file2.txt file2.txt
file3.txt file3.txt
$
```

