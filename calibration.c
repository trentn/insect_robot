#include "servo_controller.h"
#include <ncurses.h>

void init_screen(){
    initscr();
    raw();
}

int main(int argc, char** argv){
    
    /*TODO optionally initialize this from calibration file*/
    uint16_t pulses[NUM_JOINTS] = {0};


    init_servo_controller(NULL);
    init_screen();

    int calibrating = 1;
    while(calibrating){
        clear();
        noecho();
        printw("Press C to calibrate a servo\n");
        printw("Press Q to quit");
        refresh();

        char ch = getch();
        if(ch == 'c') {
            unsigned int servo_id = 0;
            uint16_t pulse_length = 1500;
            int adjust_servo = 1;
            clear();
            echo();
            printw("Select Servo: ");
            refresh();
            scanw("%d", &servo_id);
            printw("Press +/- to calibrate. Press 'S' to set the value.");
            refresh();


            while(adjust_servo){
                noecho();
                char cmd = getch();
                switch(cmd){
                    case '+':
                        pulse_length += 10;
                        break;
                    case '-':
                        pulse_length -= 10;
                        break;
                    case 's':
                        adjust_servo = 0;
                        pulses[servo_id] = pulse_length;
                        break;
                    default:
                        break;
                }
                set_servo_pwm((uint8_t)servo_id, pulse_length);
            }

            printw("\nServo %d set to %d\nPress ENTER to continue", servo_id, pulse_length);
            refresh();
            getch();
        } 
        else if(ch == 'q'){
            calibrating = 0;
        }
    }

    clear();
    printw("Calibration Complete\n\nServo ID,Pulse Length\n");
    for(int i = 0; i < NUM_JOINTS; i++){
        printw("%d,%d\n", i, pulses[i]);
    }
    printw("\n\nPress ENTER to close...");
    refresh();
    getch();


    endwin();

    return 0;
}