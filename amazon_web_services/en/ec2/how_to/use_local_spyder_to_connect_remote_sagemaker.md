* Draft: 2020-10-16 (Fri)

# How to Use Local Spyder IDE for a Code on a Remote Amazon SageMaker

Spyder IDE must exist on both sides. 

### Remote machine: Amazon SageMaker

By default, SageMaker comes with Spyder IDE. To double-check, run:

```bash
(base) [ec2-user@ip-123-45-67-89 json]$ which spyder
~/anaconda3/bin/spyder
(base) [ec2-user@ip-123-45-67-89 json]$ 
```

### Local machine: Ubuntu Linux

Install Spyder 3

```bash
$ sudo apt-get install -y spyder3
```

To verify the installation, run

```bash
$ which spyder3
/usr/bin/spyder3
$
```

To launch Spyder IDE, run:

```bash
$ spyder3 &
[1] 15302
$
```

Now Spyder IDE is installed and working. 

spyder-kernels



```bash
(pytorch_p36) [ec2-user@ip-123-45-67-89 ~]$ conda install -y spyder-kernels
```



```bash
$ sudo apt install -y python-pip
```

### 3. Connect to the Remote Server