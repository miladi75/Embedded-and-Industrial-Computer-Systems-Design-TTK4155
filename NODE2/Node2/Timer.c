/*
 * Timer.c
 *
 * Created: 10.11.2022 11:13:00
 *  Author: danie
 */ 

#include "sam.h"
#include "Timer.h"
//#include "core_cm3.h"
#include <stdint.h>


#define F_CPU 84000000
volatile uint32_t wait_ticks = 0;


void delay_init(uint32_t verdi){
	
SystemCoreClockUpdate(); // code from system
SysTick_Config(verdi * SystemCoreClock/1000000); // code from system systickconfig value = 84

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
	SysTick_Config(1000*84); //1000 to convert us to ms
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
