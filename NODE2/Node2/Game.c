/*
 * Game.c
 *
 * Created: 03.11.2022 14:57:54
 *  Author: danie
 */ 
#include "ADC.h"
#include "can_controller.h"


int counter = 0;
int lives = 3;
int pause = 0;

void score_count(int button){
	
	int IR_level = ADC_read();
	
	
	
	
	if (IR_level == 0 && pause == 0)
	{ 
		counter = counter + 1;
		
		pause = 1;
		
	}
	
	if (button = 1)
	{
		pause = 0;
	}
	
	if (counter == lives)
	{
		//printf("Game over");
		
		
		
		CAN_MESSAGE msg;
		msg.id = 5;
		msg.data_length = 2;
		msg.data[0] = counter;
		
		return msg;
		
		
		can_send(&msg,0);
		counter = 0;
	}



}