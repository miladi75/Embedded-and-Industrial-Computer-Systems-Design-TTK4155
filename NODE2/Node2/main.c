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
#include "PID.h"
#include "Solenoid.h"
#include "CAN.h"


//#include <util/delay.h>

//#define k_p		35
//#define k_i		20
//#define k_d		1
//#define T		1.0 / 50
//#define	max_u		2*0x4FF

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
	pid_controller_init(35,20,1, 1/50, 2*0x4FF);
	//delay_init();
	
	
	
	
	//motor_disable();
	motor_enable();
	
	
	//set_servo_pos(1);
	
	//test code solenoid
	//Solenoid_init();
	//
	//PIOA->PIO_CODR |= PIO_PA16;//pulse
	//delay_ms(10);
	//PIOA->PIO_SODR |= PIO_PA16;
	 //test code end
	
	//CAN_MESSAGE msg;
	//msg.id = 5;
	//msg.data_length = 4;
	//msg.data[0] = 't';
	//msg.data[1] = 'e';
	//msg.data[2] = 's';
	//msg.data[3] = 't';
	//
	////return msg;
	//
	//
	//can_send(&msg,0);
	
	
    while (1) 
    {
	CAN0_Handler();	
	score_count();
	CAN_use();
	//SysTick_Handler();
	//test();
	//message = CAN0_Handler();
	
	
	
	

	//printf("x:%d\n",message.data[0]);
	
	
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
