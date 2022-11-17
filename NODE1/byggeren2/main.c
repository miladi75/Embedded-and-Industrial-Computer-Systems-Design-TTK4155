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
#include <time.h>

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

typedef struct {
	uint16_t x;
	uint16_t y;
}coord_t;

message_t coord_via_CAN(coord_t xy, uint8_t msg_id){
	
	xy.x = (joy_read_x() + 93);
	xy.y = (joy_read_y() + 94);
	
	message_t message;
	message.length = 2;
	message.id = msg_id;
	message.data[0] = xy.x;
	
	message.data[1] = xy.y;
	 
	return message;
	
}

/**
IR sensor(svart) langt bein VCC
Hvit-Sensor: langt bein på VCC


*/

void temp_menu(){
	if (joy_read_x() < -50 && menu > 0) {
				menu--;
				oled_clear();
			}
			if (menu == 0) {
				oled_simple_menu();
			}	
				
			if (joy_read_y() < -50 && line < 7) {		
				line++;
				OLED_print_arrow(line,0);
				OLED_clear_arrow(line-1,0);	
				_delay_ms(500);	
			}
			
			if (joy_read_y() > 50 && line > 0) {
				line--;
				OLED_print_arrow(line,0);
				OLED_clear_arrow(line+1,0);		
				_delay_ms(500);
	
			}
			
			if(joy_read_x() > 50 && line == 5) {	//Higscore menu
				oled_highscores();		
				menu = 1;
					
			}
			if(joy_read_x() > 50 && line == 2) {	//PLAY GAME menu
				oled_highscores();
				menu = 1;
				
			}
			if(joy_read_x() > 50 && line == 5) {	//Higscore menu
				oled_highscores();
				
			}
}

message_t send_sliders_and_btns(){
	message_t msg;
	msg.length = 4;
	msg.id = 30;
	int l_slide_btn = buttons_slide_l();
	int r_slide_btn = buttons_slide_r();
	int slider_l = slide_read_l();
	int slider_r = slide_read_r();
	
	msg.data[0] = l_slide_btn;
	msg.data[1] = r_slide_btn;
	msg.data[2] = slider_l;
	msg.data[3] = slider_r;
	
	return msg;
	
}
int main(void)
{
	srand((unsigned int)time(NULL));
	
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
	
	//for(int i = 0; i <= 3; i++){
		//oled_pos(i,4);
		//oled_print("START GAME");

		
	//}   
	
//
	//mcp_init();
	//
	//// Setter MCP i loopbackmodus og sjekker CANSTAT:
	//mcp_set_mode(MODE_LOOPBACK);
	//printf("mode: %x\r\n", mcp_read(MCP_CANSTAT));
	//// Når MCP står i loopbackmodus skal CANSTAT være 0b01000000 aka 0x40
//
	//// Skriver en tilfeldig byte (0xA7) til MCP-sendebuffer0 og leser fra mottaksbuffer0
	//// Her bør man lese det samme som man sender så lenge MCPen står i loopbackmodus.
	//mcp_write(MCP_TXB0SIDH, 0xA7); // Skriver 0xA7 til sende-buffer nr. 0
	//mcp_request_to_send(0); // Sender 0xA7 fra bufferen ut på CAN-bussen
	//uint8_t byte = mcp_read(MCP_RXB0SIDH); // Leser fra mottaksbuffer nr. 0
	//printf("mottar: %x\r\n", byte); //Skal være samme som man sender, altså 0xA7
	
	//spi_set_ss();
	//spi_clear_ss;
	
	//getCurrentJoystickDirection();
	//joystick_pos();
	
	
	//joystick_dir_t dir = joystick_pos();

	
	
	
	//can test
	
	

	
	
	can_init(); //
	mcp_set_mode(MODE_NORMAL); //mode_loopback 0x40	
	
	
	

	_delay_ms(600);
	


		
		
		while (1) 
		{	
			//spi_write("g");
			
			joystick_dir_t dir = joystick_pos();
			
			
			//printf("x %d \n", joy_read_x());
			//printf("y %d \n", joy_read_y());

			message_t message = send_sliders_and_btns();
			
			can_send(&message);
			
			_delay_ms(500);
			temp_menu();
			//print_dir_type(dir);
			
			
		
		
		
    }

}



