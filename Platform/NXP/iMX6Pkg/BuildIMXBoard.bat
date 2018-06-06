::
::  Copyright (c), Microsoft Corporation. All rights reserved.
::
::  This program and the accompanying materials
::  are licensed and made available under the terms and conditions of the BSD License
::  which accompanies this distribution.  The full text of the license may be found at
::  http://opensource.org/licenses/bsd-license.php
::
::  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
::  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
::
::  Important Note: This script has to run from EDK2 root dir
::

@echo off
setlocal enableextensions disabledelayedexpansion

pushd %~dp0\..
set EDKROOT_DIR=%cd%

set GCC_TOOLCHAIN=GCC49
set WINGCC_TOOLCHAIN=WINGCC49
set TARGET=RELEASE
set DEFINES=
set COMPILE_PROCESSOR_COUNT=%NUMBER_OF_PROCESSORS%

:: Parse options
:GETOPTS
 if /I "%~1" == "/?" goto USAGE
 if /I "%~1" == "/h" goto USAGE
 if /I "%~1" == "/Help" goto USAGE
 if /I "%~1" == "/Debug" set TARGET=DEBUG
 if /I "%~1" == "/Secure" set DEFINES=%DEFINES% -D CONFIG_SECURE_UEFI=1
 if /I "%~1" == "/NoParallel" set COMPILE_PROCESSOR_COUNT=1
 if /I "%~2" == "" set BOARD_NAME=%~1
 shift
if not (%1)==() goto GETOPTS

if "%BOARD_NAME%"=="" goto USAGE
if "%BOARD_NAME:~0,1%"=="/" goto USAGE

:: If GCC_TOOLCHAIN_DIR environment variable is not set, a default path to the
:: GCC toolchain will be assumed.
if "%GCC_TOOLCHAIN_DIR%"=="" set GCC_TOOLCHAIN_DIR=%EDKROOT_DIR%\..\ToolChains\Arm%GCC_TOOLCHAIN%
set PATH=%EDKROOT_DIR%\BaseTools\Bin;%EDKROOT_DIR%\BaseTools\Bin\Win32;%GCC_TOOLCHAIN_DIR%\bin;%PATH%;

set %WINGCC_TOOLCHAIN%_ARM_PREFIX=arm-none-eabi-
call %EDKROOT_DIR%\edksetup.bat
if %ERRORLEVEL% neq 0 exit /b 1

build -p iMX6Pkg\Boards\%BOARD_NAME%\%BOARD_NAME%.dsc -a ARM -b %TARGET% -t %WINGCC_TOOLCHAIN% -n %COMPILE_PROCESSOR_COUNT% %DEFINES%

exit /b 0

:USAGE
echo Error: Invalid usage
echo Usage:  BuildiMXBoard.bat [/debug] [/secure] [/noparallel] ^<BOARD_NAME^>
echo.
echo    /debug      Build a debug version of UEFI. Otherwise release.
echo    /secure     Enable UEFI security features: Authenticated Variables, 
echo                SecureBoot, and fTPM. Otherwise, these features will
echo                not be enabled.
echo    /noparallel Perform single threaded compilation, otherwise perform
echo                parallel compilation with numbers of threads equal to
echo                available number of CPU cores.
echo.
echo NOTE: UEFI must run in NormalWorld after a TEE like OPTEE has initialized
echo SecureWorld and transitioned to normal world.
echo.
echo List of supported boards to use for ^<BOARD_NAME^>:
dir  iMX6Pkg\Boards /b

exit /b 1