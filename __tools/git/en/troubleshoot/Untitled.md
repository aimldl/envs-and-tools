* Draft: 2020-11-05 (Thu)



```

```

```bash
~/github$ git add .
fatal: (현재 폴더 또는 상위 폴더 중 일부가) 깃 저장소가 아닙니다: .git
~/github$ cd text_summarization_in_korean/
~/github/text_summarization_in_korean$ git add .
~/github/text_summarization_in_korean$ git commit - 'Add new stuff'
error: pathspec '-' did not match any file(s) known to git.
error: pathspec 'Add new stuff' did not match any file(s) known to git.
~/github/text_summarization_in_korean$ git commit -m 'Add new stuff'
현재 브랜치 main
브랜치가 'origin/main'보다 6개 커밋만큼 앞에 있습니다.
  (로컬에 있는 커밋을 제출하려면 "git push"를 사용하십시오)

커밋할 사항 없음, 작업 폴더 깨끗함
~/github/text_summarization_in_korean$ git push
Username for 'https://github.com': aimldl
Password for 'https://aimldl@github.com': 
오브젝트 개수 세는 중: 52, 완료.
Delta compression using up to 12 threads.
오브젝트 압축하는 중: 100% (51/51), 완료.
오브젝트 쓰는 중: 100% (52/52), 115.55 MiB | 1.29 MiB/s, 완료.
Total 52 (delta 17), reused 0 (delta 0)
remote: Resolving deltas: 100% (17/17), completed with 1 local object.
remote: error: GH001: Large files detected. You may want to try Git Large File Storage - https://git-lfs.github.com.
remote: error: Trace: f86ccfb248062e7e18c15daffb52a9cad172f41498c22e4eafa4d899bb5b331c
remote: error: See http://git.io/iEPt8g for more information.
remote: error: File project-extraction_of_korean_news/dataset/추출요약/train.jsonl is 112.83 MB; this exceeds GitHub's file size limit of 100.00 MB
To https://github.com/aimldl/text_summarization_in_korean.git
 ! [remote rejected] main -> main (pre-receive hook declined)
error: 레퍼런스를 'https://github.com/aimldl/text_summarization_in_korean.git'에 푸시하는데 실패했습니다
~/github/text_summarization_in_korean$ ls
LICENSE  README.md  images  project-extraction_of_korean_news  survey
~/github/text_summarization_in_korean$ cd project-extraction_of_korean_news/
~/github/text_summarization_in_korean/project-extraction_of_korean_news$ ls
README.md  dataset  dataset.md  ideas.md  images  notebooks
~/github/text_summarization_in_korean/project-extraction_of_korean_news$ cd dataset/
~/github/text_summarization_in_korean/project-extraction_of_korean_news/dataset$ ls
extractive_sample_submission.csv  test.jsonl  train.tar.xz  추출요약.zip
~/github/text_summarization_in_korean/project-extraction_of_k~/github/text_summarization_in_korean/project-extraction_of_k_news/dataset$ git pull origin master
Username for 'https://github.com': aimldl
Password for 'https://aimldl@github.com': 
fatal: Couldn't find remote ref master
~/github/text_summarization_in_korean/project-extraction_of_korean_news/dataset$ git pull origin main
Username for 'https://github.com': aimldl
Password for 'https://aimldl@github.com': 
https://github.com/aimldl/text_summarization_in_korean URL에서
 * branch            main       -> FETCH_HEAD
이미 업데이트 상태입니다.
~/github/text_summarization_in_korean/project-extraction_of_korean_news/dataset$ git add .
~/github/text_summarization_in_korean/project-extraction_of_korean_news/dataset$ git commit -m "Fix the file size error"
현재 브랜치 main
브랜치가 'origin/main'보다 6개 커밋만큼 앞에 있습니다.
  (로컬에 있는 커밋을 제출하려면 "git push"를 사용하십시오)

커밋할 사항 없음, 작업 폴더 깨끗함
~/github/text_summarization_in_korean/project-extraction_of_korean_news/dataset$ git push
Username for 'https://github.com': aimldl
Password for 'https://aimldl@github.com': 
오브젝트 개수 세는 중: 52, 완료.
Delta compression using up to 12 threads.
오브젝트 압축하는 중: 100% (51/51), 완료.
오브젝트 쓰는 중: 100% (52/52), 115.55 MiB | 3.76 MiB/s, 완료.
Total 52 (delta 17), reused 0 (delta 0)
remote: Resolving deltas: 100% (17/17), completed with 1 local object.
remote: error: GH001: Large files detected. You may want to try Git Large File Storage - https://git-lfs.github.com.
remote: error: Trace: b50679bad0972586e7e7b3aae423a3f90c4c64ec05e538c9b2abce3fdce528c3
remote: error: See http://git.io/iEPt8g for more information.
remote: error: File project-extraction_of_korean_news/dataset/추출요약/train.jsonl is 112.83 MB; this exceeds GitHub's file size limit of 100.00 MB
To https://github.com/aimldl/text_summarization_in_korean.git
 ! [remote rejected] main -> main (pre-receive hook declined)
error: 레퍼런스를 'https://github.com/aimldl/text_summarization_in_korean.git'에 푸시하는데 실패했습니다
~/github/text_summarization_in_korean/project-extraction_of_korean_news/dataset$ 

```

