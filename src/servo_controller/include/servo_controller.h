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
#include <stdio.h>

/* 
 * number of joints being controlled
 */
#define NUM_JOINTS 12

/*
 * 1 degree is ~10 pico seconds
 */
#define ANGLE_CONVERSION_RATE 10

typedef enum orient{left=-1,right=1} orient_type;

typedef struct servo_config {
    uint16_t zero_angle_pwm;
    orient_type orientation;
} servo_conf;

servo_conf servos[NUM_JOINTS];

/*
 * initialize the raspi SPI peripheral to talk with the 
 * FPGA SPI interface
 * 
 * Configuration details:
 *  CPOL = 1, CPHA = 0
 *  LSB first
 *  Chip Select Polarity: Low
 */
void init_servo_controller(FILE* calibration_file);

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
 *
 */

void set_servo_angle(int servo_id, int angle);

/*
 * terminate the SPI connection
 */
void close_servo_controller(void);

#endif