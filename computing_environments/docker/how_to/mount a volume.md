* Rev.1: 2020-06-11 (Thu)
* Draft: 2020-03-31 (Tue)

# How to Mount a Volume
This document explains how to use the -v option for the "docker run" command. For details, refer to [docker docs > Use volumes](https://docs.docker.com/storage/volumes/).

```bash
$ docker run -it -v /path/to/source:/path/to/destination image_name bash
```

It's written in Korean below.

## 매핑 (볼륨 마운트)된 컨테이너 안밖의 디렉토리의 동작 확인
컨테이너 안밖이 같이 동작하는 것은 간단하게 확인할 수 있습니다.

### 컨테이너 안에서 만든 파일이 밖에서 보임
컨테이너 안에서 text.txt라는 파일은 만듭니다. ls 명령어로 hands-on 디렉토리에 있음을 알 수 있습니다.

```
(base) user@69833fa22777:~$ echo "test" > hands-on/test.txt
(base) user@69833fa22777:~$ ls hands-on/
data  notebooks  test.txt
(base) user@69833fa22777:~$ 
```

Ctrl+p+q를 눌러서 컨테이너 밖으로 나옵니다. 컨테이너 안에서 만든 test.txt가 외부에서도 보입니다. 우연히 같은 이름의 파일이 있는 건 아닌지 내용물을 확인해봅니다. cat 명령어로 텍스트 파일의 내용물을 보니까 "test"입니다. 동일한 파일임이 확인됐습니다.

```
~/github/VOX/kaggle/Compete/titanic_dataset/data$ cd ..
~/github/VOX/kaggle/Compete/titanic_dataset$ ls
data  notebooks  test.txt
~/github/VOX/kaggle/Compete/titanic_dataset$ cat test.txt 
test
~/github/VOX/kaggle/Compete/titanic_dataset$
```

### 컨테이너 바깥에서 만든 파일이 안에서도 보임

컨테이너 바깥, 그러니까 Ubuntu의 터미널, 에 있는 파일은 컨테이너 안에서도 보이는 것은 이미 알고 있습니다. 하지만 다시 한번 확인해보기 위해서 hello.txt을 만듭니다.

```
~/github/VOX/kaggle/Compete/titanic_dataset$ echo "hello" > hello.txt
~/github/VOX/kaggle/Compete/titanic_dataset$ ls
data  hello.txt  notebooks  test.txt
~/github/VOX/kaggle/Compete/titanic_dataset$
```

새로운 파일들이 생겼는데 tree 명령어로 큰 그림을 봐봅니다. 디렉토리/파일 구조가 약간 바뀌었습니다.

```
~/github/VOX/kaggle/Compete/titanic_dataset$ tree
.
├── data
│   ├── gender_submission.csv
│   ├── test.csv
│   └── train.csv
├── hello.txt
├── notebooks
└── test.txt

2 directories, 5 files
~/github/VOX/kaggle/Compete/titanic_dataset$
```

"docker attach" 명령어로 titanic 컨테이너 안으로 들어갑니다. ls 명령어를 실행해보니 hello.txt가 생겼습니다.

```
~/github/VOX/kaggle/Compete/titanic_dataset$ docker attach titanic
(base) user@69833fa22777:~$ ls hands-on/
data  hello.txt  notebooks  test.txt
(base) user@69833fa22777:~$ 
```

큰 그림을 보기 위해서 tree 명령어를 실행합니다. 이것은 컨테이너 안쪽의 트리 구조입니다. 컨테이너 바깥의 트리 구조와 비교해보면 동일하다는 것을 알 수 있습니다.

```
(base) user@69833fa22777:~$ tree hands-on/
hands-on/
|-- data
|   |-- gender_submission.csv
|   |-- test.csv
|   `-- train.csv
|-- hello.txt
|-- notebooks
`-- test.txt

2 directories, 5 files
(base) user@69833fa22777:~$
```

위의 예제를 통해 "docker run"의 -v 옵션으로 컨테이너 바깥의 볼륨을 안에 마운트함으로써 바깥의 특정 디렉토리 A와 안의 특정 디렉토리 B가 매핑될 수 있음을 확인했습니다. -v옵션을 쓰기 위해 "docker"를 실행하는 명령어가 길어져서 번거롭다고 생각할 수 있습니다. 하지만 안밖의 파일을 동일하게 취급 할 수 있게 되어 편리해지는 것에 비하면 아무것도 아닙니다. 이제 디렉토리 A와 B가 같다고 생각하고 쓰시면 됩니다.
