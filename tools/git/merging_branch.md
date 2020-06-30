##### aimldl/computing_environments/git/merging_branch.md

# Merge a Branch
* [branch 병합](https://opentutorials.org/module/2676/15262), 지옥에서 온 Git
* [branch 병합 시 충돌해결](https://opentutorials.org/module/2676/15275), 지옥에서 온 Git

```bash
$ ./batch_git_pull
```
## Problem
```bash
cd /home/aimldl/github/technical_skills
git pull
remote: Enumerating objects: 36, done.
remote: Counting objects: 100% (36/36), done.
remote: Compressing objects: 100% (20/20), done.
remote: Total 28 (delta 10), reused 26 (delta 8), pack-reused 0
Unpacking objects: 100% (28/28), done.
From https://github.com/aimldl/technical_skills
   f705ba2..6f75f05  master     -> origin/master
Auto-merging computing_environments/linux_ubuntu/bash_scripts/install_ubuntu_basic_packages
Auto-merging computing_environments/linux_ubuntu/INSTALL.md
CONFLICT (content): Merge conflict in computing_environments/linux_ubuntu/INSTALL.md
Automatic merge failed; fix conflicts and then commit the result.
```

`CONFLICT (content):` shows the file with conflict `computing_environments/linux_ubuntu/INSTALL.md`.
```bash
CONFLICT (content): Merge conflict in computing_environments/linux_ubuntu/INSTALL.md
Automatic merge failed; fix conflicts and then commit the result.
```
The full path is:
`/home/aimldl/github/technical_skills/computing_environments/linux_ubuntu/INSTALL.md`

## Hint
```bash
$ cd technical_skills/
$ pwd
~/github/technical_skills
```

```bash
$ git status
```

```bash
On branch master
Your branch and 'origin/master' have diverged,
and have 1 and 10 different commits each, respectively.
  (use "git pull" to merge the remote branch into yours)

You have unmerged paths.
  (fix conflicts and run "git commit")
  (use "git merge --abort" to abort the merge)

Changes to be committed:

	modified:   computing_environments/gpgpu/INSTALL.md
  ...
Unmerged paths:
  (use "git add <file>..." to mark resolution)

	both modified:   computing_environments/linux_ubuntu/INSTALL.md

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git checkout -- <file>..." to discard changes in working directory)
  (commit or discard the untracked or modified content in submodules)

	modified:   coding/python/packages/tpot/test_codes (modified content, untracked content)
$
```

Open the file with a text editor.
```bash
$ gedit computing_environments/linux_ubuntu/INSTALL.md &
```

In the file, 
```
## References

<<<<<<< HEAD
* [003. 리눅스 운영체제 설치하기-Ubuntu Linux 설치](https://m.blog.naver.com/PostView.nhn?blogId=aimldl&logNo=221478627994&referrerCode=0&searchKeyword=linux)

||||||| merged common ancestors
* [003. 리눅스 운영체제 설치하기-Ubuntu Linux 설치](https://m.blog.naver.com/PostView.nhn?blogId=aimldl&logNo=221478627994&referrerCode=0&searchKeyword=linux)
=======
* [003. 리눅스 운영체제 설치하기-Ubuntu Linux 설치](https://m.blog.naver.com/PostView.nhn?blogId=aimldl&logNo=221478627994&referrerCode=0&searchKeyword=linux)
>>>>>>> 6f75f05af05acc332e43bc3e4156debf4171bf83
```

'<<<<<<< HEAD' 부터 '=======' 사이의 구간이 현재 체크 아웃된 파일의 내용이고 '=======' 부터 '>>>>>>> exp' 사시의 구간이 병합하려는 대상인 exp 브랜치의 코드 내용입니다.  이 정보를 참고로해서 두개의 코드를 병합한 후에 특수기호들을 제거해주시면 됩니다. 작업이 끝나면 파일을 저장.

충돌 작업을 끝냈다는 것을 깃에게 알려줍니다. 
1
	
git add 'conflicted file name'

Change it to
```
* [003. 리눅스 운영체제 설치하기-Ubuntu Linux 설치](https://m.blog.naver.com/PostView.nhn?blogId=aimldl&logNo=221478627994&referrerCode=0&searchKeyword=linux)
```
and remove all the special characters, too.

```bash
$ git add computing_environments/linux_ubuntu/INSTALL.md 
```
