* Rev.1: 2020-06-23 (Tue)
* Draft: 2019-10-10 (Tue)
# How to Configure Korean on Ubuntu (18.04)
## 1. Open the `Settings > Region & Language` menu
There are two ways to open the menu.

### 1.1. Click and move to the `Region & Language` menu
Click the dropdown menu, `Settings` and then `Region & Language`

#### Step 1. Click the down arrow on the top right corner.
<img src="images/ubuntu_18_04-top_right_corner-menu.png">

#### Step 2. Click the `Settings` icon on the left bottom of the dropdown menu.
<img src="images/ubuntu_18_04-drop_down_menu-icons-settings.png">

#### Step 3. Click `Region & Language` on the left menu (when the `Settings` window is open)
<img src="images/ubuntu_18_04-settings-region_and_language.png">

### 1.2. Search and launch the `Region & Language` menu
Click `Show Applications`, search for `Region & Language` and click 

#### Step 1. Click the `Show Applications` menu on the bottom left corner.
<img src="images/ubuntu_18_04-show_applications_button.png">

And the following menu is open.
<img src="images/ubuntu_18_04-show_applications-menu.png">

#### Step 2. Search for `Region & Language` in the search box
<img src="images/ubuntu_18_04-show_applications-search_box-region.png">

And the search results are shown like below.
<img src="images/ubuntu_18_04-show_applications-search_box-region-result.png">

#### Step 3. Click `Region & Language` next to `Settings`
And the `Region & Language` window is launched.

<img src="images/ubuntu_18_04-settings-region_and_language.png">

## 2. Install language packs
In `Settings > Region & Language` presented above, click `Manage Installed Languages` to launch the `Language Support` window shown below.

<img src="images/ubuntu_18_04-settings-region_and_language-manage_installed_languages-language_support.png">

Click the `Install/Remove Languages...` button and the `Installed languages` are shown.
<img src="images/ubuntu_18_04-settings-region_and_language-manage_installed_languages-initial_window.png">

Scroll down to find `Korean`, check the box for Korean, and click the `Apply` button.
<img src="images/ubuntu_18_04-language_support-installed_languages-korean.png">

The `Applying changes` window pops up and installation begins.

Alternatively, you may run the following commands, but not enough to set up everything.
```bash
$ sudo apt install -y language-pack-ko
$ sudo apt install -y korean*
```

A pop-up window `The language support is not installed completely` may open when the `Language Support` window is open again. If so, click `install` and install the language support completely.

<img src="images/ubuntu_18_04-language_support-the_language_support_is_not_installed_completely.png">

## 3. Configure IBus
#### Step 1. Log out & log back in or reboot the system
#### Step 2. Set `Keyboard input method system` to `IBus`
<img src="images/ubuntu_18_04-settings-region_and_language-manage_installed_languages-language_support.png">

#### Step 3. Open a terminal and launch the `IBus Preferences` window.
Note this window cannot be launched from the `Settings > Region & Language` menu.
```bash
$ ibus-setup
```
<img src="images/ubuntu-configure_korean-ibus_preferences-launch_window.png">

#### Step 4. Click the `Input Method` tab and the `Add` button
<img src="images/ubuntu_18_04-ibus_preferences-input_method.png">

`IBus Preferences > Input Method -> Add` launches the `Select an input method` window.
<img src="images/ubuntu_18_04-ibus_preferences-input_method-add.png">

#### Step 4. 

https://github.com/aimldl/technical_skills/tree/master/computing_environments/linux_ubuntu/how_to/images


<img src="images/">
<img src="images/">



<img src="images/">

If no search result is shown, the language packs are not installed properly. Go back to the previous step and fix the problem first.
<img src="images/ubuntu_18_04-ibus_preferences-input_method-add-search-korean-no_search_result.png">

<img src="images/">
<img src="images/">


## Troubleshoot
만약 설치를 끝내고 난 후에도 목록에 한국어가 없다면 Install/Remove Languages에서 설치된 Korean을 지우고 동일한 방법으로 설치하시면 됩니다.

## References
* [[Ubuntu] Ubuntu 18.04 LTS 한글 설치 및 설정](https://gabii.tistory.com/entry/Ubuntu-1804-LTS-%ED%95%9C%EA%B8%80-%EC%84%A4%EC%B9%98-%EB%B0%8F-%EC%84%A4%EC%A0%95)
* [[UBUNTU] 18.04에서 한글 입력 및 한영키 사용](https://tobelinuxer.tistory.com/15)
* [[Ubuntu 18.04] 한글 입력 추가 및 한영키 사용 설정](https://greedywyatt.tistory.com/105)
