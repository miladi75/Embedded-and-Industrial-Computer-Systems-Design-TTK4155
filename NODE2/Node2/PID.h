/*
 * PID.h
 *
 * Created: 10.11.2022 11:58:36
 *  Author: danie
 */ 


#ifndef PID_H_
#define PID_H_


//define PI variables
typedef struct {
	float Kp;
	float Ki;
	int sum_error;
	int prev_error;
	float T;
	int max_u;
} PID_DATA;


int PI_controller(int ref, int current_value); // PI controller for use



void PI_controller_init(void); // first set-up with PI values



#endif /* PID_H_ */