* Draft: 2020-05-25 (Mon)
# Windows Command Line Commands

For details, refer to [Command Line List and Reference](https://commandwindows.com/command3.htm).

By [*Vic Laurie*](https://commandwindows.com/author.htm), 출처: <https://commandwindows.com/command3.htm> 

| **Command**   | **Example**                                                  | **Description**                                              |
| ------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| assoc         | [details here](https://commandwindows.com/assoc.htm)         | Displays or modifies file name extension associations. Used alone**,** displays a list of all the current file name associations |
| at            |                                                              | Schedules commands and programs to run on a computer at a specified time and date. Requires the Schedule service. Superseded by *schtasks* |
| attrib        | [details here](https://commandwindows.com/command2.htm)      | Configures file attributes *read only, hidden, system*       |
| bootcfg       | [details here](http://vlaurie.com/computers2/Articles/bootini.htm) | Used to repair or edit the *boot.ini* file                   |
| cd or chdir   | cd folderpath                                                | Displays the name of the current directory or changes the current folder |
| chkdsk        | [details here](http://vlaurie.com/computers2/Articles/chkdsk.htm) | Checks hard drives for errors. With switches,does repairs.   |
| cls           | cls                                                          | Clears the screen                                            |
| copy          | copy somefile somefolder                                     | Copies a file from one location to another                   |
| del           | [details here](https://commandwindows.com/command2.htm)      | Deletes one or more files                                    |
| dir           | [details here](https://commandwindows.com/command2.htm)      | Displays a list of a folder's files and subfolders           |
| diskpart      | [details here](https://commandwindows.com/diskpart.htm)      | Disk management shell. A suite of various commands           |
| driverquery   | [Example here](https://commandwindows.com/tipsandtricks.htm#dq) | Displays a list of all installed device drivers and their properties. Requires administrator privileges. (Not available in Windows XP Home) |
| echo          | echo message                                                 | Used to display a message or to turn off/on messages in batch scripts |
| exit          | exit                                                         | Exits batch script or current command control                |
| fc            | fc file1 file2                                               | Compares two files and displays the differences between them |
| find          |                                                              | Searches for a text string in a file or files. Can also be used with output from another command. |
| findstr       |                                                              | Searches for text string patterns in a file using regular expressions |
| for           | [details here](https://commandwindows.com/batchfiles-iterating.htm) | Runs a specified command for each item in a set              |
| fsutil        | [details here](https://commandwindows.com/fsutil.htm)        | Displays and configures certain file system properties. A suite of various commands |
| ftype         | [details here](https://commandwindows.com/assoc.htm)         | Displays or modifies file types used in file name extension associations |
| getmac        | getmac                                                       | Returns the media access control (MAC) address for your network card |
| goto          | [details here](https://commandwindows.com/batchfiles-branching.htm) | Directs the Windows command interpreter to a labeled line in a batch program |
| if            | [details here](https://commandwindows.com/batchfiles-branching.htm) | Performs conditional processing in batch programs            |
| ipconfig      | [details here](https://commandwindows.com/tcpiputil.htm)     | Displays all current TCP/IP network configuration values and refreshes Dynamic Host Configuration Protocol (DHCP) and Domain Name System (DNS) settings |
| md or mkdir   | [details here](https://commandwindows.com/command2.htm)      | Creates a directory (folder) or subdirectory (subfolder)     |
| more          | [details here](https://commandwindows.com/filters.htm)       | Displays one screen of output at a time. Used with another command that has extensive output |
| move          | [details here](https://commandwindows.com/command2.htm)      | Moves a file from one folder to another                      |
| net           | [details here](https://commandwindows.com/netservices.htm)   | A suite of various networking and service commands           |
| netsh         | [details here](https://commandwindows.com/netsh.htm)         | Network services shell . Complex suite of commands.          |
| netstat       | [details here](https://commandwindows.com/netstat.htm)       | Displays active TCP connections, ports on which the computer is listening, Ethernet statistics, the IP routing table, statistics for the IP, ICMP, TCP, and UDP protocols |
| path          | [details here](http://vlaurie.com/computers2/Articles/environment.htm) | Sets the command path in the PATH environment variable, which is the set of directories used to search for executable files |
| pathping      | [details here](https://commandwindows.com/tcpiputil.htm)     | Provides information about network performance and conditions at intermediate hops between a source and destination |
| pause         | pause                                                        | Used in batch scripts                                        |
| ping          | [details here](https://commandwindows.com/tcpiputil.htm)     | Checks connectivity to other networked computers, routers, or Internet sites |
| popd          | popd                                                         | Pushd changes the directory and stores the previous directory. |
| pushd         | pushd somefolder                                             | Popd changes the current directory to the directory stored by the pushd command |
| powercfg      |                                                              | Manages the power settings such as hibernation. Has numerous switches |
| reg           | [details here](https://commandwindows.com/reg.htm)           | Adds, changes, and displays registry entries. A suite of various commands |
| rd or rmdir   | [details here](https://commandwindows.com/command2.htm)      | Deletes a directory (folder)                                 |
| ren or rename | [details here](https://commandwindows.com/command2.htm)      | Changes the name of a file or a set of files                 |
| sc            | [details here](https://commandwindows.com/sc.htm)            | Used to obtain information about services and to configure them. A suite of various commands |
| schtasks      |                                                              | Schedules commands and programs to run periodically or at a specific time |
| set           | details here and also here                                   | Displays, sets, or removes environment variables             |
| sfc           | sfc /scannow                                                 | System file checker scans and verifies the versions of all protected system files |
| shutdown      | [details here](http://vlaurie.com/computers2/Articles/shortcuts2.htm) | Shuts down or restarts a computer                            |
| sort          |                                                              | Alphabetizes strings from a text file or the output of a command. |
| start         | [details here](https://commandwindows.com/tipsandtricks.htm#startcommand) | Starts an application or opens a new command window          |
| subst         | [details here](https://commandwindows.com/command2.htm)      | Associates a folder with a drive letter                      |
| systeminfo    | systeminfo \| more                                           | Displays detailed configuration information about a computer and its operating system |
| taskkill      | [details here](https://commandwindows.com/taskkill.htm)      | Ends one or more tasks or processes                          |
| tasklist      | [details here](https://commandwindows.com/tasklist.htm)      | Displays a list of applications and services with their Process ID (PID) for all tasks running |
| tree          | tree somefolder                                              | Graphically displays the directory structure of a folder or drive |
| type          | type somefile.txt                                            | Displays the contents of a text file                         |
| vssadmin      | [details here](https://commandwindows.com/vssadmin.htm)      | For administering and configuring volume shadow copies       |
| xcopy         | [details here](https://commandwindows.com/xcopy.htm)         | Powerful command with many switches for copying and backing up files and folders |