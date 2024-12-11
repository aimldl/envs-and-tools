* Draft: 2021-07-15 (Thu)

18 files and the total size is 3.9MB.

TODO

```bash
$ ls -p | grep -v / | xargs -I {} convert {} -quality 60 {}
```

didn't compress the file size



```bash
$ ls -p | grep -v / | xargs -I {} convert {} -quality 60 output/{}
```

spits errors

