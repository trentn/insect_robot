#include "leg_control.h"
#include "kinematics.h"
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void print_pose(struct pose* leg_pose) {
    printf("Computed Leg Pose\n");
    printf("Coxa:   %f\n", leg_pose->coxa_theta);
    printf("Femur:  %f\n", leg_pose->femur_theta);
    printf("Tibia:  %f\n", leg_pose->tibia_theta);
}


int main(int argc, char** argv){
    load_calibration(argv[1]);

    set_leg_pose(front_left, 0,0,0);
    set_leg_pose(front_right, 0,0,0);
    set_leg_pose(back_left, 0,0,0);
    set_leg_pose(back_right, 0,0,0);

    struct point desired_point = {100.0, -10.0, -10.0};
    struct pose leg_pose = {0.0, 0.0, 0.0};
    inv_leg_kin(&desired_point, &leg_pose);
    
    leg_pose.coxa_theta = round(leg_pose.coxa_theta);
    leg_pose.femur_theta = round(leg_pose.femur_theta);
    leg_pose.tibia_theta = round(leg_pose.tibia_theta);


    set_leg_pose(front_right,
                 (int)leg_pose.coxa_theta,
                 (int)leg_pose.femur_theta,
                 (int)leg_pose.tibia_theta);


    return 0;
}
