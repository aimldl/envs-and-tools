

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



```
$ aws s3 cp test.txt s3://aimldl
upload failed: ./test.txt to s3://aimldl/test.txt An error occurred (AccessDenied) when calling the PutObject operation: Access Denied


$ aws s3 cp test.txt s3://aimldl/
upload: ./test.txt to s3://aimldl/test.txt

$ ls
dota  dota1_1024  dota_dataset-prepared.tar.gz  nohup.out  test.txt


Be careful not to do this.

$ aws s3 cp Arirang_Dataset.zip s3://aimldl/public
upload: ./Arirang_Dataset.zip to s3://aimldl/public 

```

