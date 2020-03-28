#include "leg_control.h"
#include "kinematics.h"
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void print_pose(struct pose* leg_pose) {
    printf("Computed Leg Pose\n");
    printf("Coxa:   %f\n", leg_pose->coxa_theta);
    printf("Femur:  %f\n", leg_pose->femur_theta);
    printf("Tibia:  %f\n", leg_pose->tibia_theta);
}


void round_and_set(struct pose* leg_pose){
    int coxa_theta  =(int)round(leg_pose->coxa_theta);
    int femur_theta =(int)round(leg_pose->femur_theta);
    int tibia_theta =(int)round(leg_pose->tibia_theta);


    set_leg_pose(front_right,
                 coxa_theta,
                 femur_theta,
                 tibia_theta);

}

int main(int argc, char** argv){
    load_calibration(argv[1]);

    set_leg_pose(front_left, 0,0,0);
    set_leg_pose(front_right, 0,0,0);
    set_leg_pose(back_left, 0,0,0);
    set_leg_pose(back_right, 0,0,0);

    struct point desired_point = {150.0, 0.0, -50.0};
    struct pose leg_pose = {0.0, 0.0, 0.0};

    inv_leg_kin(&desired_point, &leg_pose);
    round_and_set(&leg_pose);
    sleep(1);

    desired_point.X = 120.0;

    inv_leg_kin(&desired_point, &leg_pose);
    round_and_set(&leg_pose);
    sleep(1);

    desired_point.Z = 50.0;

    inv_leg_kin(&desired_point, &leg_pose);
    round_and_set(&leg_pose);
    sleep(1);

    desired_point.X = 150.0;

    inv_leg_kin(&desired_point, &leg_pose);
    round_and_set(&leg_pose);
    sleep(1);

    desired_point.X = 160.0;
    desired_point.Z = 0.0;
    desired_point.Y = 0.0;

    inv_leg_kin(&desired_point, &leg_pose);
    round_and_set(&leg_pose);
    sleep(1);

    return 0;
}
