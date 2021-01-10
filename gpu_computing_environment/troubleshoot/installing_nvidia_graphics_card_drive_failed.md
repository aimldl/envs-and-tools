









```bash
$ sudo ubuntu-drivers autoinstall
[sudo] aimldl의 암호: 
패키지 목록을 읽는 중입니다... 완료
의존성 트리를 만드는 중입니다       
상태 정보를 읽는 중입니다... 완료
몇몇 패키지를 설치할 수 없습니다. 요청한 상황이 불가능할 수도 있고,
불안정 배포판을 사용해서 일부 필요한 패키지를 아직 만들지 않았거나,
아직 Incoming에서 나오지 않은 경우일 수도 있습니다.
이 상황을 해결하는데 다음 정보가 도움이 될 수도 있습니다:

다음 패키지의 의존성이 맞지 않습니다:
 linux-modules-nvidia-460-generic-hwe-20.04-edge : 의존: nvidia-kernel-common-460 (>= 460.32.03) 하지만 460.27.04-0ubuntu1 패키지를 설치할 것입니다
 nvidia-driver-460 : 의존: libnvidia-compute-460 (= 460.27.04-0ubuntu1) 하지만 460.32.03-0ubuntu0.20.04.1 패키지를 설치할 것입니다
                     의존: libnvidia-decode-460 (= 460.27.04-0ubuntu1) 하지만 %s 패키지를 설치하지 않을 것입니다
                     의존: libnvidia-encode-460 (= 460.27.04-0ubuntu1) 하지만 %s 패키지를 설치하지 않을 것입니다
                     추천: nvidia-settings 하지만 %s 패키지를 설치하지 않을 것입니다
                     추천: nvidia-prime (>= 0.8) 하지만 %s 패키지를 설치하지 않을 것입니다
                     추천: libnvidia-compute-460:i386 (= 460.27.04-0ubuntu1)
                     추천: libnvidia-decode-460:i386 (= 460.27.04-0ubuntu1)
                     추천: libnvidia-encode-460:i386 (= 460.27.04-0ubuntu1)
                     추천: libnvidia-ifr1-460:i386 (= 460.27.04-0ubuntu1)
                     추천: libnvidia-fbc1-460:i386 (= 460.27.04-0ubuntu1)
                     추천: libnvidia-gl-460:i386 (= 460.27.04-0ubuntu1)
E: 문제를 바로잡을 수 없습니다. 망가진 고정 패키지가 있습니다.
$
```

