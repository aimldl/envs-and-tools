* Rev.1: 2021-02-18 (Thu)
* Draft: 2019-11-28 (Thu)

# AWS Remote Access

## Naming conventions

### An old conventions

My old naming conventions are below. While the list is organized and it has naming conventions, it is hard to read and I feel like a part of information is missing from the file names.

```bash
$ ls
VOX.pem
aimldl-e2e-automated-ml-workflow-kp.pem
key_for_mrtonnet_in_oregon.pem
key_for_mrtonnet_in_oregon.ppk
mrtonnet.pem
my_vpc1.pem
my_vpc1.ppk
private_key-aimldl_GPU_DESKTOP.pem
private_keys
sftp-ec2_oregon
sftp-ec2_seoul-aimldl
sftp-ec2_seoul-wordpress
ssh-ec2_oregon
ssh-ec2_seoul-aimldl
ssh-ec2_seoul-vox
ssh-ec2_seoul-wordpress
ssh-seoul-sagemaker-aimldl-gpu-instance
$
```

### The new conventions

The better naming convention (to me) is to start from the type of task followed by the actual file name.

`type_of_task-actual_file_name.file_extension`

`type_of_task`: ssh, sftp, keypair

`file_extension`: pem, ppk, (no extension)

The actual file name consists of:

* `purpose`-`aws_service_type`_`region`-`instance_type`

For example,

* `darknet_benchmark_on_v100`-`ec2_seoul`-`p3_2xlarge`

I try to match the `purpose` to the instance's name which helps finding the instance among a list of many instances.



Prerequisites

  1. Change the permission of this file.
       $ chmod +x ssh-ec2_seoul-aimldl
     Otherwise, the following error is expected.
       $ ./ssh-ec2_seoul-aimldl
       bash: ./ssh-ec2_seoul-aimldl: Permission denied
       #
    2.Change the permission of the key. The key must not be publicly viewable for SSH to work.
       $ chmod 400 my_vpc1.pem
     Otherwise, the following error is expected.
       $ ssh -i "mrtonnet.pem" ubuntu@15.165.221.187
       @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
       @         WARNING: UNPROTECTED PRIVATE KEY FILE!          @
       @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
       Permissions 0664 for 'mrtonnet.pem' are too open.
       It is required that your private key files are NOT accessible by others.
       This private key will be ignored.
       Load key "mrtonnet.pem": bad permissions
       Permission denied (publickey).
       $
   3. Update the accessing IP address if the EC2 instance has been restarted.
      When an instance is stopped and restarted, the public IP address is renewed.
        $ ./connect_aws-ec2-oregon 
        ssh -i <access_key>.pem -L 8888:localhost:8888 -X ubuntu@<ip_address>
        ssh: connect to host <ip_address> port 22: Connection timed out
#
      Possible Error message
        $ ./connect_aws-ec2-oregon 
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        @    WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!     @
        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        IT IS POSSIBLE THAT SOMEONE IS DOING SOMETHING NASTY!
        Someone could be eavesdropping on you right now (man-in-the-middle attack)!
        It is also possible that a host key has just been changed.
          ...
        Host key verification failed.
        $
#
How to check the public IP
  1. Sign in to the AWS Management Console at https://aws.amazon.com/console/
  2. Select the region on the top right corner of the console.
  3. Go to EC2/Instances and see IP address.
     Web browser: "IPv4 Public IP" in the "Description" tab
     AWS Console App: "Public IP"
#
When the connection is successfully established,
      $ ./connect_aws-ec2-oregon 
      ssh -i <access_key>.pem -L 8888:localhost:8888 -X ubuntu@<ip_address>
      The authenticity of host '<ip_address> (<ip_address>)' can't be established.
      ECDSA key fingerprint is <fingureprint>.
      Are you sure you want to continue connecting (yes/no)? yes
      Warning: Permanently added '<ip_address>' (ECDSA) to the list of known hosts.
        ...
      ubuntu@ip-<private_ip_address>:~$
#
How to check if the -X option works.
  1. Connect to the remote server
  2. Run xclock on the remote server
     $ xlock &
 3. Wait until xlock pops up on the local machine.
    I may take long on a slow Internet connection.
    On my office GPU desktop, it took almost 30 seconds!
