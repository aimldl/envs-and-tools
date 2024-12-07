* Draft: 2021-06-25 (Fri)

# AWS Compute

AWS Core Service 중 가장 기본

## 목차

* EC2 개요
* EC2 인스턴스 타입
* EC2 인스턴스 선택
* 컴퓨팅 관련 추가 서비스들

## EC2 개요

가상 서버 인스턴스

* Amazon EC2

관리형 EC2 클러스터 위에서 실행되는 컨테이너 오케스트레이션 서비스

* Amazon EKS

* Amazon FARGATE

이벤트 트리거로 stateless 코드를 실행하는 서버리스 컴퓨팅

* AWS LAMBDA

### EC2

* AWS 가용영역의 물리서버
* 게스트1, 게스트2, ..., 게스트 n
* 하이퍼바이저
* 호스트 서버

Linux | WIndows | MAC

ARM | x86 아키텍쳐

범용 및 특정 워크로드용

베어메탈, 디스크 네트워크 성능

packages

여러가지 구매 옵션: 온디맨드, 예약 인스턴스, 스팟, 세이빙 플랜



### AMI (Amazone Machine Image)

[Virtual Box 생각하면 된다. 한 대를 설정하고 난 다음 custom AMI 하는 방법 핸즈온?]

* 인스턴스를 Launch할 때 필요한 정보를 제공
* 하나의 AMI로 여러 개의 인스턴스를 시작 가능
* AMI에는 다음과 같은 정보가 있음
  * 루트 볼륨을 구성하는 템플릿 (OS, 어플리케이션 등)
  * 인스턴스에 연결되는 볼륨의 블록 디바이스 매핑

Amazon EC2 인스턴스 스토어

물리 호스트 머신 (EC2 instances, 인스턴스 스토어)

* 인스턴스의 로컬 저장소 (휘발성)
* 임시 데이터 저장소
* 데이터 복제 미 지원
* Snapshot 미 지원
* SSD 또는 HDD

### Amazon EBS

* 블록 스토리지
* API를 이용하여 생성, 연결, 수정
* 워크로드에 따라 스토리지 및 컴퓨팅 선택
* 하나의 EBS 볼륨은 하나의 인스턴스에만 연결
* ...
* EBS volume
  * EBS SSD-backend volumes
  * EBS HDD-backend volumes
  * EBS 스냅샷 (Amazon S3)

### EC2 인스턴스 수명 주기

* 실행 중 (Running)
* 정지됨 (Stopped)
* 종료됨 (Terminated)

[그림]

Q: 블록 스토리지 vs. 인스턴스 스토어 의 IO 속도

* 블록 스토리지도 굉장히 빠르다
* 블록 스토리지



### Amazon EC2 Instance Types

#### AWS 혁신의 속도

2020: 400여개의 인스턴스 타입 신규 출시

* 160+ new launches
* 100 new instances
* 130+ new feature releases

#### 광범위하고 세분화된 플랫폼 선택

* 분류
* Capabilities
* Options

크게 5가지 정도로 분류 가능

범용, 컴퓨팅, 메모리, 스토리지, 가속화

#### Linux

* Linux distros
* Amazon Linux 2
  * CentOS 기반, AWS에서 직접 관리

#### Windows on AWS

* Windows 워크로드를 위한 가장 인기있고 안전하며 신뢰할 수 있는 클라우드 플랫폼
* BIOL (Bring Your Own Licence)라고 기존 보유 라이센스 사용 가능

[MS만큼 지원하는지는 모르겠다]



#### Amazon EC2 Mac Instance: Apple 개발자를 위한 인스턴스

* 2020에 추가됨

#### 범용 워크로드

* M타입
* T타입 (버스트 타입 프리티어로 사용 가능, )

웨/앱서버, 엔터프라이즈 앱, 게임 서버, 캐시 클러스터, 분석 애플리케이션, 개발/테스트 환경

#### 컴퓨팅 집약적인 워크로드

* C타입

배치 프로세싱, 분산 컴퓨팅 분석, 고성능 컴퓨턴 HPC, 광고 게시, 멀티 플레이어 게임, 비디오 인코딩

#### 메모리 집약적인 워크로드

* R 타입, X타입
* 인메모리 캐시
* 고성능 데이터베이스
* 빅데이터 분석

#### 컴퓨팅 가속화 워크로드

P타입, G타입

머신러닝/AI, 구성능 컴퓨팅, 그래픽스

스토리지 집약적인 워크로드

* I타입: 높은 I/O 성능
* D타입:
* 높은 I/O: 고성능 데이터베이스, 실시간 분석, 트랜잭션 워크로드, NoSQL 데이터베이스
* 고밀도 스토리지: 빅데이터, 데이터 웨어하우스, ... [추가할 것]



#### 인스턴스 유형 세부 정보

https://aws.amazon.com/ko/ec2/instance-types

## Amazon EC2 인스턴스 선택

[400 여개 인스턴스가 있으므로 ]

### Amazo EC2 인스턴스 표기법

CPU, Memory, Storage, Network performance

인스턴스 유형: 패밀리, 세대, 추가 기능. 크기, 예: M5d.xlarge

d는 4개의 NVME이 적용된 유형

### EC2 인스턴스 추가 기능 표시

프로세서

g: AWS Graviton 프로세서

AMD EPYC 프로세서

스토리지 및 네트워크

* d: 빠른 로컬 NVMe 스토리지

* n: 최대 100Gbps 네트워크 성능

성능

e ... 추가

최신 세대의 인스턴스를 선택하세요

#### 인스턴스 크기

xlarge 8시간 운영하는 비용 = 8xlarge 1시간 운영하는 비용

성능도 차이가 별로 없는 것 같다

c4.8xlarge ~ 2xc4.4xlarge

인스턴스를 최대한 적게 만들어서 빠르게 확장성 있게 사용하는게 효율적이다

* 작은 인스턴스 단위로 구성하는게 낫다
* 프로젝트 초기에는 작은 단위로 시작하는 것을 권고

#### Amazon EC2 인스턴스이 크기

* 작은 인스턴스 vs. 큰 인스턴스
* 50% 절약 

#### 최적의 인스턴스 선택

* 최적의 인스턴스를 어떻게 선택해야 할까요?
* 언제든지 인스턴스를 바꿀 수 있다
  * 다운 타임 발생

#### 최적의 인스턴스 및 크기 선택

* Cost Explorer (서비스)
  * 지난 14일간의 최대 CPU 및 메모리 사용 기록에 기반
  * 동일한 인스턴스 패밀리 내의 EC2 인스턴스 적정 크기 권장
* AWS Compute Optimizer
  * 최적의 AWS 리소스를 권장하는 머신러닝 깁나 서비스
  * ... [to write]

#### Amazon EC2 구매 옵션

* 온디맨드 (사용한 만큼 지불한다)
  * 장기 약정 없이 초 단위로 컴퓨팅 용량 지불
  * 갑작스럽거나 예측할 수 없는 워크로드, 수요 정의
* 예약 인스턴스
  * 1년 또는 3년 약정으로 온디맨드 가격에서 대폭 할인
  * 확약 및 예측 가능한 안정적인 수요
* 세이빙 플랜
  * 예약 인스턴스와 같은 할인에 좀 더 높은 유연성
  * EC2 및 Fargate에 대해 저렴한 요금을 제공하는 유연한 요금 모델
* 스팟 인스턴스
  * 여분의 EC2 용량으로 온디맨드 가격에서 최대 90% 할인 제공
  * 내결함성, 유연성, 상태 비저장 워크로드
  * (의사와 다르게 끊길 수 있다. 하지만 갑자기 끊지는 않는다.)

#### 비용 최적화

장기적으로 사용하는 안정적인 워크로드 --> 예약 인스턴스 또는 세이빙 플랫 -> 비용 절감

급중하는 stateful 워크로드의 스케일링은 온디멘드 인스턴스

* 룰은 만들 수 있을 것 같다. 예: AWS CLI에서 가능할 듯...

#### Elastic Load Balancing

* 애플리케이션 트래픽을 Amazon EC2
* 인스턴스, 컨테이너, IP주소, Lambda
* 함수와 같은 여러 대상에 자동으로 분산

#### ELB: Options

* Gateway Load Balancer
* Application Load Balancer
  * IPv4
  * Layer 7 switch
  * HTTP, HTTPS
* Network Load Balancer
  * IPv4
  * Layer 4 switch (성능이 좋다 초당 수백 request까지 처리 가능)
  * 급격한 traffic spike가 예상되는 경우
  * TCP, UDP, TLS
* (Classic Load Balancer)

(여러가지 옵션 가능 session sticky option)

#### Amazon EC2 Auto Scaling

변화하는 수요에 동적으로 대응하고 비용을 최적화

Fleet management 기능

* 비정상 인스턴스 교체
* Auto Scaling group을 지정해서 ELB가 헬스체크를 해서 

Dynamic scaling

* 수요에 맞게 확장
* 생성해놓은 Threshold를 넘어가면 지정한 AMI를 런칭

#### Instance Connect

* SSH (Secure Shell)를 사용하여 인스턴스에 연결
* 인스턴스에 댛나 SSH 액세스 제어 및 SSH 키 공유/관리가 필요 없음
* AWS CloudTrail 로깅을 통해 연결 요청을 감시

#### 인스턴스 시작 시 사용자 데이터로 명령 실행

* 일반적인 구성 작업을 자동으로 수행
  * 쉘 스크립트 방식
  * cloud-init 명령 방식

#### 시작 템플릿 (launch templates)으로 인스턴스 시작

시작을 간소화하고 단순화하기 위해 시작 요청을 템플릿화

시작 파라미터

* 일관된 경험, 단순한 권한, ...

#### Amazon CloudWatch

* AWS 리소스 및 애플리케이션의 모니터링 및 관찰 기능
* 로그, 지표 및 이벤트 형태로 ㅗ니터링 및 운영 테이터를 수집
* AWS 리소스, 애플리케이션 및 서비스에 대한 통합 뷰
* 이상 동작 감지
* 경보 설정
* 로그와 지표 시각화

(GPU 리소스 모니터링 가능)

#### Q&A

Q: 리전 선택 기준이 있나?

서울 대비 Oregon가격이 1/3인데, 같은 경우도 있고

A: 물리적 latency가 중요하지 않는다면 Oregon을 쓰는게 좋지 않나?











## EC2 인스턴스 타입

## EC2 인스턴스 선택

## 컴퓨팅 관련 추가 서비스들

