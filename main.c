/*
 * Lab_TTK4155.c
 *
 * Created: 01.09.2022 15:17:23
 * Author : danie
 */ 
#define F_CPU 4915200
#define FOSC 4915200
#define BAUD 9600 
#define MYUBRR FOSC/16/BAUD-1 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void UART_init ( unsigned int ubrr );
void UART_Transmitt (unsigned char data);
unsigned char UART_Receive( void ); 


static FILE uart_stdio = FDEV_SETUP_STREAM(
	(int(*)(char, struct __file *))UART_Transmitt,
	(int(*)(struct __file *))UART_Receive,
	_FDEV_SETUP_RW 
	);


int main(void)
{
	
	UART_init(MYUBRR);
	stdout = &uart_stdio;
	stdin = &uart_stdio;	
	
unsigned char recived_char;

    while (1) 
    {
		
		recived_char = UART_Receive();	
		
		
		printf("%c",recived_char);
		
		//printf(1);
		/*UART_Transmitt();
		UART_Receive();
		
			*/
		//_delay_ms(1000);
    }
}

void UART_init ( unsigned int ubrr ){
	
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);

	
}

void UART_Transmitt (unsigned char data){
	
	while (!(UCSR0A & (1<<UDRE0))){}
		
	UDR0 = data;
		
}

//dkjfkdjfjdkfkdjfkdfdf

unsigned char UART_Receive (void){
	
	while (!(UCSR0A &(1<<RXC0)))
	
		;
		
	return UDR0;
	
}