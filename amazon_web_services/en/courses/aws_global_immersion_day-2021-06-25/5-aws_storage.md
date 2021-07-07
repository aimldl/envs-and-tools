* Draft: 2021-06-25 (Fri)

# AWS Storage



떳따가 사라질 수 있다. 다른 곳에 생성될 수 있다.

Modern Apps

* 컨테이너, 서버리스

### AWS 스토리지 서비스

* 다양한 종류의 스토리지 서비스
  * 스토리지 타입
    * 블록: EBS
    * 파일: EFS, FSx for Windows File Server, FSx for Lustre
    * 오브젝트: S3, S# Glacier
  * 백업: Backup
* 폭넓은 데이터 마이그레이션 서비스
  * 인터넷 망을 통한 마이그레이션
    * Storage Gateway, DataSync, Transfer Family
  * 오프라인으로 마이그레이션
    * Snowmobile, Snoball, Snowcone

### 스토리지 타입

* 블록 스토리지
  * 데이터를 일정 크기의 블록으로 나누어 저장
  * 호스트에서 파일 시스템을 생성
  * SAN (Storage Area Network)
* 파일 스토리지
  * 디렉토리 구조로 파일을 저장
  * 스토리지단에서 파일 시스템을 생성
  * NAS
* 오브젝트 스토리지
  * REST 기반의 API호출을 통해 데이터에 접근
  * HTTP 프로토콜

## Amazon EBS

* EBS는 EC2에서 사용하도록

### Amazon EBS의 특징

* 고가용성
  * 99.999%의 가용성 제공
  * EBS 쓸 때는 꼭 백업해야한다
* 안정성
  * 모든 EBS 볼륨 유형은 암호화를 지원
* 확장성
  * 애플리케이션 중단없이 볼륨 유형 변경 가능
  * 볼륨 크기 확장 가능
* 성능
  * 낮은 지연 시간 제공
  * 일정한 I/O를 유지

### Amazon EBS 볼륨 타입

* Provisioned IOPS SSD (io1/io2)
* General-purpose SSD (gp2/gp3) (디폴트)
* Throughput-optimized HDD (st1)
  * 빅데이터, 분석
  * 대량의 데이터셋
* Cold HDD (sc1)
  * 자주

### Amazon EBS gp3

General Purpose SSD

* gp2
* 볼륨당 최대 250 MB/S
* 3 IOPS /GB
* $0.10 /GB
* gp3
  * GB당 비용이 20% 절감됨
  * 볼륨당 최대 
  * 3,000 IOPS (baseline) 기본 성능
  * 

I3

D2에만 지원된다





### Amazon EFS

* 안정적이고 비용 효과적인 클라우드 네이티브 NFS 파일 스토리지 서비스
* 탄력적인 확장, 고가용성, 손쉬운 운영, 고성능 제공, 비용 최적화, 하이브리드 구성

### EFS 활용 사례

[NAS이므로 파일 공유 용도로 쓰면 된다]

### AWS의 다양한 서비스와 호환

* Compute의 영구적인 스토리지로 사용 가능하다

### Amazon EFS 고가용성 아키텍처

* EFS는 여러 AZ에 걸쳐서 생성되어 고가용성을 보장함

### Amazon EFS Infrequent Acess (IA) 및 가격 체계

* 수명 주기 관리를 활성화하면 정책에 따라 파일이 IA로 자동 이동

* Standard 스토리지 클래스
  * 일반 파일 스토리지 $0.30/GB (월)
* IA 스토리지 클래스 
  * 자주 사용되지 않는 파일에 대해서는 비용 절감
  * $0.025/GB (월)
  * $0.01/GB (요청 기준)

### xxx

AWS DataSync



## Amazon FSx for Windows File Server

### Amazon FSx for Windows File Server



단일 가용 영역

다중 가용 영역

* 복수의 가용 영역 간 ...



## Amazon FSx for Lustre

### Amazon FSx for Lustre

* 컴퓨팅 워크로드를 위한



Lustre 오픈소스 기반 



## Amazon S3

* 최초의 AWS 서비스
* 최대 파일 사이즈 = 5T



데이터는 3곳 이상의 AZ에 저장

S3의 내구성:99.999999999% (11x9s)

### Amazon S3 스토리지 클래스

S3 Standard (2006)

S3 Glacier (2012) , 빙하 아카이브 용도

* 아카이브를 읽어오는데 시간이 걸린다

S3 Standard-IA (2015), Infrequent Acess

S3 One Zone-IA (2018)

S3 Intelligent-Tiering (2018), ML기반으로 standard <-> IA를 편리하게

S3 Glacier Deep Archive (2019)

* 차이: Glacier보다 

3만원이하/한달

### Amazon S3 Storage Lens

* 가시성
  * 오브젝트 스토리지에 대한 가시성을 제공
* 분석 솔루션
  * Summar
  * Outlier

### Amazon S3 쓰기 후 강력한 읽기 일관성

* Hadoop에서 