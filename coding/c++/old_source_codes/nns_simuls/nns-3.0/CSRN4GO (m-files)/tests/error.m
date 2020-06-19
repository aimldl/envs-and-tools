tk424@r99dwunsch:~$ cd ~/Work/MagicExample/
tk424@r99dwunsch:~/Work/MagicExample$ ls
magicsquare      magicsquare.m       magicsquare_mcc_component_data.c
magicsquare.ctf  magicsquare_main.c  mccExcludedFiles.log
tk424@r99dwunsch:~/Work/MagicExample$ ./magicsquare(5)
bash: syntax error near unexpected token `5'
tk424@r99dwunsch:~/Work/MagicExample$ ./magicsquare 5
./magicsquare: error while loading shared libraries: libmwmclmcrrt.so.7.2: canno t open shared object file: No such file or directory
tk424@r99dwunsch:~/Work/MagicExample$ ./magicsquare
./magicsquare: error while loading shared libraries: libmwmclmcrrt.so.7.2: cannot open shared object file: No such file or directory
tk424@r99dwunsch:~/Work/MagicExample$ ./magicsquare -h
./magicsquare: error while loading shared libraries: libmwmclmcrrt.so.7.2: cannot open shared object file: No such file or directory
tk424@r99dwunsch:~/Work/MagicExample$ ./magicsquare -help
./magicsquare: error while loading shared libraries: libmwmclmcrrt.so.7.2: cannot open shared object file: No such file or directory
tk424@r99dwunsch:~/Work/MagicExample$ ./magicsquare
./magicsquare: error while loading shared libraries: libmwmclmcrrt.so.7.2: cannot open shared object file: No such file or directory
tk424@r99dwunsch:~/Work/MagicExample$
