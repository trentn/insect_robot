#include "servo_controller.h"
#include <unistd.h>

int main(int argc, char **argv)
{
    uint8_t servo_id = 11;
    uint16_t left = 700;
    uint16_t center = 1500;
    uint16_t right = 2300;

    init_servo_controller();

    while(1){
      set_servo_pwm(servo_id, left);
      sleep(1);

      set_servo_pwm(servo_id, center);
      sleep(1);

      set_servo_pwm(servo_id, right);
      sleep(1);

      set_servo_pwm(servo_id, center);
      sleep(1);
    }

    close_servo_controller();
    return 0;
}

