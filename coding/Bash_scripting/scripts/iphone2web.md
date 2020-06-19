iphone2web.md

TODO: The script is updated. Update this document according to it.

#### Lower the resolution of an iPhone screencaptured image
A screencapture from an iPhone has a resolution of 2208x1242.
```bash
$ identify -format "%wx%h" IMG_8927.PNG
2208x1242
$
```
To convert it down to width=500 and quality=60%, run:
```bash
$ convert IMG_8942.PNG -resize 500 -quality 60 IMG_8942-500-60.PNG
```

#### Bash script that batch-converts iPhone screencaptured images.
It identifies all the screencaptures and saves the converted results to sub-directory output. The commands look like below.
```bash
$ ./iphone2web
convert IMG_8927.PNG -resize 500 -quality 60 output/500_60-IMG_8927.PNG
convert IMG_8928.PNG -resize 500 -quality 60 output/500_60-IMG_8928.PNG
  ...
convert IMG_8951.PNG -resize 500 -quality 60 output/500_60-IMG_8951.PNG
$
```
I have tested several options for the new size and quality. I liked width-500 and 60% quality, but you can change them in the Bash file.
* The width is converted down to 500 (from 2208).
* The quality is the 60% of the screencaptured image.
* An example of file lowered file size: 3.0MB -> 266.3kB,

```bash
#!/bin/bash
# iphone2web
#   converts all images in the same directory.
#   The images are screencaptured on an iPhone.
#   The purpose is to lower the resolution for a web sharing.
#
# * Draft: 2019-12-12 (Thu)

RESIZE=500
QUALITY=60

# Make the output directory if it doesn't exist.
# src: https://stackoverflow.com/questions/793858/how-to-mkdir-only-if-a-dir-does-not-already-exist
OUTPUT_DIR="output"
if [[ ! -e $OUTPUT_DIR ]]; then
  CMD="mkdir $OUTPUT_DIR"
  echo $CMD
  eval $CMD
elif [[ ! -d $OUTPUT_DIR ]]; then
  echo "$OUTPUT_DIR already exists, but is not a directory." 1>&2
fi

# Batch-convert all screencapture files.
# The file name is IMG_*.PNG, e.g. IMG_8927.PNG.
for FILE in IMG_*.PNG; do
  NEW_FILE=${OUTPUT_DIR}/${RESIZE}_${QUALITY}-${FILE}
  # TODO: separate the basename and add resize_quality between the basename and extension.
  CMD="convert ${FILE} -resize ${RESIZE} -quality ${QUALITY} ${NEW_FILE}"
  echo $CMD
  # Uncomment the following line to run/evaluate the command.
  #eval $CMD
done
# EOF
```
