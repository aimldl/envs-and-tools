##### cron.md
* Draft: 2020-03-01 (Sun)

# cron

[CronHowto](https://help.ubuntu.com/community/CronHowto)

* crontab - maintain crontab files for individual users (Vixie Cron)

## Install on Ubuntu
```bash
$ sudo apt-get install gnome-schedule
```

## crontab synopsis
For details, run "$ man crontab". 
```bash
crontab [ -u user ] file
crontab [ -u user ] [ -i ] { -e | -l | -r }
```
#### Edit the crontab file.
```bash
$ crontab -e
```
#### 
```bash
$ crontab -l
```

## How to Verify
[Simple cron example](https://www.saltycrane.com/blog/2008/09/simple-cron-example/)
```bash
$ crontab -e
```
```bash
* * * * * /bin/date >> /tmp/cron_output
```
```bash
$ tail -f /tmp/cron_output
Sun Mar  1 10:59:01 UTC 2020
Sun Mar  1 11:00:01 UTC 2020
  ...
Sun Mar  1 11:26:01 UTC 2020
```
When the command is changed, the output is changed.
$ tail -f /tmp/cron_output
Sun Mar  1 10:59:01 UTC 2020
Sun Mar  1 11:00:01 UTC 2020
  ...
Sun Mar  1 11:26:01 UTC 2020
Hi, there
Hi, there
  ...
```

### Check the Status
Verify if cron is running.
```bash
$ service cron status
```
cron is for Ubuntu. For other Linux flavors, use crond instead of cron.
```bash
$ service crond status
```

### Stop the cron service
```bash
service cron stop
```

### Start the cron service
```bash
service cron start
```

## crontab -e
```bash
# Every year, May 6, 07:08AM
#08 07 06 05 * /usr/bin/echo "Hi, I'm saying this every year at this time. :)"
```
