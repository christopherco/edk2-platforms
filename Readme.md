This branch holds all platforms actively maintained against the
[edk2](https://github.com/tianocore/edk2) master branch.

For generic information about the edk2-platforms repository, and the process
under which _stable_ and _devel_ branches can be added for individual platforms,
please see
[the introduction on the about branch](https://github.com/tianocore/edk2-platforms/blob/about/Readme.md).

# INDEX
* [Overview](#overview)
* [How To Build (Linux Environment)](#how-to-build-linux-environment)
   * [Manual building](#manual-building)
   * [Using uefi-tools helper scripts](#using-uefi-tools-helper-scripts)
* [How To Build (Windows Environment)](#how-to-build-windows-environment)
* [Supported Platforms](#supported-platforms)
* [Maintainers](#maintainers)

# Overview

Platform description files can be found under `Platform/{Vendor}/{Platform}`.

Many platforms require additional image processing beyond the EDK2 build.
Any such steps should be documented (as a Readme.md), and any necessary helper
scripts be contained, under said platform directory.

Any contributions to this branch should be submitted via email to the
edk2-devel mailing list with a subject prefix of `[platforms]`. See
[Laszlo's excellent guide](https://github.com/tianocore/tianocore.github.io/wiki/Laszlo's-unkempt-git-guide-for-edk2-contributors-and-maintainers) for details
on how to do this successfully.

# How to build (Linux Environment)

## Prerequisites
The build tools themselves depend on Python (2) and libuuid. Most Linux systems
will come with a Python environment installed by default, but you usually need
to install uuid-dev (or uuid-devel, depending on distribution) manually.

## If cross compiling
If building EDK2 for a different archtecture than the build machine, you need to
obtain an appropriate cross-compiler. X64 (x86_64) compilers also support IA32,
but the reverse may not always be true.

Target architecture | Cross compilation prefix
--------------------|-------------------------
AARCH64             | aarch64-linux-gnu-
ARM                 | arm-linux-gnueabihf-
IA32                | i?86-linux-gnu-* _or_ x86_64-linux-gnu-
IPF                 | ia64-linux-gnu
X64                 | x86_64-linux-gnu-

\* i386, i486, i586 or i686

### GCC
Linaro provides GCC toolchains for
[aarch64-linux-gnu](https://releases.linaro.org/components/toolchain/binaries/latest/aarch64-linux-gnu/)
and [arm-linux-gnueabihf](https://releases.linaro.org/components/toolchain/binaries/latest/arm-linux-gnueabihf/)
compiled to run on x86_64/i686 Linux and i686 Windows. Some Linux distributions
provide their own packaged cross-toolchains.

### clang
Clang does not require separate cross compilers, but it does need a
target-specific binutils. These are included with any prepackaged GCC toolchain
(see above), or can be installed or built separately.

## Obtaining source code
1. Create a new folder (directory) on your local development machine
   for use as your workspace. This example uses `/work/git/tianocore`, modify as
   appropriate for your needs.
   ```
   $ export WORKSPACE=/work/git/tianocore
   $ mkdir -p $WORKSPACE
   $ cd $WORKSPACE
   ```

1. Into that folder, clone:
   1. [edk2](https://github.com/tianocore/edk2)
   1. [edk2-platforms](https://github.com/tianocore/edk2-platforms)
   1. [edk2-non-osi](https://github.com/tianocore/edk2-non-osi) (if building
      platforms that need it)
   ```
   $ git clone https://github.com/tianocore/edk2.git
   ...
   $ git clone https://github.com/tianocore/edk2-platforms.git
   ...
   $ git clone https://github.com/tianocore/edk2-non-osi.git
   ```

1. Set up a **PACKAGES_PATH** to point to the locations of these three
   repositories:

   `$ export PACKAGES_PATH=$PWD/edk2:$PWD/edk2-platforms:$PWD/edk2-non-osi`

## Manual building

1. Set up the build environment (this will modify your environment variables)

   `$ . edk2/edksetup.sh`

   (This step _depends_ on **WORKSPACE** being set as per above.)
1. Build BaseTools

   `make -C edk2/BaseTools`

   (BaseTools can currently not be built in parallel, so do not specify any `-j`
   option, either on the command line or in a **MAKEFLAGS** environment
   variable.)

### Build options
There are a number of options that can (or must) be specified at the point of
building. Their default values are set in `edk2/Conf/target.txt`. If we are
working only on a single platform, it makes sense to just update this file.

target.txt option | command line | Description
------------------|--------------|------------
ACTIVE_PLATFORM   | `-p`         | Description file (.dsc) of platform.
TARGET            | `-b`         | One of DEBUG, RELEASE or NOOPT.
TARGET_ARCH       | `-a`         | Architecture to build for.
TOOL_CHAIN_TAG    | `-t`         | Toolchain profile to use for building.

There is also MAX_CONCURRENT_THREAD_NUMBER (`-n`), roughly equivalent to
`make -j`.

When specified on command line, `-b` can be repeated multiple times in order to
build multiple targets sequentially.

After a successful build, the resulting images can be found in
`Build/{Platform Name}/{TARGET}_{TOOL_CHAIN_TAG}/FV`.

### Build a platform
The main build process _can_ run in parallel - so figure out how many threads we
have available.

```
$ getconf _NPROCESSORS_ONLN
8
```
OK, so we have 8 CPUs - let's tell the build to use a little more than that:
```
$ NUM_CPUS=$((`getconf _NPROCESSORS_ONLN` + 2))
```
For the toolchain tag, use GCC5 for gcc version 5 or later, GCC4x for
earlier versions, or CLANG35/CLANG38 as appropriate when building with clang.
```
$ build -n $NUM_CPUS -a AARCH64 -t GCC5 -p Platform/ARM/JunoPkg/ArmJuno.dsc
```
(Note that the description file gets resolved by the build command through
searching in all locations specified in **PACKAGES_PATH**.)

#### If cross-compiling
When cross-compiling, or building with a different version of the compiler than
the default `gcc` or `clang`(/binutils), we additionally need to inform the
build command which toolchain to use. We do this by setting the environment
variable `{TOOL_CHAIN_TAG}_{TARGET_ARCH}_PREFIX` - in the case above,
**GCC5_AARCH64_PREFIX**.

So, referring to the cross compiler toolchain table above, we should prepend the `build` command line with `GCC5_AARCH64_PREFIX=aarch64-linux-gnu-`.

## Using uefi-tools helper scripts
uefi-tools is a completely unofficial set of helper-scripts developed by Linaro.
They automate figuring out all of the manual options above, and store the paths
to platform description files in a separate configuration file. Additionally,
they simplify bulk-building large numbers of platforms.

The (best effort) intent is to keep this configuration up to date with all
platforms that exist in the edk2-platforms master branch.

The equivalent of the manual example above would be
```
$ git clone https://git.linaro.org/uefi/uefi-tools.git
...
$ ./uefi-tools/edk2-build.sh juno
...
------------------------------------------------------------
                         aarch64 Juno (AARCH64) RELEASE pass
------------------------------------------------------------
pass   1
fail   0
```
The build finishes with a summary of which platforms/targets were built, which
succeeded and which failed (and the total number of either).

Like the `build` command itself, `edk2-build.sh` it supports specifying multiple
targets on a single command line, but it also lets you specify multiple
platforms (or `all` for building all known platforms). So in order to build all
platforms described by the configuration file, for both DEBUG and RELEASE
targets:
```
$ ./uefi-tools/edk2-build.sh -b DEBUG -b RELEASE
```

# How To Build (Windows Environment)

These instructions will be a summary of the
[Windows Systems wiki entry](https://github.com/tianocore/tianocore.github.io/wiki/Windows-systems).
The wiki entry is targeted towards using the Visual Studio compiler.  The
instructions below will have some extra steps if you are cross-compiling with GCC.

## Prerequisites
You will need Git for Windows and Visual Studio installed to build EDK2 from source.
If you wish to build the build tools, you will also need Python 2.7 for Windows
and cx_Freeze.

## If cross compiling
If building EDK2 for a different architecture than the build machine, you need to
obtain an appropriate cross-compiler. X64 (x86_64) compilers also support IA32,
but the reverse may not always be true.

Target architecture | Cross compilation prefix
--------------------|-------------------------
ARM                 | arm-eabi-

### GCC
Linaro provides a Windows-compatible GCC toolchain for [arm-eabi](https://releases.linaro.org/components/toolchain/binaries/latest/arm-eabi/)
compiled to run on x86_64/i686 Windows.  Select the i686 mingw32 variant.

To use the GCC toolchain, you will also need a Windows-compatible GNU Make.  These
instructions will use [MinGW](http://mingw.org/) but any Windows-compatible
GNU Make tool will work.

## Obtaining source code
1. Create a new folder (directory) on your local development machine
   for use as your workspace. This example uses `C:\git\tianocore`, modify as
   appropriate for your needs.

1. In a Windows command prompt:
   ```
   > set WORKSPACE=C:\git\tianocore
   > mkdir %WORKSPACE%
   > cd %WORKSPACE%
   ```

1. Into that folder, clone:
   1. [edk2](https://github.com/tianocore/edk2)
   1. [edk2-platforms](https://github.com/tianocore/edk2-platforms)
   1. [edk2-non-osi](https://github.com/tianocore/edk2-non-osi) (if building
      platforms that need it)
   ```
   > git clone https://github.com/tianocore/edk2.git
   ...
   > git clone https://github.com/tianocore/edk2-platforms.git
   ...
   > git clone https://github.com/tianocore/edk2-non-osi.git
   ```

1. Clone submodules
   ```
   > pushd edk2
   > git submodule update --init --recursive
   > popd
   ```

1. Set up a **PACKAGES_PATH** to point to the locations of these three
   repositories.

   Note: only set the path with valid locations.  If you don't use edk2-non-osi,
   do not add it to your **PACKAGES_PATH**. Otherwise, you will get errors during build.

   `> set PACKAGES_PATH=%WORKSPACE%\edk2;%WORKSPACE%\edk2-platforms;%WORKSPACE%\edk2-non-osi`

### If cross-compiling with GCC
#### GNU Make
These instructions will walk through getting and setting up mingw32-make.exe. You are
free to use other GNU make tools if those are more comfortable for you. Just make sure
the GNU make is Windows-compatible and in your PATH.

1. Download the latest [MinGW setup installer](https://sourceforge.net/projects/mingw/files/).

1. Run the setup and make sure you note down the installation directory.
This is where you will grab the binary tools later.

   Note: According to the
   [MinGW Getting Started](http://mingw.org/wiki/Getting_Started),
do not use an installation path which contains containing spaces as
the spaces may be problems.

1. Once the setup is done, launch the MinGW Installation Manager.

1. Now you will get the **make** executable.  In this case, you will get **mingw32-make.exe**
since this will work directly in a Windows environment.  In the installer, select
**All Packages**.  Scroll through the list and select the packages named `mingw32-make`.
Specifically, you will need the `bin` class package, which contains **mingw32-make.exe**.

1. Go to the Installation drop down menu and `Apply Changes`.  This will start
the download of the `mingw32-make` package into your installation directory from earlier.
Once it is done, you should have a **mingw32-make.exe** and a few other .dlls in `<MinGW folder>\bin`

1. Copy the contents of the bin folder to a folder in your workspace.
You need to copy **mingw32-make.exe** and its associated dynamically loaded libraries.
   ```
   > mkdir %WORKSPACE%\GNUMake
   > pushd %WORKSPACE%\GNUMake
   > copy <path to MinGW folder>\bin %WORKSPACE%\GNUMake
   > popd
   ```

1. Update PATH to have GNUMake folder so you can run **mingw32-make.exe** from anywhere.

   `> set PATH=%WORKSPACE%\GNUMake;%PATH%`

1. By default, the EDK2 tools will invoke **make** and not **mingw32-make**.  To fix this,
set **GNU_HOST_BIN** to add the `mingw32-` prefix.

   `> set GNU_HOST_BIN=mingw32-`

#### GCC Cross Compiler
1. Download your desired GCC cross-compiler.  For ARM32, use
[arm-eabi](https://releases.linaro.org/components/toolchain/binaries/latest/arm-eabi/)
provided by Linaro.  Make sure to download the i686 mingw version.

1. Extract the cross compiler.  You can use 7-zip or Windows Subsystem for Linux
`tar xvf` to extract the contents to a folder.

1. Create a new folder in your workspace and copy the contents into your workspace.
   ```
   > mkdir %WORKSPACE%\Toolchains
   > pushd %WORKSPACE%\Toolchains
   > copy <path to extracted GCC cross compiler> %WORKSPACE%\Toolchains
   > popd
   ```

   At this point, you should have the gcc executables in `%WORKSPACE%\Toolchains\bin`.

1. Update PATH to have the Toolchains\bin folder so you can run the toolchain binaries from anywhere.

   `> set PATH=%WORKSPACE%\Toolchains\bin;%PATH%`

## Manual building
1. Install the latest Microsoft Visual Studio from the [Visual Studio website](https://visualstudio.microsoft.com/downloads/).

1. Get the BaseTools.  You can either build them from source or fetch prebuilt binaries.
   * To build from source, follow the Windows instructions found [here](https://github.com/tianocore/edk2/blob/master/BaseTools/BuildNotes.txt).
   Note that this requires Python 2.7 and cx_Freeze.
   * To use prebuilt binaries, clone
   [edk2-BaseTools-win32](https://github.com/tianocore/edk2-BaseTools-win32)
   and set **EDK_TOOLS_BIN** to point to this location.
   ```
   > git clone https://github.com/tianocore/edk2-BaseTools-win32.git
   ...
   > set EDK_TOOLS_BIN=%WORKSPACE%\edk2-BaseTools-win32
   ```

1. Set **PATH** to include the location of the BaseTools.  For example:

   `> set PATH=%WORKSPACE%\edk2-BaseTools-win32;%PATH%`

1. Set up the build environment (this will modify your environment variables)

   `> %WORKSPACE%\edk2\edksetup.bat`

   (This step _depends_ on **WORKSPACE** being set as per above.)

   You may see a few warnings or errors:
   * PYTHON_HOME environment variable is only needed if you plan to build the BaseTools
   from source in the next step.
   * You may see warnings for NASM or CYGWIN paths not being set.
   These could be benign depending on your build toolchain.
   For our GCC cross-compile setup, we do not use NASM or Cygwin.

   `edksetup.bat` script will generate config files into the `%WORKSPACE%\edk2\Conf` folder.
   If you have made changes to your general configuration, you will need to rerun this
   script with the `Reconfig` argument to regenerate the files in the Conf folder.

1. Install the ASL compiler (if necessary) for your platform. Follow
the instructions found [here](https://github.com/tianocore/tianocore.github.io/wiki/Asl-Setup) to install
the official ASL compiler.

   Note: certain Windows IoT platforms may require the Microsoft ASL compiler.
   The Microsoft ASL compiler (asl.exe) can be obtained from the Windows Driver Kit
   ([WDK](https://docs.microsoft.com/en-us/windows-hardware/drivers/download-the-wdk)).
   It can be found in the `<path to Windows Kits>\tools\<host arch>\ACPIVerify\` folder.

1. Update **PATH** to include the location of the ASL compiler

   `> set PATH=<path to your ASL compiler>;%PATH%`

### Build options
There are a number of options that can (or must) be specified at the point of
building. Their default values are set in `edk2\Conf\target.txt`. If we are
working only on a single platform, it makes sense to just update this file.

target.txt option | command line | Description
------------------|--------------|------------
ACTIVE_PLATFORM   | `-p`         | Description file (.dsc) of platform.
TARGET            | `-b`         | One of DEBUG, RELEASE or NOOPT.
TARGET_ARCH       | `-a`         | Architecture to build for.
TOOL_CHAIN_TAG    | `-t`         | Toolchain profile to use for building.

There is also MAX_CONCURRENT_THREAD_NUMBER (`-n`), roughly equivalent to
`make -j`.

When specified on command line, `-b` can be repeated multiple times in order to
build multiple targets sequentially.

After a successful build, the resulting images can be found in
`%WORKSPACE%\Build\{Platform Name}\{TARGET}_{TOOL_CHAIN_TAG}\FV`.

#### If cross-compiling
When cross-compiling, we additionally need to inform the build command which toolchain to use.
We do this by setting the environment variable `{TOOL_CHAIN_TAG}_{TARGET_ARCH}_PREFIX`

So if we are using GCC5 cross compiler toolchain, we should set

   > set GCC5_ARM_PREFIX=arm-eabi-

to prepend the **gcc** build command line with **arm-eabi-**

### Build a platform
The main build process _can_ run in parallel - so figure out how many threads we
have available.

```
> echo %NUMBER_OF_PROCESSORS%
8
```
OK, so we have 8 CPUs - let's tell the build to use a little more than that:
```
> set /A NUM_CPUS=%NUMBER_OF_PROCESSORS%+2
```
For the toolchain tag, select a toolchain that is compatible with building in a Windows Environment. Search for 'Supported Tool Chains' in tools_def.txt to see the valid options for `TOOL_CHAIN_TAG`.  If using Visual Studio Compiler, consult the
[VS Toolchain Matrix](https://github.com/tianocore/tianocore.github.io/wiki/Windows-systems-ToolChain-Matrix)
to determine the proper VS `TOOL_CHAIN_TAG`.

```
> build -n %NUM_CPUS% -a ARM -t GCC5 -p Platform/NXP/SABRESD_IMX6Q_1GB/SABRESD_IMX6Q_1GB.dsc
```

(Note that the description file gets resolved by the build command through
searching in all locations specified in **PACKAGES_PATH**.)

### Clean Rebuild
EDK2 build system will cache the build configuration in the `edk2\Conf` folder when you
first you invoke a build.  Subsequent builds will reference this cached
configuration.  If you make a minor change to the build template, it is recommended
to run:

   `> %WORKSPACE%\edk2\edksetup.bat Reconfig`

which will regenerate the contents of `edk2\Conf` folder.

You should also delete the output folder (`%WORKSPACE%\Build\{Platform Name}\{TARGET}_{TOOL_CHAIN_TAG}`)
to remove any stale Makefiles and configurations generated during from the previous build.

# Supported Platforms

These are the platforms currently supported by this tree - grouped by
Processor/SoC vendor, rather than platform vendor.

If there are any additional build steps beyond the generic ones listed above,
they will be documented with the platform.

## AMD
* [Cello](Platform/LeMaker/CelloBoard)
* [Overdrive](Platform/AMD/OverdriveBoard)
* [Overdrive 1000](Platform/SoftIron/Overdrive1000Board)

## ARM
* [Juno](Platform/ARM/JunoPkg)
* [Versatile Express](Platform/ARM/VExpressPkg)

## Hisilicon
* [D02](Platform/Hisilicon/D02)
* [D03](Platform/Hisilicon/D03)
* [D05](Platform/Hisilicon/D05)
* [HiKey](Platform/Hisilicon/HiKey)

## Marvell
* [Armada 70x0](Platform/Marvell/Armada)

## Socionext
* [SynQuacer](Platform/Socionext/DeveloperBox)

# Maintainers

See [Maintainers.txt](Maintainers.txt).
