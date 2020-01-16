#include "servo_controller.h"
#include <unistd.h>

int main(){

	uint16_t pulses[NUM_JOINTS] = {1530,1500,1420,1500,1550,1550,1510,1540,1490,1550,1540,1420};

	init_servo_controller(NULL);

	for(int i=0; i< NUM_JOINTS; i++){
		set_servo_pwm((uint8_t)i, pulses[i]);
		//sleep(1);
	}

	close_servo_controller();

	return 0;
}
