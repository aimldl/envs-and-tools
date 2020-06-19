


#### 1. 환경 설치
1.4.3. 코드 실행 > 코드 1-2 GPU 환경 도커 컨테이너 띄우기
```bash
$ docker pull ratsgo/embedding-gpu
```
#### 2. 소스 코드 다운로드
##### 에러
```bash
~$ git pull origin master
fatal: not a git repository (or any of the parent directories): .git
~$
```
##### 해결
Docker환경의 bash shell에서 실행해야 합니다.
```bash
~/aimldl$ docker run -it --rm --runtime=nvidia ratsgo/embedding-gpu bash
root@1d9cf879e5a1:/notebooks/embedding#
```

##### 상세 내용
```bash
remote: Enumerating objects: 130, done.
remote: Counting objects: 100% (130/130), done.
remote: Total 635 (delta 130), reused 130 (delta 130), pack-reused 505
오브젝트를 받는 중: 100% (635/635), 151.54 KiB | 0 bytes/s, 완료.
델타를 알아내는 중: 100% (453/453), 로컬 오브젝트 22개 마침.
https://github.com/ratsgo/embedding URL에서
 * branch            master     -> FETCH_HEAD
   db728a6..dc3560d  master     -> origin/master
업데이트 중 db728a6..dc3560d
Fast-forward
 README.md                           |  98 ++++++-
 docker/Dockerfile-CPU               |  19 +-
 docker/Dockerfile-GPU               |  19 +-
 docs/_layouts/default.html          |   6 +-
 docs/bugs.md                        |  21 --
 docs/downloaddata.md                | 127 +++++++++
 docs/environment.md                 |  41 ++-
 docs/index.md                       | 225 +++++++--------
 docs/notice.md                      | 594 +++++++++++++++++++++++++++++++++++++++
 docs/preprocess.md                  |  87 +++---
 docs/tokenize.md                    |  87 +++---
 models/bert/tokenization.py         |   9 +-
 models/sent_eval.py                 |  34 ++-
 models/sent_utils.py                |   2 +-
 models/tune_utils.py                | 369 ++++++++++++++++++++++---
 models/visualize_utils.py           |  66 ++++-
 models/word_eval.py                 |  10 +-
 models/word_utils.py                |  28 +-
 models/xlnet/data_utils.py          | 915 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 models/xlnet/function_builder.py    | 394 ++++++++++++++++++++++++++
 models/xlnet/gpu_utils.py           |  69 +++++
 models/xlnet/model_utils.py         | 399 +++++++++++++++++++++++++++
 models/xlnet/modeling.py            | 783 ++++++++++++++++++++++++++++++++++++++++++++++++++++
 models/xlnet/prepro_utils.py        | 137 +++++++++
 models/xlnet/train_gpu.py           | 328 ++++++++++++++++++++++
 models/xlnet/xlnet.py               | 292 ++++++++++++++++++++
 preprocess.sh                       |  90 +++---
 preprocess/dump.py                  |  13 +-
 preprocess/unsupervised_nlputils.py |  28 +-
 sentmodel.sh                        | 120 ++++++--
 wordmodel.sh                        |  10 +-
 31 files changed, 5021 insertions(+), 399 deletions(-)
 delete mode 100644 docs/bugs.md
 create mode 100644 docs/downloaddata.md
 create mode 100644 docs/notice.md
 create mode 100644 models/xlnet/data_utils.py
 create mode 100644 models/xlnet/function_builder.py
 create mode 100644 models/xlnet/gpu_utils.py
 create mode 100644 models/xlnet/model_utils.py
 create mode 100644 models/xlnet/modeling.py
 create mode 100644 models/xlnet/prepro_utils.py
 create mode 100644 models/xlnet/train_gpu.py
 create mode 100644 models/xlnet/xlnet.py
root@1d9cf879e5a1:/notebooks/embedding#
```

##### 상세 내용
```bash
(base) ubuntu@ip-x-x-x-x:~$ ls
Anaconda3-2019.10-Linux-x86_64.sh  Nvidia_Cloud_EULA.pdf  README  aimldl  anaconda3  src  tools
(base) ubuntu@ip-x-x-x-x:~$ git clone https://github.com/ratsgo/embedding
Cloning into 'embedding'...
remote: Enumerating objects: 1618, done.
remote: Total 1618 (delta 0), reused 0 (delta 0), pack-reused 1618
Receiving objects: 100% (1618/1618), 405.91 KiB | 638.00 KiB/s, done.
Resolving deltas: 100% (1085/1085), done.
(base) ubuntu@ip-x-x-x-x:~$ ls
Anaconda3-2019.10-Linux-x86_64.sh  README  anaconda3  src
Nvidia_Cloud_EULA.pdf              aimldl  embedding  tools
(base) ubuntu@ip-x-x-x-x:~$ cd embedding/
(base) ubuntu@ip-x-x-x-x:~/embedding$ ls
LICENSE  README.md  docker  docs  models  preprocess  preprocess.sh  sentmodel.sh  wordmodel.sh
(base) ubuntu@ip-x-x-x-x:~/embedding$ tree -d
.
├── docker
├── docs
│   ├── _layouts
│   └── assets
│       └── css
├── models
│   ├── bert
│   ├── bilm
│   ├── swivel
│   └── xlnet
└── preprocess

11 directories
(base) ubuntu@ip-x-x-x-x:~/embedding$
```

혹은 외부에 동일한 환경을 만들어서 git clone을 해야합니다.
```bash
$ git clone https://github.com/ratsgo/embedding
$ cd embedding
~/embedding$ tree
.
├── LICENSE
├── README.md
├── docker
│   ├── Dockerfile-CPU
│   └── Dockerfile-GPU
├── docs
│   ├── _config.yml
│   ├── _layouts
│   │   └── default.html
│   ├── assets
│   │   └── css
│   │       └── style.css
│   ├── downloaddata.md
│   ├── environment.md
│   ├── index.md
│   ├── notice.md
│   ├── preprocess.md
│   └── tokenize.md
├── models
│   ├── bert
│   │   ├── create_pretraining_data.py
│   │   ├── modeling.py
│   │   ├── optimization.py
│   │   ├── run_pretraining.py
│   │   └── tokenization.py
│   ├── bilm
│   │   ├── __init__.py
│   │   ├── data.py
│   │   ├── elmo.py
│   │   ├── model.py
│   │   └── training.py
│   ├── sent_eval.py
│   ├── sent_utils.py
│   ├── swivel
│   │   ├── fastprep.cc
│   │   ├── fastprep.mk
│   │   └── swivel.py
│   ├── train_elmo.py
│   ├── tune_utils.py
│   ├── visualize_utils.py
│   ├── word_eval.py
│   ├── word_utils.py
│   └── xlnet
│       ├── data_utils.py
│       ├── function_builder.py
│       ├── gpu_utils.py
│       ├── model_utils.py
│       ├── modeling.py
│       ├── prepro_utils.py
│       ├── train_gpu.py
│       └── xlnet.py
├── preprocess
│   ├── __init__.py
│   ├── dump.py
│   ├── mecab-user-dic.csv
│   ├── supervised_nlputils.py
│   └── unsupervised_nlputils.py
├── preprocess.sh
├── sentmodel.sh
└── wordmodel.sh
```

#### 3. 데이터 다운로드
##### 에러
```bash
~/embedding$ bash preprocess.sh dump-processed
download processed data...
mkdir: cannot create directory ‘/notebooks’: Permission denied
preprocess.sh: line 70: cd: /notebooks/embedding/data: No such file or directory
/notebooks/embedding/data/processed.zip: No such file or directory
unzip:  cannot find or open processed.zip, processed.zip.zip or processed.zip.ZIP.
rm: cannot remove 'processed.zip': No such file or directory
~/embedding$
```
##### 수정
Docker환경의 bash shell에서 실행해야 합니다.
```bash
root@1d9cf879e5a1:/notebooks/embedding# bash preprocess.sh dump-processed
download processed data...
--2019-12-30 07:28:29--  https://docs.google.com/uc?export=download&confirm=Qpbs&id=1kUecR7xO7bsHFmUI6AExtY5u2XXlObOG
Resolving docs.google.com (docs.google.com)... 172.217.26.14, 2404:6800:4004:819::200e
접속 docs.google.com (docs.google.com)|172.217.26.14|:443... 접속됨.
HTTP request sent, awaiting response... 302 Moved Temporarily
Location: https://doc-0k-b8-docs.googleusercontent.com/docs/securesc/ha0ro937gcuc7l7deffksulhg5h7mbp1/73kvnltqgkebr5j6jscchh0geo6fnifs/1577685600000/05170634686643261154/*/1kUecR7xO7bsHFmUI6AExtY5u2XXlObOG?e=download [following]
Warning: wildcards not supported in HTTP.
--2019-12-30 07:28:29--  https://doc-0k-b8-docs.googleusercontent.com/docs/securesc/ha0ro937gcuc7l7deffksulhg5h7mbp1/73kvnltqgkebr5j6jscchh0geo6fnifs/1577685600000/05170634686643261154/*/1kUecR7xO7bsHFmUI6AExtY5u2XXlObOG?e=download
Resolving doc-0k-b8-docs.googleusercontent.com (doc-0k-b8-docs.googleusercontent.com)... 172.217.31.161, 2404:6800:4004:80d::2001
접속 doc-0k-b8-docs.googleusercontent.com (doc-0k-b8-docs.googleusercontent.com)|172.217.31.161|:443... 접속됨.
HTTP request sent, awaiting response... 200 OK
Length: unspecified [application/zip]
Saving to: ‘/notebooks/embedding/data/processed.zip’

/notebooks/embedding/data/     [                  <=>                 ] 401.89M  35.8MB/s    in 11s

2019-12-30 07:28:41 (37.2 MB/s) - ‘/notebooks/embedding/data/processed.zip’ saved [421408263]

Archive:  processed.zip
   creating: processed/
  inflating: processed/space-correct.model
  inflating: processed/processed_korquad.txt
  inflating: processed/processed_ratings_train.txt
  inflating: processed/processed_ratings_test.txt
  inflating: processed/processed_wiki_ko.txt
  inflating: processed/processed_ratings.txt
  inflating: processed/corrected_ratings_corpus.txt
  inflating: processed/soyword.model
  inflating: processed/processed_review_movieid.txt
  inflating: processed/corrected_ratings_train.txt
  inflating: processed/corrected_ratings_test.txt
root@1d9cf879e5a1:/notebooks/embedding#
```
```bash
root@1d9cf879e5a1:/notebooks/embedding# apt install tree
root@1d9cf879e5a1:/notebooks/embedding# tree -d
.
├── data
│   └── processed
├── docker
├── docs
│   ├── _layouts
│   └── assets
│       └── css
├── models
│   ├── bert
│   ├── bilm
│   ├── fastText
│   │   ├── alignment
│   │   ├── crawl
│   │   ├── docs
│   │   ├── python
│   │   │   ├── benchmarks
│   │   │   ├── doc
│   │   │   │   └── examples
│   │   │   └── fasttext_module
│   │   │       └── fasttext
│   │   │           ├── pybind
│   │   │           ├── tests
│   │   │           └── util
│   │   ├── scripts
│   │   │   ├── kbcompletion
│   │   │   └── quantization
│   │   ├── src
│   │   ├── tests
│   │   └── website
│   │       ├── blog
│   │       ├── core
│   │       ├── pages
│   │       │   └── en
│   │       └── static
│   │           ├── docs
│   │           │   └── en
│   │           │       └── html
│   │           │           └── search
│   │           └── img
│   │               ├── authors
│   │               └── blog
│   ├── glove
│   │   ├── build
│   │   ├── eval
│   │   │   ├── matlab
│   │   │   ├── octave
│   │   │   ├── python
│   │   │   └── question-data
│   │   └── src
│   ├── swivel
│   │   └── tensorflow
│   │       └── core
│   │           └── example
│   └── xlnet
└── preprocess

55 directories
root@1d9cf879e5a1:/notebooks/embedding#
```

디렉토리를 확인해보면,
```bash
├── data
│   └── processed
├── models
│   ├── fastText
│   │   ├── alignment
│   │   ├── crawl
│   │   ├── docs
│   │   ├── python
│   │   │   ├── benchmarks
│   │   │   ├── doc
│   │   │   │   └── examples
│   │   │   └── fasttext_module
│   │   │       └── fasttext
│   │   │           ├── pybind
│   │   │           ├── tests
│   │   │           └── util
│   │   ├── scripts
│   │   │   ├── kbcompletion
│   │   │   └── quantization
│   │   ├── src
│   │   ├── tests
│   │   └── website
│   │       ├── blog
│   │       ├── core
│   │       ├── pages
│   │       │   └── en
│   │       └── static
│   │           ├── docs
│   │           │   └── en
│   │           │       └── html
│   │           │           └── search
│   │           └── img
│   │               ├── authors
│   │               └── blog
│   ├── glove
│   │   ├── build
│   │   ├── eval
│   │   │   ├── matlab
│   │   │   ├── octave
│   │   │   ├── python
│   │   │   └── question-data
│   │   └── src
│   ├── swivel
│   │   └── tensorflow
│   │       └── core
│   │           └── example
```
가 더 생겼음을 알 수 있다.

```bash
root@1d9cf879e5a1:/notebooks/embedding# git pull origin master
https://github.com/ratsgo/embedding URL에서
 * branch            master     -> FETCH_HEAD
Already up-to-date.
root@1d9cf879e5a1:/notebooks/embedding#
```
```bash
root@1d9cf879e5a1:/notebooks/embedding# git pull origin master
https://github.com/ratsgo/embedding URL에서
 * branch            master     -> FETCH_HEAD
Already up-to-date.
root@1d9cf879e5a1:/notebooks/embedding# bash preprocess.sh dump-raw-wiki
download ko-wikipedia...
--2019-12-30 07:35:48--  https://dumps.wikimedia.org/kowiki/latest/kowiki-latest-pages-articles.xml.bz2
Resolving dumps.wikimedia.org (dumps.wikimedia.org)... 208.80.154.7, 2620:0:861:1:208:80:154:7
접속 dumps.wikimedia.org (dumps.wikimedia.org)|208.80.154.7|:443... 접속됨.
HTTP request sent, awaiting response... 200 OK
Length: 649748667 (620M) [application/octet-stream]
Saving to: ‘/notebooks/embedding/data/raw/kowiki-latest-pages-articles.xml.bz2’

kowiki-latest-pages-articl 100%[=====================================>] 619.65M  5.07MB/s    in 2m 3s

2019-12-30 07:37:53 (5.03 MB/s) - ‘/notebooks/embedding/data/raw/kowiki-latest-pages-articles.xml.bz2’ saved [649748667/649748667]
```

```bash
root@1d9cf879e5a1:/notebooks/embedding# tree -d
.
├── data
│   └── raw
```

```bash
root@1d9cf879e5a1:/notebooks/embedding# bash preprocess.sh process-wiki
processing ko-wikipedia...


Processed 10000 articles
Processed 20000 articles
Processed 30000 articles
Processed 40000 articles
Processed 50000 articles
Processed 60000 articles
Processed 70000 articles
Processed 80000 articles
Processed 90000 articles
Processed 100000 articles
Processed 110000 articles
Processed 120000 articles
Processed 130000 articles
Processed 140000 articles
Processed 150000 articles
Processed 160000 articles
Processed 170000 articles
Processed 180000 articles
Processed 190000 articles
Processed 200000 articles
Processed 210000 articles
Processed 220000 articles
Processed 230000 articles
Processed 240000 articles
Processed 250000 articles
Processed 260000 articles
Processed 270000 articles
Processed 280000 articles
Processed 290000 articles
Processed 300000 articles
Processed 310000 articles
Processed 320000 articles
Processing complete!
```
This took quite a while on p2.xlarge for me.

다시 들어가기
```bash
~$ docker exec -it eager_margulis bash
root@1d9cf879e5a1:/notebooks/embedding#
```
