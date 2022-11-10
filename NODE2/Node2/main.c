/*
 * Node2.c
 *
 * Created: 28.10.2022 11:45:03
 * Author : danie
 */ //svart kort bein mot vcc


#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"
#include "can_interrupt.h"
#include "can_controller.h"
#include "PWM.h"
#include "ADC.h"
#include "Game.h"
#include "Motor.h"
#include "DAC.h"
#include "Timer.h"


//#include <util/delay.h>
#define k_p		35
#define k_i		20
#define k_d		1
#define T		1.0 / 50
#define	max_u		0x4FF

int main(void)
{
	
	
    /* Initialize the SAM system */
	volatile char e = 'e'; //bug i printf som ikke gir ny linje
    
	SystemInit(); // system init
	WDT->WDT_MR = WDT_MR_WDDIS; //disable watchdog timer
	
	
	configure_uart();
	can_init_def_tx_rx_mb(0x00290165);
	PWM_init();
	ADC_init();
	dac_init();
	motor_init();
	Solenoid_init();
	pid_controller_init(k_p,k_i,k_d, T, max_u);
	
	
	
	
	//motor_disable();
	motor_enable();
	
	
	//set_servo_pos(1);
	
	//test code solenoid
	//Solenoid_init();
	
	//PIOA->PIO_CODR |= PIO_PA16;//pulse
	//delay_us(100000);
	//PIOA->PIO_SODR |= PIO_PA16;
	// test code end
	
	
	
    while (1) 
    {
	CAN0_Handler();	
	score_count();
	//SysTick_Handler();
	
	
	//PIOA->PIO_CODR |= PIO_PA16;
	//PIOA->PIO_SODR |= PIO_PA16;
	
	
	if (ADC_read() == 0)
	{
		//printf("FALS%c",e);
	}
	else if (ADC_read() == 1)
	{
		//printf("TRU%c\n",e);
	}
	
		
    }
}
