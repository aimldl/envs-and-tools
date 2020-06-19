#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon May 14 14:41:53 2018

@author: taehwan
"""

import os
import numpy as np

from simple_vad import VAD, UsingWebrtcvad, Progress
from scipy.io import wavfile
from time import time

transform_vad = True
transform_spectrogram = True
webrtcvad = True
normalization = True
if normalization:
  print('Data is normalized with min-max normalization')
if transform_vad and webrtcvad:
  print('Voice Activity Detection with webrtcvad library')
else:
  print('Voice Activity Detection with simple features')
if transform_spectrogram:
  print('Change wave files to spectrogram')

name = 'train'
language = 'spanish'
duration = 0.01 #10ms

wavefile_dir = os.path.join(name, 'wavefiles', language)
spectro_dir = os.path.join(name, 'spectrogram', language)
spectro_vad_dir = os.path.join(name, 'spectrogram_vad', language)
vad_wavefile_dir = os.path.join(name, 'wavefiles_vad', language)
vad_norm_wavefile_dir = os.path.join(name, 'wavefiles_norm_vad', language)
if not os.path.exists(spectro_dir):
  os.makedirs(spectro_dir)
if not os.path.exists(spectro_vad_dir):
  os.makedirs(spectro_vad_dir)
if not os.path.exists(vad_wavefile_dir):
  os.makedirs(vad_wavefile_dir)
if not os.path.exists(vad_norm_wavefile_dir):
  os.makedirs(vad_norm_wavefile_dir)
  
file_lists = os.listdir(wavefile_dir)

vad = VAD() if not webrtcvad else UsingWebrtcvad()
progress = Progress(len(file_lists))
for i in range(len(file_lists)):
  current_t =  time()
  wave_full_path = os.path.join(wavefile_dir, file_lists[i])
  fs, data = wavfile.read(wave_full_path)
  assert fs == 16000 #sampling frequency == 16kHz
  
  spectro_full_path = os.path.join(spectro_dir, os.path.splitext(file_lists[i])[0] + '.png')
  spectro_vad_full_path = os.path.join(spectro_vad_dir, os.path.splitext(file_lists[i])[0] + '.png')
  
  if normalization: 
    _data = np.int64(data)
    data = (_data - np.min(_data)) / (np.max(_data) - np.min(_data))
    vad_wave_full_path = os.path.join(vad_norm_wavefile_dir, file_lists[i])
  else:
    vad_wave_full_path = os.path.join(vad_wavefile_dir, file_lists[i])
  if transform_vad and webrtcvad:
    vad(data, fs, duration, vad_wave_full_path) #len(data) == 88000 만 가능
  else:
    vad(wave_full_path, vad_wave_full_path)
    
  if transform_spectrogram:
    os.system('sox %s -n spectrogram -o %s -r -x 100 -y 100' %(vad_wave_full_path, spectro_vad_full_path))
  progress(i, time()-current_t)
print('')
print('preprocessing is finised')

if webrtcvad:
  error_files = vad.error_file 

new_data = []
for line in error_files:
  new_data.append(line+'\n')
with open(os.path.join(name,'%s_low_energy_list.txt' %language), 'w') as f:
  f.writelines(new_data)



