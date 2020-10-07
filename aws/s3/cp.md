

# aws s3 cp

Error
From a SageMaker instance,
```bash
$ aws s3 cp sm.tar.gz s3://temp-2019-11-11
upload failed: ./sm.tar.gz to s3://temp-2019-11-11/sm.tar.gz An error occurred (AccessDenied) when calling the PutObject operation: Access Denied

$ aws s3 cp sm.tar.gz s3://temp-2019-11-11/sm.tar.gz
upload failed: ./sm.tar.gz to s3://temp-2019-11-11/sm.tar.gz An error occurred (AccessDenied) when calling the PutObject operation: Access Denied
$
```
For details, refer to [copy files from local to aws S3 Bucket(aws cli + s3 bucket)](https://qiita.com/alokrawat050/items/56820afdb6968deec6a2).
