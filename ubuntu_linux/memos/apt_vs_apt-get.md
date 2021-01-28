*

# apt vs. apt-get

Google search: apt vs apt-get

* [Difference Between apt and apt-get Explained](https://itsfoss.com/apt-vs-apt-get-difference/), 2019-06-11

> `apt` command replaces `apt-get` and `apt-cache` command options
>
> | apt command      | the command it replaces | function of the command                              |
> | :--------------- | :---------------------- | :--------------------------------------------------- |
> | apt install      | apt-get install         | Installs a package                                   |
> | apt remove       | apt-get remove          | Removes a package                                    |
> | apt purge        | apt-get purge           | Removes package with configuration                   |
> | apt update       | apt-get update          | Refreshes repository index                           |
> | apt upgrade      | apt-get upgrade         | Upgrades all upgradable packages                     |
> | apt autoremove   | apt-get autoremove      | Removes unwanted packages                            |
> | apt full-upgrade | apt-get dist-upgrade    | Upgrades packages with auto-handling of dependencies |
> | apt search       | apt-cache search        | Searches for the program                             |
> | apt show         | apt-cache show          | Shows package details                                |
>
> | new apt command  | function of the command                                  |
> | :--------------- | :------------------------------------------------------- |
> | apt list         | Lists packages with criteria (installed, upgradable etc) |
> | apt edit-sources | Edits sources list                                       |

> ### Is apt-get deprecated?
>
> I didn’t find any information that says that apt-get will be discontinued. And it actually shouldn’t be. It still has a lot more functionalities to offer than apt.
>
> ### Should I use apt or apt-get?
>
> You might be thinking if you should use apt or apt-get. And as a regular Linux user, my answer is to go with apt.