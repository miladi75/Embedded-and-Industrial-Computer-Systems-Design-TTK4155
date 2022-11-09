/*
 * IncFile1.h
 *
 * Created: 09.11.2022 18:41:14
 *  Author: danie
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

void motor_init();

void motor_run_joystick(int joystick_value);

void motor_disable();

void motor_enable();


#endif /* MOTOR_H_ */