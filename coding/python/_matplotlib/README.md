# README.md

# 1. Overview
Matplotlib is a Python library to plot like Matlab. https://matplotlib.org/ provides nice learning materials. To import matplotlib, use:
```python
import matplotlib.pyplot as plt
```
To embed the plot in a Jupyter Notebook, add:
```python
%matplotlib inline
```
## 1.1. Installation
A manual installation of Matplotlib is possible, but installing it through [Anaconda](https://www.anaconda.com/) is recommended. When Anaconda is installed, Matplotlib is automatically installed along with other useful packages.

For manual installation of Matplotlib, refer to [Matplotlib installation instructions](https://matplotlib.org/users/installing.html).
To install Anaconda, refer to [Installation in Anaconda Documentation](https://docs.anaconda.com/anaconda/install/). [Anaconda](https://www.anaconda.com/) is a data science platform which is open-source and supports Windows, macOS, and Linux. It comes with many useful packages such as:
* matplotlib,
* scipy,
* Jupyter Notebook,
* Spyder,
* and many other useful applications.

## 1.2. Examples
Refer to [Examples](https://matplotlib.org/gallery/index.html) to see what's possible with matplotlib.
> This gallery contains examples of the many things you can do with Matplotlib.

I have selected several useful examples in [Summary of Matplotlib Gallery](https://github.com/aimldl/python3/tree/master/packages/matplotlib/gallery) and added brief comments if necessary.

## 1.3. Selected Python Code Examples
matplotlib must be imported to use it. To plot [Simple Plot Example](https://github.com/aimldl/python3/tree/master/packages/matplotlib/gallery/lines_bars_and_markers#simple_plot), 
<img src="https://matplotlib.org/_images/sphx_glr_simple_plot_001.png" width="450" height="300"/>

```python
import matplotlib.pyplot as plt
import numpy as np

# Data for plotting
t = np.arange(0.0, 2.0, 0.01)
s = 1 + np.sin(2 * np.pi * t)
# Plot
fig, ax = plt.subplots()
ax.plot(t, s)
ax.set(xlabel='time (s)', ylabel='voltage (mV)', title='About as simple as it gets, folks')
ax.grid()
fig.savefig("test.png")
plt.show()
```

Another example to use Line2D is from [Composing Custom Legends](https://matplotlib.org/3.1.1/gallery/text_labels_and_annotations/custom_legends.html#sphx-glr-gallery-text-labels-and-annotations-custom-legends-py):

<img src="https://matplotlib.org/3.1.1/_images/sphx_glr_custom_legends_002.png" width="450" height="300" />

```python
from matplotlib.lines import Line2D
custom_lines = [Line2D([0], [0], color=cmap(0.), lw=4),
                Line2D([0], [0], color=cmap(.5), lw=4),
                Line2D([0], [0], color=cmap(1.), lw=4)]

fig, ax = plt.subplots()
lines = ax.plot(data)
ax.legend(custom_lines, ['Cold', 'Medium', 'Hot'])
```
# 2. Learning Materials
## 2.1. Tutorials
* [Pyplot tutorial](https://matplotlib.org/tutorials/introductory/pyplot.html)
* [Tutorials](https://matplotlib.org/3.1.1/tutorials/index.html)
* [Matplotlib Tutorial – A Complete Guide to Python Plot w/ Examples](https://www.machinelearningplus.com/plots/matplotlib-tutorial-complete-guide-python-plot-examples/), Selva Prabhakaran, January 22, 2019

## 2.2. Documentation
* [User's Guide](https://matplotlib.org/users/index.html)
* [Documentation overview](https://matplotlib.org/contents.html). 
* Github Repository: [matplotlib](https://github.com/matplotlib) / [cheatsheets](https://github.com/matplotlib/cheatsheets) 

(EOF)
