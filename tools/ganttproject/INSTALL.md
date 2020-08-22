##### aimldl/computing_environments/ganttproject/INSTALL.md

## Installing GanttProject on Linux
1. Download the installation file at [Download GanttProject](https://www.ganttproject.biz/download). You may choose free download or buy for $5+.
<img src='images/GanttProject-Download_GanttProject.png'>

An example to check the downloaded installation file is below.
```bash
~/Downloads$ ls
ganttproject_2.8.10-r2364-1_all.deb
~/Downloads$
```
2. Install the .deb file with the dpkg command. The -i option is to install.
```bash
~/Downloads$sudo dpkg -i ganttproject_2.8.10-r2364-1_all.deb 
```
For example,
```bash
~/Downloads$sudo dpkg -i ganttproject_2.8.10-r2364-1_all.deb 
Selecting previously unselected package ganttproject.
(Reading database ... 222763 files and directories currently installed.)
Preparing to unpack ganttproject_2.8.10-r2364-1_all.deb ...
Unpacking ganttproject (2.8.10-1) ...
Setting up ganttproject (2.8.10-1) ...
gtk-update-icon-cache: Cache file created successfully.
Processing triggers for mime-support (3.60ubuntu1) ...
Processing triggers for shared-mime-info (1.9-2) ...
~/Downloads$ 
```
3. Launch GanttProject.
```bash
~/Downloads$ ganttproject &
```

<img src='images/GanttProject-launch_the_program.png'>

## Comment
The following commands fail, but the program launches without a problem.

```bash
~/Downloads$ ganttproject --version
~/Downloads$ com.beust.jcommander.ParameterException: Unknown option: --version
	at com.beust.jcommander.JCommander.parseValues(JCommander.java:551)
	at com.beust.jcommander.JCommander.parse(JCommander.java:231)
	at com.beust.jcommander.JCommander.parse(JCommander.java:214)
	at com.beust.jcommander.JCommander.<init>(JCommander.java:172)
	at net.sourceforge.ganttproject.GanttProject.main(GanttProject.java:967)
	at net.sourceforge.ganttproject.application.MainApplication.run(MainApplication.java:37)
	at org.bardsoftware.impl.eclipsito.ApplicationLauncher.launchApplication(ApplicationLauncher.java:29)
	at org.bardsoftware.impl.eclipsito.BootImpl$2.run(BootImpl.java:50)
Jan 26, 2020 7:20:14 AM net.sourceforge.ganttproject.GPLogger log
INFO: Program terminated
^C
~/Downloads$ ganttproject --help
~/Downloads$ com.beust.jcommander.ParameterException: Unknown option: --help
	at com.beust.jcommander.JCommander.parseValues(JCommander.java:551)
	at com.beust.jcommander.JCommander.parse(JCommander.java:231)
	at com.beust.jcommander.JCommander.parse(JCommander.java:214)
	at com.beust.jcommander.JCommander.<init>(JCommander.java:172)
	at net.sourceforge.ganttproject.GanttProject.main(GanttProject.java:967)
	at net.sourceforge.ganttproject.application.MainApplication.run(MainApplication.java:37)
	at org.bardsoftware.impl.eclipsito.ApplicationLauncher.launchApplication(ApplicationLauncher.java:29)
	at org.bardsoftware.impl.eclipsito.BootImpl$2.run(BootImpl.java:50)
Jan 26, 2020 7:20:27 AM net.sourceforge.ganttproject.GPLogger log
INFO: Program terminated
^C
```
