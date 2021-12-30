* Draft: 2021-12-15 (Wed)

# How to Install Anaconda on macOS

Source: [Installing on macOS](https://docs.anaconda.com/anaconda/install/mac-os/)

## Prerequisite
Install Python3
```bash
$ python --version
Python 2.7.18
$
```

## Download Anaconda Installer for macOS
* Open a web browser and go to [Anaconda macOS installer](https://www.anaconda.com/downloads#macos).
* Scroll down to Anaconda Installers
<img src='images/anaconda_installer_macos_64bit_command_line_installer.png'>

Click `64-Bit Command Line Installer` and download will start.
<img src='images/anaconda_installer_macos_64bit_command_line_installer-downloading.png'>

Open a terminal and check if the downloaded installer exists. Ensure the file extension is `.sh`.
```bash
$ ls ~/Downloads/Ana*
/Users/aimldl/Downloads/Anaconda3-2021.11-MacOSX-x86_64.sh
$
```

Note `64-Bit Graphical Installer` has `.pkg` as the file extension.
```bash
$ ls ~/Downloads/Ana*
/Users/thekim/Downloads/Anaconda3-2021.11-MacOSX-x86_64.pkg
$
```

## [Verify data integrity with SHA-256](https://docs.anaconda.com/anaconda/install/hashes/).
```bash
$ shasum -a 256 ~/Downloads/Anaconda3-2021.11-MacOSX-x86_64.sh 
6a9217d1a08c599f860045d56ef64fc6c3e3112b55cc97f3d07c573d7bbcdb58  /Users/thekim/Downloads/Anaconda3-2021.11-MacOSX-x86_64.sh
$
```

## Install Anaconda
```bash
$ bash ~/Downloads/Anaconda3-2021.11-MacOSX-x86_64.sh
```
In the message, press ENTER

```bash
Welcome to Anaconda3 2021.11

In order to continue the installation process, please review the license
agreement.
Please, press ENTER to continue
>>>
```

Enter `yes`
```bash
  ...
Do you accept the license terms? [yes|no]
[no] >>> 
```
Press ENTER
```bash
Anaconda3 will now be installed into this location:
/Users/thekim/anaconda3

  - Press ENTER to confirm the location
  - Press CTRL-C to abort the installation
  - Or specify a different location below

[/Users/thekim/anaconda3] >>> 
```

## Dealing with the error by Santa
This part applies only to

`python3.9`.

Clicking the `Ignore` button doesn't remove the error. Click "Upvote" button
Santa blocks the execution. Reinstalling with the same command fails with the following error.
```bash
  ...
[/Users/thekim/anaconda3] >>> 
ERROR: File or directory already exists: '/Users/thekim/anaconda3'
If you want to update an existing installation, use the -u option.
$
```

I've deleted the directory '/Users/thekim/anaconda3' and ran the installation command.

```bash
Santa

This application has been blocked from executing
because its trustworthiness cannot be determined.

Path:       /Users/thekim/anaconda3/conda.exe
Identifier: 8d9538da8e406dcea76ef2a1b3e2eb63c04c1f3c979bf6153ec4a6b02e522b37
Parent:     bash (90385)

More info:
https://upvote. (...)

/Users/thekim/Downloads/Anaconda3-2021.11-MacOSX-x86_64.sh: line 406: 90551 Exit 141                { dd if="$THIS_PATH" bs=1 skip=15687381 count=8491 2> /dev/null; dd if="$THIS_PATH" bs=16384 skip=958 count=31578 2> /dev/null; dd if="$THIS_PATH" bs=1 skip=533069824 count=4623 2> /dev/null; }
     90552 Killed: 9               | "$CONDA_EXEC" constructor --extract-tar --prefix "$PREFIX"
/Users/thekim/Downloads/Anaconda3-2021.11-MacOSX-x86_64.sh: line 408: 90559 Killed: 9               "$CONDA_EXEC" constructor --prefix "$PREFIX" --extract-conda-pkgs
$
```
Go to the URL under `More info:`, that is `https://upvote. (...)` and click the `VOTED TO APPROVE` button.

`What happens next?
You are now able to run this application!
You may need to wait up to 10 minutes for your machine to sync.
Alternatively, (...)
`
1 more vote needed to approve this application.

To get the necessary votes, you can...
