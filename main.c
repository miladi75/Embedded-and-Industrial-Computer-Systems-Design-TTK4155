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
#include <stdlib.h>



void UART_init ( unsigned int ubrr );
void UART_Transmitt (unsigned char data, FILE * file);//, FILE * file
unsigned char UART_Receive(FILE * file); // FILE * file 

/*
static FILE uart_stdio = FDEV_SETUP_STREAM(
	(int(*)(char, struct __file *))UART_Transmitt,
	(int(*)(struct __file *))UART_Receive,
	_FDEV_SETUP_RW 
	);
*/

int main(void)
{
	
	SRAM_init();
	UART_init(MYUBRR);
	//stdout = &uart_stdio;
	//stdin = &uart_stdio;
	//unsigned char recived_char;
	SRAM_test();
	
    while (1) 
    {
		
	
		//printf("a");
		//recived_char = UART_Receive(FILE * file);// FILE * file
		//printf("%c",recived_char);
	
		/*if (recived_char == 's')
		{
			SRAM_test();
		}
		*/
    }
}

void UART_init ( unsigned int ubrr ){
	
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
	
	fdevopen(UART_Transmitt, UART_Receive);

	
}

void UART_Transmitt (unsigned char data, FILE * file){//, FILE * file
	
	while (!(UCSR0A & (1<<UDRE0)))
		;
		UDR0 = data;

	return 0;
		
	
}

unsigned char UART_Receive (FILE * file){//FILE * file
	
	while (!(UCSR0A &(1<<RXC0))){
		
	return UDR0;
	}
}

//
//void xmem_init ( void ){
	//MCUCR |= (1 << SRE ); // enable XMEM
	//SFIOR |= (1 << XMM0 ); // mask unused bits
//}

void SRAM_init() {
	MCUCR |= (1 << SRE); 
	SFIOR |= (1 << XMM2)|(1<<XMM0); //fjerner JTAG
	
}

void SRAM_test(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}

