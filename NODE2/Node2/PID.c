/*
 * PID.c
 *
 * Created: 10.11.2022 11:58:22
 *  Author: danie
 */ 

#include "sam.h"
#include "PID.h"




static PID_DATA PID = {0, 0, 0, 0, 0, 0, 0};
	
	
	
	
void PI_controller_init(void) {
	// set parameters
	PID.Kp = 25;//25 best values but not tuned properly
	PID.Ki = 5;//5
	
	//reset errors
	PID.sum_error = 0;
	PID.prev_error = 0;
	
	//time step
	PID.T = 1/50; 
	
	//max motor speed
	PID.max_u = 0x9c4;//2500 0xbb8; 3000 
}

int PI_controller(int ref, int current_value) {
	
	int error = ref - current_value;
	PID.sum_error += error;
	//printf("error%d\n",error);

	volatile int u_p = PID.Kp * error;
	volatile int u_i = PID.T * PID.Ki * PID.sum_error;
	volatile int u = u_p + u_i;
	//printf("error: %d\n",error);
	//printf("kp: %d\nui: %d\nu: %d\n",PID.Kp,u_i,u);

	PID.prev_error = error;

	if (u > PID.max_u) {
		u = PID.max_u; //max motor speed
	}
	else if (u < -PID.max_u) {
		u = -PID.max_u;
	}

	return u;
}