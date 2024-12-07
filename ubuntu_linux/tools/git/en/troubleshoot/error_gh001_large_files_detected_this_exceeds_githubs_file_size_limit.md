* Draft: 2021-01-26 (Tue)
# remote: error: GH001: Large files detected  ... this exceeds GitHub's file size limit of 100.00 MB

## 개요
* 100MB보다 사이즈가 큰 파일은 푸쉬할 때 문제가 됩니다. 
* 예를 들어 `yolov3.weights`는 236.52MB라서 `git push`할 때 에러가 발생합니다.

```bash
remote: error: File npu_performance_validation/yolov3/keras/yolov3.weights is 236.52 MB; this exceeds GitHub's file size limit of 100.00 MB
```

## 문제
* 아래는 해당 파일을 지우고 난 다음에도 찌꺼기고 남아서 문제가 되는 경우입니다.
* `batch_git_push`는 여러 개의 `git 저장소`를 동시에 `git push`하는 bash script입니다.

```bash
$ ./batch_git_push
  ...
커밋할 사항 없음, 작업 폴더 깨끗함
cd /home/aimldl/github/projects
git add . && git commit -m 'Add new stuff by batch_git_push' && git push
현재 브랜치 master
브랜치가 'origin/master'보다 3개 커밋만큼 앞에 있습니다.
  (로컬에 있는 커밋을 제출하려면 "git push"를 사용하십시오)

커밋하도록 정하지 않은 변경 사항:
	수정함:        npu_performance_validation/yolov3/keras/keras-yolo3 (수정한 내용, 추적하지 않은 내용)

커밋할 변경 사항을 추가하지 않았습니다
$
```

* 문제가 된 디렉토리로 이동해서 수동으로 `git push`명령어를 실행해도 문제 해결이 되지 않습니다.
* 실제로는 사이즈가 큰 파일을 지웠지만 찌꺼기가 남은 경우입니다.

`(base) aimldl@aimldl-home-desktop:~/github/projects`에서 실행
```bash
$ cd ~/github/projects
$ git push
Username for 'https://github.com': aimldl
Password for 'https://aimldl@github.com': 
오브젝트 개수 세는 중: 25, 완료.
Delta compression using up to 8 threads.
오브젝트 압축하는 중: 100% (23/23), 완료.
오브젝트 쓰는 중: 100% (25/25), 220.14 MiB | 6.71 MiB/s, 완료.
Total 25 (delta 8), reused 0 (delta 0)
remote: Resolving deltas: 100% (8/8), completed with 2 local objects.
remote: error: GH001: Largremote: error: File npu_performance_validation/yolov3/keras/yolov3.weights is 236.52 MB; this exceeds GitHub's file size limit of 100.00 MBe files detected. You may want to try Git Large File Storage - https://git-lfs.github.com.
remote: error: Trace: d1c3b99050b114fa7742d01c560c98ec14ff3a9dcdb4a995e9cc99382084df0c
remote: error: See http://git.io/iEPt8g for more information.
remote: error: File npu_performance_validation/yolov3/keras/yolov3.weights is 236.52 MB; this exceeds GitHub's file size limit of 100.00 MB
To https://github.com/aimldl/projects.git
 ! [remote rejected]   master -> master (pre-receive hook declined)
error: 레퍼런스를 'https://github.com/aimldl/projects.git'에 푸시하는데 실패했습니다
$
```

## 힌트
TODO
