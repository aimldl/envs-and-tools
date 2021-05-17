* Draft: 2021-05-17 (Mon)

# How to Install Google Cloud SDK



https://cloud.google.com/sdk

Step 1. Go to https://cloud.google.com/sdk

<img src="images/gcp-cloud_sdk-homepage.png">

Step 2. Click `Get started`

[Installing Google Cloud SDK](https://cloud.google.com/sdk/docs/install)

```bash

$ python --version
Python 3.8.5
$

```





Download and initialize the                          latest version of Cloud SDK.

| Platform              | Package                                                      | Size    | SHA256 Checksum                                              |
| --------------------- | ------------------------------------------------------------ | ------- | ------------------------------------------------------------ |
| Linux 64-bit (x86_64) | [google-cloud-sdk-340.0.0-linux-x86_64.tar.gz](https://dl.google.com/dl/cloudsdk/channels/rapid/downloads/google-cloud-sdk-340.0.0-linux-x86_64.tar.gz) | 85.1 MB | f2ae79ff55a3bbe700208ccdde49c2fd5511c03016e3a09f69257ffdd6a6a9d6 |
| Linux 32-bit (x86)    | [google-cloud-sdk-340.0.0-linux-x86.tar.gz](https://dl.google.com/dl/cloudsdk/channels/rapid/downloads/google-cloud-sdk-340.0.0-linux-x86.tar.gz) | 82.5 MB | 0446d7fd770601389c878640c8749d6336f3097c5e99005d5eab4b911343baf1 |

For x86_64

```bash
$ curl -O https://dl.google.com/dl/cloudsdk/channels/rapid/downloads/google-cloud-sdk-340.0.0-linux-x86_64.tar.gz
$ ls
google-cloud-sdk-340.0.0-linux-x86_64.tar.gz
$
```



Extract

```bash
$ tar -xvf google-cloud-sdk-340.0.0-linux-x86_64.tar.gz 

```

```bash
$ ./google-cloud-sdk/install.sh
  ...
Do you want to help improve the Google Cloud SDK (y/N)? 
```

Enter `n`. You may choose to enter `y`.

```bash
  ...
To install or remove components at your current SDK version [340.0.0], run:
  $ gcloud components install COMPONENT_ID
  $ gcloud components remove COMPONENT_ID

To update your SDK installation to the latest version [340.0.0], run:
  $ gcloud components update


Modify profile to update your $PATH and enable shell command 
completion?

Do you want to continue (Y/n)?
```

Enter `y`.

```bash
Enter a path to an rc file to update, or leave blank to use 
[/home/k8smaster/.bashrc]: 
```

Hit the enter key.



```bash
  ...
==> Start a new shell for the changes to take effect.


For more information on how to get started, please visit:
  https://cloud.google.com/sdk/docs/quickstarts
$
```



Run gloud init to initialize the SDK.



```bash
$ ./google-cloud-sdk/bin/gcloud init

```

The full message is below.

```bash
Welcome! This command will take you through the configuration of gcloud.

Your current configuration has been set to: [default]

You can skip diagnostics next time by using the following flag:
  gcloud init --skip-diagnostics

Network diagnostic detects and fixes local network connection issues.
Checking network connection...done.                                            
Reachability Check passed.
Network diagnostic passed (1/1 checks passed).

You must log in to continue. Would you like to log in (Y/n)?
```

Enter `y` and a web browser pops up. Select your Google account and click `Allow`.

sign in and verify the account.

Download the SDK to your local computer.

<img src="images/sign_in_with_google.png">

Install it on your local machine.

<img src="images/">

TODO: https://cloud.google.com/sdk/docs/install

<img src="images/">



<img src="images/">



<img src="images/">

