* Updated: 2024-10-04 (Fri)
* Created: 2024-10-04 (Fri)

# Google Cloud > Cloud SDK

# Install
Source: Google Cloud > Cloud SDK > Doc. > Guides > [Install the gcloud CLI](https://cloud.google.com/sdk/docs/install#deb)

```bash
# Before you begin
sudo apt-get update
sudo apt-get install apt-transport-https ca-certificates gnupg curl

# Installation
curl https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo gpg --dearmor -o /usr/share/keyrings/cloud.google.gpg
echo "deb [signed-by=/usr/share/keyrings/cloud.google.gpg] https://packages.cloud.google.com/apt cloud-sdk main" | sudo tee -a /etc/apt/sources.list.d/google-cloud-sdk.list
sudo apt-get update && sudo apt-get install google-cloud-cli

# Get started with
gcloud init
```

# Get started with `gcloud init`
The full message
```bash
Welcome! This command will take you through the configuration of gcloud.

Your current configuration has been set to: [default]

You can skip diagnostics next time by using the following flag:
  gcloud init --skip-diagnostics

Network diagnostic detects and fixes local network connection issues.
Checking network connection...done.                                                       
Reachability Check passed.
Network diagnostic passed (1/1 checks passed).

You must sign in to continue. Would you like to sign in (Y/n)?  y

Your browser has been opened to visit:

    https://accounts.google.com/o/oauth2/auth?response_type=code&client_id=...&code_challenge_method=S256

You are signed in as: [your@account_name].

This account has a lot of projects! Listing them all can take a while.
 [1] Enter a project ID
 [2] Create a new project
 [3] List projects
Please enter your numeric choice:
```

```bash
Please enter your numeric choice: 1
```
```bash
Enter project ID you would like to use:  
```
