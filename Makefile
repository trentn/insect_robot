all: calibration spi_test angle_test reset stand_up

calibration: servo_controller.o
	gcc calibration.c servo_controller.o -lbcm2835 -lncurses -o calibration

spi_test: servo_controller.o
	gcc spi_test.c servo_controller.o -lbcm2835 -o spi_test

angle_test: servo_controller.o
	gcc angle_test.c servo_controller.o -lbcm2835 -o angle_test

reset: servo_controller.o
	gcc reset.c servo_controller.o	-lbcm2835 -o reset

stand_up: servo_controller.o
	gcc stand_up.c servo_controller.o	-lbcm2835 -o stand_up

servo_controller.o: servo_controller.c
	gcc -c servo_controller.c -o servo_controller.o


.PHONY: clean
cleanall: clean
	-rm *.o

clean:
	-rm calibration
	-rm reset
	-rm spi_test
	-rm angle_test
	-rm stand_up

