##### aimldl > computing_environments > bash > basics > unix_shell_programming_tools > 12_3-a_safe_delete_command.md
* Rev.1: 2019-11-28 (Wed)
* Draft: Long long time ago
##### TODO:
Fix "bash: [: eq: binary operator expected" in:
```bash
/temp$ delete *
bash: [: eq: binary operator expected
You are about to delete these files: aaa aab dda ddb
Are you sure about this? Enter y for yes.y
```
But it works just fine.

### Functions for a new rm command and a safe delete command
Add the following part in .bash_profile or .bash_rc
```bash
#############################
#  A Safe "delete" Command  #
#############################
# Disable the rm command and define a safe "delete" command.
# The delete command forcefully moves all specified files to directory .trash.
# Directory .trash works exactly same as Ubuntu GUI's "Trash" and Windows "Trash".
#
# Caution: Empty the .trash directory every now and then.
# TODO:
#   Create a house-keeping function to delete all trash files more than 30 days old.
#   The house-keeping function might also monitor how large the trash directory is getting.
#   If too many files are being stored, perhaps some need to be deleted to free up disk space.
# Source: pp.492~495, Unix Shell Programming Tools, David Medinets, McGraw-Hill

# Create a rm function that does nothing.
# This should help users keep out of mischief.
rm () {
  echo "Please use the delete command."
}

delete () {
  # Create directory ~/.trash if it doesn't exist.
  if [ ! -d ~/.trash ]; then
    mkdir ~/.trash
  fi

  if [ $# eq 0 ]; then
    # Warning message if there is no input argument.
    echo "Please specify a filename to delete."
  else
    echo "You are about to delete these files: $@"
    echo -n "Are you sure about this? Enter 'y' for yes."
    read
    # If 'y', force to move all the files to directory .trash.
    if [ "$REPLY" = "y" ]; then
      mv --force $@ ~/.trash
    fi
  fi
}
```

### Test if the functions work well.
This example is identical to the book with a slight change by me.
```bash
$ bash
2019-11-28 (Thu) 16:53 (47th week)
$ mkdir temp
$ cd temp/
/temp$ echo "test" > aaa
/temp$ echo "test" > aab
/temp$ mkdir dda
/temp$ mkdir ddb
/temp$ echo "test" > dda/aaa
/temp$ echo "test" > dda/aab
/temp$ ls -p
aaa  aab  dda/  ddb/
/temp$ rm aaa
Please use the delete command.
/temp$ rm *
Please use the delete command.
/temp$ delete *
You are about to delete these files: aaa aab dda ddb
Are you sure about this? Enter 'y' for yes.y
/temp$ ls -p
/temp$ ls ~/.trash
aaa  aab  dda  ddb
/temp$
```

To delete a large number of files with, disable the function in the .bashrc.
```bash
$ rm -rf *
Please use the delete command.
$ which delete
```
```bash
rm () {
  echo "Please use the delete command."
}
```
Uncomment this function and run .bashrc again.
```bash
#rm () {
#  echo "Please use the delete command."
#}
```
Rerun the .bashrc.
```bash
$ source .bashrc
```
```bash
~/anaconda3$ rm -rf *
```
