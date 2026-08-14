@echo off
rem compile.cmd - Build 2H4U with GCC under ArcaOS
rem
rem Requires SDL2 from ANPM.
rem   anpm install SDL2-devel SDL2_image-devel SDL2_mixer-devel SDL2_ttf-devel
rem
rem Usage: compile.cmd

set EMXOMFLD_TYPE=WLINK
set EMXOMFLD_LINKER=wl.exe
set EMXOMFLD_PRELINK=0
set EMXOMFLD_SYSTEM=os2v2_pm

make -f makefile.os2 clean
make -f makefile.os2 2>&1 | tee compile.log

echo.
echo Build complete. See compile.log for details.