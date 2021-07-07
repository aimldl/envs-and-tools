* Draft: 2021-06-25 (Fri)

# Database

## 목차

데이터 트렌드

Amazon RDS

Amazon Aurora

AWS 데이터 서비스

AWS 데이터베이스 마이그레이션 서비스 (DMS)

AWS SCT (Schema Conversion Tool)



## 데이터 트렌드

* 폭발적인 데이터 증가
  * 매 5년마다 약 10배 증가하는 데이터
* Micro-services로 변화된 데이터, 분석 요구
  * 목적에 맞게 구축된 데이터베이스는 최적화된 성능 및 비용 절감을 제공
* 빠른 변화율
  * Dev/Ops 도입으로 인한 변화율 증가
    * 이전: 한 달에 한번 > 요즘에 더 잦음

## 데이터에서 더 많은 가치를 얻기 위해 고객 분들은

완전관리형 데이터베이스 서비스로 이전

목적에 맞게 구축된 데이터베이스로 최신 애플리케이션 구축

Legacy 데이터베이스에서 벗어나려는 시도

## 자체 관리 데이터베이스 및 분석 서비스 단점

하드웨어 및 소프트웨어 설치, 구성, 패치, 백업

성능 및 가용성 이슈

컴퓨팅 및 스토리지 용량 계획 및 클러스터 확장

보안 및 규정 준수

AWS의 완전 관리형 데이터베이스 서비스

자체 관리 vs. 완전 관리

* You: 스키마 디자인, 쿼리 구성, 쿼리 최적화
* AWS:

완전 관리형 데이터베이스로 마이글레이션

RDB:

Non-RDB: mongoDB > DocumentDB

Cassandra > keysspaces

## 데이터에서 더 많은 가치를 얻기 위해 고객 분들은...

목적에 맞게 구축된 데이터테이스

## 목적에 맞게 구축된 데이터테이스

Relational ...

## The Pokemon Company

## Legacy 상업용 데이터베이스

[문제점] 비싼 가격, 소유권, Lock-in, 징벌적 라이센싱, 잦은 감사 (audio)

## 삼성전자 

Solution: 레거시 오라클 IDC 솔루션을 Amazon Aurora로 마이그레이션

## Amazon RDS

가장 많이 선호하는 6가지 데이터베이스 엔진을 갖춘 관계형 데이터베이스

Amazon Aurora, MySQL, PostgreSQL, MariaDB, Microsoft SQL Server, Oracle DB

### 운영 편의성

AWS 관리 콘설이나 AWS CLI, 간단한 API 호출 등으로 모든 관계형 DB 관리 기능

운영 편의성 - Provision

몇 분 만에 서비스에 필요한 데이터베이스 구성

상면, 서버, 네트워크, OS 설치, DB 설치 등...

### 모니터링

DB 인스턴스에 대한 CloudWatch 지표 모니터링

DB로그를 CloudWatch logs에 직접 upload

Enhanced  모니터링

* 시스템 수준 지표 모니터링, 1초단위까지 지표 수집

3rd party 모니터링툴과 통합 가능

### 경보 (Alarm)

Amazon SNS (Simple Notification Service)를 통해 RDS에서 이벤트 발생 시 경보

### 성능 개선 도우미 (Performance Insights)

* 

RDS의 주요 버틀넥이 IOPS이다 > Provisions IOPS 선택 가능

### 빠른 성능과 보안 - Security

AWS KMS (Key Managed Service)

TDE

* SSL 보호 사용

## Amazon Aurora

### Amazon Aurora: 오픈소스 호환, ...

* MySQL, PostgreSQL 호환

### 확장, 분산형 아키텍쳐

* Instance node와 데이터 스토리지 layer를 분리함

### 전통적인 데이터 복제 방식

Primary instance - Standby instance

### Amazon Aurora의 데이터 복제 방식

### Aurora 서버리스 (PostgreSQL, MySQL)

* 서버리스이므로 instance가 보이지 않아 관리포인트가 줄어든다

### Aurora 글로벌 데이터베이스

* DR을 위해 원격 

### 빠른 계정 간 데이터베이스 복제

[예: 조직간 계정이 다른 경우]

### Amazon Aurora ML

* Amazon SageMaker & Amazon Comprehend와의 간단하고 최적화된 안전한 통합

### Amazon RDS Proxy

* RDS가 fail되도 RDS proxy가 대응 가능
* Connection Pooling
* 많은 수의 애플리케이션 연결 지원
* 여러 AZ에 배포되며 연결이 끊어지지 않고 장애 조치
* AWS Secrets Manager, IAM과 통합
* 콘솔에서 몇 ...

### Aurora MySQL 멀티 마스터

* 멀티 마스터로 지속적 가용성 확보

## AWS 데이터 서비스

## AWS 데이터베이스 마이그레이션 서비스 (DMS)

* 관리형 데이터 마이그레이션 서비스
* 동종 및 이기종 데이터 복제 지원
* 소스 데이터베이스의 변동사항 지속 복제 (CDC)
* 인스턴스 ...

## AWS SCT (Schema Conversion Tool)

* 기존 데이터베이스 스키마를 다른 데이터베이스 엔진 스키마로 변환