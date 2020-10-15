* Draft: 2020-10-15 (Thu)

# `touch` command

Google search: linux how to change the date of file

[5 Linux Touch Command Examples (How to Change File Timestamp)](https://www.thegeekstuff.com/2012/11/linux-touch-command/)

> ### 4. Explicitly Setting Access and Modification time using -t and -d
>
> Instead of taking the current time-stamp, you can explicitly specify the time using -t and -d options.
>
> The format for specifying -t is [[CC]YY]MMDDhhmm[.SS]
>
> ```
> $ touch -t [[CC]YY]MMDDhhmm[.SS]
> ```
>
> The following explains the above format:
>
> - CC – Specifies the first two digits of the year
> - YY – Specifies the last two digits of the year. If the value of the YY is between 70 and 99, the value of the CC digits is assumed to be 19. If the value of the YY is between 00 and 37, the value of the CC digits is assumed to be 20. It is not possible to set the date beyond January 18, 2038.
> - MM – Specifies the month
> - DD – Specifies the date
> - hh – Specifies the hour
> - mm – Specifies the minute
> - SS – Specifies the seconds
>
> For example:
>
> ```bash
> $ touch -a -m -t 203801181205.09 tgs.txt
> ```

## Changing the timestamp of files

My device Soloshot3's internal clock is errorneous and marked 2020-10-11 as 2018-02-21. About two dozens of files have wrong timestamps.

The `touch` command with the `-t` option has corrected the timestamps easily.

```bash
$ touch -t 202010111000 SS3_T*.*`
```

The full commands to verify the changes are below.

```bash
$ ls -al
  ...
  ... Feb 21  2018 SS3_EDIT_2018_02_21_134845.SESSION
  ... Feb 21  2018 SS3_TRACK_VIDEO_2018_02_21_135144-1.MP4
  ... Feb 21  2018 SS3_TRACK_VIDEO_2018_02_21_135144-1.THM
  ...
  ... Feb 21  2018 SS3_TRACK_VIDEO_2018_02_21_143454-1.THM
$ touch -t 202010111000 SS3_T*.*                      
$ ls -al
total 5662176
  ...
  ... Oct 11 10:00 SS3_EDIT_2018_02_21_134845.SESSION
  ... Oct 11 10:00 SS3_TRACK_VIDEO_2018_02_21_135144-1.MP4
  ... Oct 11 10:00 SS3_TRACK_VIDEO_2018_02_21_135144-1.THM
  ...
  ... Oct 11 10:00 SS3_TRACK_VIDEO_2018_02_21_143454-1.THM
$
```

