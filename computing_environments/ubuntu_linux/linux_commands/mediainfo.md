* Rev.1: 2020-06-11 (Thu)
* Draft: 2018-11-29 (Thu)

# mediainfo
## Usage
```bash
$ mediainfo file_name.wav
```
## 
```bash
$ mediainfo check_me_out-Amy.mp3 
General
Complete name                            : check_me_out-Amy.mp3
Format                                   : MPEG Audio
File size                                : 5.55 KiB
Duration                                 : 940 ms
Overall bit rate mode                    : Constant
Overall bit rate                         : 48.0 kb/s
Writing library                          : LAME3.99.5UUUUUUfPzT

Audio
Format                                   : MPEG Audio
Format version                           : Version 2
Format profile                           : Layer 3
Duration                                 : 940 ms
Bit rate mode                            : Constant
Bit rate                                 : 48.0 kb/s
Channel(s)                               : 1 channel
Sampling rate                            : 22.05 kHz
Frame rate                               : 38.281 FPS (576 SPF)
Compression mode                         : Lossy
Stream size                              : 5.51 KiB (99%)
Writing library                          : LAME3.99.5UUUUUUfPzT
```
Notice .pcm file has no media information. This is expected because .pcm file includes no format information.
```bash
$ mediainfo check_me_out-Amy.pcm

$
```
