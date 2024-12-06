- Updated: 2024-10-04 (Fri)
- Created: 2024-10-04 (Fri)

# OpenShot (Video Editor)
OpenShot Video Editor is a free and open-source video editor for Windows, macOS, Linux, and ChromeOS.
- Homepage: https://www.openshot.org/videos/

[OpenShot 3.0 Released | First Look](https://youtu.be/JHiDOBWXQH8?si=Ug2crgvZX9dJnXiK) /[0:44/]

# Install
## OpenShot Video Editor > [Installation](https://www.openshot.org/static/files/user-guide/installation.html) > [Chrome OS (Chromebook)](https://www.openshot.org/static/files/user-guide/installation.html#chrome-os-chromebook)

## For Chromebook
```bash
$ sudo apt install -y libfuse2
$ bash <(wget -O - http://openshot.org/files/chromeos/install-stable.sh)
```
The message should look like:
```bash
Redirecting output to ‘wget-log’.

Installing Openshot on Chrome OS [stable].........
- Installing dependencies.........................
  [ This might take a while... please be patient ]
  ...
INFO main_window: ---------------- Shutting down -----------------
INFO thumbnail: Shutting down thumbnail server: ('127.0.0.1', 44529)
INFO logger_libopenshot: Shutting down libopenshot logger
INFO updates: Remove listener from UpdateManager: <windows.preview_thread.PreviewParent object at 0x7fda5c1e7af0>
INFO app:             OpenShot's session ended            
INFO app:             Fri Oct  4 13:51:30 2024            
INFO app: ================================================
$
```
OpenShot will be automatically launched.

<img src="../../images/openshot_lauched_for_the_first_time.png">

### Expected error without `libfuse2`
With running the following command, 
```bash
$ sudo apt install -y libfuse2
```
the expected error is
```bash
$ bash <(wget -O - http://openshot.org/files/chromeos/install-stable.sh)
Redirecting output to ‘wget-log’.

Installing Openshot on Chrome OS [stable].........
  ...
- Make AppImage executable........................
- OpenShot installed successfully.................
- Running OpenShot................................
dlopen(): error loading libfuse.so.2

AppImages require FUSE to run. 
You might still be able to extract the contents of this AppImage 
if you run it with the --appimage-extract option. 
See https://github.com/AppImage/AppImageKit/wiki/FUSE 
for more information
$
```

