/*
 * PID.c
 *
 * Created: 10.11.2022 11:58:22
 *  Author: danie
 */ 

#include "sam.h"
#include "PID.h"




static PID_DATA PID = {0, 0, 0, 0, 0, 0, 0};
	
	
	
	
void pid_controller_init(float k_p, float k_i, float k_d, float timestep, int max_u) {
	// set parameters
	PID.Kp = 40;
	PID.Ki = 20;
	PID.Kd = 1;
	
	//reset errors
	PID.sum_error = 0;
	PID.prev_error = 0;
	
	PID.T = 1/50;
	PID.max_u = 0xbb8; // 3000
}

int pid_controller(int ref, int current_value) {
	int error = ref - current_value;
	PID.sum_error += error;
	//printf("error%d\n",error);

	volatile int u_p = PID.Kp * error;
	volatile int u_i = PID.T * PID.Ki * PID.sum_error;
	//int u_d = (PID.Kd / PID.T) * (error - PID.prev_error);
	int u = u_p + u_i;// + u_d;
	//printf("error: %d\n",error);
	//printf("kp: %d\nui: %d\nu: %d\n",PID.Kp,u_i,u);

	PID.prev_error = error;

	if (u > PID.max_u) {
		u = PID.max_u;
	}
	else if (u < -PID.max_u) {
		u = -PID.max_u;
	}

	return u;
}