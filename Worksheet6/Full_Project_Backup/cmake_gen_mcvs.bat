@echo OFF
REM cmake_gen_msvc.bat ----------------------------------------------
REM Make sure this file is in the system path
REM Overwrite the path with minimal path to the correct compiler and Qt tools
REM This avoids problems if multiple (32 and 64bit) versions of MinGW have been installed
set PATH=%PATH%;C:\Qt\6.2.0\msvc2019_64\bin;C:\VTK-9.1.0\msvcVTK-9.1.0\bin
REM Invoke cmake, telling it where the correct version of Qt is located
cmake -DCMAKE_PREFIX_PATH="C:\VTK-9.1.0\msvcVTK-9.1.0;C:\Qt\6.2.0\msvc2019_64"-G"Visual Studio 16 2019" ..
REM ------------------------------------------------------------------