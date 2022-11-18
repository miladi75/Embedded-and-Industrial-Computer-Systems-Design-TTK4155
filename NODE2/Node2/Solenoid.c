/*
 * Solenoid.c
 *
 * Created: 10.11.2022 12:12:52
 *  Author: danie
 */ 
#include "sam.h"
#include "Solenoid.h"
#include "Timer.h"


void Solenoid_init(){
	//set to output using PA7 on shield //MÅ BYTTE TIL RIKTIG UTGANG
	PIOA->PIO_PER |= PIO_PA16;
	PIOA->PIO_OER |= PIO_PA16;
	PIOA->PIO_SODR |= PIO_PA16;  
	
}
 volatile int flag = 0;
 
void Solenoid_pulse(int button){
	//check if btn pressed and flag not active 
	if (button == 4 && flag == 0)
	{
// 		printf("test");
// 		printf("solenoid %d\n",button);

		//flag to prevent multiple pulses
		flag = 1;
		//printf("-------------->flag %d \n",flag);
		
		
		//pulse out on PA7					 MÅ BYTTE TIL RIKTIG UTGANG
		PIOA->PIO_CODR |= PIO_PA16;// clear PIO
		delay_ms(100);						//MÅ SETTE RIKTIG DELAY
		PIOA->PIO_SODR |= PIO_PA16; // set PIO
		
	}
	else if(button != 4) {
		
		//reset flag
		flag = 0;
		//PIOA->PIO_SODR |= PIO_PA16;
	}
	
// 	
// 		printf("flag %d\n",flag);
}
