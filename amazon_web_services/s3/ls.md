
```bash
$ aws s3 ls s3://hula-dataset
```

```bash
$ aws s3 ls s3://hula-dataset/korean | wc -l
999
```

```bash
$ aws s3 ls s3://hula-dataset/korean-*.wav
```
This fails
