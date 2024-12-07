* Draft: 2021-01-09 (Sat)

# Printing everything except the first field with awk

Google search: awk print except the first column

[Printing everything except the first field with awk](https://stackoverflow.com/questions/4198138/printing-everything-except-the-first-field-with-awk)

> Great. Got rid of the leading space with sed :
>
> `awk {'first = $1; $1=""; print $0'}|sed 's/^ //g'`

For a usage example, refer to [../how_to/get_history_of_commands_smartly.md](../how_to/get_history_of_commands_smartly.md).

