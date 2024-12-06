* Rev.1: 2022-04-13 (Wed)
* Draft: 2021-05-13 (Thu)
 
# history

## How to Print History Command Without Line Numbers
Google search: linux output command without index
Google search: linux command history without numbers
* [Linux Print History Command Without Line Numbers](https://www.poftut.com/linux-history-command-without-line-numbers/), 2016-09-15, İsmail Baydan
* [How To Display Bash History Without Line Numbers](https://ostechnix.com/how-to-display-bash-history-without-line-numbers/)

### Option 1. Print `.bash_history`

```bash
$ cat ~/.bash_history
```

### Option 2. Using the cut command
```bash
$ history | cut -c 8-
```
Source: [How To Display Bash History Without Line Numbers](https://ostechnix.com/how-to-display-bash-history-without-line-numbers/)

or
```bash
$ history | cut -d ' ' -f 4-
```
Note there exists a space in -d ' '.

Source: [Linux Print History Command Without Line Numbers](https://www.poftut.com/linux-history-command-without-line-numbers/), 2016-09-15, İsmail Baydan

### Option 3. Use the awk command
```bash
$ history | awk '{$1=""; print substr($0,2)}'
```
### Option 4. Using the sed command
```bash
$ history | sed 's/^[ ]*[0-9]\+[ ]*//'
```
