/*
 * OLED.c
 *
 * Created: 10/20/2022 11:32:53 AM
 *  Author: seyed
 */ 
#include "OLED.h"
#include "FONTS.h"



void show_highscore() { oled_print("test");/* Viser highscore */ }void oled_write_command(int command) {
	volatile char *ext_oled_command = (char *) 0x1000;
	ext_oled_command[0] = command;
}void oled_write_data(int data) {
	volatile char *ext_oled_data = (char *) 0x1200;
	ext_oled_data[0] = data;
}void oled_init() {
	//oled_write_command(0xae); // display off
	oled_write_command(0xa1); //segment remap
	oled_write_command(0xda); //common pads hardware: alternative
	oled_write_command(0x12);
	oled_write_command(0xc8); //common output scan direction:com63~com0
	oled_write_command(0xa8); //multiplex ration mode:63
	oled_write_command(0x3f);
	oled_write_command(0xd5); //display divide ratio/osc. freq. mode
	oled_write_command(0x80);
	oled_write_command(0x81); //contrast control
	oled_write_command(0x50);
	oled_write_command(0xd9); //set pre-charge period
	oled_write_command(0x21);
	oled_write_command(0x20); //Set Memory Addressing Mode
	oled_write_command(0x02);//orginal
	//oled_write_command(0b10);
	oled_write_command(0xdb); //VCOM deselect level mode
	oled_write_command(0x30);
	oled_write_command(0xad); //master configuration
	oled_write_command(0x00);
	oled_write_command(0xa4); //out follows RAM content
	oled_write_command(0xa6); //set normal display
	oled_write_command(0xaf); // display on
}

void oled_clear(){
	for (int line = 0; line < 8; line++) {
		oled_goto_line(line);
		oled_goto_column(0);
		for (int i = 0; i < 128; i++) {
			oled_write_data(0b00000000);
		}
	}
}



void oled_goto_line(int n){
	oled_write_command(0xB0 + n);
}

void oled_goto_column(int column) {
	oled_write_command(0x00 + (column % 16)); // Lower nibble
	oled_write_command(0x10 + (column / 16)); // Higher nibble
}

void oled_pos(int line, int coll){
	oled_goto_line(line);
	oled_goto_column(coll);
}


void oled_print_char(char ch) {
	ch -= 32;
	for (int i = 0; i < 8; i++) {
		//change of font8[ch][i] to font8[12][i]
		int byte = pgm_read_byte(&font8[ch][i]);
		oled_write_data(byte);
	}
}

void oled_print( char ch[]) {
	
	for (int i = 0; i < strlen(ch); i++) {
		
		oled_print_char(ch[i]);
	}
}




void OLED_print_arrow ( int row , int col )
{
	//OLED_pos ( row , col );
	oled_write_data (0b00011000 );
	oled_write_data (0b00011000 );
	oled_write_data (0b01111110 );
	oled_write_data (0b00111100 );
	oled_write_data (0b00011000 );
}