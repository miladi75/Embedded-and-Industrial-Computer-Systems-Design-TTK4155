/*
 * UART.h
 *
 * Created: 10/20/2022 11:24:05 AM
 *  Author: seyed
 */ 


#ifndef UART_H_
#define UART_H_
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>



void UART_Transmitt (unsigned char data, FILE * file);

unsigned char UART_Receive (FILE * file);

void UART_init ( unsigned int ubrr );



#endif /* UART_H_ */