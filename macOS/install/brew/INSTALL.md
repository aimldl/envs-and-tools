* Draft: 2021-12-15 (Wed)

# How to Install Homebrew on macOS
Google search: mac how to install brew
* [Installing Homebrew on a Mac](https://treehouse.github.io/installation-guides/mac/homebrew) > Installation Steps

## Bash
It takes less than a minute to install.

### Command to install `brew` with Bash
```bash
$ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

#### Messages
```bash
==> Checking for `sudo` access (which may request your password)...
Password: 
==> This script will install:
/usr/local/bin/brew
/usr/local/share/doc/homebrew
/usr/local/share/man/man1/brew.1
/usr/local/share/zsh/site-functions/_brew
/usr/local/etc/bash_completion.d/brew
/usr/local/Homebrew

Press RETURN to continue or any other key to abort:
```

```bash
  ...
==> Installation successful!

==> Homebrew has enabled anonymous aggregate formulae and cask analytics.
Read the analytics documentation (and how to opt-out) here:
  https://docs.brew.sh/Analytics
No analytics data has been sent yet (nor will any be during this install run).

==> Homebrew is run entirely by unpaid volunteers. Please consider donating:
  https://github.com/Homebrew/brew#donations

==> Next steps:
- Run brew help to get started
- Further documentation:
    https://docs.brew.sh
$
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

### Command to install `brew` with Ruby

```bash
$ ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```
#### Messages
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
  ...
==> Installation successful!

==> Homebrew has enabled anonymous aggregate formulae and cask analytics.
Read the analytics documentation (and how to opt-out) here:
  https://docs.brew.sh/Analytics
No analytics data has been sent yet (nor will any be during this install run).

==> Homebrew is run entirely by unpaid volunteers. Please consider donating:
  https://github.com/Homebrew/brew#donations

==> Next steps:
- Run brew help to get started
- Further documentation:
    https://docs.brew.sh
$
```
### Verify the installation
Unlike the installation success message above, a `brew` command shows an error message.
```bash
$ brew help
shell-init: error retrieving current directory: getcwd: cannot access parent directories: Operation not permitted
Error: The current working directory doesn't exist, cannot proceed.
$
```
```bash
$ sudo brew help
Password: 
shell-init: error retrieving current directory: getcwd: cannot access parent directories: Operation not permitted
Error: The current working directory doesn't exist, cannot proceed.
$ 
```

### Error
Both Bash & Ruby commands failed.
