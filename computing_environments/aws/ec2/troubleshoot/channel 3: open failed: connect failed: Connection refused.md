
Connection fails right after ssh login.
```bash
   ...
0 packages can be updated.
0 updates are security updates.


Last login: Wed Jan 29 04:31:54 2020 from w.x.y.z
(base) ubuntu@ip-10-0-2-222:~$ channel 3: open failed: connect failed: Connection refused
  ...
channel 3: open failed: connect failed: Connection refused
```


Connection to Spyder IDE is refused.
```bash
(pytorch) ubuntu@ec2-seoul-aimldl:~/wav2vec$ QXcbConnection: XCB error: 3 (BadWindow), sequence: 1087, resource id: 12787425, major code: 40 (TranslateCoords), minor code: 0
channel 6: open failed: connect failed: Connection refused
  ...
channel 3: open failed: connect failed: Connection refused
(pytorch) ubuntu@ec2-seoul-aimldl:~/wav2vec$  channel 3: open failed: connect failed: Connection refused
  ...
channel 3: open failed: connect failed: Connection refused
```

or Jupyter Notebook's connection is broken.
```bash
  ...
[I 02:30:00.130 NotebookApp] Saving file at /notebooks/references/07-short_tutorial-torchaudio_load.ipynb
packet_write_wait: Connection to w.x.y.z port 22: Broken pipe
(base) aimldl@GPU-Desktop:~/aws_keys$ ^C
```
