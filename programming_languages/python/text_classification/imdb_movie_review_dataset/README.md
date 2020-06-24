##### aimldl > python3 > text_classification > imdb_movie_review_dataset > README.md
* Rev.1: 2019-11-11 (Mon)
* Draft: 2019-10-23 (Wed)
# 1. Overview: Text Classification with IMDB Movie Review Dataset
## 1.1. Directory & File Structure
```
$ tree imdb_movie_review_dataset/
imdb_movie_review_dataset/
├── README.md
├── requirements.txt
├── bin
├── data
│   ├── archive
│   ├── downloads
│   ├── input
│   └── output
├── documents
│   ├── image_files
│   ├── jupyter_notebooks
│   └── references
├── history
│   └── log
└── source_codes
```
Each directory has its town README.md.

# 2. 환경설정
## 2.1. TensorFlow 설치
[aimldl > python3 > packages > tensorflow > README.md](#../../packages/tensorflow/README.md)를 참고합니다.

## 2.2. 필요한 Python Package 설치
프로젝트 디렉토리에 있는 requirements.txt에는 필요한 package명의 리스트가 있습니다. 아래의 명령어로 실행하여 환경을 설정합니다.
```bash
$ pip install -r requirements.txt
```
이 명령어는 requirements.txt에 있는 package를 하나씩 다운 받고 설치합니다.

## 2.3. 수동으로 NLTK의 stopwords 다운로드
requirements.txt에서 실행할 수 없는 NLTK의 stopwords를 다운로드 받습니다.

```bash
$ python
Python 3.7.4 (default, Aug 13 2019, 20:35:49)
[GCC 7.3.0] :: Anaconda, Inc. on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> import nltk
>>> nltk.download('stopwords')
[nltk_data] Downloading package stopwords to /home/aimldl/nltk_data...
[nltk_data]   Unzipping corpora/stopwords.zip.
True
>>> exit()
$
```
만약 이 다운로드 과정없이 "1_2-data_preprocessing-imdb.py"를 실행하면 아래와 같은 에러가 발생합니다. 그러면 위의 명령어를 실행해서 다운로드 받으면 됩니다.
```bash
$ python 1_2-data_preprocessing-imdb.py
  ...

During handling of the above exception, another exception occurred:

Traceback (most recent call last):
  File "1_2-data_preprocessing-imdb.py", line 142, in <module>
    clean_review = preprocessing( review )
  File "1_2-data_preprocessing-imdb.py", line 119, in preprocessing
    stop_words = set( stopwords.words('english') )
  File "/home/aimldl/anaconda3/envs/hula/lib/python3.7/site-packages/nltk/corpus/util.py", line 123, in __getattr__
    self.__load()
  File "/home/aimldl/anaconda3/envs/hula/lib/python3.7/site-packages/nltk/corpus/util.py", line 88, in __load
    raise e
  File "/home/aimldl/anaconda3/envs/hula/lib/python3.7/site-packages/nltk/corpus/util.py", line 83, in __load
    root = nltk.data.find('{}/{}'.format(self.subdir, self.__name))
  File "/home/aimldl/anaconda3/envs/hula/lib/python3.7/site-packages/nltk/data.py", line 701, in find
    raise LookupError(resource_not_found)
LookupError:
**********************************************************************
  Resource stopwords not found.
  Please use the NLTK Downloader to obtain the resource:

  >>> import nltk
  >>> nltk.download('stopwords')

  For more information see: https://www.nltk.org/data.html

  Attempted to load corpora/stopwords

  Searched in:
    - '/home/aimldl/nltk_data'
    - '/home/aimldl/anaconda3/envs/hula/nltk_data'
    - '/home/aimldl/anaconda3/envs/hula/share/nltk_data'
    - '/home/aimldl/anaconda3/envs/hula/lib/nltk_data'
    - '/usr/share/nltk_data'
    - '/usr/local/share/nltk_data'
    - '/usr/lib/nltk_data'
    - '/usr/local/lib/nltk_data'
**********************************************************************
```

(EOF)
