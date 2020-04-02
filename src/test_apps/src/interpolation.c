#include "leg_control.h"
#include "kinematics.h"
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NUM_POINTS 100

void print_pose(struct pose* leg_pose) {
    printf("Computed Leg Pose\n");
    printf("Coxa:   %f\n", leg_pose->coxa_theta);
    printf("Femur:  %f\n", leg_pose->femur_theta);
    printf("Tibia:  %f\n", leg_pose->tibia_theta);
}

void print_point(struct point* point) {
    printf("X: %f\n", point->X);
    printf("Y: %f\n", point->Y);
    printf("Z: %f\n\n", point->Z);
}


struct point** interpolate(struct point* start, struct point* end, int num_points) {
    struct point** points = (struct point**)malloc(sizeof(struct point*)*num_points);

    double dX = end->X - start->X;
    double dY = end->Y - start->Y;
    double dZ = end->Z - start->Z;

    *(points) = start;

    for(int i = 1; i < num_points-1; i++){
        *(points+i) = (struct point*)malloc(sizeof(struct point));
        
        double r = ((double)i/(double)num_points);

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

    struct timespec ts = {0, 10L};
    struct pose leg_pose = {0.0, 0.0, 0.0};


    struct point point_1 = {150.0, 0.0, 50.0};
    struct point point_2 = {150.0, 0.0, -50.0};
    struct point point_3 = {100.0, 50.0, 75.0};
    struct point** points_first = interpolate(&point_1, &point_2, NUM_POINTS);

    for(int i = 0; i < NUM_POINTS; i++){
	print_point(*(points_first+i));
        inv_leg_kin(*(points_first+i), &leg_pose);
        set_leg_pose(front_right,
                 leg_pose.coxa_theta,
                 leg_pose.femur_theta,
                 leg_pose.tibia_theta);
    }
    
    struct point** points_second = interpolate(&point_2, &point_3, NUM_POINTS);

    for(int i = 0; i < NUM_POINTS; i++){
	print_point(*(points_second+i));
        inv_leg_kin(*(points_second+i), &leg_pose);
        set_leg_pose(front_right,
                 leg_pose.coxa_theta,
                 leg_pose.femur_theta,
                 leg_pose.tibia_theta);

    }


    return 0;
}
