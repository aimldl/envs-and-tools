
* Rev.1: 2020-05-15 (Fri)
* Draft: 2020-02-19 (Wed)
# du
du stands for Disk Usage. It displays the file size used by the specified files or directories.

## Get the size of a directory
```bash
$ du -h [directory_name_1] [directory_name_2] ... [directory_name_n]
```
The -h option returns the size in the human readable format. 
>   -h, --human-readable  print sizes in human readable format (e.g., 1K 234M 2G)

For example, get the directory size of my home directory.
```bash
$ du -h ~
4.0K	/home/aimldl/.gvfs
  ...
269M	/home/aimldl/tensorflow_datasets
146G	/home/aimldl
$
```

>  -c, --total           produce a grand total

## Sort the size of directories by size
```bash
$ du -h [directory_name] | sort -h
```
Note the -h option in the sort command. Without this option, the "du -h" option fails with the sort command.
>   -h, --human-numeric-sort    compare human readable numbers (e.g., 2K 1G)

For example,
```bash
$ sudo du -h ~ | sort -h
4.0K	/home/aimldl/.adobe/Acrobat/9.0/AdobeIDataSync
4.0K	/home/aimldl/.adobe/Acrobat/9.0/Cert
  ...
81G	/home/aimldl/Desktop
146G	/home/aimldl
$
```
## Get the top n largest files under a directory
``` bash
$ du -h [directory_name] | sort -rh | head -n
```
The -r option for the sort command sorts the output in the reverse order. 
>  -r, --reverse               reverse the result of comparisons 
The head command shows the top nth outputs.

For example, the ten largest directories is obtained by running:
``` bash
$ sudo du -h ~ | sort -rh | head -10
```

## Limit the max depth
```bash
$ du -hd N [directory_name]
$ du -h --max-depth=N [directory_name]
```
>   -d, --max-depth=N     print the total for a directory (or file, with --all)
                          only if it is N or fewer levels below the command
                          line argument;  --max-depth=0 is the same as
                          --summarize
For example,
```bash
$ du -hd 1 ~
68K	./.aws
2.6M	./.ipython
  ...
269M	./tensorflow_datasets
146G	.
$
```
`$ du -h -d 1 ~` and `$ du -h --max-depth=1 ~` return the same result.

## Find the total size of certain file type under a specified directory

```bash
$ du -ch ./* | grep total
21G	total
$
```
Equivalently, the following command works, too. 16G+1.9G+1.7G+1.7G+196M=21.496G
```bash
$ find . -type f -name '*' -exec du -ch {} + | grep total$
16G	total
1.9G	total
1.7G	total
1.7G	total
196M	total
$
```
Caution: Don't forget the quote marks ' around the aesterisk *.
```bash
$ find . -type f -name * -exec du -ch {} + | grep total$
find: paths must precede expression: `AlexNet to AlphaGo Zero.png'
find: possible unquoted pattern after predicate `-name'?
$
```

## References
* [How to Get the Size of a Directory in Linux](https://linuxize.com/post/how-get-size-of-file-directory-linux/)
* [Find the total size of certain files within a directory branch](https://unix.stackexchange.com/questions/41550/find-the-total-size-of-certain-files-within-a-directory-branch)
