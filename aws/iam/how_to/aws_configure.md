* Rev.1: 2020-10-07 (Wed)
* Draft: 2020-04-05 (Sun)

# aws configure

`aws configure` is a command to configure AWS CLI (Command Line Interface). The `aws` command refers to the AWS configuration files `config` and `credentials` under the `~/.aws` directory to grant access rights. If AWS is not configured, `Access Denied` error occurs as follows.

```bash
$ aws s3 cp test.txt s3://aimldl
upload failed: ./test.txt to s3://aimldl/test.txt An error occurred (AccessDenied) when calling the PutObject operation: Access Denied
$
```

To resolved the `Access Denied` issue, `aws configure` allows a user to configure the access rights

* [Configuring the AWS CLI](https://docs.aws.amazon.com/cli/latest/userguide/cli-chap-configure.html) (The Same document in Korean, [AWS CLI 구성](https://docs.aws.amazon.com/ko_kr/cli/latest/userguide/cli-chap-configure.html))

## Prerequisites

It is assumed that the AWS CLI is configured on your terminal. 

## Basic Commands

`aws configure` or `aws configure --profile default` shows the existing configuration.

### $ aws configure

At the beginning, nothing is configured.

```bash
$ aws configure
AWS Access Key ID [None]: 
AWS Secret Access Key [None]: 
Default region name [ap-northeast-2]: 
Default output format [None]: 
$
```

When the credentials are configured, the same command `aws configure` displays the existing configuration.

```
$ aws configure
AWS Access Key ID [****************QRST]: 
AWS Secret Access Key [****************jklm]: 
Default region name [us-west-2]: 
Default output format [json]: 
$
```

Note Amazon SageMaker resets the user home directories except the `~/SageMaker` directory. This resets AWS configuration files saved under the `~/.aws` directory. 

### Locate the `config` and `credentials` Files

Under the user home directory, the `~/.aws` directory has `config` and `credentials` which are text files. 

```bash
$ cd ~/.aws
~/.aws$ tree
.
├── config
└── credentials

0 directories, 2 files
~/.aws$ cat config 
[default]
region = us-west-2
output = json
~/.aws$ cat credentials 
[default]
aws_access_key_id = ABCDEFGHIJKLMNOPQRST
aws_secret_access_key = abcdefghijklmnopqrstuvwxyz/abcdefghijklm
$
```

### $ aws configure --profile default

The `--profile default` option can be used to see the default profile. The output message is identical to the above one.

```bash
$ aws configure --profile default
AWS Access Key ID [****************QRST]: 
AWS Secret Access Key [****************jklm]: 
Default region name [us-west-2]: 
Default output format [json]: 
$
```