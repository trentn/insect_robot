#include <stdio.h>

#include "servo_controller.h"
#include "leg_control.h"

const leg_struct legs[]  = {
    { .coxa_ID = 4, .femur_ID = 2, .tibia_ID = 0},
    { .coxa_ID = 5, .femur_ID = 3, .tibia_ID = 1},
    { .coxa_ID = 10, .femur_ID = 8, .tibia_ID = 6},
    { .coxa_ID = 11, .femur_ID = 9, .tibia_ID = 7}
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

void set_leg_pose(int leg_ID, double coxa_theta, double femur_theta, double tibia_theta) {
	set_servo_angle(legs[leg_ID].coxa_ID, coxa_theta);
	set_servo_angle(legs[leg_ID].femur_ID, femur_theta);
	set_servo_angle(legs[leg_ID].tibia_ID, tibia_theta);
}
