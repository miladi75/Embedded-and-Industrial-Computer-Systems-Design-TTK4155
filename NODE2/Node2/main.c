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



//#include <util/delay.h>

int main(void)
{
    /* Initialize the SAM system */
	volatile char e = 'e'; //bug i printf 
    
	SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS; //disable watchdog timer
	configure_uart();
	can_init_def_tx_rx_mb(0x00290165);
	PWM_init();
	ADC_init();
	dac_init();
	motor_init();
	
	
	
	
	motor_disable();
	motor_enable();
	
	
	//set_servo_pos(1);
    /* Replace with your application code */
	//set_servo_pos(1);
    while (1) 
    {
	CAN0_Handler();	
	score_count();
	//motor_run_joystick()
	
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
