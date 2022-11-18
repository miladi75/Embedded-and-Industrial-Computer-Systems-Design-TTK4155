/*
 * IncFile1.h
 *
 * Created: 09.11.2022 18:41:14
 *  Author: danie
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

void Motor_init();

void Motor_run_joystick(int joystick_value);

void Motor_disable();

void Motor_enable();

int Motor_encoder();

void Motor_joystick_PID(int reference);

static int Motor_scale_encoder_value(int value);


#endif /* MOTOR_H_ */