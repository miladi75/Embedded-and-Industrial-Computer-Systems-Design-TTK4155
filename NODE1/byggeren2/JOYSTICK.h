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

void joystick_debugg(uint16_t addr );


void joyslide_pos (uint16_t addrx);

//int joystick_pos();
joystick_dir_t joystick_pos(void);

int joystick_clickBtn_read();

int joystick_read_xVal();

int joystick_read_yVal();

int joystick_slider_readLeft();

int joystick_slider_readRight();


void joystick_dir_debugg(joystick_dir_t dir);


int button_left();


int button_right();




#endif /* JOYSTICK_H_ */