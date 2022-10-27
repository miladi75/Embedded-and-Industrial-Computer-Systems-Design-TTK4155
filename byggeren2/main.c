/*
 * byggeren2.c
 *
 * Created: 10/20/2022 11:22:01 AM
 * Author : seyed
 */ 

#include <avr/io.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "UART.h"
#include "SRAM.h"
#include "OLED.h"
#include "OLEDMENU.h"
#include "JOYSTICK.h"

#include "CAN.h"
#include "MCP.h"
#include "SPI.h"
#include "MCP2515.h"





#define FOSC 4915200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

volatile int line = 0;
volatile int menu = 0;


void print_dir_type(joystick_dir_t dir){
	switch(dir){
		case UP:
			printf("\nUP\n");
			break;
		case DOWN:
			printf("\nDOWN\n");
			break;
			
		case RIGHT:
			printf("\nRIGHT\n");
			break;
		
		case LEFT:
			printf("\nLEFT\n");
			break;

		case NEUTRAL:
			printf("\nNEUTRAL\n");
			break;
			
	}
}

int main(void)
{
	oled_write_command(0x81);
	oled_write_command(0b1111111);
	oled_write_command(0xe3);
	//oled_write_command(0b1111111);
	oled_write_command(0xaf); //Turn on LCD screen
	oled_write_command(0x20); // set memory addressing mode
	oled_write_command(0b10); // set page addressing mode
	oled_write_command(0x2a);
	oled_write_command(0xae);
	
	UART_init(MYUBRR);
	SRAM_init();
	clk(0);
	oled_clear();
	oled_init();
	
	//xmem_read();
	//xmem_write();
	//stdout = &uart_stdio;
	//stdin = &uart_stdio;
	//unsigned char recived_char;
	//SRAM_test();
	
	//oled_goto_line(0);
	//oled_goto_column(0);
	
	for(int i = 0; i <= 3; i++){
		//oled_pos(i,4);
		//oled_print("START GAME");

		
	}   
	

	
	
	//getCurrentJoystickDirection();
	//joystick_pos();
	
	
	//joystick_dir_t dir = joystick_pos();

	
	
	
	//CAN TEST
	UART_init(MYUBRR);
	
	//uart_init(UBRR);
	can_init(); // Denne initierer mcp, som initierer spi.
	mcp_set_mode(MODE_NORMAL); //MODE_LOOPBACK

	// Sender melding
	message_t* message = {
		1, // Id
		32, // Lengde på dataen
		"NEW MESSAGE" // Data. Maks åtte byte
	};
	can_send(message); // Sender melding

	// Nå er meldingen sendt. Fordi vi er i loopbackmodus blir meldingen umiddelbart "mottatt" ac MCP2515.

	// Mottar melding
	message_t receive = can_receive();
	printf("Heisann sveisann, vi har fått ei melding.\r\n");
	printf("Id: %d \r\n", receive.id);
	printf("Lengde: %d \r\n", receive.length);
	printf("Melding: %s \r\n\r\n", receive.data);

	return 0;
		
	
		while (1) 
		{
			//spi_write("g");
			//_delay_ms(1000);
			
			//joystick_pos();
			//printf("X Pos: %d	", joy_read_x());
			//printf("Y Pos: %d		", joy_read_y());
			//printf("Line:  %d \n",line);
			//
		//
			////_delay_us(500);
			//joystick_dir_t dir = joystick_pos();
			//print_dir_type(dir);
			//
			//if (joy_read_x() < -50 && menu > 0) {
				//menu--;
				//oled_clear();
			//}
			//if (menu == 0) {
				//oled_simple_menu();
			//}	
				//
			//if (joy_read_y() < -50 && line < 7) {		
				//line++;
				//OLED_print_arrow(line,0);
				//OLED_clear_arrow(line-1,0);	
				//_delay_ms(500);	
			//}
			//
			//if (joy_read_y() > 50 && line > 0) {
				//line--;
				//OLED_print_arrow(line,0);
				//OLED_clear_arrow(line+1,0);		
				//_delay_ms(500);
	//
			//}
			//
			//if(joy_read_x() > 50 && line == 5) {	//Higscore menu
				//oled_highscores();		
				//menu = 1;
					//
			//}
			//if(joy_read_x() > 50 && line == 2) {	//PLAY GAME menu
				//oled_highscores();
				//menu = 1;
				//
			//}
			//if(joy_read_x() > 50 && line == 5) {	//Higscore menu
				//oled_highscores();
				//
			//}
		
		
		
    }

}



