/*
 * PID.h
 *
 * Created: 10.11.2022 11:58:36
 *  Author: danie
 */ 


#ifndef PID_H_
#define PID_H_

typedef struct {
	float Kp;
	float Ki;
	float Kd;
	int sum_error;
	int prev_error;
	float T;
	int max_u;
} PID_DATA;




#endif /* PID_H_ */