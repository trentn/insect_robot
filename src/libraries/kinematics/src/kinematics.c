/*
 * Implementation of kinematics.h
 */

#include "kinematics.h"
#include "robot_parameters.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


#define RAD2DEG(x) x * (180.0/M_PI)
#define DEG2RAD(x) x * (M_PI/180.0)

#define DEBUG(x) printf("DEBUG x %f\n", x);

/*
 * @param pose is a leg pose in degrees
 * 
 * reference: Page 329, Theory of Applied Robotics
 */

struct point* fwd_leg_kin(struct pose* pose) {
    struct point* foot_location = (struct point*)malloc(sizeof(struct point));

    double coxa_theta =     DEG2RAD(pose->coxa_theta);
    double femur_theta =    DEG2RAD(pose->femur_theta);
    double tibia_theta =    DEG2RAD(pose->tibia_theta);

    foot_location->X = TIBIA_LENGTH*sin(femur_theta + tibia_theta)*cos(coxa_theta)
                        + FEMUR_LENGTH*cos(coxa_theta)*cos(femur_theta);

    foot_location->Y = TIBIA_LENGTH*sin(femur_theta + tibia_theta)*sin(coxa_theta)
                        + FEMUR_LENGTH*sin(coxa_theta)*cos(femur_theta);

    foot_location->Z = COXA_LENGTH
                        - TIBIA_LENGTH*cos(femur_theta+tibia_theta)
                        + FEMUR_LENGTH*sin(femur_theta);  

    return foot_location;
}



/*
 * @return leg pose in degrees
 *
 * reference: Page 329, Theory of Applied Robotics
 * reference: Page 338, Theory of Applied Robotics (solves for femur_theta)
 */
void inv_leg_kin( struct point* desired_endpoint, struct pose* leg_pose) {
    leg_pose->coxa_theta = atan2(desired_endpoint->Y, desired_endpoint->X);

    DEBUG(leg_pose->coxa_theta);

    double tmp = (desired_endpoint->X*cos(leg_pose->coxa_theta)
                    + desired_endpoint->Y*sin(leg_pose->coxa_theta));

    double a = -2.0*FEMUR_LENGTH*tmp;
    double b = 2*FEMUR_LENGTH*(COXA_LENGTH-desired_endpoint->Z);
    double c = TIBIA_LENGTH*TIBIA_LENGTH - 
                ( tmp*tmp 
                    + COXA_LENGTH*COXA_LENGTH 
                    - 2*COXA_LENGTH*desired_endpoint->Z
                    + FEMUR_LENGTH*FEMUR_LENGTH
                    + desired_endpoint->Z*desired_endpoint->Z);
    
    double r = sqrt(a*a + b*b);

    //TODO: error checking to ensure this is solvable
    leg_pose->femur_theta = atan2(c,sqrt(r*r-c*c)) - atan2(a,b);


    double numerator = desired_endpoint->X*cos(leg_pose->coxa_theta)
                            + desired_endpoint->Y*sin(leg_pose->coxa_theta)
                            - FEMUR_LENGTH*cos(leg_pose->femur_theta);
    double denominator = COXA_LENGTH
                            + FEMUR_LENGTH*sin(leg_pose->femur_theta)
                            - desired_endpoint->Z;

    leg_pose->tibia_theta = atan2(numerator,denominator) - leg_pose->femur_theta;


    //convert to degrees
    leg_pose->coxa_theta =  RAD2DEG(leg_pose->coxa_theta);
    leg_pose->femur_theta = RAD2DEG(leg_pose->femur_theta);
    leg_pose->tibia_theta = RAD2DEG(leg_pose->tibia_theta);

    return leg_pose;
}