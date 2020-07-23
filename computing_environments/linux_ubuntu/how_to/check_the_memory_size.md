* Draft: 2020-07-23
# Checking the Memory Size on Ubuntu Linux 

> Google search: ubuntu linux how to check memory size
> [5 Ways to Check Available Memory in Ubuntu 20.04](https://vitux.com/5-ways-to-check-available-memory-in-ubuntu/)
> 
> * The free command
> * The vmstat command
> * The /proc/meminfo command
> * The top command
> * The htop command

The memory is in Mega byte.
```bash
$ free -m
              total        used        free      shared  buff/cache   available
Mem:          32071        3459       23968         272        4644       28039
Swap:             0           0           0
$
```
So 32071 MB is equal to 32.071 GB.
