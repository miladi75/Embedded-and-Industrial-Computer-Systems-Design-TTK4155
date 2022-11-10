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
	PID.Kp = k_p;
	PID.Ki = k_i;
	PID.Kd = k_d;
	
	//reset errors
	PID.sum_error = 0;
	PID.prev_error = 0;
	
	PID.T = timestep;
	PID.max_u = max_u;
}

int pid_controller(int ref, int current_value) {
	int error = ref - current_value;
	PID.sum_error += error;

	int u_p = PID.Kp * error;
	int u_i = PID.T * PID.Ki * PID.sum_error;
	int u_d = (PID.Kd / PID.T) * (error - PID.prev_error);
	int u = u_p + u_i + u_d;

	PID.prev_error = error;

	if (u > PID.max_u) {
		u = PID.max_u;
	}
	else if (u < -PID.max_u) {
		u = -PID.max_u;
	}

	return u;
}