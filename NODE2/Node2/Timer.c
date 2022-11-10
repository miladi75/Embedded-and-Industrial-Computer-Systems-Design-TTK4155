/*
 * Timer.c
 *
 * Created: 10.11.2022 11:13:00
 *  Author: danie
 */ 

#include "sam.h"
#include "Timer.h"



static void SysTick_init_us(int period) {
	// set SysTick reload value
	SysTick->LOAD = ((int)(period*84) & SysTick_LOAD_RELOAD_Msk)-1;

	// reset SysTick counter value
	SysTick->VAL = 0;

	// set SysTick interrupt priority
	NVIC_SetPriority(SysTick_IRQn, 0);

	// set SysTick timer to MCK, enable interrupt and timer
	SysTick->CTRL  = (1 << SysTick_CTRL_CLKSOURCE_Pos) & SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= (1 << SysTick_CTRL_TICKINT_Pos) & SysTick_CTRL_TICKINT_Msk;
	SysTick->CTRL |= (1 << SysTick_CTRL_ENABLE_Pos) & SysTick_CTRL_ENABLE_Msk;
}


void delay_us(uint16_t us) {
	volatile int wait_ticks = 0;
	wait_ticks = us;
	SysTick_init_us(1);
	while(wait_ticks != 0);
}