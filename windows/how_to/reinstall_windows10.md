* Draft:2020-11-14 (Sat)

# 초기화를 선택해서 윈도우 10 재설치하기 (How to Reinstall Windows 10)
## 개요 (Overview)
윈도우 10이 설치된 환경에서 시스템이 느려져서 재설치를 하고자 합니다. 윈도우 설치를 처음부터 하게 되면
* 윈도우10의 라이센스 키 및
* 오피스 도구의 라이센스 키
를 알아내야 하고, 설치를 위한 부팅가능한 USB메모리 (Bootable USB Memory)를 만들고, 설치파일을 다운로드 받는 등의 번거로운 절차를 거쳐야 합니다.

윈도우 10에 초기화를 선택해서 재설치하는 기능이 있습니다. 
* 이 기능을 이용하면 윈도우 설치에 필요한 아래의 절차없이 운영환경을 재설치할 수 있어서 편리합니다.
  * 윈도우 10 라이센스 키
  * 오피스 도구의 라이센스 키
  * 설치 파일 다운로드
  * 부팅가능한 USB메모리로 윈도우 설치파일 준비
* 재설치 전에 오피스 도구가 설치되어 있고, 라이센스 키를 활성화한 상태라면 윈도우 10 재설치 후
  * 오피스 아이콘을 눌러서 재설치하는 것만으로도 바로 오피스를 쓸 수 있습니다.
  * 즉, 오피스 라이센스 키 입력 절차가 필요 없습니다.

## 재설치 하기

<img src='images/win10-control_panel-update&security-backup-initialize_this_pc.png'>

깔끔하게 시작하려면 '모든 항목 제거'를 선택합니다.
<img src='images/win10-control_panel-update&security-backup-initialize_this_pc-select_option.png'>

'다시 설정'을 선택합니다. 새로 설정한다는 것이 아니라 다음으로 넘어간다는 뜻입니다.
<img src='images/win10-control_panel-update&security-backup-initialize_this_pc-ready_to_initialize.png'>

윈도우즈 초기화가 진행되면서 진행률이 보여집니다. 시스템 사양에 따라 다르지만 약 1시간 정도 걸립니다.
<img src='images/win10-control_panel-update&security-backup-initialize_this_pc-initializing.png'>

* 설치가 진행되며 50%와 같이 진행율이 보이는 동안은 윈도우가 켜져 있는 상태로 웹브라우저 등 다른 프로그램을 정상적으로 사용할 수 있습니다.
* 진행이 다 끝나고 재부팅이 되면 윈도우 설치창과 같은 화면이 나옵니다. 일반적인 윈도우 설치와 같이 선택하면서 설치를 진행하면 됩니다.
* 오피스 도구를 쓸려면 시작메뉴에서 오피스 아이콘을 눌려서, 프로그램의 다운로드 등을 해줘야 합니다.
  * 라이센스 키를 입력하는 절차가 생략되므로, 윈도우 10을 처음부터 설치한 후 오피스 도구를 설치하는 것보다는 편리합니다.
