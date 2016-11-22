@ECHO OFF
SET VSVERSION=14
SET SRCDIR=%CD%
CD ..

CD %SRCDIR%
IF exist build-vs%VSVERSION% goto HAVEDIR
mkdir build-vs%VSVERSION%
:HAVEDIR
cd build-vs%VSVERSION%
"%ProgramFiles(x86)%\CMake\bin\cmake.exe" -G "Visual Studio %VSVERSION%" -DCMAKE_MODULE_PATH="%SRCDIR%/cmake/Modules" -DCMAKE_SUPPRESS_REGENERATION=TRUE ..
PAUSE
