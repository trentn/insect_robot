#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "USART.h"
#include "servo.h"
#include "utils.h"

#include "movement.h"

volatile char bytes[10] = {0};
volatile int bytes_index = 0;

volatile char servo_select = 0;
volatile int run = 0;

ISR(USART_RX_vect) {
	char byte = UDR0;
	transmitByte(byte);
	if (byte == '\r') {
		printString("\n> ");
		bytes[bytes_index] = 0;
		switch(bytes[0]) {
			case 's':
				servo_select = atoi(bytes+1);
				run = 5;
				break;
			case 'w':
			    run = 1;
				break;
			case 'x':
				run = 2;
				break;
			case 'a':
				run = 3;
				break;
			case 'd':
				run = 4;
				break;
			case 'p':
				run = 0;
				break;
			default:
				setServoAngle(servo_select, atoi(bytes));
				break;
		}
		bytes_index = 0;
	} else {
		bytes[bytes_index] = byte;
		bytes_index = (bytes_index + 1)%10;
	}
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
		switch(run) {
			case 0:
				stand();
				break;
			case 1:
				moveForward();
				break;
			case 2:
				moveBackward();
				break;
			case 3:
				moveLeft();
				break;
			case 4:
				moveRight();
				break;
			default:
				break;
		}
	}
	return 0;
}