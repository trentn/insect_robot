#include "servo_controller.h"
#include <unistd.h>
#include <time.h>

void set_to_zero(void) {
    for(int i = 0; i < NUM_JOINTS; i++){
        set_servo_angle(i, 0);
    }
}

int main(int argc, char** argv){

    if(argc != 2) {
        printf("Please specify a calibration file.\n");
        return 1;
    }

    FILE* calibration_file = fopen(argv[1], "r");

    init_servo_controller(calibration_file);
    fclose(calibration_file);

    //set robot to 0 position
    set_to_zero();
    sleep(1);


    struct timespec ts = {0, 100000000L};

    //right front leg
    set_servo_angle(4, 45);
    set_servo_angle(2,-45);
    set_servo_angle(0, 90);
    nanosleep(&ts, NULL);


    //left front leg
    set_servo_angle(5, 45);
    set_servo_angle(3,-45);
    set_servo_angle(1, 90);
    nanosleep(&ts, NULL);


    //left rear leg
    set_servo_angle(11, -45);
    set_servo_angle(9, -45);
    set_servo_angle(7,  90);
    nanosleep(&ts, NULL);

    //right rear leg
    set_servo_angle(10, -45);
    set_servo_angle(8,-45);
    set_servo_angle(6, 90);
    nanosleep(&ts,NULL);


    set_servo_angle(2, -15);
    set_servo_angle(3, -15);
    set_servo_angle(9, -15);
    set_servo_angle(8, -15);


}
