/*
 * interrupt.c
 *
 * Author: Gustav O. Often and Eivind H. J�lsgard
 *
 * For use in TTK4155 Embedded and Industrial Computer Systems Design
 * NTNU - Norwegian University of Science and Technology
 *
 */ 

#include "can_interrupt.h"

#include <stdio.h>
#include "sam.h"

//#include "../uart_and_printf/printf-stdarg.h"
#include "printf-stdarg.h"
#include "can_controller.h"
#include "Motor.h"
#include "DAC.h"


#define DEBUG_INTERRUPT 0
volatile char e = 'e';
uint16_t UP = 2;
uint16_t DOWN = 3;
uint16_t LEFT = 0;
uint16_t RIGHT = 1;
uint16_t NEUTRAL = 4;
/**
 * \brief CAN0 Interrupt handler for RX, TX and bus error interrupts
 *
 * \param void
 *
 * \retval 
 */
void CAN0_Handler( void )
{
	if(DEBUG_INTERRUPT)printf("CAN0 interrupt\n\r");
	char can_sr = CAN0->CAN_SR; 
	
	//RX interrupt
	if(can_sr & (CAN_SR_MB1 | CAN_SR_MB2) )//Only mailbox 1 and 2 specified for receiving
	{
		CAN_MESSAGE message;
		if(can_sr & CAN_SR_MB1)  //Mailbox 1 event
		{
			can_receive(&message, 1);

		}
		else if(can_sr & CAN_SR_MB2) //Mailbox 2 event
		
		{
			can_receive(&message, 2);
		}
		else
		{
			printf("CAN0 message arrived in non-used mailbox\n\r");
		}
		
		if (message.id == 50)
		{
			printf("melding");
			//printf("new message mb_id 2%c\n",e);
			printf("id %d\n",message.id);
			printf("length %d\n",message.data_length);
			printf("data %c\n",message.data[0]);
			printf("data %c\n",message.data[1]);
			printf("data %c\n",message.data[2]);
			printf("data %c\n",message.data[3]);
			printf("data %c\n",message.data[4]);
		}
		
		if (message.id == 10)
		{
			
			//printf("new message%c\n",e);
			//printf("id %d\n",message.id);
			//printf("length %d\n",message.data_length);
			//
			if (message.data[0] == UP)
			{
				printf("up %c\n",e);
				printf("%c\n",message.data[0]);
			}
			else if (message.data[0] == DOWN)
			{
				printf("down %c\n",e);
				printf("%c\n",message.data[0]);
			}
			else if (message.data[0] == LEFT)
			{
				printf("left %c\n",e);
				printf("%c\n",message.data[0]);
			}
			else if (message.data[0] == RIGHT)
			{
				printf("right %c\n",e);
				printf("%c\n",message.data[0]);
			}
			else if (message.data[0] == NEUTRAL)
			{
				printf("neutral %c\n",e);
				printf("%c\n",message.data[0]);
			}
		}
		
		
		if (message.id == 20)
		{
			
			//set_servo_pos(message.data[0]);
			motor_run_joystick(message.data[0]);
			printf("x:%d    y%d\n",message.data[0],message.data[1]);
			
		}

		if(DEBUG_INTERRUPT)printf("message id: %d\n\r", message.id);
		if(DEBUG_INTERRUPT)printf("message data length: %d\n\r", message.data_length);
		for (int i = 0; i < message.data_length; i++)
		{
			if(DEBUG_INTERRUPT)printf("%d ", message.data[i]);
		}
		if(DEBUG_INTERRUPT)printf("\n\r");
	}
	
	if(can_sr & CAN_SR_MB0)
	{
		if(DEBUG_INTERRUPT) printf("CAN0 MB0 ready to send \n\r");
		
	//Disable interrupt
		CAN0->CAN_IDR = CAN_IER_MB0;

	}

	if(can_sr & CAN_SR_ERRP)
	{
		if(DEBUG_INTERRUPT)printf("CAN0 ERRP error\n\r");

	}
	if(can_sr & CAN_SR_TOVF)
	{
		if(DEBUG_INTERRUPT)printf("CAN0 timer overflow\n\r");

	}
	
	NVIC_ClearPendingIRQ(ID_CAN0);
	//sei();*/
}
