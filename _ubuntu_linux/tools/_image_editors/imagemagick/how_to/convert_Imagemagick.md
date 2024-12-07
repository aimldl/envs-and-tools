* Rev.1: 2021-07-15 (Thu)
* Draft: 2021-05-26 (Wed)

## convert (Imagemagick)

Google search: linux command to convert image resolution and size
* [How to Quickly Resize, Convert & Modify Images from the Linux Terminal](https://www.howtogeek.com/109369/how-to-quickly-resize-convert-modify-images-from-the-linux-terminal/)

This page is a summary of the above article in addition to some Bash scripts.
Refer also to the following article.
* [Batch Resize Images using Linux Command Line and Imagemagick](https://guides.wp-bullet.com/batch-resize-images-using-linux-command-line-and-imagemagick/)

### Usage
Convert to other format.
```bash
$ convert howtogeek.png howtogeek.jpg
```
Specify a compression level.
```bash
$ convert howtogeek.png -quality 95 howtogeek.jpg
```
Resize an image.
```bash
$ convert example.png -resize 200x100 example.png
```
Note ImageMagick will try to preserve the aspect ratio.

To force the aspect ratio, add an exclamation mark.
```bash
$ convert example.png -resize 200x100! example.png
```
Specify width or height.
```bash
$ convert example.png -resize 200 example.png
$ convert example.png -resize x100 example.png
```
Rotate an image.
```bash
$ convert howtogeek.jpg -rotate 90 howtogeek-rotated.jpg
```
Apply an effect
* Charcoal effect
```bash
$ convert howtogeek.jpg -charcoal 2 howtogeek-charcoal.jpg
```
* Implode effect with a strength of 1
  * This effect change the image as if a black hole is at the center of the image.
```bash
$ convert howtogeek.jpg -implode 1 howtogeek-imploded.jpg
```
### Advanced Usage
Combine multiple options
```bash
$ convert howtogeek.png -resize 400x400 -rotate 180 -charcoal 4 -quality 95 howtogeek.jpg
```
Batch processing
```bash
$ for file in *.png; do convert $file -rotate 90 rotated-$file; done
```

### Bash Scripts
Several example Bash scripts are below. Save the following lines into a text file and run it on the terminal.
#### Rotate 90 degrees
```bash
#!/bin/bash
# rotate-90
for FILE in *.png; do
  CMD="convert ${FILE} -rotate 90 rotated-${FILE}"
  echo $CMD
  eval $CMD
done
```

#### Lower the resolution of an iPhone screencaptured image
To learn about a Bash script that bath-process all screencaptures images file, refer to [iphone2web](https://github.com/aimldl/coding/blob/06a6b9aaf1b11b5537fb421b7439ae62beb1ddae/bash_scripting/en/bash_scripts/iphone2web.md).
