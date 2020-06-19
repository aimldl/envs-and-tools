### Fetching a file from a remove server

```bash
$ sftp ubuntu@aa.bb.c.ddd
ubuntu@aa.bb.c.ddd's password:
Connected to aa.bb.c.ddd
sftp> cd target_directory
sftp> ls
file2download.txt
sftp> !ls
Downloads
sftp> get file2download.txt
Fetching /home/ubuntu/target_directory/file2download.txt to file2download.txt
/home/ubuntu/target_directory/file2download.txt                                   100%   86KB   3.1MB/s   00:00
sftp> !ls
file2download.txt  Downloads
sftp> bye
```

### Access an AWS EC2 Instance which is a remove server

```bash
$ sftp -i <ssh_key2server> <user_id>@<public_ip>
```
##### ssh_key2server
File extension for the SSH key:
* .pem is for Linux & iOS (MAC).
* .ppk is for Windows
##### user_id & public_ip
You can use the same user ID and public IP for an SSH access.

##### Example to Fetch a File
```bash
$ sftp -i ec2-t2-micro.pem ubuntu@12.345.67.89
Connected to 12.345.67.89.
sftp> ls
aws_polly                          etc
sftp> cd aws_polly/
sftp> ls
aws_polly.tar.gz                   run_polly
sftp> get aws_polly.tar.gz
Fetching /home/user_id/aws_polly/aws_polly.tar.gz to aws_polly.tar.gz
/home/user_id/aws_polly/aws_polly.tar.gz                               100%   36MB  11.0MB/s   00:03
sftp> !ls
aws_polly.tar.gz	      ec2-t2-micro.pem    miscellaneous
sftp> bye
$
```
Note the SSH key file, e.g. ec2-t2-micro.pem, is located in the same directory where the command is ran.

##### Example to Put a File from the Local Computer
```bash
$ sftp -i ec2-t2-micro.pem ubuntu@12.345.67.89
Connected to 12.345.67.89.
sftp> cd aws_polly/
sftp> mkdir new
sftp> cd new/
sftp> ls
sftp> !ls
file2upload.txt	      ec2-t2-micro.pem    miscellaneous
sftp> put file2upload.txt .
Uploading file2upload.txt to /home/user_id/aws_polly/new/file2upload.txt
file2upload.txt                                               100% 1085   194.1KB/s   00:00
sftp> ls
file2upload.txt
sftp> bye
```

## sftp> help
```bash
sftp> help
Available commands:
bye                                Quit sftp
cd path                            Change remote directory to 'path'
chgrp grp path                     Change group of file 'path' to 'grp'
chmod mode path                    Change permissions of file 'path' to 'mode'
chown own path                     Change owner of file 'path' to 'own'
df [-hi] [path]                    Display statistics for current directory or
                                   filesystem containing 'path'
exit                               Quit sftp
get [-afPpRr] remote [local]       Download file
reget [-fPpRr] remote [local]      Resume download file
reput [-fPpRr] [local] remote      Resume upload file
help                               Display this help text
lcd path                           Change local directory to 'path'
lls [ls-options [path]]            Display local directory listing
lmkdir path                        Create local directory
ln [-s] oldpath newpath            Link remote file (-s for symlink)
lpwd                               Print local working directory
ls [-1afhlnrSt] [path]             Display remote directory listing
lumask umask                       Set local umask to 'umask'
mkdir path                         Create remote directory
progress                           Toggle display of progress meter
put [-afPpRr] local [remote]       Upload file
pwd                                Display remote working directory
quit                               Quit sftp
rename oldpath newpath             Rename remote file
rm path                            Delete remote file
rmdir path                         Remove remote directory
symlink oldpath newpath            Symlink remote file
version                            Show SFTP version
!command                           Execute 'command' in local shell
!                                  Escape to local shell
?                                  Synonym for help
```
