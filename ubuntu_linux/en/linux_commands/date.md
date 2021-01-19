* Draft: 2021-01-19 (Tue)

# date

```bash
$ date +"%Y-%m-%d_%H%M%S"
2021-01-19_154031
$
```

```bash
$ date +"%Y-%m-%d %H:%M:%S"
2021-01-19 15:40:58
$
```
시간을 확인하기 위해서는

```bash
#!/bin/bash

NOW=`date +"%Y-%m-%d_%H%M"`
FILE_NAME="test_run-${NOW}.log"
START_TIME=`date +"%Y-%m-%d %H:%M:%S"`
echo "Started at $START_TIME" > $FILE_NAME

./darknet detector demo cfg/coco.data cfg/yolov3.cfg cfg/yolov3.weights

END_TIME=`date +"%Y-%m-%d %H:%M:%S"`
echo "Finished at $END_TIME" >> $FILE_NAME
```
