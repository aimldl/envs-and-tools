##### run a script to launch jupyter notebook.md
* Draft: 2020-0324 (Tue)

# Run a Simple Script to Launch Jupyter Notebook in a Docker Container

[TODO] Organize and summarize

Add the following lines in .bashrc
```bash
(base) user@df4703dbba5f:~/bin$ cd      
(base) user@df4703dbba5f:~$ nano .bashrc
```

> alias j="run_jupyter_notebook"
export PATH="/home/user/bin:$PATH"

```bash

#!/bin/bash
#  run_jupyter_notebook
#    * Draft: 2020-0324 (Tue)
#    runs jupyter notebook inside a Docker container.
#
#    The Docker container should be started with the "-p 8080:8080" option.
#      $ docker run -it -p 8080:8080 ...
#    For example,
#      $ docker run -it -p 8080:8080 --name conda aimldl/baseimage_python3.7.6_conda_4.8.2_ubuntu18.04.4 bash
#
#    Open and edit the .bashrc file.
#      (base) user@df4703dbba5f:~/bin$ cd      
#      (base) user@df4703dbba5f:~$ nano .bashrc
#    Add the following lines in .bashrc.
#     alias j="run_jupyter_notebook"
#     export PATH="/home/user/bin:$PATH"
#    Restart th Bash shell.
#      (base) user@df4703dbba5f:~$ bash
#      (base) user@df4703dbba5f:~$ 
#    Now a Jupyter Notebook can be launched simply by typing in:
#      (base) user@df4703dbba5f:~$ j
#    Anywhere because /home/use/bin is added to the PATH.

jupyter notebook --ip=0.0.0.0 --port=8080
```


```bash

(base) user@df4703dbba5f:~/bin$ bash
(base) user@df4703dbba5f:~/bin$ j
[I 08:22:55.143 NotebookApp] Writing notebook server cookie secret to /home/user/.local/share/jupyter/runtime/notebook_cookie_secret
[I 08:22:55.449 NotebookApp] JupyterLab extension loaded from /home/user/anaconda3/lib/python3.7/site-packages/jupyterlab
[I 08:22:55.449 NotebookApp] JupyterLab application directory is /home/user/anaconda3/share/jupyter/lab
[I 08:22:55.453 NotebookApp] Serving notebooks from local directory: /home/user/bin
[I 08:22:55.453 NotebookApp] The Jupyter Notebook is running at:
[I 08:22:55.453 NotebookApp] http://df4703dbba5f:8080/?token=d53c242623ff1e5f1685507a2fa0ce73ce9b9a66e3644f40
[I 08:22:55.453 NotebookApp]  or http://127.0.0.1:8080/?token=d53c242623ff1e5f1685507a2fa0ce73ce9b9a66e3644f40
[I 08:22:55.453 NotebookApp] Use Control-C to stop this server and shut down all kernels (twice to skip confirmation).
[W 08:22:55.457 NotebookApp] No web browser found: could not locate runnable browser.
[C 08:22:55.457 NotebookApp] 
    
    To access the notebook, open this file in a browser:
        file:///home/user/.local/share/jupyter/runtime/nbserver-54-open.html
    Or copy and paste one of these URLs:
        http://df4703dbba5f:8080/?token=d53c242623ff1e5f1685507a2fa0ce73ce9b9a66e3644f40
     or http://127.0.0.1:8080/?token=d53c242623ff1e5f1685507a2fa0ce73ce9b9a66e3644f40

```
