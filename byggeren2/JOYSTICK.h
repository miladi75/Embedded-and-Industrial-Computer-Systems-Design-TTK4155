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



void clk (int max);

void test_joystick(uint16_t addr );


void joyslide_pos (uint16_t addrx);

int joystick_pos();

int joy_read_x();

int joy_read_y();

int slide_read_l();

int slide_read_r();




#endif /* JOYSTICK_H_ */