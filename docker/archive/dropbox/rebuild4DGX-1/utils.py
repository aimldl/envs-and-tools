#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Apr  9 17:58:13 2018

@author: taehwan
"""
import os
import sys
import numpy as np
import skimage.io

np.random.seed(1234)
  
class Progress():
  def __init__(self):
    self.total_loss = []
  
  def show(self, current_iter, max_iter, epoch, loss, ips, max_bar = 50):
    self.total_loss.append(loss)
    current_iter += 1
    step = round(current_iter/max_iter * max_bar) + 1
    percent = current_iter/max_iter* 100
    bar = '%7.3f%% |' %percent + '>' * step + ' ' * (max_bar - step) + '|'
    sys.stdout.write('\r [%3d] [%4d] %s %.3f (it/s) [loss: %.5f]' %(epoch, current_iter, bar, ips, loss)) # /r이 없으면 한 줄에서 덮어쓰기가 안 됨.
  #  %8.3f -> 8: 전체 글자수(.도 포함), 3: 소수점 자리수
    sys.stdout.flush()
    if current_iter == max_iter:
      sys.stdout.write('\r [%3d] [%4d] %s %.3f (it/s) [avg of loss: %.5f] \n' %(epoch, current_iter, bar, ips, np.sum(self.total_loss)/max_iter))
      sys.stdout.flush()
      self.total_loss = []
    
def copy_weights(weights, pretrained_weights):
  weight_copy_op = []
  for i in range(0, len(weights), 2):
    weight_name = weights[i].name.split('/')[0]
    try:
      weight_copy_op.append([weights[i].assign(pretrained_weights[weight_name][0]), weights[i+1].assign(pretrained_weights[weight_name][1])])
    except:
      print('%s is not in pre-trained network' %weight_name)
      
  return weight_copy_op

class Data():
  def __init__(self, path, language, batch_size, test_rate = 0.2, n_data=20000): # eng: 86536, french: 22330, german: 24020, italian: 10524, spanish: 23408
    self.path=path
    self.languages = language
    self.n_trn = int(n_data * (1-test_rate))
    self.n_test = n_data - self.n_trn
    self.n_class = len(language)
    self.trn_dataset, self.trn_labelset, self.test_dataset, self.test_labelset = self.load_files()
    self.n_iter = int(self.n_trn*self.n_class / batch_size)

  def load_files(self):
    self.trn_data = []
    self.trn_labels = []
    self.test_data = []
    self.test_labels = []
    
    for _idx, _language in enumerate(self.languages):
      _file_list = []
      _file_dir = os.path.join(self.path, _language)
      print('Load %s from %s' %(_language, _file_dir))
      for root, dirs, files in os.walk(_file_dir):
        for fname in files:
          _file_list.append(os.path.join(root, fname))
      _trn_file_list = _file_list[:self.n_trn]
      _test_file_list = _file_list[self.n_trn:self.n_trn + self.n_test]
      self.trn_data.extend(_trn_file_list)
      self.test_data.extend(_test_file_list)
      self.trn_labels.extend(self.one_hot(self.n_trn, _idx))
      self.test_labels.extend(self.one_hot(self.n_test, _idx))
      
    self.height, self.width, self.channel = np.shape(skimage.io.imread(self.trn_data[0]))
    return self.trn_data[:], self.trn_labels[:], self.test_data[:], self.test_labels[:] # shallow copy

  def data_shape(self):
    return self.height, self.width, self.channel
  
  def one_hot(self, n_data, classe):
    one_hot = np.zeros([n_data,self.n_class], dtype=np.int32)
    one_hot[:, classe] = 1
    return one_hot

  def next_train_batch(self, batch_size=10):
    batch = []
    labels = []
    for _ in range(batch_size):
      _idx = np.random.choice(len(self.trn_data), 1, replace=False)[0]
      assert len(self.trn_data) == len(self.trn_labels)
      img_name = self.trn_data.pop(_idx)
      img_label = self.trn_labels.pop(_idx)
      if not img_name.split('.')[-1] == "png": raise ValueError('Wrong data %s' %img_name)
      image = skimage.io.imread(img_name).astype(np.float32)
      if not len(np.shape(image)) == 3: raise ValueError('Not RGB image, %s'%img_name)
      data = image / 255.
      batch.append(list(data))
      labels.append(img_label) 
    
    if len(self.trn_data) < batch_size:
      self.trn_data = self.trn_dataset[:]
      self.trn_labels = self.trn_labelset[:]
      
    return np.array(batch), np.array(labels)
  
  def next_test_batch(self, batch_size=10):
    batch = []
    labels = []
    idxs = np.random.choice(len(self.test_data), batch_size, replace=False)
    for _idx in idxs:
      img_name = self.test_data[_idx]
      img_label = self.test_labels[_idx]
      if not img_name.split('.')[-1] == "png": raise ValueError('Wrong data %s' %img_name)
      image = skimage.io.imread(img_name).astype(np.float32)
      data = image / 255.
      batch.append(list(data))
      labels.append(img_label)

    return np.array(batch), np.array(labels)
  
  