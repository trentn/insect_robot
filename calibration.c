#include "servo_controller.h"
#include <ncurses.h>

void init_screen(){
    initscr();
    raw();
}

int main(int argc, char** argv){

    unsigned int servo_id = 11;
    uint16_t pulse_length = 1500;
    int adjust_servo = 1;
    int cali = 1;


    init_servo_controller();
    init_screen();

    while(cali){
        clear();
        noecho();
        printw("Press C to calibrate a servo\n");
        printw("Press Q to quit");
        refresh();

        char ch = getch();
        if(ch == 'c') {
            adjust_servo = 1;
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
            cali = 0;
        }
    }
    endwin();

    return 0;
}