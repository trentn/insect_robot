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
 */

int fwd_leg_kin(struct pose* pose, struct point* foot_location) {
    double coxa_theta =     DEG2RAD(pose->coxa_theta);
    double femur_theta =    DEG2RAD(pose->femur_theta);
    double tibia_theta =    DEG2RAD(pose->tibia_theta);
    
    return -1;
}



/*
 * @return leg pose in degrees
 * 
 * solved geometrically.
 */
int inv_leg_kin( struct point* desired_endpoint, struct pose* leg_pose) {
    leg_pose->coxa_theta = atan2(desired_endpoint->Y, desired_endpoint->X);

    //TODO: bettering variable names
    double x = sqrt(desired_endpoint->X*desired_endpoint->X + desired_endpoint->Y*desired_endpoint->Y)-COXA_LENGTH;
    printf("%lf\n",x);
    double y = desired_endpoint->Z;

    double a = TIBIA_LENGTH;
    double b = FEMUR_LENGTH;
    

    double hyp = sqrt(x*x+y*y);

    if(hyp > (a+b))return -1;

    if(hyp == (a+b)){
        leg_pose->femur_theta = asin(y/hyp);
        leg_pose->tibia_theta = 0.0;
    }
    else{
        //https://www.mathsisfun.com/algebra/trig-solving-sss-triangles.html
        leg_pose->tibia_theta = -(M_PI - acos((a*a+b*b-x*x+y*y)/(2*a*b)));
        leg_pose->femur_theta = asin(y/hyp) + acos((b*b+x*x+y*y-a*a)/(2*a*hyp));
    }

    leg_pose->coxa_theta =  RAD2DEG(leg_pose->coxa_theta);
    leg_pose->femur_theta = RAD2DEG(leg_pose->femur_theta);
    leg_pose->tibia_theta = RAD2DEG(leg_pose->tibia_theta);

    if(leg_pose->coxa_theta > 90.0 || leg_pose->coxa_theta < -90.0) return -1;
    if(leg_pose->femur_theta > 90.0 || leg_pose->femur_theta < -90.0) return -1;
    if(leg_pose->tibia_theta > 90.0 || leg_pose->tibia_theta < -90.0) return -1;

    return 0;
}
