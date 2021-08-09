* Draft: 2021-08-09 (Mon)

# Google Cloud Platform





5-install_google_cloud_sdk.md

```bash
$ ./install_google_cloud_sdk
```



```bash
  ...
Do you want to help improve the Google Cloud SDK (y/N)?  y
  ...
Do you want to continue (Y/n)?  y
  ...
You must log in to continue. Would you like to log in (Y/n)?  y

Your browser has been opened to visit:

    https://accounts.google.com/o/oauth2/auth?response_type=  ...

Updates are available for some Cloud SDK components.  To install them,
please run:
  $ gcloud components update

You are logged in as: [aimldl*@gmail.com].

Pick cloud project to use: 
 [1] planar-hangout-320905
 [2] psyched-subset-320905
 [3] Create a new project
Please enter numeric choice or text value (must exactly match list 
item):  3

Enter a Project ID. Note that a Project ID CANNOT be changed later.
Project IDs must be 6-30 characters (lowercase ASCII, digits, or
hyphens) in length and start with a lowercase letter. kubeflow-1-2-0-cluster

  ...

Created a default .boto configuration file at [/home/aimldl/.boto]. See this file and
[https://cloud.google.com/storage/docs/gsutil/commands/config] for more
information about configuring Google Cloud Storage.
Your Google Cloud SDK is configured and ready to use!

* Commands that require authentication will use aimldl.tkim@gmail.com by default
* Commands will reference project `kubeflow-1-2-0-cluster` by default
Run `gcloud help config` to learn how to change individual settings

This gcloud configuration is called [default]. You can create additional configurations if you work with multiple accounts and/or projects.
Run `gcloud topic configurations` to learn more.

Some things to try next:

* Run `gcloud --help` to see the Cloud Platform services you can interact with. And run `gcloud help COMMAND` to get help on any gcloud command.
* Run `gcloud topic --help` to learn about advanced features of the SDK like arg files and output formatting
$
```

## Verify

```bash
$ tree -d -L 2 google-cloud-sdk
google-cloud-sdk
├── bin
│   └── bootstrapping
├── data
│   └── cli
├── deb
│   └── mapping
├── lib
│   ├── googlecloudsdk
│   ├── surface
│   ├── third_party
│   └── tools
├── platform
│   ├── anthoscli_licenses
│   ├── bq
│   ├── ext-runtime
│   └── gsutil
└── rpm
    └── mapping

18 directories
$
```



The configuration

```bash
$ ./google-cloud-sdk/bin/gcloud init
Welcome! This command will take you through the configuration of gcloud.

Settings from your current configuration [default] are:
core:
  account: aimldl.tkim@gmail.com
  disable_usage_reporting: 'False'
  project: kubeflow-1-2-0-cluster

Pick configuration to use:
 [1] Re-initialize this configuration [default] with new settings 
 [2] Create a new configuration
Please enter your numeric choice: 
$
```

Enter `Ctrl+C` to exit

7-configure_a_default_compute_region_and_zone.md



[Google 클라우드 플랫폼](https://console.cloud.google.com/?hl=ko)

