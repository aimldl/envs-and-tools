##### aws/ec2/README.md


[Amazon EC2 Instance Types](https://aws.amazon.com/ec2/instance-types/)
Instance types comprise varying combinations of CPU, memory, storage, and networking capacity.
* General Purpose
* Compute Optimized
* Memory Optimized
* Accelerated Computing
* Storage Optimized
* Instance Features
* Measuring Instance Performance

General Purpose/T2
<img src="images/amazon_EC2_Instance_Types-general_purpose_T2.png">
2019-12-18 (Wed): Change Instance Type: t2.micro -> t2.large

t2.nano is used to run WordPress which serves my personal homepage.

[AWS > Documentation > Amazon VPC > User Guide > VPCs and Subnets](https://docs.aws.amazon.com/vpc/latest/userguide/VPC_Subnets.html)

[Assign Public IP (not Elastic IP) after instance launched](https://serverfault.com/questions/706560/assign-public-ip-not-elastic-ip-after-instance-launched)

####
[Which is low cost Sagemaker or EC2?](https://stackoverflow.com/questions/52198660/which-is-low-cost-sagemaker-or-ec2)
> Q: For example, ml.p2.8xlarge for training job at ap-northeast on Sagemaker takes 16.408 USD / hour, but p2.8xlarge for on-demand at ap-northeast on Ec2 takes 12.336 USD/hour. Is it cheep to just train the DL models on Ec2 rather than Sagemaker if we only use it for training?
> A: You are correct about EC2 being cheaper than Sagemaker.

> However you have to understand their differences. EC2 provides you computing power Sagemaker (try to) provides a fully configured environment and computing power with a seamless deployment model for you to start training your model on day one If you look at Sagemaker's overview page, it comes with Jupyter notebooks, pre-installed machine learning algorithms, optimized performance, seamless rollout to production etc.

> Note that this is the same as self-hosting a EC2 MYSQL server and utilizing AWS managed RDS MYSQL. Managed services always appears to be more expensive, but if you factor in the time you have to spent maintaing server, updating packages etc., the extra 30% cost may be worth it.

> So in conclusion if you rather save some money and have the time to set up your own server or environment, go for EC2. If you do not want to be bothered with these work and want to start training as soon as possible, use Sagemaker.


Deep Learning Base AMI (Ubuntu 16.04) Version 21.0 - ami-06e910f75335da77e
Comes with foundational platform of NVidia CUDA, cuDNN, NCCL, GPU Drivers, Intel MKL-DNN and other system libraries to deploy your own custom deep learning environment. For a fully managed experience, check: https://aws.amazon.com/sagemaker

Deep Learning Base AMI (Ubuntu 18.04) Version 21.0 - ami-06584f2f0ef43f39b
Comes with foundational platform of NVidia CUDA, cuDNN, NCCL, GPU Drivers, Intel MKL-DNN and other system libraries to deploy your own custom deep learning environment. For a fully managed experience, check: https://aws.amazon.com/sagemaker

AWS ec2 fixed IP
Assign a Fixed IP to an AWS EC2 Instance
Click on the Elastic IPs link in the AWS Console.
Allocate a new address.
Associate the address with a running instance.
Note the IP being assigned to your instance.
[Assign a Fixed IP to an AWS EC2 Instance](https://dzone.com/articles/assign-fixed-ip-aws-ec2)
