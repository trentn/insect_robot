#include "kinematics.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char** argv){
	struct point des_posn = {0,0,0};
	struct pose pose = {0,0,0};

	
	des_posn.X = strtod(argv[1],NULL);	
	des_posn.Y = strtod(argv[2],NULL);
	des_posn.Z = strtod(argv[3],NULL);
	
		
	printf("Input: X %lf, Y %lf, Z %lf\n",des_posn.X,des_posn.Y,des_posn.Z);

	inv_leg_kin(&des_posn,&pose);

	printf("Pose: Coxa %lf, Femur %lf, Tibia %lf\n",pose.coxa_theta,pose.femur_theta,pose.tibia_theta);

	return 0;
}
	
