#include "movement.h"
#include <util/delay.h>

void stand(void) {
    //knees
    setServoAngle(0, 110);
    setServoAngle(4, 110);
    setServoAngle(2, 70);
    setServoAngle(6, 70);


    //hips
	setServoAngle(1, 140);
	setServoAngle(5, 140);
	setServoAngle(3, 40);
	setServoAngle(7, 40);
}

void moveForward(void) {
    //lift front left and rear right legs
    FRONT_LEFT_LIFT();
    REAR_RIGHT_LIFT();
    //move lifted legs forward
    FRONT_LEFT_HIP(90);
    REAR_RIGHT_HIP(180);

    //move lowered legs back
    FRONT_RIGHT_HIP(90);
    REAR_LEFT_HIP(0);
    _delay_ms(500); //delay to allow servos to actuall move;

    //lower legs
    FRONT_LEFT_LOWER();
    REAR_RIGHT_LOWER();
    _delay_ms(500);

    //lift front right and rear left legs
    FRONT_RIGHT_LIFT();
    REAR_LEFT_LIFT();

    //move lifted legs forward
    FRONT_RIGHT_HIP(0);
    REAR_LEFT_HIP(90);

    //move lowered legs back
    FRONT_LEFT_HIP(180);
    REAR_RIGHT_HIP(90);
    _delay_ms(500);

    //lower legs
    FRONT_RIGHT_LOWER();
    REAR_LEFT_LOWER();
    _delay_ms(500);
}

void moveBackward(void) {
    //lift front left and rear right legs
    FRONT_LEFT_LIFT();
    REAR_RIGHT_LIFT();
    //move lifted legs backward
    FRONT_LEFT_HIP(180);
    REAR_RIGHT_HIP(90);
    //move lowered legs forward
    FRONT_RIGHT_HIP(0);
    REAR_LEFT_HIP(90);
    _delay_ms(500); //delay to allow servos to actuall move;

    //lower legs
    FRONT_LEFT_LOWER();
    REAR_RIGHT_LOWER();
    _delay_ms(500);

    //lift front right and rear left legs
    FRONT_RIGHT_LIFT();
    REAR_LEFT_LIFT();
    //move lifted legs backward
    FRONT_RIGHT_HIP(90);
    REAR_LEFT_HIP(0);
    //move lowered legs forward
    FRONT_LEFT_HIP(90);
    REAR_RIGHT_HIP(180);
    _delay_ms(500);

    //lower legs
    FRONT_RIGHT_LOWER();
    REAR_LEFT_LOWER();
    _delay_ms(500);
}

void moveLeft(void) {
    FRONT_LEFT_LIFT();
    REAR_RIGHT_LIFT();

    FRONT_LEFT_HIP(90);
    REAR_RIGHT_HIP(40);

    FRONT_RIGHT_HIP(140);
    REAR_LEFT_HIP(90);
    _delay_ms(500);

    FRONT_LEFT_LOWER();
    REAR_RIGHT_LOWER();
    _delay_ms(3000);

    FRONT_RIGHT_LIFT();
    REAR_LEFT_LIFT();

    FRONT_RIGHT_HIP(90);
    REAR_LEFT_HIP(140);

    FRONT_LEFT_HIP(40);
    REAR_RIGHT_HIP(90);
    _delay_ms(500);

    FRONT_RIGHT_LOWER();
    REAR_LEFT_LOWER();
    _delay_ms(3000);
}

void moveRight(void) {
    FRONT_LEFT_LIFT();
    REAR_RIGHT_LIFT();

    FRONT_LEFT_HIP(40);
    REAR_RIGHT_HIP(90);

    FRONT_RIGHT_HIP(90);
    REAR_LEFT_HIP(140);
    _delay_ms(500);

    FRONT_LEFT_LOWER();
    REAR_RIGHT_LOWER();
    _delay_ms(3000);

    FRONT_RIGHT_LIFT();
    REAR_LEFT_LIFT();

    FRONT_RIGHT_HIP(140);
    REAR_LEFT_HIP(90);

    FRONT_LEFT_HIP(90);
    REAR_RIGHT_HIP(40);
    _delay_ms(500);

    FRONT_RIGHT_LOWER();
    REAR_LEFT_LOWER();
    _delay_ms(3000);
}