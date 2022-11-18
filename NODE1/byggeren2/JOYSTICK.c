/*
 * JOYSTICK.c
 *
 * Created: 10/20/2022 11:43:45 AM
 *  Author: seyed
 */ 
#include "JOYSTICK.h"
#ifndef F_CPU
#define F_CPU 4915200
#endif

#define x_offset 160
#define y_offset 162


void clk (int max){
	DDRD	|= (1<< DDD4);
	TCCR3A	|= (1<< COM3A0);
	TCCR3B	|= (1<< WGM32);
	OCR3A	= max;
	TCCR3B	|= (1<< CS30);
}

void joystick_debugg(uint16_t addr ){
	//Offset base address: 0x1400
	volatile char *adc = (char *) 0x1400;
	adc[0] = addr;

	_delay_us(20);

	uint8_t verdi = adc[0];
	printf("verdi %d\n", verdi);

	_delay_ms(200);
}

int joystick_clickBtn_read() {
	DDRB &= ~(1 << DDB0);
	return (PINB & (1 << DDB0));
	
}


int joystick_read_xVal() {
	uint8_t addrx = 0b10000100;//left/right
	volatile char *adc = (char *) 0x1400;
	adc[0] = addrx;

	_delay_us(20);

	uint8_t verdix = adc[0];
	
	int pos = ( verdix - x_offset) * 100 / 127;
	int offset = 127 - x_offset;
	if (pos > 0) {
		pos = (pos *  100) / (100 + offset);
		} else if (pos < 0) {
		pos = (pos * 100) / (100 - offset);
	}
	return pos;
}

int joystick_read_yVal() {
	uint8_t addry = 0b10000001; //up/down
	volatile char *adc = (char *) 0x1400;
	adc[0] = addry;

	_delay_us(20);

	uint8_t verdiy = adc[0];
	
	int pos = ( verdiy - y_offset) * 100 / 127;
	int offset = 127 - y_offset;
	if (pos > 0) {
		pos = (pos * 100) / (100 + offset);
		} else if (pos < 0) {
		pos = (pos * 100) / (100 - offset);
	}
	return pos;
}

int joystick_slider_readLeft() {
	uint8_t addrsl = 0b10000011; //up/down
	volatile char *adc = (char *) 0x1400;
	adc[0] = addrsl;

	_delay_us(20);

	uint8_t verdisl = adc[0];
	
	int pos = verdisl;
	
	return pos;
}


int joystick_slider_readRight() {
	uint8_t addrsr = 0b10000010; //up/down
	volatile char *adc = (char *) 0x1400;
	adc[0] = addrsr;

	_delay_us(20);

	uint8_t verdisr = adc[0];
	int pos = verdisr;
	
	return pos;
}

joystick_dir_t joystick_pos() {
	
	int x = joystick_read_xVal();
	int y = joystick_read_yVal();
	
	if (abs(x) >= abs(y)){
		if (abs(x) < 10){
			return NEUTRAL;
		}
		else if (x <= -50){
			return LEFT;
		}
		else if (x >= 50) {
			return RIGHT;
		}
	}
	else{
		if (abs(y) < 10){
			return NEUTRAL;
		}
		else if (y < -50){
			return DOWN;
		}
		else if (y > 50) {
			return UP;
		}
	}
	
}

//For debugging
int getCurrentJoystickDirection(){
	int joyPos = joystick_pos();
	
	printf("\npos = %d\n", joyPos);
	return 0;
}


void joystick_dir_debugg(joystick_dir_t dir){
	switch(dir){
		case UP:
		printf("\nUP\n");
		break;
		case DOWN:
		printf("\nDOWN\n");
		break;
		
		case RIGHT:
		printf("\nRIGHT\n");
		break;
		
		case LEFT:
		printf("\nLEFT\n");
		break;

		case NEUTRAL:
		printf("\nNEUTRAL\n");
		break;
		
	}
}

int button_left(){
	//left button pin
	return PINB & (1 << DDB1);
}


int button_right(){
	//left button pin
	return PINB & (1 << DDB2);
}



