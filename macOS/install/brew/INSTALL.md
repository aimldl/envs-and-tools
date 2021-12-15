* Draft: 2021-12-15 (Wed)

# How to Install Homebrew on macOS
Google search: mac how to install brew
* [Installing Homebrew on a Mac](https://treehouse.github.io/installation-guides/mac/homebrew) > Installation Steps

## Bash
### Command to install `brew`
```bash
$ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

## Ruby
I don't recommend to use the following ruby command because
1. it took several tens of minutes on my newest macOS Pro and
2. installing Homebrew with Ruby is deprecated as follows:

```
Warning: The Ruby Homebrew installer is now deprecated and has been rewritten in
Bash. Please migrate to the following command:
  /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

### Command to install `brew`

```bash
$ ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```
Enter the root password.
```bash
  ...
==> Checking for `sudo` access (which may request your password)...
Password: 
```
Enter the root password again.
```
==> This script will install:
  ...
==> /usr/bin/sudo /bin/rm -f /tmp/.com.apple.dt.CommandLineTools.installondemand.in-progress
Password: 
```
