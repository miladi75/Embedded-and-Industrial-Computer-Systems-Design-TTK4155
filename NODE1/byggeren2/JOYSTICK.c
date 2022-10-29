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
	DDRD |= (1<< DDD4);//PD4 som output
	TCCR3A |= (1<< COM3A0);
	TCCR3B |= (1<< WGM32);
	OCR3A = max;
	TCCR3B |= (1<< CS30);
}

void test_joystick(uint16_t addr ){
	volatile char *adc = (char *) 0x1400;//BASE_ADDRESS
	adc[0] = addr;

	_delay_us(20);

	uint8_t verdi = adc[0];
	printf("verdi %d\n", verdi);

	_delay_ms(200);
}

int joy_click() {
	DDRB &= ~(1 << DDB0);
	return (PINB & (1 << DDB0));
	
}


int joy_read_x() {
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

int joy_read_y() {
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

int slide_read_l() {
	uint8_t addrsl = 0b10000011; //up/down
	volatile char *adc = (char *) 0x1400;
	adc[0] = addrsl;

	_delay_us(20);

	uint8_t verdisl = adc[0];
	
	int pos = verdisl;
	
	return pos;
}


int slide_read_r() {
	uint8_t addrsr = 0b10000010; //up/down
	volatile char *adc = (char *) 0x1400;
	adc[0] = addrsr;

	_delay_us(20);

	uint8_t verdisr = adc[0];
	int pos = verdisr;
	
	return pos;
}

joystick_dir_t joystick_pos() {
	
	int x = joy_read_x();
	int y = joy_read_y();
	
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


int getCurrentJoystickDirection(){
	int joyPos = joystick_pos();
	
	printf("\npos = %d\n", joyPos);
	return 0;
}