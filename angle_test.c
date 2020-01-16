#include "servo_controller.h"
#include <unistd.h>

int main(int argc, char** argv){

    FILE* calibration_file = NULL;

    if(argc == 2){
        calibration_file = fopen(argv[1], "r");
    }
	init_servo_controller(calibration_file);

    for(;;){
	set_servo_angle(11,0);
    sleep(1);

    set_servo_angle(11,-90);
    sleep(1);

    set_servo_angle(11,0);
    sleep(1);

    set_servo_angle(11,90);
    sleep(1);
    }

	close_servo_controller();

	return 0;
}
