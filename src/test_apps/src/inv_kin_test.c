#include "servo_controller.h"
#include "kinematics.h"
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void print_pose(struct pose* leg_pose) {
    printf("Computed Leg Pose\n");
    printf("Coxa:   %f\n", leg_pose->coxa_theta);
    printf("Femur:  %f\n", leg_pose->femur_theta);
    printf("Tibia:  %f\n", leg_pose->tibia_theta);
}


int main(int argc, char** argv){

    struct point desired_point = {100.0, 10.0, 10.0};
    struct pose leg_pose = {0.0, 0.0, 0.0};
    inv_leg_kin(&desired_point, &leg_pose);
    print_pose(&leg_pose);

    desired_point.X = 0.0;
    desired_point.Y = 100.0;
    inv_leg_kin(&desired_point, &leg_pose);
    print_pose(&leg_pose);

    return 0;
}
