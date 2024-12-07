##### aimldl > computing_environments > ubuntu_linux > commands > README.md
* Rev.1: None
* Draft: 2019-02-12 (Tue)
#### Remove Every Other Line
Commands are summarized below. For details, refer to [How to delete every second line from a file?](https://unix.stackexchange.com/questions/219859/how-to-delete-every-second-line-from-a-file).
##### sed
```bash
$ sed -e n\;d < file_name
```
##### AWK
```bash
$ awk 'FNR%2' < file_name
```
##### Perl
```bash
$ perl -ne 'print if $. % 2' < file_name
```
#### Several Topics on My Blog
* [Removing every other line. 한 줄 띄워 한 줄 제거하기](https://aimldl.blog.me/221571889094).
* [1.awk로 빈 줄을 지우고, 2.Python 으로 정렬](https://aimldl.blog.me/221584703463)
* [Symbolic Link를 이용해서 즐겨찾기 (Favorites) 만들기](https://aimldl.blog.me/221577596405)

(EOF)
