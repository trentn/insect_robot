#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//AVR Lib includes
#include "USART.h"
#include "ADC.h"
#include "utils.h"

//Project Includes
#include "movement.h"


#define ADC_PIN 5


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
				run = 100;
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
			case 'q':
				run = 5;
				break;
			case 'e':
				run = 6;
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
	printString("Welcome!\r\n");
	
	initADC(ADC_PIN);
	
	initLegs();
	stand();

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
			case 5:
				turnRight();
				break;
			case 6:
				turnLeft();
				break;
			default:
				break;
		}
	}
	return 0;
}