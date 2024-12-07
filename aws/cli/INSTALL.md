* Draft: 2020-04-05 (Sun)

# AWS CLI 설치 및 설정하기

Python과 pip이 이미 설치된 상황을 가정합니다.

* 참고문서
  * 공식 문서는 [AWS CLI 사용 설명서](https://docs.aws.amazon.com/ko_kr/cli/latest/userguide/cli-chap-welcome.html)입니다.
  * 기본 설치 및 설정에 대한 설명은 [AWS CLI 설치 및 구성 (공식 문서) ](https://docs.aws.amazon.com/ko_kr/streams/latest/dev/kinesis-tutorial-cli-installation.html)을 참고
  * 복수의 프로필 설정 등 보다 구체적인 내용은 [AWS CLI 구성 (공식 문서)](https://docs.aws.amazon.com/ko_kr/cli/latest/userguide/cli-chap-configure.html)을 참고

## AWS CLI 설치하기

```
$ curl "https://bootstrap.pypa.io/get-pip.py" -o "get-pip.py"
$ sudo python get-pip.py
$ sudo pip install awscli
```

## AWS CLI 설정하기

```
$ aws configure
AWS Access Key ID [None]: AKIAIOSFODNN7EXAMPLE
AWS Secret Access Key [None]: wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY
Default region name [None]: us-west-2
Default output format [None]: json
$
```

## AWS CLI 업그레이드하기

```
$ pip install awscli --upgrade --user
```



## 다수의 사용자 프로파일 설정하기

상세한 내용은 [AWS CLI 구성](https://docs.aws.amazon.com/ko_kr/cli/latest/userguide/cli-chap-configure.html)을 참고하세요. 

### 새로운 IAM 사용자 크레덴셜 생성하기



### 여러 프로파일 생성



$ aws configure --profile produser

--profile profilename을 지정하고 해당 이름으로 저장된 자격 증명 및 설정을 사용

