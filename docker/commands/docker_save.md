* Draft: 2021-02-09 (Tue)

# [docker save](https://docs.docker.com/engine/reference/commandline/save/)

컨테이너를 파일로 저장하는데 쓰입니다.

> ## Examples
>
> **Create a backup that can then be used with `docker load`.**
>
> ```bash
> $ docker save busybox > busybox.tar
> $ ls -sh busybox.tar
> 2.7M busybox.tar
> 
> $ docker save --output busybox.tar busybox
> $ ls -sh busybox.tar
> 2.7M busybox.tar
> 
> $ docker save -o fedora-all.tar fedora
> $ docker save -o fedora-latest.tar fedora:latest
> ```
>
> **Save an image to a tar.gz file using gzip**
>
> You can use gzip to save the image file and make the backup smaller.
>
> ```bash
> docker save myimage:latest | gzip > myimage_latest.tar.gz
> ```
>
> ### Cherry-pick particular tags
>
> You can even cherry-pick particular tags of an image repository.
>
> ```bash
> $ docker save -o ubuntu.tar ubuntu:lucid ubuntu:saucy
> ```



도커 이미지를

```bash
$ docker images
REPOSITORY      TAG                       IMAGE ID      CREATED            SIZE
aimldl/darknet  gpu_cudnn_opencv_version  4b159247967d  About an hour ago  6.51GB
  ...
$
```

`export`하려면 에러가 발생합니다. 이럴 경우 `save`를 써야 합니다.

```bash
$ docker export aimldl/darknet:gpu_cudnn_opencv_version > darknet_gpu_cudnn_opencv_version.tar
Error response from daemon: No such container: aimldl/darknet:gpu_cudnn_opencv_version
$ docker save aimldl/darknet:gpu_cudnn_opencv_version > darknet_gpu_cudnn_opencv_version.tar
$
```



Google search: ubuntu 파일 사이즈가 너무 큽니다.

[파일이 너무 커서 대상 파일 시스템에서 사용할 수 없습니다. 해결법](https://ykarma1996.tistory.com/15)



[docker image를 tar 파일로 저장 (export / import / save / load)](https://www.leafcats.com/240)

> (중요) export - import 와 save - load의 차이
>
> docker export의 경우 컨테이너를 동작하는데 필요한 모든 파일이 압충된다. 즉, tar파일에 컨테이너의 루트 파일시스템 전체가 들어있는 것이다. 반면에 docker save는 레이어 구조까지 포함한 형태로 압축이 된다.
>
> 즉, 기반이 되는 이미지가 같더라도 export와 save는 압축되는 파일 구조와 디렉터리가 다르다.
>
> 결론은 export를 통해 생성한 tar 파일은 import로, save로 생성한 파일은 load로 이미지화 해야 한다.



