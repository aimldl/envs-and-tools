* Draft: 2020-10-07 (Wed)

# Installing Sublime Text on Ubuntu Linux

## References

* [Install Sublime Text 3 in Ubuntu 16.04 & Higher The Official Way](https://easycloudsupport.zendesk.com/hc/en-us/articles/360006586972-Install-Sublime-Text-3-in-Ubuntu-16-04-Higher-The-Official-Way)

* [Sublime Text 다운로드 및 설치](http://zeany.net/20)

## Installation

Step 1. Set up the official APT repository

```bash
  $ wget -qO - https://download.sublimetext.com/sublimehq-pub.gpg | sudo apt-key add -
  $ echo "deb https://download.sublimetext.com/ apt/stable/" | sudo tee /etc/apt/sources.list.d/sublime-text.list
  $ sudo apt-get update
```

Step 2. Install Sublime-text

```bash
$ sudo apt-get install -y sublime-text
```

For details, refer to [Install Sublime Text 3 in Ubuntu 16.04 & Higher The Official Way](https://easycloudsupport.zendesk.com/hc/en-us/articles/360006586972-Install-Sublime-Text-3-in-Ubuntu-16-04-Higher-The-Official-Way). 

To launch Sublime Text, run:

```bash
$ subl
```

or go to "Activities" on Ubuntu's GUI and find Sublime Text.

