/* 
 * kinematics library
 *
 * Author: Trent Novelly
 * Date: 3/7/2020
 */


struct point {
    double X;
    double Y;
    double Z;
};

struct pose {
    double coxa_theta;
    double femur_theta;
    double tibia_theta;
};


/*
 * @param pose- input pose of the leg
 * @returns pointer to struct with location of foot
 */
int fwd_leg_kin(struct pose* pose, struct point* foot_location);

/*
 * @param desired_endpoint - the desired location of the point foot
 * @returns pointer to pose structure to receive calculated pose.
 */
int inv_leg_kin( struct point* desired_endpoint,  struct pose* leg_pose);



int fwd_leg_kin_example(struct pose* pose, struct point* foot_location);
int inv_leg_kin_example( struct point* desired_endpoint,  struct pose* leg_pose);