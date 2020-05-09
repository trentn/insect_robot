#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "leg_control.h"
#include "kinematics.h"

int main(int argc, char** argv){
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    struct timespec ts = {0, 100000000L};
    
    struct point foot_positions[4] = {0};
    struct pose leg_poses[4] = {0};


    //open file
    fp = fopen(argv[1], "r");
    if(fp == NULL){
        exit(EXIT_FAILURE);
    }

    load_calibration(argv[2]);


    //for each line in file
    while((read = getline(&line,&len,fp)) != -1) {
        //parse line in X,Y,Zs
        char* token = strtok(line, ",");
        for(int i = 0; i < 4; i++){
            if(token[0] == '*'){
            } else {
                //compute legs poses
                char ** coords = &token;
                foot_positions[i].X = strtod(*coords,coords);
                foot_positions[i].Y = strtod(*coords,coords);
                foot_positions[i].Z = strtod(*coords,NULL);

                inv_leg_kin(&foot_positions[i],&leg_poses[i]);
            }
            token = strtok(NULL, ",");
        }
        
        set_leg_pose(front_left,leg_poses[front_left].coxa_theta,leg_poses[front_left].femur_theta,leg_poses[front_left].tibia_theta);
	set_leg_pose(front_right,leg_poses[front_right].coxa_theta,leg_poses[front_right].femur_theta,leg_poses[front_right].tibia_theta);
        set_leg_pose(back_left,leg_poses[back_left].coxa_theta,leg_poses[back_left].femur_theta,leg_poses[back_left].tibia_theta);
        set_leg_pose(back_right,leg_poses[back_right].coxa_theta,leg_poses[back_right].femur_theta,leg_poses[back_right].tibia_theta);
        
        //wait for specified time
        //TODO prase this from input
        nanosleep(&ts, NULL);

    }

    fclose(fp);

    return 0;
}
