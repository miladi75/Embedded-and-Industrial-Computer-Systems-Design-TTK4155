/*
 * Node2.c
 *
 * Created: 28.10.2022 11:45:03
 * Author : danie
 * 
 * uart.c
 * Author: Gustav O. Often and Eivind H. Jølsgard
 *
 *
 * can_controller.h
 * Author: Gustav O. Often and Eivind H. J?lsgard
 *
 *
 * printf-stdarg
 * Edited 2020 by Eivind H. Jølsgard and Gustav O. Often for use in course TTK4155
 */ 


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


//svart kort bein mot vcc

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
	DAC_init();
	Motor_init();
	Solenoid_init();
	PI_controller_init();
	//delay_init();
	Motor_enable();
	
	
		
		
	
	
    while (1) 
    {
	CAN0_Handler();	
	//score_count();
	CAN_use();
	//SysTick_Handler();
	//test();
	//message = CAN0_Handler();
	
// 	if (CAN_use()== 10)
// 	{
// 		CAN_MESSAGE msg_1;
// 		msg_1.id = 2;
// 		msg_1.data_length = 4;
// 		msg_1.data[0] = 't';
// 		msg_1.data[1] = 't';
// 		msg_1.data[2] = 't';
// 		msg_1.data[3] = 't';
// 		
// 		can_send(&msg_1,0);
// 		
// 		printf("msg sent");
// 	}
	//can_send(&msg,0);
	
	

	//printf("x:%d\n",message.data[0]);
	
	
	//PIOA->PIO_CODR |= PIO_PA16;
	//PIOA->PIO_SODR |= PIO_PA16;
// 	
// 	printf("adc: %d\n",ADC_read());
// 	if (ADC_read() == 0)
// 	{
// 		printf("FALS%c",e);
// 	}
// 	else if (ADC_read() == 1)
// 	{
// 		printf("TRU%c\n",e);
// 	}
// 	
// 	
    }
}
