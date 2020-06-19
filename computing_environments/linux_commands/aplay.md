* Rev.1: 2020-06-11 (Thu)
* Draft: 2018-11-29 (Thu)
# aplay

```bash
$ aplay file_name.wav
```

```bash
$ aplay LDC2006S42.wav 
Playing WAVE 'LDC2006S42.wav' : Signed 16 bit Little Endian, Rate 16000 Hz, Mono
^CAborted by signal Interrupt...
aplay: pcm_write:1940: write error: Interrupted system call
$
```

```bash
$ aplay english.au
Playing raw data 'english.au' : Unsigned 8 bit, Rate 8000 Hz, Mono
^CAborted by signal Interrupt...
aplay: pcm_write:1940: write error: Interrupted system call
$
```
