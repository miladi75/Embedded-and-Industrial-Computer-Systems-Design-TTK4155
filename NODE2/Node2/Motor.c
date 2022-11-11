/*
 * Motor.c
 *
 * Created: 09.11.2022 18:41:06
 *  Author: danie
 */ 
#include "sam.h"
#include "DAC.h"
#include "Motor.h"
#include "Joystick.h"
#include "Timer.h"


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


void motor_run_joystick(int x_level) {
	//printf("\nxlevel%d\n",x_level); // for testing
	int joystick_value = joy_read_x(x_level);//convert from 0 -> 205 to -100 -> 100
	
	if (joystick_value > 0) {
		 PIOD->PIO_SODR = PIO_PD10; //set dir right
	}
	else
	 {
		PIOD->PIO_CODR = PIO_PD10; // set dir left
	}

	uint16_t speed = (uint16_t) 2*(0x4FF * abs(joystick_value) / 100);
	
	//printf("\nspeed:%d\n",speed); //for testing
	dac_write(speed); 
}

void motor_disable() {
	dac_write(0);//set motor speed to 0
	PIOD->PIO_CODR = PIO_PD9;
}

void motor_enable() {
	PIOD->PIO_SODR = PIO_PD9;
}


int motor_encoder(){
	
	PIOD->PIO_CODR |= PIO_PD0; //!EO (output encoder)

	PIOD->PIO_CODR |= PIO_PD2; // SEL low extract MSB
	//delay_us(20);
	for (int i = 0; i < 1000000; i++ ){
		;
	}
	uint8_t msb = (PIOC->PIO_PDSR & (0xFF << 1)) >> 1;

	PIOD->PIO_SODR |= PIO_PD2;// SEL high extract LSB
	//delay_us(20);
	for (int i = 0; i < 1000000; i++ ){
	;}
	
	uint8_t lsb = (PIOC->PIO_PDSR & (0xFF << 1)) >> 1;
	
	PIOD->PIO_CODR |= PIO_PD1;//reseting encoder
	PIOD->PIO_SODR |= PIO_PD1;

	PIOD->PIO_SODR |= PIO_PD0; //!OE disable output

	uint16_t encoder_data = ((msb << 8) | lsb);
	if (encoder_data & (1 << 15)) {
		return ((uint16_t) (~encoder_data) + 1);
	}
	return encoder_data;

	
}

static int scale_encoder_value(int value) {
	return 100 * value / (8800 - 0);//max value * value / max encoder value- min encoder value
}


void motor_joystick_PID(int reference) {
	int encoder_value = motor_encoder();
	int current_position = scale_encoder_value(encoder_value);
	int reference_value = joy_read_x(reference);
	int u = pid_controller(reference, current_position);
	printf("reference: %d		encoder_value:%d\n U value%d\n",reference_value,current_position,u);
	if (u > 0) {
		PIOD->PIO_SODR = PIO_PD10;// set dir right
		dac_write(u); //motor speed
	}
	else {
		PIOD->PIO_CODR = PIO_PD10;//set dir left
		dac_write(-u); //motor speed
	}
}