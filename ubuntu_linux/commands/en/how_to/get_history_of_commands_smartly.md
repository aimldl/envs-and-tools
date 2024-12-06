





```bash
$ history | awk {'first = $1; $1=""; print $0'}|sed 's/^ //g' | sort | uniq -c | sort -r | more
     88 ls
     36 bundle exec jekyll serve
     23 ./batch_git_push
     21 cd ..
  ...
      1 ./install_ubuntu_packages
      1 ./batch_git_clone
$
```

Google search: awk print except the first column

[Printing everything except the first field with awk](https://stackoverflow.com/questions/4198138/printing-everything-except-the-first-field-with-awk)

> Great. Got rid of the leading space with sed :
>
> `awk {'first = $1; $1=""; print $0'}|sed 's/^ //g'`