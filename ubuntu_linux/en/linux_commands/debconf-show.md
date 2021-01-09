* Draft: 2020-05-28 (Thu)

# debconf-show

## Problem

To install Java, the terms and conditions must be agreed which can be automated by `deb-conf-set-selections`. The problem is I don't know what variables should be used.

## Hint

Google search: debconf-set-selections

[How to find out the variable names for debconf-set-selections?](https://unix.stackexchange.com/questions/457388/how-to-find-out-the-variable-names-for-debconf-set-selections)

> Q: Let's say I want to install `mysql` from a script without being asked any configuration questions like what root password I want to set by `apt`. I would then preset the `debconf` variables:
>
> ```
> echo mysql-server-5.5 mysql-server/root_password password xyzzy | debconf-set-selections
> echo mysql-server-5.5 mysql-server/root_password_again password xyzzy | debconf-set-selections
> ```
>
> * How did the guy find out the variable names?
> * How did he knew that he had to set `mysql-server-5.5 mysql-server/root_password password` and `mysql-server-5.5 mysql-server/root_password_again` respectively?

> A: You can get the variables for a specific *installed* package using 
>
> ​     `debconf-show packagename`
>
> ```bash
> $ sudo debconf-show mysql-server-5.7
> * mysql-server/root_password: (password omitted)
> * mysql-server/root_password_again: (password omitted)
>   mysql-server-5.7/start_on_boot: true
>   mysql-server/no_upgrade_when_using_ndb:
>   mysql-server/password_mismatch:
>   mysql-server-5.7/really_downgrade: false
>   mysql-server-5.7/nis_warning:
>   mysql-server-5.7/postrm_remove_databases: false
>   mysql-server-5.7/installation_freeze_mode_active:
> ```

or

> You can get a list of all the installed packages that have variables in the database using 
>        `debconf-show --listowners`,
> so if you're not sure what the package name is you could do something like:
>
> ```bash
> # debconf-show --listowners | grep mysql | xargs debconf-show
> * mysql-server/root_password: (password omitted)
> * mysql-server/root_password_again: (password omitted)
>   mysql-server-5.7/postrm_remove_databases: false
>   mysql-server-5.7/nis_warning:
>   mysql-server-5.7/installation_freeze_mode_active:
>   mysql-server/password_mismatch:
>   mysql-server-5.7/start_on_boot: true
>   mysql-server/no_upgrade_when_using_ndb:
>   mysql-server-5.7/really_downgrade: false
> #
> ```

## Solution

```bash
$ sudo debconf-show oracle-java14-installer
  shared/error-oracle-license-v1-2:
  oracle-java14-installer/local:
* shared/present-oracle-license-v1-2:
  oracle-java14-installer/not_exist:
* shared/accepted-oracle-license-v1-2: true
$
```

