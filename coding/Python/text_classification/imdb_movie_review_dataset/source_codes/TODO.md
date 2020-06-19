TODO.md


#### 2019-11-11 (Mon)
Fix this error.

```bash
$ python 3_4-modeling_with_rnn-imdb.py
Loaded from ../data/output/train_input.npy...
Loaded from ../data/output/train_label.npy...
74066
74065 74067
WARNING:tensorflow:From /home/aimldl/anaconda3/envs/hula/lib/python3.7/site-packages/tensorflow_core/python/ops/resource_variable_ops.py:1630: calling BaseResourceVariable.__init__ (from tensorflow.python.ops.resource_variable_ops) with constraint is deprecated and will be removed in a future version.
Instructions for updating:
If using Keras pass *_constraint arguments to layers.
WARNING:tensorflow:From /home/aimldl/anaconda3/envs/hula/lib/python3.7/site-packages/tensorflow_core/python/training/training_util.py:236: Variable.initialized_value (from tensorflow.python.ops.variables) is deprecated and will be removed in a future version.
Instructions for updating:
Use Variable.read_value. Variables in 2.X are initialized automatically both in eager and graph (inside tf.defun) contexts.
Traceback (most recent call last):
  File "3_4-modeling_with_rnn-imdb.py", line 187, in <module>
    est.train( train_input_fn )
  File "/home/aimldl/anaconda3/envs/hula/lib/python3.7/site-packages/tensorflow_estimator/python/estimator/estimator.py", line 370, in train
    loss = self._train_model(input_fn, hooks, saving_listeners)
  File "/home/aimldl/anaconda3/envs/hula/lib/python3.7/site-packages/tensorflow_estimator/python/estimator/estimator.py", line 1160, in _train_model
    return self._train_model_default(input_fn, hooks, saving_listeners)
  File "/home/aimldl/anaconda3/envs/hula/lib/python3.7/site-packages/tensorflow_estimator/python/estimator/estimator.py", line 1187, in _train_model_default
    input_fn, ModeKeys.TRAIN))
  File "/home/aimldl/anaconda3/envs/hula/lib/python3.7/site-packages/tensorflow_estimator/python/estimator/estimator.py", line 1024, in _get_features_and_labels_from_input_fn
    self._call_input_fn(input_fn, mode))
  File "/home/aimldl/anaconda3/envs/hula/lib/python3.7/site-packages/tensorflow_estimator/python/estimator/estimator.py", line 1115, in _call_input_fn
    return input_fn(**kwargs)
  File "3_4-modeling_with_rnn-imdb.py", line 100, in train_input_fn
    dataset  = tf.data.shuffle( buffer_size=50000 )
AttributeError: module 'tensorflow_core._api.v2.data' has no attribute 'shuffle'
$
```

2019-07-29(Mon) 18:13pm
Start from 6-CNN Classification

## Refactorize all the codes for better readability
v 1
v 2
v 3
v 4
 5
 6

## Fix error(s)

### v kaggle-word2vec-nlp-tutorial-5_modeling_with_rnn.py
#### Problem
$ python kaggle-word2vec-nlp-tutorial-5_modeling_with_rnn.py
...
Traceback (most recent call last):
  File "kaggle-word2vec-nlp-tutorial-5_modeling_with_rnn.py", line 95, in <module>
    print( type( prepro_configs['vocab_size'] ) )
TypeError: string indices must be integers
$

#### Hint
I tracked down prepro_configs and found the .json file was not properly stored.

#### Solution
I fixed the part to save the .json file and this problem was solved!

### v kaggle-word2vec-nlp-tutorial-2_data_preprocessing.py
#### Problem 1: bs4.FeatureNotFound error

$ ! pip install bs4
$ python kaggle-word2vec-nlp-tutorial-2_data_preprocessing.py
...
bs4.FeatureNotFound: Couldn't find a tree builder with the features you requested: html5lib. Do you need to install a parser library?
...
$

#### Hint
* Source Code
def preprocessing( review, remove_stopwords=True, remove_html_tags=True, verbose=False ):
    # Remove html tags
    if remove_html_tags:
        review = BeautifulSoup( review, 'html5lib').get_text()

* Installing a parser¶
  Another alternative is the pure-Python html5lib parser, which parses HTML the way a web browser does. Depending on your setup, you might install html5lib with one of these commands:
    $ apt-get install python-html5lib
    $ easy_install html5lib
    $ pip install html5lib
Source: https://www.crummy.com/software/BeautifulSoup/bs4/doc/

#### Solution
$ pip install html5lib
As soon as the parser was installed, the problem has been solved!

#### Problem 2: AttributeError
AttributeError: module 'tensorflow._api.v1.data' has no attribute 'shuffle'

#### Hint
* Source code

def train_input_fn():
    ...
    dataset  = tf.data.shuffle( buffer_size=50000 )
    ...


## Write a code

To increase the readability,
### v def save() -> def save2np()
file = dir_data_out + file_test_input_data
with open( file, 'wb') as f:
    np.save( f, file_test_input_data )
    print(f'Saved to {file}...')
->
save( file_test_input_data, 'wb' )

* The default option is 'w'
save( file_test_input_data, 'w' ) or
save( file_test_input_data )
### v def load() -> def load_np() & def load_json()

file = dir_data_out + file_train_input_data
with open( file, 'rb') as f:
    input_data = np.load( f )
    print(f'Loaded from {file}...')
->
load( file_train_input_data, 'rb' )
