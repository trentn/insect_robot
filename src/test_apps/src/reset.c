#include "leg_control.h"
#include <unistd.h>

int main(int argc, char** argv){
	load_calibration(argv[1]);
	set_leg_pose(front_left, 0,0,0);
	set_leg_pose(front_right, 0,0,0);
	set_leg_pose(back_left, 0,0,0);
	set_leg_pose(back_right, 0,0,0);
	return 0;
}
