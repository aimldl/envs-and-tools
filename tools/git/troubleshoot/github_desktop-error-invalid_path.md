* Draft: 2020-11-22 (Sun)
# error: invalid path 'path/to/file'

## Problem
* When repository `projects` is being cloned, an error message occured:
```
Cloning into 'C:\github\projects'...
remote: Enumerating objects: 123, done.        
remote: Counting objects: 100% (123/123), done.        
remote: Compressing objects: 100% (100/100), done.        
remote: Total 39413 (delta 52), reused 45 (delta 15), pack-reused 39290        
Receiving objects: 100% (39413/39413), 1.86 GiB | 10.23 MiB/s, done.
Resolving deltas: 100% (6283/6283), done.
error: invalid path 'dacon.io/papers/DOTA: A Large-scale Dataset for Object Detection in Aerial Images.md'
fatal: unable to checkout working tree
warning: Clone succeeded, but checkout failed.
You can inspect what was checked out with 'git status'
and retry with 'git restore --source=HEAD :/'

Would you like to retry cloning ?
```

* When repository `environments` is being cloned, an error message occured:
```
Cloning into 'C:\github\environments'...
remote: Enumerating objects: 121, done.        
remote: Counting objects: 100% (121/121), done.        
remote: Compressing objects: 100% (121/121), done.        
remote: Total 10038 (delta 63), reused 9 (delta 0), pack-reused 9917        
Receiving objects: 100% (10038/10038), 582.10 MiB | 10.53 MiB/s, done.
Resolving deltas: 100% (3997/3997), done.
error: invalid path 'anaconda/troubleshoot/CondaError: Failed to write to.md'
fatal: unable to checkout working tree
warning: Clone succeeded, but checkout failed.
You can inspect what was checked out with 'git status'
and retry with 'git restore --source=HEAD :/'

Would you like to retry cloning ?
```

## Hint
When the file caused the error is delete, the problem has been solved. But a long list of subsequent error messages occured. All of the file names causing the error have characters such as ":", ">", and so on.

## Solution
Changing the file name WITHOUT those characters solved the problem.
