/* 
 * leg control library
 *
 * Author: Trent Novelly
 * Date: 1/26/2020
 */

#ifndef LEG_CONTROL_H
#define LEG_CONTROL_H

typedef struct leg {
	int coxa_ID;
	int femur_ID;
	int tibia_ID;
} leg_struct;


extern const leg_struct legs[];

enum leg_ids{front_left, front_right, back_left, back_right};

void load_calibration(char* calibration_filename);

void reset_all_legs(void);

void set_leg_pose(int leg_ID, int coxa_theta, int femur_theta, int tibia_theta);

#endif
