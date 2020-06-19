* Draft: 2020-04-05 (Sun)

# aws configure

"aws configure" is a command to configure AWS CLI.

* [Configuring the AWS CLI](https://docs.aws.amazon.com/cli/latest/userguide/cli-chap-configure.html) (The Same document in Korean, [AWS CLI 구성](https://docs.aws.amazon.com/ko_kr/cli/latest/userguide/cli-chap-configure.html))

## How to Locate the Files for "aws configure"

It is assumed that the AWS CLI is configured on your terminal.

### $ aws configure

Run "aws configure" to see the default set-up.

```
$ aws configure
/usr/lib/python3/dist-packages/requests/__init__.py:80: RequestsDependencyWarning: urllib3 (1.25.5) or chardet (3.0.4) doesn't match a supported version!
  RequestsDependencyWarning)
AWS Access Key ID [****************QRST]: 
AWS Secret Access Key [****************jklm]: 
Default region name [us-west-2]: 
Default output format [json]: 
$
```

### $ aws configure --profile default

The "--profile default" option can be used to see the default profile. The output message is identical to the above one.

```
$ aws configure --profile default
/usr/lib/python3/dist-packages/requests/__init__.py:80: RequestsDependencyWarning: urllib3 (1.25.5) or chardet (3.0.4) doesn't match a supported version!
  RequestsDependencyWarning)
AWS Access Key ID [****************QRST]: 
AWS Secret Access Key [****************jklm]: 
Default region name [us-west-2]: 
Default output format [json]: 
$
```

### Locate the config and credentials Files

Under the home directory, the ".aws" directory has "config" and "credentials" which are text files. 

```
$ cd ~/.aws
~/.aws$ tree
.
├── config
└── credentials

0 directories, 2 files
~/.aws$ cat credentials 
[default]
aws_access_key_id = ABCDEFGHIJKLMNOPQRST
aws_secret_access_key = abcdefghijklmnopqrstuvwxyz/abcdefghijklm
~/.aws$ cat config 
[default]
region = us-west-2
output = json
$
```

### "aws configure" vs. credentials & config

For convenience, the outputs are compared below . Obviously, both files "credentials" and "config" contain the information for "aws configure".

| AWS Access Key ID [****************QRST]: <br/>AWS Secret Access Key [****************jklm]: <br/>Default region name [us-west-2]: <br/>Default output format [json]: |
| ------------------------------------------------------------ |
| [default]<br/>aws_access_key_id = ABCDEFGHIJKLMNOPQRST<br/>aws_secret_access_key = abcdefghijklmnopqrstuvwxyz/abcdefghijklm<br/>[default]<br/>region = us-west-2<br/>output = json<br/> |

