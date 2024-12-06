* Draft: 2021-06-11 (Fri)

# su 

`su` stands for "substitute user" or "switch user".

## Syntax

### `$ su [user_name]`

```bash
$ su [user_name]
```

### `$ su`

`$ su` =   `$ su root`

* Switch user to root
  * `$ su` logs in as root by default.
  * Equivalently, `$ su root`. 
* The working directory remains identical.

### `$ su -`

`$ su -` =   `$ su root` + `$ cd /` 

​               = ` $ su -l` or `$ su --login`

* Switch user to root and go to its home directory `/`

## References

* [Learn Difference Between “su” and “su -” Commands in Linux](https://www.tecmint.com/difference-between-su-and-su-commands-in-linux/), 2018-02-05, TecMint
* [[Ubuntu/Linux] su와 su - 차이점을 정리해보기](https://storycompiler.tistory.com/44), 2015-06-10, [아프니까 개발자다]