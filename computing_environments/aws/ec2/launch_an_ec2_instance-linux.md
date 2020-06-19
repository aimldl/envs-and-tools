##### aimldl/aws/ec2/launch_an_ec2_instance-linux.md


Some helpful resources to get you started
[How to connect to your Linux instance](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/AccessingInstances.html)
[Amazon EC2: User Guide](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/concepts.html)
[Learn about AWS Free Usage Tier](https://aws.amazon.com/free/?all-free-tier.sort-by=item.additionalFields.SortRank&all-free-tier.sort-order=asc)
[Amazon EC2: Discussion Forum](https://forums.aws.amazon.com/forum.jspa?forumID=30)

While your instances are launching you can also
Create status check alarms to be notified when these instances fail status checks. (Additional charges may apply)
Create and attach additional EBS volumes (Additional charges may apply)
Manage security groups

How to connect to your instances
Your instances are launching, and it may take a few minutes until they are in the running state, when they will be ready for you to use. Usage hours on your new instances will start immediately and continue to accrue until you stop or terminate your instances.
Click View Instances to monitor your instances' status. Once your instances are in the running state, you can connect to them from the Instances screen. Find out how to connect to your instances.

Assign a static IP address

Elastic IP addresses
An Elastic IP address is a static, public IPv4 address that you allocate to your AWS account and is reachable from the internet. Learn more

SageMaker's directory
```bash
sh-4.2$ pwd
/home/ec2-user
sh-4.2$ ls
anaconda3  Nvidia_Cloud_EULA.pdf  SageMaker         sample-notebooks-1577664136  tools
examples   README                 sample-notebooks  src                          tutorials
sh-4.2$
```

Ec2
```bash
ubuntu@ip-y-y-y-y:~$ wget https://repo.anaconda.com/archive/Anaconda3-2019.10-Linux-x86_64.sh
ubuntu@ip-y-y-y-y:~$ ls
Anaconda3-2019.10-Linux-x86_64.sh  Nvidia_Cloud_EULA.pdf  README  src  tools
ubuntu@ip-y-y-y-y:~$ bash Anaconda3-2019.10-Linux-x86_64.sh
  ...
==> For changes to take effect, close and re-open your current shell. <==
  ...
ubuntu@ip-y-y-y-y:~$ ls
Anaconda3-2019.10-Linux-x86_64.sh  Nvidia_Cloud_EULA.pdf  README  anaconda3  src  tools
ubuntu@ip-y-y-y-y:~$ exit
logout
Connection to x.x.x.x closed.
```
Reconnect to the EC2 instance.
```bash
  ...
(base) ubuntu@ip-y-y-y-y:~$
```
Let's check the virtual environment. The base environment exists by default.
```bash
(base) ubuntu@ip-y-y-y-y:~$ conda info -e
# conda environments:
#
base                  *  /home/ubuntu/anaconda3

(base) ubuntu@ip-y-y-y-y:~$
```
For convenience, "ubuntu@ip-y-y-y-y" is omitted below.


p2.xlarge

#### Install Basic packages
tree, gedit
