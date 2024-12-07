##### aimldl > aws > s3 > mb.md

# aws s3 mb 

To create a Bucket, run:
```bash
  $ aws s3 mb s3://bucket-name
```
For example,
```bash
$ aws s3 mb s3://temp-2019-11-11
make_bucket: temp-2019-11-11
$ aws s3 ls
  ...
2019-11-11 04:49:04 temp-2019-11-11
$
```
