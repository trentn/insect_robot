#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "USART.h"
#include "servo.h"
#include "utils.h"

volatile char bytes[10] = {0};
volatile int bytes_index = 0;

volatile char servo_select = 0;

volatile int run = 0;

ISR(USART_RX_vect) {
	char byte = UDR0;
	transmitByte(byte);
	if (byte == '\r') {
		transmitByte('\n');
		bytes[bytes_index] = 0;
		if(bytes[0] == 's') {
			servo_select = atoi(bytes+1);
		} else if (bytes[0] == 'r') {
			run = 1;
		} else if (bytes[0] == 'p') {
			run = 0;
		} else {
			setServoAngle(servo_select, atoi(bytes));
		}
		bytes_index = 0;
	} else {
		bytes[bytes_index] = byte;
		bytes_index = (bytes_index + 1)%10;
	}
}


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
    setServoAngle(0, 180);
    setServoAngle(4, 180);
    //move lifted legs forward
    setServoAngle(1, 90);
    setServoAngle(5, 180);

    //move lowered legs back
    setServoAngle(3, 90);
    setServoAngle(7, 0);
    _delay_ms(500); //delay to allow servos to actuall move;

    //lower legs
    setServoAngle(0, 110);
    setServoAngle(4, 110);
    _delay_ms(500);

    //lift front right and rear left legs
    setServoAngle(2, 0);
    setServoAngle(6, 0);

    //move lifted legs forward
    setServoAngle(3, 0);
    setServoAngle(7, 90);

    //move lowered legs back
    setServoAngle(1, 180);
    setServoAngle(5, 90);
    _delay_ms(500);

    //lower legs
    setServoAngle(2, 70);
    setServoAngle(6, 70);
    _delay_ms(500);
}


int main(void) {
	clear_clkpr(); //set clock to 8MHz
	initUSART(8);


	registerServo(0);
	registerServo(1);
	registerServo(2);
	registerServo(3);
	registerServo(4);
	registerServo(5);
	registerServo(6);
	registerServo(7);
	
	initServoTimer();
    stand();

	printString("Welcome!\r\n");

	while(1) {
		if(run == 1) {
		    moveForward();
        } else {
            stand();
        }
	}
	return 0;
}
