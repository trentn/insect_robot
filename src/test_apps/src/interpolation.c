#include "leg_control.h"
#include "kinematics.h"
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NUM_POINTS 10

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


struct point** interpolate(struct point* start, struct point* end, int num_points) {
    struct point** points = (struct point**)malloc(sizeof(struct point*)*num_points);

    double dX = abs(start->X - end->X);
    double dY = abs(start->Y - end->Y);
    double dZ = abs(start->Z - end->Z);

    *(points) = start;

    for(int i = 1; i < num_points-1; i++){
        *(points+i) = (struct point*)malloc(sizeof(struct point));
        
        float r = ((float)i/(float)num_points);

        (*(points+i))->X = start->X + r*dX;
        (*(points+i))->Y = start->Y + r*dY;
        (*(points+i))->Z = start->Z + r*dZ;

    }

    *(points +(num_points-1)) = end;

    return points;
}


int main(int argc, char** argv){
    load_calibration(argv[1]);

    set_leg_pose(front_left, 0,0,0);
    set_leg_pose(front_right, 0,0,0);
    set_leg_pose(back_left, 0,0,0);
    set_leg_pose(back_right, 0,0,0);

    struct timespec ts = {0, 100000000L};
    struct pose leg_pose = {0.0, 0.0, 0.0};


    struct point start_point = {150.0, 0.0, 50.0};
    struct point end_point = {150.0, 0.0, -50.0};
    struct point** points = interpolate(&start_point, &end_point, NUM_POINTS);

    for(int i = 0; i < NUM_POINTS; i++){
        inv_leg_kin(*(points+i), &leg_pose);
        round_and_set(&leg_pose);
        nanosleep(&ts, NULL);
    }


    return 0;
}
