# makefile
# Created by IBM WorkFrame/2 MakeMake at 0:37:54 on 30 June 1999
#
# The actions included in this make file are:
#  Compile::C++ Compiler
#  Link::Linker

.SUFFIXES: .c .obj 

.all: \
    .\sysinfo.exe

.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /Ss /Ti /C %s

{e:\data\c\sysinfo}.c.obj:
    @echo " Compile::C++ Compiler "
    icc.exe /Ss /Ti /C %s

.\sysinfo.exe: \
    .\sysinfo.obj \
    {$(LIB)}os2386.lib \
    {$(LIB)}sysinfo.def
    @echo " Link::Linker "
    icc.exe @<<
     /B" /de"
     /Fesysinfo.exe 
     os2386.lib 
     sysinfo.def
     .\sysinfo.obj
<<

.\sysinfo.obj: \
    e:\data\c\sysinfo\sysinfo.c
