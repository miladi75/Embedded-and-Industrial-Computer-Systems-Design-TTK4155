/*
 * Motor.c
 *
 * Created: 09.11.2022 18:41:06
 *  Author: danie
 */ 
#include "sam.h"
#include "DAC.h"
#include "Motor.h"


void motor_init() {
	dac_init();

	// enable PIOD pins to motor box as output
	PIOD->PIO_PER |= PIO_PD10 | PIO_PD9 | PIO_PD2 | PIO_PD1 | PIO_PD0;
	PIOD->PIO_OER |= PIO_PD10 | PIO_PD9 | PIO_PD2 | PIO_PD1 | PIO_PD0;

	// enable PIOC pins from motor encoder as input
	PIOC->PIO_PER |= (0xFF << 1);
	PIOC->PIO_ODR |= (0xFF << 1);

	// enable PIOC clock
	PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_PIOC << PMC_PCR_PID_Pos);
	PMC->PMC_PCER0 |= 1 << (ID_PIOC);
}


void motor_run_joystick(int joystick_value) {
	if (joystick_value > 95) {
		//motor_set_direction(RIGHT);
		 PIOD->PIO_SODR = PIO_PD10;
	}
	else {
		//motor_set_direction(LEFT);
		PIOD->PIO_CODR = PIO_PD10;
	}

	uint16_t speed = (uint16_t) (0x4FF * abs(joystick_value) / 100);
	//motor_set_speed(speed);
	dac_write(speed); 
}

void motor_disable() {
	//motor_set_speed(0);
	dac_write(0);
	PIOD->PIO_CODR = PIO_PD9;
}

void motor_enable() {
	PIOD->PIO_SODR = PIO_PD9;
}