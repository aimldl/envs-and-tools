* Rev.1: 2020-06-19 (Fri)
* Draft: ?

# Jupyter

Developers describe Jupyter as "Multi-language interactive computing environments". The Jupyter Notebook is a web-based interactive computing platform. 

[Jupyter vs Apache Zeppelin]([https://stackshare.io/stackups/jupyter-vs-zeppelin#:~:text=The%20Jupyter%20Notebook%20is%20a,that%20enables%20interactive%20data%20analytics%22.](https://stackshare.io/stackups/jupyter-vs-zeppelin#:~:text=The Jupyter Notebook is a,that enables interactive data analytics".))



README.md

There're lots of existing kernels under directory ".local/share/jupyter/runtime".
```bash
~$ cd
~$ cd .local/share/jupyter/runtime
~/.local/share/jupyter/runtime$ ls
kernel-03f462a0-c666-46c4-8f08-7c2d7780059c.json  kernel-e36af02e-abb4-4a62-8992-d2c0b78cf9f3.json
  ...
kernel-dbbceba7-a193-4ef6-857b-08fce2f85070.json
~/.local/share/jupyter/runtime$
```
After deleting all of them, Spyder is launched again and a new configuration file is created.
```bash
~/.local/share/jupyter/runtime$ ls
kernel-354ca5119753.json
~/.local/share/jupyter/runtime$ 
```
