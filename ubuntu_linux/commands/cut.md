* Draft: 2021-05-12 (Wed)

# cut

A column in the standard output can be "cut" with the `cut` command.

Instead of 

```bash
$ awk '{print $1;}' filename.txt
# or
$ cat filename.txt | awk '{print $1;}'
```

you may use

```bash
$ cat filename.txt | cut -d " " -f 1
```

I prefer `awk` to `cut` because `awk` is more flexible and has more functionalities than `cut`. Transforming a simple command to more sophisticated one is possible with `awk`.

At any rate, `cut` can be useful for very simple commands like fetching the first column from text lines.

## Kubeflow

```bash
$ kubectl get pods -n knative-sercing | cut -d " " -f 1 | grep -v "NAME"
```

shows the list of `knative-serving` without the first line which includes `NAME`.

## References

[cut command in Linux with examples](https://www.geeksforgeeks.org/cut-command-linux-examples/), GeeksforGeeks

> Syntax:
>
>   $ cut OPTION... [FILE]...
>
> Example text file
>
> ```bash
> $ cat state.txt
> Andhra Pradesh
> Arunachal Pradesh
> Assam
> Bihar
> Chhattisgarh
> $
> ```
>
> If -d option is used then it considered space as a field separator or delimiter:
>
> ```bash
> $ cut -d " " -f 1 state.txt
> Andhra
> Arunachal
> Assam
> Bihar
> Chhattisgarh
> $
> ```
>
> Options
>
> 1. -b (byte)
>
> * List without ranges
>
>   ```bash
>   $ cut -b 1,2,3 state.txt
>   And
>   Aru
>   Ass
>   Bih
>   Chh
>   $
>   ```
>
> * List with ranges
>
>   ```bash
>   $ cut -b 1-3,5-7 state.txt
>   Andra
>   Aruach
>   Assm
>   Bihr
>   Chhtti
>   $
>   ```

> In this, 1- indicate from 1st byte to end byte of a line
>
> ```bash
> $ cut -b 1- state.txt
> Andhra Pradesh
> Arunachal Pradesh
> Assam
> Bihar
> Chhattisgarh
> $
> ```
>
> In this, -3 indicate from 1st byte to 3rd byte of a line
>
> ```bash
> $ cut -b -3 state.txt
> And
> Aru
> Ass
> Bih
> Chh
> $
> ```
>
> For more content, refer to [cut command in Linux with examples](https://www.geeksforgeeks.org/cut-command-linux-examples/), GeeksforGeeks.