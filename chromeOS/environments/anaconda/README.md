* Updated: 2024-09-04 (Wed)
* Created: 2024-09-04 (Wed)

# Anaconda

> Anaconda is a distribution of the Python and R programming languages for scientific computing, that aims to simplify package management and deployment. 
> Supported OS include Windows, Linux, and macOS.

Source: Wikipedia > [Anaconda (Python distribution)](https://en.wikipedia.org/wiki/Anaconda_(Python_distribution))

Chrome OS is indirectly supported via `Crostini` which is [Linux on ChromeOS](https://chromeos.dev/en/linux#:~:text=Linux%20on%20ChromeOS%2C%20sometimes%20called,the%20best%20of%20both%20worlds.).

## Hiccups with Chrome OS to install Anaconda
The default configuration for Linux on Chrome OS resulted in the `Not enough free disk space` error.
```bash
thekim@penguin:~$ bash Anaconda3-2024.06-1-Linux-x86_64.sh 

Welcome to Anaconda3 2024.06-1

In order to continue the installation process, please review the license
agreement.
Please, press ENTER to continue
>>> 

Do you accept the license terms? [yes|no]
>>> 

[/home/thekim/anaconda3] >>> 
ERROR: Not enough free disk space: 7044088 < 7208985
thekim@penguin:~$ 
```
Go to Settings and increase the disk space to fix the error.
