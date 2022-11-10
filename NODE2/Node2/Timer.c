/*
 * Timer.c
 *
 * Created: 10.11.2022 11:13:00
 *  Author: danie
 */ 

#include "sam.h"
#include "Timer.h"


#define F_CPU 84000000


volatile int wait_ticks = 0;

static void SysTick_init_us(int value) { 
	SysTick->LOAD = ((int)(value*84) & SysTick_LOAD_RELOAD_Msk)-1; //reload value
	
	SysTick->VAL = 0;//reset counter value

	NVIC_SetPriority(SysTick_IRQn, 3);//interrupt priority

	SysTick->CTRL  = (1 << SysTick_CTRL_CLKSOURCE_Pos) & SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= (1 << SysTick_CTRL_TICKINT_Pos) & SysTick_CTRL_TICKINT_Msk;
	SysTick->CTRL |= (1 << SysTick_CTRL_ENABLE_Pos) & SysTick_CTRL_ENABLE_Msk;


}


void delay_us(uint16_t us) {
	wait_ticks = us;
	SysTick_init_us(1);
	while(wait_ticks != 0);
}


void delay_ms(uint16_t ms) {
	wait_ticks = ms;
	SysTick_init_us(1000);
	while(wait_ticks != 0);
}


void SysTick_Handler(void) {
	if(wait_ticks!=0) {
		wait_ticks--;
	}
	else {
		SysTick->CTRL = 0;
	}
}

