#####  aimldl/computing_environments/docker/how_to/use jupyter notebook.md
* Draft: 2020-0317 (Tue)
# How to Use Jupyter Notebook on Docker

## Use "-p 8080:8080" and "--ip=0.0.0.0 --port=8080"
```bash
$ docker run -it -p 8080:8080 ...
(surprise) user@3d628cbdcff4:~$ jupyter notebook --ip=0.0.0.0 --port=8080
  ...
http://(3d628cbdcff4 or 127.0.0.1):8080/?token=6cc8bd243c258b50b27d013e66ee14837c7638a2aecf6442
```
Copy and paste "http://127.0.0.1:8080/?token=6cc8bd243c258b50b27d013e66ee14837c7638a2aecf6442" on a web browser.

<img src="images/docker-container-jupyter_notebook-webbrowser.png">

```bash
$ docker run -it -p 8080:8080 --name surprise baseimage_surprise_python3.7.6_conda_4.8.2_ubuntu18.04.4 bash
(surprise) user@3d628cbdcff4:~$ jupyter notebook --ip=0.0.0.0 --port=8080
[I 15:34:22.182 NotebookApp] Serving notebooks from local directory: /home/user
[I 15:34:22.182 NotebookApp] The Jupyter Notebook is running at:
[I 15:34:22.182 NotebookApp] http://(3d628cbdcff4 or 127.0.0.1):8080/?token=6cc8bd243c258b50b27d013e66ee14837c7638a2aecf6442
[I 15:34:22.182 NotebookApp] Use Control-C to stop this server and shut down all kernels (twice to skip confirmation).
[W 15:34:22.182 NotebookApp] No web browser found: could not locate runnable browser.
[C 15:34:22.183 NotebookApp]

    Copy/paste this URL into your browser when you connect for the first time,
    to login with a token:
        http://(3d628cbdcff4 or 127.0.0.1):8080/?token=6cc8bd243c258b50b27d013e66ee14837c7638a2aecf6442
[I 15:34:51.916 NotebookApp] 302 GET /?token=6cc8bd243c258b50b27d013e66ee14837c7638a2aecf6442 (172.17.0.1) 0.47ms
```

### Example: aimldl/kaggle_telco_customer_churn:ver0.1
```bash
$ docker run -it -p 8080:8080 --name telco aimldl/kaggle_telco_customer_churn:ver0.1 bash
(base) user@d66b3d6118b2:~$ jupyter notebook --ip=0.0.0.0 --port=8080
[I 14:56:50.099 NotebookApp] JupyterLab extension loaded from /home/user/anaconda3/lib/python3.7/site-packages/jupyterlab
[I 14:56:50.099 NotebookApp] JupyterLab application directory is /home/user/anaconda3/share/jupyter/lab
[I 14:56:50.104 NotebookApp] Serving notebooks from local directory: /home/user
[I 14:56:50.104 NotebookApp] The Jupyter Notebook is running at:
[I 14:56:50.104 NotebookApp] http://d66b3d6118b2:8080/?token=6091c3a9fed303f27cc59d18e42409bc511b3b8fdb4399b7
[I 14:56:50.104 NotebookApp]  or http://127.0.0.1:8080/?token=6091c3a9fed303f27cc59d18e42409bc511b3b8fdb4399b7
[I 14:56:50.104 NotebookApp] Use Control-C to stop this server and shut down all kernels (twice to skip confirmation).
[W 14:56:50.149 NotebookApp] No web browser found: could not locate runnable browser.
[C 14:56:50.150 NotebookApp]

    To access the notebook, open this file in a browser:
        file:///home/user/.local/share/jupyter/runtime/nbserver-25-open.html
    Or copy and paste one of these URLs:
        http://d66b3d6118b2:8080/?token=6091c3a9fed303f27cc59d18e42409bc511b3b8fdb4399b7
     or http://127.0.0.1:8080/?token=6091c3a9fed303f27cc59d18e42409bc511b3b8fdb4399b7
```

## Troubleshooting

```bash
(surprise) user@3d628cbdcff4:~$ jupyter notebook
[I 15:34:02.028 NotebookApp] Writing notebook server cookie secret to /home/user/.local/share/jupyter/runtime/notebook_cookie_secret
Traceback (most recent call last):
  File "/usr/local/bin/jupyter-notebook", line 11, in <module>
    sys.exit(main())
  File "/usr/local/lib/python3.6/dist-packages/jupyter_core/application.py", line 266, in launch_instance
    return super(JupyterApp, cls).launch_instance(argv=argv, **kwargs)
  File "/usr/local/lib/python3.6/dist-packages/traitlets/config/application.py", line 657, in launch_instance
    app.initialize(argv)
  File "<decorator-gen-7>", line 2, in initialize
  File "/usr/local/lib/python3.6/dist-packages/traitlets/config/application.py", line 87, in catch_config_error
    return method(app, *args, **kwargs)
  File "/usr/local/lib/python3.6/dist-packages/notebook/notebookapp.py", line 1602, in initialize
    self.init_webapp()
  File "/usr/local/lib/python3.6/dist-packages/notebook/notebookapp.py", line 1381, in init_webapp
    self.http_server.listen(port, self.ip)
  File "/usr/local/lib/python3.6/dist-packages/tornado/tcpserver.py", line 143, in listen
    sockets = bind_sockets(port, address=address)
  File "/usr/local/lib/python3.6/dist-packages/tornado/netutil.py", line 168, in bind_sockets
    sock.bind(sockaddr)
OSError: [Errno 99] Cannot assign requested address
(surprise) user@3d628cbdcff4:~$ 
```
