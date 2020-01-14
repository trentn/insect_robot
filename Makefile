calibration:
	gcc calibration.c servo_controller.o -lbcm2835 -lncurses -o calibration