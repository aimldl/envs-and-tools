# Troubleshoot: `SEARCH STACK OVERFLOW` in Google Colab

## 개요

* `SEARCH STACK OVERFLOW`버튼을 클릭하면 관련 문서를 보여줍니다
* 이 기능을 써서 Keras 코드의 에러를 수정한 간단한 예제입니다.

## Problem

**ValueError: Input 0 of layer sequential_3 is incompatible with the layer: expected axis -1 of input shape to have value 3 but received input with shape [None, 32, 32, 3, 1]**

Running `model.`fit` results in the following error.

> model.fit( x_train, y_train, batch_size=batch_size, epochs=epochs, validation_split=0.1 )

The full error message is below.

```bash
Epoch 1/15
WARNING:tensorflow:Model was constructed with shape (None, 32, 32, 1) for input Tensor("input_2:0", shape=(None, 32, 32, 1), dtype=float32), but it was called on an input with incompatible shape (None, 32, 32, 3).
---------------------------------------------------------------------------
ValueError                                Traceback (most recent call last)
<ipython-input-15-d465bbcb4857> in <module>()
      3 
      4 model.compile( loss="categorical_crossentropy", optimizer="adam", metrics=["accuracy"] )
----> 5 model.fit( x_train, y_train, batch_size=batch_size, epochs=epochs, validation_split=0.1 )

10 frames
/usr/local/lib/python3.6/dist-packages/tensorflow/python/framework/func_graph.py in wrapper(*args, **kwargs)
    971           except Exception as e:  # pylint:disable=broad-except
    972             if hasattr(e, "ag_error_metadata"):
--> 973               raise e.ag_error_metadata.to_exception(e)
    974             else:
    975               raise

ValueError: in user code:

    /usr/local/lib/python3.6/dist-packages/tensorflow/python/keras/engine/training.py:806 train_function  *
        return step_function(self, iterator)
    /usr/local/lib/python3.6/dist-packages/tensorflow/python/keras/engine/training.py:796 step_function  **
        outputs = model.distribute_strategy.run(run_step, args=(data,))
    /usr/local/lib/python3.6/dist-packages/tensorflow/python/distribute/distribute_lib.py:1211 run
        return self._extended.call_for_each_replica(fn, args=args, kwargs=kwargs)
    /usr/local/lib/python3.6/dist-packages/tensorflow/python/distribute/distribute_lib.py:2585 call_for_each_replica
        return self._call_for_each_replica(fn, args, kwargs)
    /usr/local/lib/python3.6/dist-packages/tensorflow/python/distribute/distribute_lib.py:2945 _call_for_each_replica
        return fn(*args, **kwargs)
    /usr/local/lib/python3.6/dist-packages/tensorflow/python/keras/engine/training.py:789 run_step  **
        outputs = model.train_step(data)
    /usr/local/lib/python3.6/dist-packages/tensorflow/python/keras/engine/training.py:747 train_step
        y_pred = self(x, training=True)
    /usr/local/lib/python3.6/dist-packages/tensorflow/python/keras/engine/base_layer.py:985 __call__
        outputs = call_fn(inputs, *args, **kwargs)
    /usr/local/lib/python3.6/dist-packages/tensorflow/python/keras/engine/sequential.py:372 call
        return super(Sequential, self).call(inputs, training=training, mask=mask)
    /usr/local/lib/python3.6/dist-packages/tensorflow/python/keras/engine/functional.py:386 call
        inputs, training=training, mask=mask)
    /usr/local/lib/python3.6/dist-packages/tensorflow/python/keras/engine/functional.py:508 _run_internal_graph
        outputs = node.layer(*args, **kwargs)
    /usr/local/lib/python3.6/dist-packages/tensorflow/python/keras/engine/base_layer.py:976 __call__
        self.name)
    /usr/local/lib/python3.6/dist-packages/tensorflow/python/keras/engine/input_spec.py:216 assert_input_compatibility
        ' but received input with shape ' + str(shape))

    ValueError: Input 0 of layer conv2d_2 is incompatible with the layer: expected axis -1 of input shape to have value 1 but received input with shape [None, 32, 32, 3]
```

## Hint

구글 코랩의 경우`SEARCH STACK OVERFLOW`버튼을 클릭하면 관련 문서를 보여줍니다.

<img src='images/error-5_cifar10-cnn-keras_ipynb.png'>



[Tensorflow 2.0.0-rc0 - incorrect data shape for SparseCategoricalCrossentropy #32333](Tensorflow 2.0.0-rc0 - incorrect data shape for SparseCategoricalCrossentropy #32333)

## Solution

```python
# Before
input_shape = (32, 32, 1)
# After
input_shape = (32, 32, 3)
```

## Appendix. Source Code

```python
from tensorflow import keras

(x_train, y_train), (x_test, y_test) = keras.datasets.cifar10.load_data()

#from keras.datasets import cifar10
#(x_train, y_train), (x_test, y_test) = cifar10.load_data()

# Scale images to the [0, 1] range
x_train = x_train.astype("float32") / 255
x_test = x_test.astype("float32") / 255

import numpy as np

# Make sure images have shape (32, 32, 1)
x_train = np.expand_dims( x_train, -1 )
x_test = np.expand_dims( x_test, -1 )

print( "x_train shape:", x_train.shape )
print( x_train.shape[0], "train samples" )
print( x_test.shape[0], "test samples" )

num_classes = 10
input_shape = (32, 32, 1)

# Convert class vectors to binary class matrices
y_train = keras.utils.to_categorical( y_train, num_classes )
y_test = keras.utils.to_categorical( y_test, num_classes )

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras import layers

model = keras.Sequential(
    [
        keras.Input(shape=input_shape),
        layers.Conv2D(32, kernel_size=(3, 3), activation="relu"),
        layers.MaxPooling2D(pool_size=(2, 2)),
        layers.Conv2D(64, kernel_size=(3, 3), activation="relu"),
        layers.MaxPooling2D(pool_size=(2, 2)),
        layers.Flatten(),
        layers.Dropout(0.5),
        layers.Dense(num_classes, activation="softmax"),
    ]
)

model.summary()

batch_size = 128
epochs = 15

model.compile( loss="categorical_crossentropy", optimizer="adam", metrics=["accuracy"] )
model.fit( x_train, y_train, batch_size=batch_size, epochs=epochs, validation_split=0.1 )

score = model.evaluate( x_test, y_test, verbose=0 )
print("Test loss:", score[0])
print("Test accuracy:", score[1])
```

