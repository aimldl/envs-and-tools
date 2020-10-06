* Draft: 2020-10-06 (Tue)


```bash
$ gcc --version
$ sudo yum-config-manager --enable epel
$ sudo yum install gcc72 gcc72-c++
$ gcc --version
$ gcc72 --version
$ which gcc
$ alias gcc="gcc72"
$ gcc --version
```

[How do I enable the EPEL repository for my Amazon EC2 instance running CentOS, RHEL, or Amazon Linux?](https://aws.amazon.com/premiumsupport/knowledge-center/ec2-enable-epel/?nc1=h_ls)

### Amazon Linux Amazon Machine Image (AMI):
The EPEL repository is already installed on the original version of Amazon Linux, but you must enable it. You can enable this repository either by using the yum-config-manager command or by editing the epel.repo file.
```bash
$ sudo yum-config-manager --enable epel
```


[Install External Libraries and Kernels in Notebook Instances](https://docs.aws.amazon.com/sagemaker/latest/dg/nbi-add-external.html)

Package installation tools
SageMaker notebooks support the following package installation tools:

conda install

pip install

Lifecycle configuration scripts.

For example scripts, see SageMaker Notebook Instance Lifecycle Config Samples. For more information on lifecycle configuration, see Customize a Notebook Instance Using a Lifecycle Configuration Script.

Notebooks – The following commands are supported. The % install commands are recommended.

%conda install

%pip install

!conda install

!pip install

The Jupyter terminal – You can install packages using pip and conda directly.


