* Draft: 2021-05-18 (Tue)

# How to Configure a Default Compute Region and Zone

* After running the `$ ./google-cloud-sdk/bin/gcloud init` command, enter the necessary information as follows. 
* Refer to [Regions and zones](https://cloud.google.com/compute/docs/regions-zones) for details.
* That's it.

```bash
$ ./google-cloud-sdk/bin/gcloud init
  ...
You are logged in as: [user_id@gmail.com].

Pick cloud project to use: 
 [1] polar-scene-314004
 [2] tensorflow-training-314006
 [3] Create a new project
Please enter numeric choice or text value (must exactly match list 
item):  2

Your current project has been set to: [tensorflow-training-314006].

Do you want to configure a default Compute Region and Zone? (Y/n)?  y

Which Google Compute Engine zone would you like to use as project 
default?
If you do not specify a zone via a command line flag while working 
with Compute Engine resources, the default is assumed.
 [1] us-east1-b
 [2] us-east1-c
   ...
 [50] asia-northeast3-a
Did not print [27] options.
Too many options [77]. Enter "list" at prompt to print choices fully.
Please enter numeric choice or text value (must exactly match list 
item):  50

Your project default Compute Engine zone has been set to [asia-northeast3-a].
You can change it by running [gcloud config set compute/zone NAME].

Created a default .boto configuration file at [/home/aimldl/.boto]. See this file and
[https://cloud.google.com/storage/docs/gsutil/commands/config] for more
information about configuring Google Cloud Storage.
Your Google Cloud SDK is configured and ready to use!

* Commands that require authentication will use tkim.aimldl@gmail.com by default
* Commands will reference project `tensorflow-training-314006` by default
* Compute Engine commands will use region `asia-northeast3` by default
* Compute Engine commands will use zone `asia-northeast3-a` by default

Run `gcloud help config` to learn how to change individual settings

This gcloud configuration is called [default]. You can create additional configurations if you work with multiple accounts and/or projects.
Run `gcloud topic configurations` to learn more.

Some things to try next:

* Run `gcloud --help` to see the Cloud Platform services you can interact with. And run `gcloud help COMMAND` to get help on any gcloud command.
* Run `gcloud topic --help` to learn about advanced features of the SDK like arg files and output formatting
$
```

