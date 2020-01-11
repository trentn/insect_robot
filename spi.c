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

#include <bcm2835.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    // If you call this, it will not actually access the GPIO
// Use for testing
//        bcm2835_set_debug(1);

    if (!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root??\n");
      return 1;
    }

    if (!bcm2835_spi_begin())
    {
      printf("bcm2835_spi_begin failed. Are you running as root??\n");
      return 1;
    }
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_LSBFIRST);
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE2);
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // the default
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // the default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default
    

    uint8_t servo_id = 11;
    uint8_t fb1 = 0x02;
    uint8_t lb1 = 0xbc;

    uint8_t fb2 = 0x05;
    uint8_t lb2 = 0xdc;

    uint8_t fb3 = 0x09;
    uint8_t lb3 = 0x47;

    while(1){
    bcm2835_spi_transfer(servo_id);
    bcm2835_spi_transfer(fb1);
    bcm2835_spi_transfer(lb1);

    sleep(1);

    bcm2835_spi_transfer(servo_id);
    bcm2835_spi_transfer(fb2);
    bcm2835_spi_transfer(lb2);

    sleep(1);

    bcm2835_spi_transfer(servo_id);
    bcm2835_spi_transfer(fb3);
    bcm2835_spi_transfer(lb3);

    sleep(1);

    bcm2835_spi_transfer(servo_id);
    bcm2835_spi_transfer(fb2);
    bcm2835_spi_transfer(lb2);

    sleep(1);
    }

    bcm2835_spi_end();
    bcm2835_close();
    return 0;
}

