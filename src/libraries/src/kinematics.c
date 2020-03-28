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

#ifdef __DEBUG__
#define DEBUG(s,x) printf("DEBUG %s %f\n", s, x);
#else
#define DEBUG(s,x) 
#endif

/*
 * @param pose is a leg pose in degrees
 * 
 * reference: Page 329, Theory of Applied Robotics
 */

int fwd_leg_kin(struct pose* pose, struct point* foot_location) {
    double coxa_theta =     DEG2RAD(pose->coxa_theta);
    double femur_theta =    DEG2RAD(pose->femur_theta);
    double tibia_theta =    DEG2RAD(pose->tibia_theta);


    foot_location->X = TIBIA_LENGTH*cos(coxa_theta)*sin(femur_theta+tibia_theta) +
                        cos(coxa_theta)*(COXA_LENGTH+FEMUR_LENGTH*cos(femur_theta));

    foot_location->Y = TIBIA_LENGTH*sin(coxa_theta)*sin(femur_theta+tibia_theta) +
                        sin(coxa_theta)*(COXA_LENGTH+FEMUR_LENGTH*cos(femur_theta));


    foot_location->Z = FEMUR_LENGTH*sin(femur_theta) -
                        TIBIA_LENGTH*cos(femur_theta+tibia_theta);
    return 0;
}



/*
 * @return leg pose in degrees
 *
 * reference: Page 329, Theory of Applied Robotics
 * reference: Page 338, Theory of Applied Robotics (solves for femur_theta)
 */
int inv_leg_kin( struct point* desired_endpoint, struct pose* leg_pose) {
    leg_pose->coxa_theta = atan2(desired_endpoint->Y, desired_endpoint->X);

    //TODO: bettering variable names
    double x = sqrt(desired_endpoint->X*desired_endpoint->X + desired_endpoint->Y+desired_endpoint->Y)-COXA_LENGTH;
    double y = desired_endpoint->Z;

    double a = FEMUR_LENGTH;
    double b = TIBIA_LENGTH;

    double hyp = sqrt(x*x+y*y);

    if(hyp > (a+b))return -1;

    if(hyp == (a+b)){
        leg_pose->femur_theta = asin(y/hyp);
        leg_pose->tibia_theta = 0.0;
    }
    else{
        leg_pose->tibia_theta = -(M_PI - acos((x*x+y*y-a*a-b*b)/(-2*a*b)));
        printf("first tibia angle: %f\n", RAD2DEG(leg_pose->tibia_theta));
        if(leg_pose->tibia_theta < M_PI/2.0 && leg_pose->tibia_theta > -M_PI/2.0){
            leg_pose->femur_theta = asin(y/hyp) + acos((b*b-x*x-y*y-a*a)/(-2*a*hyp));
        } else {
            leg_pose->tibia_theta = (M_PI - acos((x*x+y*y-a*a-b*b)/(-2*a*b)));
            leg_pose->femur_theta = -(asin(y/hyp) + acos((b*b-x*x-y*y-a*a)/(-2*a*hyp)));
        }   
    }

    leg_pose->coxa_theta =  RAD2DEG(leg_pose->coxa_theta);
    leg_pose->femur_theta = RAD2DEG(leg_pose->femur_theta);
    leg_pose->tibia_theta = RAD2DEG(leg_pose->tibia_theta);

    // if(leg_pose->coxa_theta > 90.0 && leg_pose->coxa_theta < -90.0) return -1;
    // if(leg_pose->femur_theta > 90.0 && leg_pose->femur_theta < -90.0) return -1;
    // if(leg_pose->tibia_theta > 90.0 && leg_pose->tibia_theta < -90.0) return -1;

    return 0;
}




int fwd_leg_kin_example(struct pose* pose, struct point* foot_location) {
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

    return 0;
}

int inv_leg_kin_example( struct point* desired_endpoint, struct pose* leg_pose) {
    leg_pose->coxa_theta = atan2(desired_endpoint->Y, desired_endpoint->X);

    DEBUG("leg_pose->coxa_theta",leg_pose->coxa_theta)

    double tmp = (desired_endpoint->X*cos(leg_pose->coxa_theta)
                    + desired_endpoint->Y*sin(leg_pose->coxa_theta));

    double a = -2.0*FEMUR_LENGTH*tmp;
    double b = 2.0*FEMUR_LENGTH*(COXA_LENGTH-desired_endpoint->Z);
    double c = TIBIA_LENGTH*TIBIA_LENGTH - 
                ( tmp*tmp 
                    + COXA_LENGTH*COXA_LENGTH 
                    - 2.0*COXA_LENGTH*desired_endpoint->Z
                    + FEMUR_LENGTH*FEMUR_LENGTH
                    + desired_endpoint->Z*desired_endpoint->Z);
    
    double r = sqrt(a*a + b*b);

    DEBUG("a",a)
    DEBUG("b",b)
    DEBUG("c",c)
    DEBUG("r",r)



    //TODO: error checking to ensure this is solvable
    leg_pose->femur_theta = atan2(c,sqrt(r*r-c*c)) - atan2(a,b);


    double numerator = desired_endpoint->X*cos(leg_pose->coxa_theta)
                            + desired_endpoint->Y*sin(leg_pose->coxa_theta)
                            - FEMUR_LENGTH*cos(leg_pose->femur_theta);
    double denominator = COXA_LENGTH
                            + FEMUR_LENGTH*sin(leg_pose->femur_theta)
                            - desired_endpoint->Z;

    leg_pose->tibia_theta = atan(numerator/denominator) - leg_pose->femur_theta;


    //convert to degrees
    leg_pose->coxa_theta =  RAD2DEG(leg_pose->coxa_theta);
    leg_pose->femur_theta = RAD2DEG(leg_pose->femur_theta);
    leg_pose->tibia_theta = RAD2DEG(leg_pose->tibia_theta);

    if(leg_pose->coxa_theta > 90.0 && leg_pose->coxa_theta < -90.0) return -1;
    if(leg_pose->femur_theta > 90.0 && leg_pose->femur_theta < -90.0) return -1;
    if(leg_pose->tibia_theta > 90.0 && leg_pose->tibia_theta < -90.0) return -1;

    return 0;
}
