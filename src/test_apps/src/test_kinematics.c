#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "kinematics.h"


void print_pose(struct pose* leg_pose) {
    printf("Computed Leg Pose\n");
    printf("Coxa:   %f\n", leg_pose->coxa_theta);
    printf("Femur:  %f\n", leg_pose->femur_theta);
    printf("Tibia:  %f\n", leg_pose->tibia_theta);
}

void print_point(struct point* point) {
    printf("Point\n");
    printf("X:   %f\n", point->X);
    printf("Y:  %f\n", point->Y);
    printf("Z:  %f\n", point->Z);
}



int main(int argc, char** argv){
    struct point desired_point = {150.0, 0.0, 50.0};
    struct pose leg_pose = {0.0, 0.0, 0.0};

    inv_leg_kin(&desired_point, &leg_pose);
    print_pose(&leg_pose);
    sleep(1);

    desired_point.Z = -50;

    inv_leg_kin(&desired_point, &leg_pose);
    print_pose(&leg_pose);
    sleep(1);

    desired_point.X = 120.0;

    inv_leg_kin(&desired_point, &leg_pose);
    print_pose(&leg_pose);
    sleep(1);

    desired_point.Z = 50;

    inv_leg_kin(&desired_point, &leg_pose);
    print_pose(&leg_pose);
    sleep(1);

    desired_point.X = 160.0;
    desired_point.Z = 0.0;

    inv_leg_kin(&desired_point, &leg_pose);
    print_pose(&leg_pose);
    sleep(1);
    
    return 0;
}