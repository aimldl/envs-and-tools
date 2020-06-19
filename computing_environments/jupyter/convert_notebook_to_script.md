##### convert_notebook_to_script.md

Google search: convert_notebook_to_script.py

[How do I convert a IPython Notebook into a Python file via commandline?](https://stackoverflow.com/questions/17077494/how-do-i-convert-a-ipython-notebook-into-a-python-file-via-commandline)
```bash
If you don't want to output a Python script every time you save, or you don't want to restart the IPython kernel:
On the command line, you can use nbconvert:
$ jupyter nbconvert --to script [YOUR_NOTEBOOK].ipynb
```

ls
```bash
$ ls
Continuous_Control.ipynb
$ jupyter nbconvert --to script Continuous_Control.ipynb
[NbConvertApp] Converting notebook Continuous_Control.ipynb to script
[NbConvertApp] Writing 10294 bytes to Continuous_Control.py
$ ls
Continuous_Control.ipynb  Continuous_Control.py
$
```
