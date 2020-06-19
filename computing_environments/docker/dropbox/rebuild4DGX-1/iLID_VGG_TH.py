#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Apr  9 17:12:13 2018

@author: taehwan
"""

import tensorflow as tf
import numpy as np

from utils import Data, Progress, copy_weights
from time import time

np.random.seed(1234)
tf.set_random_seed(1234)

flags = tf.app.flags

#flags.DEFINE_string("language", "english,spanish", "languages are aviailable english, french, german, italian, spanish")
flags.DEFINE_bool("grad_clip", False, "gradient cliping during training")
flags.DEFINE_bool("transfer_learning", False, "transfer learning")
conf = flags.FLAGS

DATA_DIR = '/home/taehwan/Documents/Data/voxforge/spectrogram'
LANGUAGES = conf.language.replace(" ", "").split(',')
grad_clip = conf.grad_clip
transfer_learning = conf.transfer_learning
LOG_DIR = 'log/vgg/%s/grad_%s/transfer_%s' %("".join(['%c' %i[0] for i in LANGUAGES]), grad_clip, transfer_learning)
print("Language Identification with %s" %LANGUAGES)

batch_size = 32
learning_rate = 0.001
clip_val = 1

data = Data(DATA_DIR, LANGUAGES, batch_size, test_rate = 0.02)
N_EPOCHS = 100
N_iters = data.n_iter
N_classes = data.n_class

height, width, channel = data.data_shape()
print("Spectrogram image size: [%d, %d, %d]" %(height, width, channel))
summary_step = N_iters

conv_initializer = tf.contrib.layers.xavier_initializer_conv2d()
weight_initializer = tf.contrib.layers.xavier_initializer()
bias_initializer = tf.constant_initializer()

def get_shape(layer):
  return layer.get_shape().as_list()

def Conv_Weights(input_dim, output_dim, k_h, k_w):
  return tf.get_variable('w', [k_h, k_w, input_dim, output_dim], initializer=conv_initializer),\
         tf.get_variable('b',[output_dim], initializer=tf.constant_initializer(0.0))
         
def ConvLayer(scope, input_var, out_channel, act=None, k_h=1, k_w=1, s_h=1, s_w=1, reuse=False): # NHWC
  print('%s layer(shape: %s) - kernel: [%d, %d], stride: [%d, %d]' %(scope, get_shape(input_var), k_h, k_w, s_h, s_w))
  _batch_size, _height, _width, in_channel = get_shape(input_var)
  with tf.variable_scope(scope, reuse=reuse):
    kernel, bias = Conv_Weights(in_channel, out_channel, k_h, k_w)
    strides = [1, s_h, s_w, 1]
    
    _conv_layer = tf.nn.bias_add(tf.nn.conv2d(input_var, kernel, strides = strides, padding='SAME'), bias, name='conv')
    if not act == None:
      _conv_layer = act(_conv_layer)
    return _conv_layer

def fc(scope, input, out_dim, act=None, reuse=False):
  with tf.variable_scope(scope, reuse=reuse):
    _batch_size, _in_dim = input.get_shape().as_list()
    w = tf.get_variable('w', [_in_dim, out_dim], initializer=weight_initializer) #NHWC
    b = tf.get_variable('b', [out_dim], initializer=bias_initializer)
    
    layer = tf.matmul(input, w) + b
    
    if not act==None:
      layer = act(layer)
  
  return layer

with tf.device("/device:GPU:0"):
  x = tf.placeholder(tf.float32, [None, height, width, channel])
  y = tf.placeholder(tf.float32, [None, N_classes])
  
  kernel_size = [3,3]
  conv1_1 = ConvLayer('conv1_1', x, 64, tf.nn.relu, *kernel_size)
  conv1_2 = ConvLayer('conv1_2', conv1_1, 64, tf.nn.relu, *kernel_size)
  max_pool1 = tf.nn.max_pool(conv1_2, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')
  
  kernel_size = [3,3]
  conv2_1 = ConvLayer('conv2_1', max_pool1, 128, tf.nn.relu, *kernel_size)
  conv2_2 = ConvLayer('conv2_2', conv2_1, 128, tf.nn.relu, *kernel_size)
  max_pool2 = tf.nn.max_pool(conv2_2, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')
  
  kernel_size = [3,3]
  conv3_1 = ConvLayer('conv3_1', max_pool2, 256, tf.nn.relu, *kernel_size)
  conv3_2 = ConvLayer('conv3_2', conv3_1, 256, tf.nn.relu, *kernel_size)
  conv3_3 = ConvLayer('conv3_3', conv3_2, 256, tf.nn.relu, *kernel_size)
  max_pool3 = tf.nn.max_pool(conv3_3, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')
  
  kernel_size = [3,3]
  conv4_1 = ConvLayer('conv4_1', max_pool3, 512, tf.nn.relu, *kernel_size)
  conv4_2 = ConvLayer('conv4_2', conv4_1, 512, tf.nn.relu, *kernel_size)
  conv4_3 = ConvLayer('conv4_3', conv4_2, 512, tf.nn.relu, *kernel_size)
  max_pool4 = tf.nn.max_pool(conv4_3, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')
  
  kernel_size = [3,3]
  conv5_1 = ConvLayer('conv5_1', max_pool4, 512, tf.nn.relu, *kernel_size)
  conv5_2 = ConvLayer('conv5_2', conv5_1, 512, tf.nn.relu, *kernel_size)
  conv5_3 = ConvLayer('conv5_3', conv5_2, 512, tf.nn.relu, *kernel_size)
  max_pool5 = tf.nn.max_pool(conv5_3, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')
  
  flatten_layer = tf.layers.flatten(max_pool5) # [?, 8192]
  
  fc1 = fc('fc1', flatten_layer, 1000, tf.nn.relu)
  dropout_layer1 = tf.nn.dropout(fc1, 0.5)
  fc2 = fc('fc2', dropout_layer1, 1000, tf.nn.relu)
  dropout_layer2 = tf.nn.dropout(fc2, 0.5)
  fc3 = fc('fc3', dropout_layer2, 100, tf.nn.relu)
  dropout_layer3 = tf.nn.dropout(fc3, 0.5)
  logits = fc('logits', dropout_layer3, N_classes)
  prob = tf.nn.softmax(logits)
  loss = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(labels=y , logits=logits))
  correct_pred = tf.equal(tf.argmax(prob, 1), tf.argmax(y, 1))
  acc = tf.reduce_mean(tf.cast(correct_pred, tf.float32))

optimizer = tf.train.RMSPropOptimizer(learning_rate)

if transfer_learning:
  weights = tf.get_collection(tf.GraphKeys.TRAINABLE_VARIABLES)
  data_dict = np.load('vgg16.npy', encoding='latin1').item()
  copy_weights_op = copy_weights(weights, data_dict)
  tvar_lists = []
  
  for tvar in tf.trainable_variables():
    if not tvar.name.split('/')[0] in data_dict:
      tvar_lists.append(tvar)
else:
  tvar_lists = tf.trainable_variables()
  
grads_and_vars = optimizer.compute_gradients(loss, var_list=tvar_lists)

if grad_clip:
  grads_and_vars = [(tf.clip_by_value(gv[0], -clip_val, clip_val), gv[1]) for gv in grads_and_vars]
else:
  grads_and_vars = [(gv[0], gv[1]) for gv in grads_and_vars]
  
train = optimizer.apply_gradients(grads_and_vars)

config = tf.ConfigProto()
config.gpu_options.allow_growth = True

sess = tf.Session(config=config)
sess.run(tf.global_variables_initializer())

saver = tf.train.Saver(max_to_keep = 3)
summary_writer = tf.summary.FileWriter(LOG_DIR, sess.graph)

with tf.variable_scope('misc'):
  tf.summary.scalar('loss', loss)
  tf.summary.scalar('accuracy', acc)
  
summary_op = tf.summary.merge_all() 
  
if transfer_learning: sess.run(copy_weights_op)

print('Trainable Variables:')
print(" ".join([i.name.split(":")[0] for i in tf.trainable_variables()]))

progress = Progress()
for epoch in range(N_EPOCHS):
  for iter in range(N_iters):
    trn_imgs, trn_labels = data.next_train_batch(batch_size)# height, width, channel
    feed_dict = {x:trn_imgs, y:trn_labels}
    start_time = time()
    _, loss_val = sess.run([train, loss], feed_dict=feed_dict)
    progress.show(iter, N_iters, epoch, loss_val, (time() - start_time))
    
    total_iter = epoch*N_iters + iter
    if (iter+1) == N_iters:
      test_batch_size = 200
      test_imgs, test_labels = data.next_test_batch(test_batch_size)
      feed_dict = {x:test_imgs, y:test_labels}
      summary, acc_val = sess.run([summary_op, acc], feed_dict=feed_dict)
      summary_writer.add_summary(summary, total_iter)
      print('Test accuracy: %d%%' %(acc_val*100))
      for i, language in enumerate(LANGUAGES):
        print('%s: %d' %(language, np.sum(test_labels[:,i])), end= "\n" if i==(N_classes-1) else " ")
      
      saver.save(sess, LOG_DIR+'/model.ckpt', global_step=total_iter)
  
  
  