/*
 * Solenoid.c
 *
 * Created: 10.11.2022 12:12:52
 *  Author: danie
 */ 
#include "sam.h"
#include "Solenoid.h"


void Solenoid_init(){
	//setter utganger MÅ BYTTE TIL RIKTIG UTGANG
	PIOA->PIO_PER |= PIO_PA16;
	PIOA->PIO_OER |= PIO_PA16;
	PIOA->PIO_SODR |= PIO_PA16;
	
}

void Solenoid_pulse(int button){
	
	if (button ==1 )
	{
	
	//pulse MÅ BYTTE TIL RIKTIG UTGANG
	PIOD->PIO_CODR |= PIO_PD8;// set PIO
	delay_us(300);						//MÅ SETTE RIKTIG DELAY
	PIOD->PIO_SODR |= PIO_PD8; // reset PIO
	
	}
	
	
}
