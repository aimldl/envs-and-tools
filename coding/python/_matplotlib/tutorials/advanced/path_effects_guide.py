#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
matplotlib > tutorials > advanced > path_effects_guide.py
Path effects guide
https://matplotlib.org/3.1.1/tutorials/advanced/patheffects_guide.html#sphx-glr-tutorials-advanced-patheffects-guide-py
"""

import matplotlib.pyplot as plt
import matplotlib.patheffects as path_effects

fig = plt.figure(figsize=(5, 1.5))
text = fig.text(0.5, 0.5, 'Hello path effects world!\nThis is the normal '
                          'path effect.\nPretty dull, huh?',
                ha='center', va='center', size=20)
text.set_path_effects([path_effects.Normal()])
plt.show()
