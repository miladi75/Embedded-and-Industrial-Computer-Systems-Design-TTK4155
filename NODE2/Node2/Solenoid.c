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
	//setter utganger MÅ BYTTE TIL RIKTIG UTGANG
	PIOA->PIO_PER |= PIO_PA16;
	PIOA->PIO_OER |= PIO_PA16;
	PIOA->PIO_SODR |= PIO_PA16;
	
}
 volatile int flag = 0;
 
void Solenoid_pulse(int button){
	
	if (button == 4 && flag == 0)
	{
// 		printf("test");
// 		printf("solenoid %d\n",button);
	
		flag = 1;
		//printf("-------------->flag %d \n",flag);
	//pulse MÅ BYTTE TIL RIKTIG UTGANG
		PIOA->PIO_CODR |= PIO_PA16;// clear PIO
		delay_ms(100);						//MÅ SETTE RIKTIG DELAY
		PIOA->PIO_SODR |= PIO_PA16; // set PIO
		
	}
	else if(button != 4) {
		
		flag = 0;
		//PIOA->PIO_SODR |= PIO_PA16;
	}
	
// 	
// 		printf("flag %d\n",flag);
}
