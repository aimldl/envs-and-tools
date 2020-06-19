##### aimldl > aws > s3 > README.md
* Rev.1: 2019-11-11 (Mon)
* Draft: Some time ago
## CLI (Command Line Interface) Commands
To get a help on the CLI commands for s3, run:
```bash
$ aws s3 help
```
### Download all the files in a S3 buccket
Unlike Dropbox or Google Drive, you can't download all the files in an S3 bucket at a time on the web browser. Amazon S3 is an object storage and doesn't provide such functionality while you can click to download a single file. Instead, you may use CLI command as follows.

```bash
$ aws s3 sync s3://<source_bucket> <local_destination>
# For example,
$ aws s3 sync s3://example-bucket .
```
For details, refer to [Downloading an entire S3 bucket?](https://stackoverflow.com/questions/8659382/downloading-an-entire-s3-bucket/55061863).

#### Example
* Situation
There is a S3 bucket with .wav files. In the bucket, the file names are english-*.wav, korean-*.wav, japanese-*.wav, chinese-*.wav, and so on. The bucket name is "hula" something and the exact name is forgotten.

* Task
1. To figure out the bucket name, The 's3 ls' command lists the buckets on S3.
```bash
$ aws s3 ls
   ...
2019-09-17 16:27:07 hula-dataset
   ...
$
```
The bucket name is found to be "hula-dataset".

2. Download all the files in the bucket to the current directory.
```bash
$ aws s3 cp s3://hula-dataset .
```
Note it's possible to download all the files with the sync command as well. 
```bash
$ aws s3 sync s3://hula-dataset .
```
However cp is faster than sync because no sync information needs to be updated.

3. Download certain files in the bucket to the current directory.
```bash
$ aws s3 cp s3://hula-dataset/english-*.wav .
$ aws s3 cp s3://hula-dataset/english-* .
```
Note the following commands fail.
```bash
$ aws s3 sync s3://hula-dataset/english-*.wav .
$ aws s3 sync s3://hula-dataset/english-* .
```
(EOF)

TODO: Qb: Verify and correct the errors in the following commands.

(hula) aimldl@GPU-Desktop:~/aimldl/private/hula-HunkLabeling/input/wav_files/downloads$ aws s3 cp s3://hula-dataset/english-*.wav .
fatal error: An error occurred (404) when calling the HeadObject operation: Key "english-*.wav" does not exist
(hula) aimldl@GPU-Desktop:~/aimldl/private/hula-HunkLabeling/input/wav_files/downloads$ aws s3 cp s3://hula-dataset .
(hula) aimldl@GPU-Desktop:~/aimldl/private/hula-HunkLabeling/input/wav_files/downloads$ ls
(hula) aimldl@GPU-Desktop:~/aimldl/private/hula-HunkLabeling/input/wav_files/downloads$ aws s3 cp s3://hula-dataset/ .
(hula) aimldl@GPU-Desktop:~/aimldl/private/hula-HunkLabeling/input/wav_files/downloads$ ls
(hula) aimldl@GPU-Desktop:~/aimldl/private/hula-HunkLabeling/input/wav_files/downloads$ aws s3 cp s3://hula-dataset/* .
fatal error: An error occurred (404) when calling the HeadObject operation: Key "*" does not exist
(hula) aimldl@GPU-Desktop:~/aimldl/private/hula-HunkLabeling/input/wav_files/downloads$ 

[How to delete multiple files in S3 bucket with AWS CLI](https://stackoverflow.com/questions/41733318/how-to-delete-multiple-files-in-s3-bucket-with-aws-cli)
```
USING UNIX WILDCARDS WITH AWS S3 (AWS CLI)

Currently AWS CLI doesn’t provide support for UNIX wildcards in a command’s “path” argument. However, it is quite easy to replicate this functionality using the --exclude and --include parameters available on several aws s3 commands.

The wildcards available for use are:

"*" – Matches everything

"?" – Matches any single character

"[]" – Matches any single character between the brackets

"[!]" – Matches any single character not between the brackets

A few things to remember about using --include and --exclude with the aws s3 command:

You may use any number of --include and --exclude parameters.

Parameters passed later take precedence over parameters passed earlier (in the same command).

All files and objects are “included” by default, so in order to include only certain files you must use “exclude” then “include”. --recursive must be used in conjunction with --include and --exclude or else commands will only perform single file/object operations.

Examples: Copy all files from working directory to the big-datums bucket:

aws s3 cp ./ s3://big-datums/ --recursive

Delete all ".java" files from the big-datums bucket:

aws s3 rm s3://big-datums/ --recursive --exclude "*" --include "*.java"

Delete all files in the big-datums bucket with a file extension beginning with "j" or "c" (".csv", ".java, ".json", ."jpeg", etc.):

aws s3 rm s3://big-datums/ --recursive --exclude "*" --include "*.[jc]*"

Copy ".txt" and ".csv" files from big-datums S3 bucket to local working directory:

aws s3 cp s3://big-datums/ . --recursive --exclude "*" --include "*.txt" --include "*.csv"

#Copy all files from working directory to the big-datums bucket:
aws s3 cp ./ s3://big-datums/ --recursive

#Delete all ".java" files from the big-datums bucket:
aws s3 rm s3://big-datums/ --recursive --exclude "*" --include "*.java"

#Delete all files in the big-datums bucket with a file extension beginning with "j" or "c" (".csv", ".java, ".json", ."jpeg", etc.):
aws s3 rm s3://big-datums/ --recursive --exclude "*" --include "*.[jc]*"

#Copy ".txt" and ".csv" files from big-datums S3 bucket to local working directory:
aws s3 cp s3://big-datums/ . --recursive --exclude "*" --include "*.txt" --include "*.csv" ```
```
