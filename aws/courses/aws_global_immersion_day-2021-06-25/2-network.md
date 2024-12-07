* Draft: 2021-06-25 (Fri)

AWS VPC 개요

구성

On-prem 네트워크 연결

Transit GateWay

Amazon VPC 정의

VPC (Virtual Private Cloud)



AWS

VPC

가용영역a

퍼블릭 서브넷

프라이빗 서브넷

완전한 네크워크 제어 가능

IP 범위, Subnet, Route Table 등

VPC 생성 순서

* 마법사를 통해서 하게 됨
  * 리전 선택 및 IP주소 범위 설정
  * 인터넷 게이트웨이 생성
  * 가용 영역 내에 필요한 서브넷 정의
  * 라우팅 구성
  * VPC로 송수신되는 트래픽 제어

VPC 생성: 이전 선택

* 현재 서울 리전은 4개의 AZ이 있음

VPC 생성: 주소 범위 설정

CIDR (사이더 표기법)을 사용

CIDER 블록 설정

RFC 1918에 정의된 사설 IP대역 사용 권고

VPC CIDR은 생성 후 변경 불가능

VPC의 네트워크 범위는 /16 ~/28까지 가능

향후 직접 연결할 가능성이 있는 네트워크와 주소가 중복되지 않도록 권고



(참고) 주소 범위 CIDER 이해하기

IP주소를 4개 블록으로 나눠서 표기

/16~/28로 마스킹

예: 192.168.0.0/16, 192.168까지 고정하고 뒷부분을 자유롭게 사용



VPC 생성 : 서브넷 정의

집만들 때 방 만드는 것과 유사함

고가용성을 보장하기 위해서는 AZ 여러개를 사용해야 한다.

VPC 생성: 서브넷 정의 및 IPv4 주소 대역 할당

/24는 3자리까지 마스킹



Internet traffic 인터넷 트래픽을 위한 5가지 고려 요소

1. 공인 IP주소
2. IGW (Internet Gateway)와 VPC 연결
3. 인터넷 게이트웨이로 라우팅 구성
4. NACL (Network Access Control List) 구성
5. Security Group 허용 정책 구성

NACL: stateless (나가는 것과 들어오는 것을 명시적으로 표기해야 함)

Security Group: stateful



EC2 인스턴스를 위한 공인 IP주소

* 공인 IP주소의 자동 할당
* EIP (Elastic IP addresses)
  * 계정에 할당된 고정 IP
  * Q: stop했을 떄는 돈 안 나가나?



xxx

VPC 생성: 인터넷 게이트웨이 생성 및 설정

* 인터넷 게이트웨이
* 라우팅 테이블

IPv4 0.0.0./0의 목적지 인터넷 게이트웨이



VPC 생성: 라우팅 구성

* Public subnet
  * Q: ::/0
* Private subnet

퍼블릭



NAT (Network Address translation) Gateway

* private subnet을 위해 public subnet에 NAT GW 설정
* private subnet <-> public subnet (NAT Gateway) <-> Internet Gateway



VPC 생성: VPC로 송수신되는 트래픽 제어

* 네트워크 제어: 네트워크 ACL (NACL), 보안그룹
* 네크워크 ACL
* 보안 그룹

네크워크 ACLs

* 정책: ALLOW, DENY와 같다
* 리눅스의 ip.allow와 같지는 않다. ()

보안 그룹 - Inbound

* Security group의 chaining을 해서
* Web server (TCP/8443)만 오픈
* Application Server는 Custom TCP Rule TCP/8443만 오픈하면 된다

보안 그룹 - Outbound

* NACL의 prefixLists



AWS VPC 연결

VPC 간 연결 방법 1 - 인터넷 게이트웨이를 통한 연결

* 외부 인터넷을 통해서 나가는 경우

VPC간 연결 방법 2 - 동일 리전 PC peering

* 외부로 나가지 않는 경우
  * VPC Peering을 통한 연결
  * Create Peering Connection를 사용
    * Requester - Accepter 설정이 필요

VPC peering 구성 전에 알아두어야 할 것들

* 같은 리전의 VPC Peer 에서 Security Group  참조 가능
* DNS Host Name
* IP 주소 대역 중복 할당 불가능
* 양방향 Peering 불가능
  * Traversal peering이 안 된다는 뜻 (삼각형으로)
* VPC Peering에서 Jumbo Frame

* 

ㅌㅌㅌ

AWS Transit Gateway -  간편한 멀티 VPC 접근 모델

* 많을 경우에 모두 Mesh로 peering을 엮어야 하나?
* Transit Gateway에서 



VPC Endpoint

Gateway VPC endpoints

* 리전 단위로 서비스를 제공하는 S3, DynamoDB와 같은 서비스와 연결할 경우
  * 일반적으로 인터넷 게이트웨이로 연결
    * 민감한 정보라서 인터넷을 거치고 싶지 않은 경우
  * Gateway VPC Endpoint를 통해서 직접 연결 가능
    * Route Table에 직접 설정한다
    * VPC 단위로 설정

Interface VPC endpoints (AWS PrivateLink)

* 녀ㅠㅜㄷㅅ eksdnlfh dusruf rksmd



(네크워크 관련 추가 서비스)

VPC flow logs

* Amazon CloudWatch Logs / S3
* 성능/응답시간에 영향 없음
* VPC, Subnet, ENI에 적용 가능
* 허용, 거부



IP pool관리를 하기 위해서 subnetting을 한다

예: EC2와 Lambda를 쓸 때, Lambda가 scale-out할 경우 문제가 발생할 수 있다.

IP충돌이 난다는 뜻인가? A: IP자원이 모자랄 수 있다. 별도 subnet을 가지면 자원이 모자라는 문제를 경감할 수 있다.