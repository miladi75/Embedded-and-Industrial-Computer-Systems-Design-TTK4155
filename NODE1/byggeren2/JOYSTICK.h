/*
 * JOYSTICK.h
 *
 * Created: 10/20/2022 11:42:45 AM
 *  Author: seyed
 */ 

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

typedef enum {LEFT, RIGHT, UP, DOWN, NEUTRAL} joystick_dir_t;
	


void clk (int max);

void test_joystick(uint16_t addr );


void joyslide_pos (uint16_t addrx);

//int joystick_pos();
joystick_dir_t joystick_pos(void);

int joy_click();

int joy_read_x();

int joy_read_y();

int slide_read_l();

int slide_read_r();


void print_dir_type(joystick_dir_t dir);


int buttons_slide_l();


int buttons_slide_r();


int btn_left();
int btn_right();




#endif /* JOYSTICK_H_ */