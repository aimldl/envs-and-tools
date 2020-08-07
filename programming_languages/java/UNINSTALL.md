* Draft: 2020-08-07 (Fri)

# How to Uninstall Java

## Check the existing Java installation
```
$ dpkg --list | grep java
ii  gir1.2-javascriptcoregtk-4.0:amd64         2.28.4-0ubuntu0.18.04.1                          amd64        JavaScript engine library from WebKitGTK+ - GObject introspection data
ii  gjs                                        1.52.5-0ubuntu18.04.1                            amd64        Mozilla-based javascript bindings for the GNOME platform
ii  java-common                                0.68ubuntu1~18.04.1                              all          Base package for Java runtimes
ii  libgjs0g                                   1.52.5-0ubuntu18.04.1                            amd64        Mozilla-based javascript bindings for the GNOME platform
ii  libjavascriptcoregtk-4.0-18:amd64          2.28.4-0ubuntu0.18.04.1                          amd64        JavaScript engine library from WebKitGTK+
iF  oracle-java11-installer-local              11.0.8-1~linuxuprising0                          amd64        Oracle Java(TM) Development Kit (JDK) 11
$
```

## Remove it with `apt`
```bash
$ sudo apt remove oracle-java11-installer-local
```

## References
* [How to Install Oracle Java 13 in Ubuntu 18.04, 16.04, 19.04](http://ubuntuhandbook.org/index.php/2019/10/how-to-install-oracle-java-13-in-ubuntu-18-04-16-04-19-04/)
