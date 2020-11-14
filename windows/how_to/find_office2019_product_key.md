* Draft: 2020-11-14 (Sat)
# 오피스 2019의 제품키 찾기 (Finding Office 2019 Product Key)
## 개요 (Overview)
윈도우 재설치를 위해 Office 2019 정품의 제품키가 필요한 상황입니다. 재설치 때 입력해야 하는 전체 제품키를 깔끔하게 찾아주는 `License Crawler` 프로그램을 이용합니다.

별도 프로그램을 설치하지 않고 윈도우의 기능 안에서 해결하려고 했지만, 결국 `License Crawler`를 쓰는 방법 만이 유일하게 정품 제품키를 찾게 해줬습니다.
* 참고: [How to view license key or serial number Office 2019](https://technowikis.com/1530/how-to-view-license-key-or-serial-number-office-2019)
* 마이크로소프트 홈페이지에서 권장하는 방법은 전혀 도움이 되지 않았습니다.
* 그 외의 웹검색 결과에서 권장하는 방식 중 윈도우10의 기능을 쓰는 방식으로는 전체 제품키를 찾을 수 없었습니다.
  * CMD에서 명령어를 입력하는 방법은
    * 마지막 4가지 숫자만 확인 가능
  * Record Editor (regedit)에서 확인하는 방법
    * binary값을 보여주므로 눈으로 확인하기 힘듭니다.

## `License Crawler` 프로그램을 쓰는 방법
이 프로그램은 `localhost`, 즉 설치된 컴퓨터의 운영체제 안에 있는 License를 검색해줍니다.
