/*
 * Node2.c
 *
 * Created: 28.10.2022 11:45:03
 * Author : danie
 */ 


#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"
#include "can_interrupt.h"
#include "can_controller.h"

//#include <util/delay.h>

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	//WDT->WDT_MR = WDT_MR_WDDIS; //disable watchdog timer
	configure_uart();
	can_init_def_tx_rx_mb(0x00290165);
	
	
	
	volatile char e = 'e';
	//uint8_t mb_id = 1;
	//CAN_MESSAGE mymsg;
	////can_receive(&mymsg, mb_id);
	//if (can_receive(&mymsg, mb_id)==0)
	//{
		//printf("new message mb id 1%c\n",e);
		//printf("id %d\n",mymsg.id);
		//printf("length %c\n",mymsg.data_length);
		//printf("data %c\n",mymsg.data);
	//}
	//else if (can_receive(&mymsg, mb_id+1)==0)
	//{
		//printf("new message mb_id 2%c\n",e);
		//printf("id %d\n",mymsg.id);
		//printf("length %c\n",mymsg.data_length);
		//printf("data %c\n",mymsg.data);
	//}
	//else if (can_receive(&mymsg, mb_id)==1)
	//{
		//printf("Mailbox busy");
	//}
	//
	
    /* Replace with your application code */
    while (1) 
    {
	CAN0_Handler();	
	
		
    }
}
