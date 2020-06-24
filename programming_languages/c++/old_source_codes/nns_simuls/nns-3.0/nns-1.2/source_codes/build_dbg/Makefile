# Makefile
#
#    This file should be in the same directory where the source codes are stored.
#    - Compilation
#    To compile these files, run `make` in directory either bld_dbg or bld_opt.
#    These two sub-directories "bld_opt" and "bld_dbg" stand for "build the optim" and "build for debugging".
#    Both of the directories have Makefile which include Makefile.in in directory cpp_files.
#    Refer to the following directory structure.
#    
#    	\source_codes
#          Make.in
#    	   \build_dbg
#    	     Makefile
#    	   \build_opt
#    	     Makefile
#    
#    The reason why we maintain two separate directories is because it is possible to compile in the two directories 
#    simultaneously because the compiled results are stored in the two separate directories.
#    
# Version: 1.2
# Last updated:  Mar.6, 2011 (Sun)
# First written: Feb.22, 2008 (Fri)
#
# Written by Tae-Hyung D. Kim, mrtonnet [at] gmail [dot] com

# May 12, 2009 (Tue)
# nns.exe is used instead of nns in order to use an IDE Eclipse
# because Eclipse does not recognize an exeutable with an extension .exe.

# Mar.6, 2011 (Sun)
# Change for the version-up to 1.2
# File name changed from nns-${VERSION}-full.exe to nns-${VERSION}-dbg.exe

VERSION = 1.2
FILE_EXE = nns-${VERSION}-dbg.exe
CXXFLAGS = -ggdb

include ../Makefile.in
