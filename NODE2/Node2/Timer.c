/*
 * Timer.c
 *
 * Created: 10.11.2022 11:13:00
 *  Author: danie
 */ 

#include "sam.h"
#include "Timer.h"
#include "core_cm3.h"
#include <stdint.h>


#define F_CPU 84000000
#define interrupt_prio 0


volatile uint32_t wait_ticks = 0;

//static void SysTick_init_us(int value) { 
	//SysTick->LOAD = ((value*84) & SysTick_LOAD_RELOAD_Msk)-1; //reload value
	//
	//SysTick->VAL = 0;//reset counter value and flag
//
	//NVIC_SetPriority(SysTick_IRQn, interrupt_prio);//interrupt priority
//
	//SysTick->CTRL |= (1 << SysTick_CTRL_CLKSOURCE_Pos) & SysTick_CTRL_CLKSOURCE_Msk;
	//SysTick->CTRL |= (1 << SysTick_CTRL_TICKINT_Pos) & SysTick_CTRL_TICKINT_Msk;
	//SysTick->CTRL |= (1 << SysTick_CTRL_ENABLE_Pos) & SysTick_CTRL_ENABLE_Msk;
//
//
//}
//
void delay_init(uint32_t verdi){
	
SystemCoreClockUpdate();
SysTick_Config(verdi * SystemCoreClock/1000000);

}

void delay_us(uint32_t us) {
	wait_ticks = us;
	//SysTick_init_us(1);
	SysTick_Config(84);
	//SysTick_Handler();
	//delay_init(1);
	while(wait_ticks > 0);
	SysTick->CTRL = 0;
}


void delay_ms(uint32_t ms) {
	wait_ticks = ms;
	//systick_init_us(1000);
	SysTick_Config(1000*84);
	//systick_handler();
	//delay_init(1000);
	while(wait_ticks > 0);
	SysTick->CTRL = 0;
	
}


void SysTick_Handler(void) {
	wait_ticks--;
	
	//else {
		//SysTick->CTRL = 0;
	//}
}
