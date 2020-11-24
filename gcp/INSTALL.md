* Draft: 2020-11-24 (Tue)

# 



[Quickstart: Getting started with Cloud SDK](https://cloud.google.com/sdk/docs/quickstart)





```bash
ls
Dropbox      bin               google-cloud-sdk-319.0.0-linux-x86_64.tar.gz  문서      사진
GoogleDrive  github            공개                                          바탕화면  음악
anaconda3    google-cloud-sdk  다운로드                                      비디오    템플릿


$ ./google-cloud-sdk/install.sh
$
```





```bash
$ ./google-cloud-sdk/install.sh
Your current Cloud SDK version is: 319.0.0
The latest available version is: 319.0.0

┌────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│                                                 Components                                                 │
├───────────────┬──────────────────────────────────────────────────────┬──────────────────────────┬──────────┤
│     Status    │                         Name                         │            ID            │   Size   │
├───────────────┼──────────────────────────────────────────────────────┼──────────────────────────┼──────────┤
│ Not Installed │ App Engine Go Extensions                             │ app-engine-go            │  4.9 MiB │
│ Not Installed │ Appctl                                               │ appctl                   │ 21.0 MiB │
│ Not Installed │ Cloud Bigtable Command Line Tool                     │ cbt                      │  7.7 MiB │
│ Not Installed │ Cloud Bigtable Emulator                              │ bigtable                 │  6.6 MiB │
│ Not Installed │ Cloud Datalab Command Line Tool                      │ datalab                  │  < 1 MiB │
│ Not Installed │ Cloud Datastore Emulator                             │ cloud-datastore-emulator │ 18.4 MiB │
│ Not Installed │ Cloud Firestore Emulator                             │ cloud-firestore-emulator │ 42.1 MiB │
│ Not Installed │ Cloud Pub/Sub Emulator                               │ pubsub-emulator          │ 56.3 MiB │
│ Not Installed │ Cloud SQL Proxy                                      │ cloud_sql_proxy          │  7.6 MiB │
│ Not Installed │ Cloud Spanner Emulator                               │ cloud-spanner-emulator   │ 21.5 MiB │
│ Not Installed │ Emulator Reverse Proxy                               │ emulator-reverse-proxy   │ 14.5 MiB │
│ Not Installed │ Google Cloud Build Local Builder                     │ cloud-build-local        │  6.3 MiB │
│ Not Installed │ Google Container Registry's Docker credential helper │ docker-credential-gcr    │  1.8 MiB │
│ Not Installed │ Kind                                                 │ kind                     │  4.5 MiB │
│ Not Installed │ Kustomize                                            │ kustomize                │ 25.9 MiB │
│ Not Installed │ Minikube                                             │ minikube                 │ 22.9 MiB │
│ Not Installed │ Nomos CLI                                            │ nomos                    │ 17.8 MiB │
│ Not Installed │ Skaffold                                             │ skaffold                 │ 14.8 MiB │
│ Not Installed │ anthos-auth                                          │ anthos-auth              │ 16.3 MiB │
│ Not Installed │ config-connector                                     │ config-connector         │ 41.5 MiB │
│ Not Installed │ gcloud Alpha Commands                                │ alpha                    │  < 1 MiB │
│ Not Installed │ gcloud Beta Commands                                 │ beta                     │  < 1 MiB │
│ Not Installed │ gcloud app Java Extensions                           │ app-engine-java          │ 59.4 MiB │
│ Not Installed │ gcloud app Python Extensions                         │ app-engine-python        │  6.1 MiB │
│ Not Installed │ gcloud app Python Extensions (Extra Libraries)       │ app-engine-python-extras │ 27.1 MiB │
│ Not Installed │ kpt                                                  │ kpt                      │ 11.4 MiB │
│ Not Installed │ kubectl                                              │ kubectl                  │  < 1 MiB │
│ Not Installed │ pkg                                                  │ pkg                      │          │
│ Installed     │ BigQuery Command Line Tool                           │ bq                       │  < 1 MiB │
│ Installed     │ Cloud SDK Core Libraries                             │ core                     │ 15.5 MiB │
│ Installed     │ Cloud Storage Command Line Tool                      │ gsutil                   │  3.5 MiB │
└───────────────┴──────────────────────────────────────────────────────┴──────────────────────────┴──────────┘
To install or remove components at your current SDK version [319.0.0], run:
  $ gcloud components install COMPONENT_ID
  $ gcloud components remove COMPONENT_ID

To update your SDK installation to the latest version [319.0.0], run:
  $ gcloud components update


Modify profile to update your $PATH and enable shell command 
completion?

Do you want to continue (Y/n)?  

The Google Cloud SDK installer will now prompt you to update an rc 
file to bring the Google Cloud CLIs into your environment.

Enter a path to an rc file to update, or leave blank to use 
[/home/k8smaster/.bashrc]:  
Backing up [/home/k8smaster/.bashrc] to [/home/k8smaster/.bashrc.backup].
[/home/k8smaster/.bashrc] has been updated.

==> Start a new shell for the changes to take effect.


For more information on how to get started, please visit:
  https://cloud.google.com/sdk/docs/quickstarts

$
```

