ERROR-git_push.md

2019-11-15 (Fri) 16:00
```bash
remote: Resolving deltas: 100% (57/57), completed with 3 local objects.
remote: warning: File dropbox/1-installation/physionet_ECG_data-master.zip is 66.85 MB; this is larger than GitHub's recommended maximum file size of 50.00 MB
remote: error: GH001: Large files detected. You may want to try Git Large File Storage - https://git-lfs.github.com.
remote: error: Trace: 1ca6c17b5a6021abe81137fe57b1a7d4
remote: error: See http://git.io/iEPt8g for more information.
remote: error: File dropbox/1-installation/matlab_R2019a_glnxa64.zip is 130.32 MB; this exceeds GitHub's file size limit of 100.00 MB
To https://github.com/aimldl/matlab.git
 ! [remote rejected] master -> master (pre-receive hook declined)
error: 레퍼런스를 'https://github.com/aimldl/matlab.git'에 푸시하는데 실패했습니다
```

```bash
cd /home/aimldl/aimldl/python3
git add . && git commit -m 'Add new stuff by batch_git_push' && git push
warning: adding embedded git repository: topics/medium/Building a Dead Simple Speech Recognition Engine using ConvNet in Keras/DeadSimpleSpeechRecognizer
hint: You've added another git repository inside your current repository.
hint: Clones of the outer repository will not contain the contents of
hint: the embedded repository and will not know how to obtain it.
hint: If you meant to add a submodule, use:
hint: 
hint: 	git submodule add <url> topics/medium/Building a Dead Simple Speech Recognition Engine using ConvNet in Keras/DeadSimpleSpeechRecognizer
hint: 
hint: If you added this path by mistake, you can remove it from the
hint: index with:
hint: 
hint: 	git rm --cached topics/medium/Building a Dead Simple Speech Recognition Engine using ConvNet in Keras/DeadSimpleSpeechRecognizer
hint: 
hint: See "git help submodule" for more information.


^C
```

```bash
(base) aimldl@GPU-Desktop:~/aimldl/python3$ git rm --cached topics/medium/Building\ a\ Dead\ Simple\ Speech\ Recognition\ Engine\ using\ ConvNet\ in\ Keras/DeadSimpleSpeechRecognizer/
fatal: pathspec 'topics/medium/Building a Dead Simple Speech Recognition Engine using ConvNet in Keras/DeadSimpleSpeechRecognizer/' did not match any files
```
