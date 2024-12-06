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

```bash
$ echo `date +%F" "%a" "%H:%M" (week "%U")"`
2021-01-21 목 17:47 (week 03)
$
```
시간을 확인하기 위해서는

## test_script
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

```bash
$ chmod +x test_script
$ ./test_script
$ ls
test_script   test_run-2021-01-19_1619.log
$ cat test_run-2021-01-19_1619.log 
Started at 2021-01-19 16:19:43
Finished at 2021-01-19 16:19:43
$
```
