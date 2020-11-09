ls.md


Google search: linux command to list only directory without . and ..

[How to List Only Directories in Linux](https://linoxide.com/linux-command/linux-commad-to-list-directories-directory-names-only/)

```bash
$ ls -d */
$ ls -ld */
$ ls -lF | grep \/$
$ ls -laF | grep \/$
$ ls -F | grep \/$
$ ls -l | grep ^d  |
$ ls -l | grep ^d | awk '{print $8,$9}'
$ ls -la | grep ^d  |   |
```

Other Commands
$ echo */
$ printf '%s\n' */
$ find . -maxdepth 1 -type d

[List of All Folders and Sub-folders [closed]](https://stackoverflow.com/questions/14827686/list-of-all-folders-and-sub-folders)

```bash
find . -type d
tree -d
ls -lad **/*

# To exclue certain directory,
find . -type d ! -name "~snapshot"
```

## Example:
[LibriSpeech ASR Corpus](http://www.openslr.org/12/) has a well-structured, but relatively complex directory structure. When all the compressed files are downloaded and uncompressed, the directory structure looks like below.

```bash
$ tree -d
.
├── books
│   ├── ascii
│   │   ├── 1
│   │   ├── 1000001
│   │   ├── 1000003
  ...
    ├── 982
    │   ├── 133222
    │   └── 133226
    └── 985
        ├── 126224
        ├── 126226
        └── 126228

20111 directories
```
When I'm interested only in the sub-sub-directories, I may use the following command along with the -lad option.
```bash
(pytorch) ubuntu@ec2-seoul-gpu:~/wav2vec/dataset/LibriSpeech$ ls -lad **/*/*
dr-xr-xr-x 2 ubuntu ubuntu   4096 Sep 21  2014 books/ascii/1
dr-xr-xr-x 2 ubuntu ubuntu   4096 Sep 21  2014 books/ascii/1000001
  ...
drwxr-xr-x 2 ubuntu ubuntu   4096 Aug 16  2014 train-other-500/985/126226
drwxr-xr-x 2 ubuntu ubuntu   4096 Aug 16  2014 train-other-500/985/126228
```
