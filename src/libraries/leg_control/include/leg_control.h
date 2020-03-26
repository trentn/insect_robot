/* 
 * leg control library
 *
 * Author: Trent Novelly
 * Date: 1/26/2020
 */

typedef struct leg {
	int coxa_ID;
	int femur_ID;
	int tibia_ID;
} leg_struct;


leg_struct legs[]  = {
	{ .coxa_ID = 0, .femur_ID = 2, .tibia_ID = 4},
	{ .coxa_ID = 1, .femur_ID = 3, .tibia_ID = 5},
	{ .coxa_ID = 6, .femur_ID = 8, .tibia_ID = 10},
	{ .coxa_ID = 7, .femur_ID = 9, .tibia_ID = 11}
};

enum legs{front_left, front_right, back_left, back_right};

void load_calibration(char* calibration_filename);

void reset_all_legs(void);

void set_leg_pose(int leg_ID, int coxa_theta, int femur_theta, int tibia_theta);
