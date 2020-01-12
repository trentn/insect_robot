/*
 * servo_controller.h
 *
 * functions to interface with the fpga servo controller
 *
 * Author: Trent Novelly
 * 1/12/2020
 */
#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

#include <stdint.h>

/*
 * initialize the raspi SPI peripheral to talk with the 
 * FPGA SPI interface
 * 
 * Configuration details:
 *  CPOL = 1, CPHA = 0
 *  LSB first
 *  Chip Select Polarity: Low
 */
void init_servo_controller(void);

/*
 *
 * @param servo_id is the 8 bit servo identifier. There are 12 PWM generators,
 *      so the valid range is 0-11.
 *
 * @param pulse_length is a 16 bit pulse length in milliseconds
 *      valid range is roughly 700-2300
 */
void set_servo_pwm(uint8_t servo_id, uint16_t pulse_length);

/*
 * terminate the SPI connection
 */
void close_servo_controller(void);

#endif