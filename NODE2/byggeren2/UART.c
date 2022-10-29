/*
 * UART.c
 *
 * Created: 10/20/2022 11:25:44 AM
 *  Author: seyed
 */ 
#include "UART.h"



void UART_Transmitt (unsigned char data, FILE * file){//, FILE * file
	
	while (!(UCSR0A & (1<<UDRE0)))
	;
	UDR0 = data;
	
}

unsigned char UART_Receive (FILE * file){//FILE * file
	
	while (!(UCSR0A &(1<<RXC0))){
		
		return UDR0;
	}
}

void UART_init ( unsigned int ubrr ){
	
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
	
	fdevopen(UART_Transmitt, UART_Receive);

	
}
