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
#include <stdlib.h>

void init_servo_controller(FILE* calibration_file){
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

    /* TODO proper error handling on poor formatted calibration files */
    if(calibration_file == NULL){
      for(int i = 0; i < NUM_JOINTS; i++){
        servos[i].zero_angle_pwm = 1500;
        servos[i].orientation = right;
      }
    } else {
      for(int i = 0; i < NUM_JOINTS; i++){
        char buff[10] = {0};
        fgets(buff, 10, calibration_file);

        servos[i].zero_angle_pwm =  atoi(buff);
        servos[i].orientation = i%2==0? right : left;
      }
    }
}

void set_servo_pwm(uint8_t servo_id, uint16_t pulse_length){
    uint8_t first_byte, second_byte;
    first_byte = (uint16_t)(pulse_length>>8);
    second_byte = (uint8_t)pulse_length;

    bcm2835_spi_transfer(servo_id);
    bcm2835_spi_transfer(first_byte);
    bcm2835_spi_transfer(second_byte);
}

void set_servo_angle(int servo_id, int angle){
  int pulse_length = servos[servo_id].zero_angle_pwm + (angle*ANGLE_CONVERSION_RATE)*servos[servo_id].orientation;

  set_servo_pwm((uint8_t)servo_id, (uint16_t)pulse_length);
}

void close_servo_controller(){
    bcm2835_spi_end();
    bcm2835_close();
}