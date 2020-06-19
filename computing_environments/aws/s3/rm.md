TODO: Write this document

$ aws s3 rm s3://hula-dataset --recursive --exclude "*" --include "korean-*.wav"
delete: s3://hula-dataset/korean-1.wav
  ...
delete: s3://hula-dataset/korean-998.wav
$

Wrong
$ aws s3 rm s3://hula-dataset/korean-*.wav

[How to delete multiple files in S3 bucket with AWS CLI](https://stackoverflow.com/questions/41733318/how-to-delete-multiple-files-in-s3-bucket-with-aws-cli)
> Delete all ".java" files from the big-datums bucket:
aws s3 rm s3://big-datums/ --recursive --exclude "*" --include "*.java"
