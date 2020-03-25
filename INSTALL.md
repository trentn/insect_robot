# Raspberry Pi Firmware Installation Guide

## Raspbian Configuration

Download and install [Raspbian](https://www.raspberrypi.org/downloads/raspbian/)
This has been tested with the September 2019 build of Raspbian Buster Lite.

Enable the SPI overlay, either using raspi-config or by modifying the config.txt file before booting (uncomment or add the line `dtparam=spi=on`).



## Source Code Build

### Native Build
First run:

```
install_dependencies.sh
```

This will download, build, and install the BCM2835 C Library v1.60 from Mike McCauley.
Additionally it will install via APT the following libraries:

- cmake
- libncurses5
- libncurses5-dev

Once the dependecies are installed, run the following to build and install the robot firmware:

```
mkdir build && cd build
cmake ..
make
make install
```

### Cross-Compile

I am using a cross-compilation toolchain built using crosstool-ng.  
Currently the insect robot is using a Raspberry Pi Zero W, which uses armv6.

Run:

```
install_dependencies.sh -x armv6-rpi-linux-gnueabi
```

This will download the source code for the required dependencies and compile them for the Raspberry Pi.

```
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../ToolChain.cmake ..
make
make install
```