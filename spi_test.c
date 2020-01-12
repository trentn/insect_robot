// spi.c
//
// Example program for bcm2835 library
// Shows how to interface with SPI to transfer a byte to and from an SPI device
//
// After installing bcm2835, you can build this 
// with something like:
// gcc -o spi spi.c -l bcm2835
// sudo ./spi
//
// Or you can test it before installing with:
// gcc -o spi -I ../../src ../../src/bcm2835.c spi.c
// sudo ./spi
//
// Author: Mike McCauley
// Copyright (C) 2012 Mike McCauley
// $Id: RF22.h,v 1.21 2012/05/30 01:51:25 mikem Exp $

#include "servo_controller.h"
#include <unistd.h>

int main(int argc, char **argv)
{
    uint8_t servo_id = 11;
    uint16_t left = 700;
    uint16_t center = 1500;
    uint16_t right = 2300;

    init_servo_controller();

    while(1){
      set_servo_pwm(servo_id, left);
      sleep(1);

      set_servo_pwm(servo_id, center);
      sleep(1);

      set_servo_pwm(servo_id, right);
      sleep(1);

      set_servo_pwm(servo_id, center);
      sleep(1);
    }

    close_servo_controller();
    return 0;
}

