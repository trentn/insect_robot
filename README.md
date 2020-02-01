# Insect Robot

## Introduction
This repo serves as a collection of code, resources, and documentation for my personal quadruped robot project. The goal of this project to to build a walking robot inspired by insects.

## Guiding Goals/Constraints
There are a number of arbitrary choices which will influence the building of this robot, all for the sake of converting book knowledge to practical experience.

- Design the physical construction from the ground up, using CAD software, 3D printing, circuit design and manufacture, etc.
- Design kinematic and dynamic models of the robot for the purposes of motion planning.
- Incorporate the use of a raspberry pi, microcontroller, and fpga - purely for the sake of using all three in a single project.


## Iterations

### MK1
The most recent "functioning" prototype was a 4-legged cardboard+hotglue contraption, controlled by an ATMega328, with buggy radio communications.

Some cringe-worthy videos of the development of this design:
- [Part 1](https://www.youtube.com/watch?v=GIuDwQUMZN4)
- [Part 2](https://www.youtube.com/watch?v=eBIZqJubI6w)
- [Part 3](https://www.youtube.com/watch?v=ZrnUjtwmfK0)

[Mark 1 Source Code](https://github.com/trentn/insect_robot/releases/tag/mk1)

---

### MK2
Currently in development is a 3D printed prototype utilizing an FPGA as a servo controller.

Current Status:
- [Fusion360 Design](https://a360.co/30rR8bb)
- [Matlab Simulation](https://twitter.com/trentnov/status/1117585657046732800)
- [Assembled Leg](https://twitter.com/trentnov/status/1087395075364130817)
- [Fully Working Robot - Stands up](https://twitter.com/trentnov/status/1217634557660487680)


#### FPGA Servo Controller
The servo controller is a verilog implementation using the [TinyFPGA BX](https://tinyfpga.com/) as the hardware platform.

The fpga_servo_controller submodule contains the code which implements a simple SPI interface and 12 PWM generators (this number can be arbitrarily increased).

This verilog is synthezised using the [APIO project](https://github.com/FPGAwars/apio)

#### Raspberry Pi Firmware
The high level logic is run on a [Raspberry Pi Zero W](https://www.raspberrypi.org/products/raspberry-pi-zero-w/) running Raspbian Buster Lite. 

For instructions on how to build and install the firmware please see the [Installation Guide](./INSTALL.md)

##### Servo Controller Library
The [BCM2835 C Library](https://www.airspayce.com/mikem/bcm2835/) is used to configure the SPI interface for use with the custom servo controller described above.

The servo_controller.* files implement a library to interface with the SPI peripheral, selecting servos and setting angles.

#### Up Next for MK2
These are a few things I have in mind for next steps:
- Python wrapper around servo_controller.c
- Walking gaits, first hard-coded/hand designed, then investigate gait generation/discovery
- Battery Power
