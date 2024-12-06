* Created: 2024-09-23 (Mon)

# flatpak

## Why `flatpak` was installed?
I wanted to install a photo editing app `gimp` and `flatpak` was required.

## Google search: how to install flatpak on chromebook terminal
Source: [Chrome OS Quick Setup > Follow these simple steps to start using Flatpak](https://flatpak.org/setup/Chrome%20OS)

On a terminal, install `flatpak`, add the Flathub repository and restart Linux. 
```
$ sudo apt install flatpak
$ flatpak --user remote-add --if-not-exists flathub https://dl.flathub.org/repo/flathub.flatpakrepo
```

## Verify the installation
After closing and then restarting the terminal,
```
$ which flatpak
/usr/bin/flatpak
$
```
