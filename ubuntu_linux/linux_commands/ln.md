##### ln.md

# ln

[[Linux] Symbolic Link를 이용해서 즐겨찾기 (Favorites) 만들기](https://aimldl.blog.me/221577596405)

TODO: Fix the writing below.

## Symbolic Link 만들기
```bash
$ ln -s <source> <link_name>
```
# 명령어 예시
$ ln -s ~/Dropbox/sw-done/aws/hula-HunkLabeling ~/hula

# Symbolic Link 제거하기
$ unlink linkname
# 명령어 예시
$ unlink ~/hula

Symbolic Link를 이용해서 즐겨찾기 (Favorites) 만들기

Linux의 Terminal에서 '즐겨찾기'처럼 자체 파일을 유지하면서 해당 파일에 쉽게 접근하는 방법을 알아봅니다. Symbolic Link를 만들면 즐겨찾기와 같이 특정 파일 혹은 디렉토리에 쉽게 접근할 수 있습니다. 연결고리를 만들 때는 ln명령어 (Link), 끊을 때는 unlink명령어 (혹은 rm명령어)를 쓰면 됩니다. 각 명령어의 문법은 다음과 같습니다.

ln명령어 문법

    (Syntax)

      $ ln -s <SOURCE> <LINK_NAME>

    ​

    Create a symbolic link to a file.

      $ ln -s /path/to/file /path/to/symlink

    ​

    Create a symbolic link to a directory:

      $ ln -s /path/to/dir /path/to/symlink

    구글 검색: linux symbolic link

    SymLink – HowTo: Create a Symbolic Link – Linux

    https://www.shellhacks.com/symlink-create-symbolic-link-linux/

unlink/rm명령어 문법
$ unlink linkname
$ rm linkname

    Linux Delete Symbolic Link ( Softlink )

    Delete Symbolic Link File

      $ unlink linkname

      $ rm linkname

    Delete Symbolic Link Directory

      $ unlink linkDirName

      $ rm linkDirName

    Linux Delete Symbolic Link ( Softlink ), https://www.cyberciti.biz/faq/linux-remove-delete-symbolic-softlink-command/

예1

유저 홈 디렉토리 밑에 Symbolic Link를 만들어보려고 합니다. 작업 디렉토리는 "~/Dropbox/sw-done/aws/hula-HunkLabeling/"으로 자주 사용할 경우 홈 디렉토리 밑에 즐겨찾기처럼 Symbolic Link가 있으면 편리하기 때문입니다. 
~$ tree -d -L 1
.
├── Desktop
├── Documents
├── Downloads
├── Music
├── Pictures
├── Public
├── Templates
├── Videos
└── hula-HunkLabeling -> /home/aimldl/Dropbox/sw-done/aws/hula-HunkLabeling/

명령어는 다음과 같습니다. 소스 디렉토리를 "~/Dropbox/sw-done/aws/hula-HunkLabeling/"로 지정하고 링크명을 
$ ln -s ~/Dropbox/sw-done/aws/hula-HunkLabeling/ ~/
$ ln -s ~/Dropbox/sw-done/aws/hula-HunkLabeling ~/hula
$ ls ~/hula
hula-HunkLabeling
$

​

Symbolic Link 지우기

​

unlink 명령어를 쓰면 ln로 연결된 Symbolic Link를 없앨 수 있습니다.
~$ cd hula/
~/hula$ ls
hula-HunkLabeling
~/hula$ unlink hula-HunkLabeling
~/hula$ ls
~/hula$

예2

Symbolic Link를 저장하고 싶은 디렉토리에 이동해서,

소스 디렉토리명과 서브 디렉토리명 (예제에서는 hula)를 을 입력합니다.
~$ cd
~$ cd .mwd
~/.mwd$ ln -s /home/aimldl/projects/hula-HunkLabeling hula
~/.mwd$ ls
hula
~/.mwd$ cd hula
~/.mwd/hula$ ls
BUGS    HISTORY  TODO     bin   doc    src
~/.mwd/hula$ 

예3

~/aimldl이라는 디렉토리는 상당히 복잡한 디렉토리를 가지고 있습니다. 각 서브 디렉토리 (예: aws, bindsnet 등)은 github repository인데요. 하위의 하위에 있는 서브 디렉토리 중 자주 찾게 되는 서브 디렉토리를 이 레벨로 끌어와서 Command line에서 즐겨찾기처럼 쉽게 접근하고 싶습니다. 이때 Symbolic Link를 써보겠습니다.

​

아래는 입력한 명령어입니다.
$ ls
aws/              batch_git_pull*  bindsnet/                cpp/        matlab/   python3/
batch_git_clone*  batch_git_push*  computing_environments/  documents/  private/  sql/
$ ln -s ~/aimldl/python3/packages/keras keras
$ ls
aws              batch_git_pull  bindsnet                cpp        keras   private  sql
batch_git_clone  batch_git_push  computing_environments  documents  matlab  python3
$ ln -s ~/aimldl/python3/packages/tensorflow tensorflow
$ ls
aws              batch_git_pull  bindsnet                cpp        keras   private  sql
batch_git_clone  batch_git_push  computing_environments  documents  matlab  python3  tensorflow
$ ln -s ~/aimldl/python3/packages/matplotlib
$ ls
aws              batch_git_push          cpp        matlab      python3
batch_git_clone  bindsnet                documents  matplotlib  sql
batch_git_pull   computing_environments  keras      private     tensorflow
$ ln -s ~/aimldl/python3/packages/matplotlib matplotlib
$ l
aws/              batch_git_push*          cpp/        matlab/      python3/
batch_git_clone*  bindsnet/                documents/  matplotlib@  sql/
batch_git_pull*   computing_environments/  keras@      private/     tensorflow@
$ ln -s ~/aimldl/python3/topics/medium topics-medium
$ ln -s ~/aimldl/python3/topics/towardsdatascience topics-towardsdatascience
$ l
aws/              bindsnet/                keras@       python3/        topics-towardsdatascience@
batch_git_clone*  computing_environments/  matlab/      sql/
batch_git_pull*   cpp/                     matplotlib@  tensorflow@
batch_git_push*   documents/               private/     topics-medium@
$ ln -s ~/aimldl/python3/topics/command_line_arguments topics-command_line_arguments
$ l
aws/              computing_environments/  matplotlib@  topics-command_line_arguments@
batch_git_clone*  cpp/                     private/     topics-medium@
batch_git_pull*   documents/               python3/     topics-towardsdatascience@
batch_git_push*   keras@                   sql/
bindsnet/         matlab/                  tensorflow@
$

tree 명령어로 Symbolic Link를 확인해보면 아래와 같습니다. 자주 들어가는 몇 개의 서브 디렉토리를 꺼내서 즐겨찾기처럼 더 쉽게 접근할 수 있게 되었습니다. 
~$ tree aimldl/ -d -L 1
aimldl/
├── aws
├── bindsnet
├── computing_environments
├── cpp
├── documents
├── keras -> /home/aimldl/aimldl/python3/packages/keras
├── matlab
├── matplotlib -> /home/aimldl/aimldl/python3/packages/matplotlib
├── private
├── python3
├── sql
├── tensorflow -> /home/aimldl/aimldl/python3/packages/tensorflow
├── topics-command_line_arguments -> /home/aimldl/aimldl/python3/topics/command_line_arguments
├── topics-medium -> /home/aimldl/aimldl/python3/topics/medium
└── topics-towardsdatascience -> /home/aimldl/aimldl/python3/topics/towardsdatascience

15 directories
~$
