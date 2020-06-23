* Rev.1: 2020-06-23 (Tue)
* Draft: 2019-10-10 (Tue)
# How to Configure Korean on Ubuntu (18.04)
## Open the `Settings > Region & Language` menu
There are two ways to open the menu.

### Option 1: Click and move to the `Region & Language` menu
Click the dropdown menu, `Settings` and then `Region & Language`

#### Step 1. Click the down arrow on the top right corner.
<img src="images/ubuntu_18_04-top_right_corner-menu.png">

#### Step 2. Click the `Settings` icon on the left bottom of the dropdown menu.
<img src="images/ubuntu_18_04-drop_down_menu-icons-settings.png">

#### Step 3. Click `Region & Language` on the left menu (when the `Settings` window is open)
<img src="images/ubuntu_18_04-settings-region_and_language.png">

### Option 2: Search and launch the `Region & Language` menu
Click `Show Applications`, search for `Region & Language` and click 

#### Step 1. Click the `Show Applications` menu on the bottom left corner.
<img src="images/ubuntu_18_04-show_applications_button.png">

And the following menu is open.
<img src="images/ubuntu_18_04-show_applications-menu.png">

#### Step 2. Search for `Region & Language` in the search box
<img src="images/ubuntu_18_04-show_applications-search_box-region.png">

And the search results are shown like below.
<img src="images/ubuntu_18_04-show_applications-search_box-region-result.png">

<img src="images/">



## Install
```bash
$ sudo apt install -y language-pack-ko
$ sudo apt install -y korean*
```

<img src="images/">
<img src="images/">
<img src="images/">


## Configure ibus
Launch the `IBus Preferences` window. Note this window cannot be launched from the `Settings > Region & Language` menu.
```bash
$ ibus-setup
```
<img src="images/ubuntu-configure_korean-ibus_preferences-launch_window.png">

## Troubleshoot
만약 설치를 끝내고 난 후에도 목록에 한국어가 없다면 Install/Remove Languages에서 설치된 Korean을 지우고 동일한 방법으로 설치하시면 됩니다.

## References
* [[Ubuntu] Ubuntu 18.04 LTS 한글 설치 및 설정](https://gabii.tistory.com/entry/Ubuntu-1804-LTS-%ED%95%9C%EA%B8%80-%EC%84%A4%EC%B9%98-%EB%B0%8F-%EC%84%A4%EC%A0%95)
* [[UBUNTU] 18.04에서 한글 입력 및 한영키 사용](https://tobelinuxer.tistory.com/15)
