SRC = servo_controller.c leg_control.c
OBJECTS = servo_controller.o leg_control.o

all: calibration reset stand_up

calibration: $(OBJECTS)
	gcc calibration.c $(OBJECTS) -lbcm2835 -lncurses -o $@

spi_test: $(OBJECTS)
	gcc spi_test.c $(OBJECTS) -lbcm2835 -o $@

angle_test: $(OBJECTS)
	gcc angle_test.c $(OBJECTS) -lbcm2835 -o $@

reset: $(OBJECTS)
	gcc reset.c $(OBJECTS) -lbcm2835 -o $@

stand_up: $(OBJECTS)
	gcc stand_up.c $(OBJECTS) -lbcm2835 -o $@

$(OBJECTS): %.o :%.c
	gcc -c $< -o $@


.PHONY: clean
cleanall: clean
	-rm *.o

clean:
	-rm calibration
	-rm reset
	-rm spi_test
	-rm angle_test
	-rm stand_up

