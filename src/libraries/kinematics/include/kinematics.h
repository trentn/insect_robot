/* 
 * kinematics library
 *
 * Author: Trent Novelly
 * Date: 3/7/2020
 */


struct point {
    float X;
    float Y;
    float Z;
};

struct pose {
    float coxa_theta;
    float femur_theta;
    float tibia_theta;
};


/*
 * @param pose- input pose of the leg
 * @returns pointer to struct with location of foot
 */
 struct point* fwd_leg_kin(struct pose* pose);

/*
 * @param desired_endpoint - the desired location of the point foot
 * @returns pointer to pose structure to receive calculated pose.
 */
 struct pose* inv_leg_kin( struct point* desired_endpoint);