#include <stdio.h>

#include "servo_controller.h"
#include "leg_control.h"

const leg_struct legs[]  = {
    { .coxa_ID = 0, .femur_ID = 2, .tibia_ID = 4},
    { .coxa_ID = 1, .femur_ID = 3, .tibia_ID = 5},
    { .coxa_ID = 6, .femur_ID = 8, .tibia_ID = 10},
    { .coxa_ID = 7, .femur_ID = 9, .tibia_ID = 11}
};

void load_calibration(char* calibration_filename) {
    FILE* calibration_file = fopen(calibration_filename, "r");

    init_servo_controller(calibration_file);
    fclose(calibration_file);
}

void reset_all_legs(void) {
    for(int i = 0; i < NUM_JOINTS; i++){
        set_servo_angle(i, 0);
    }
}

void set_leg_pose(int leg_ID, int coxa_theta, int femur_theta, int tibia_theta) {
	set_servo_angle(legs[leg_ID].coxa_ID, coxa_theta);
	set_servo_angle(legs[leg_ID].femur_ID, femur_theta);
	set_servo_angle(legs[leg_ID].tibia_ID, tibia_theta);
}
