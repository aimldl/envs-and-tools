* Rev.1: 2022-04-13 (Wed)
* Draft: 2021-05-13 (Thu)

# How to Print History Command Without Line Numbers
> Google search: linux output command without index
>
> * [Linux Print History Command Without Line Numbers](https://www.poftut.com/linux-history-command-without-line-numbers/), 2016-09-15, İsmail Baydan

> Option 2. Use the `awk` command
>
> ```bash
> $ history | awk '{$1=""; print substr($0,2)}'
> ```

For the rest of options, refer to tools/__linux_commands/[history.md](https://github.com/aimldl/tools/blob/main/__linux_commands/history.md)
