/*
 * servo_controller.c
 *
 * implements servo_controller.h
 *
 * Author: Trent Novelly
 * 1/12/2020
 */

#include "servo_controller.h"
#include <bcm2835.h>
#include <stdio.h>
#include <unistd.h>

void init_servo_controller(){
    if (!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root??\n");
    }

    if (!bcm2835_spi_begin())
    {
      printf("bcm2835_spi_begin failed. Are you running as root??\n");
    }
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_LSBFIRST);
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE2);
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // the default
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // the default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default
}

void set_servo_pwm(uint8_t servo_id, uint16_t pulse_length){
    uint8_t first_byte, second_byte;
    first_byte = (uint16_t)(pulse_length>>8);
    second_byte = (uint8_t)pulse_length;

    bcm2835_spi_transfer(servo_id);
    bcm2835_spi_transfer(first_byte);
    bcm2835_spi_transfer(second_byte);
}

void close_servo_controller(){
    bcm2835_spi_end();
    bcm2835_close();
}