/*
 * OLED.c
 *
 * Created: 10/20/2022 11:32:53 AM
 *  Author: seyed
 */ 
#include "OLED.h"
#include "FONTS.h"

void OLED_show_highscore() { OLED_write_str("test");/* Viser highscore */ }void OLED_write_cmd(int command) {
	volatile char *ext_oled_command = (char *) 0x1000;
	ext_oled_command[0] = command;
}void OLED_write_buff_data(int buf) {
	volatile char *data_ext_offset = (char *) 0x1200;
	data_ext_offset[0] = buf;
}void OLED_init() {
	//different command to from OLED datasheet manual
	OLED_write_cmd(0xa1); //segment remap
	OLED_write_cmd(0xda); //common pads hardware: alternative
	OLED_write_cmd(0x12);
	OLED_write_cmd(0xc8); //common output scan direction:com63~com0
	OLED_write_cmd(0xa8); //multiplex ration mode:63
	OLED_write_cmd(0x3f);
	OLED_write_cmd(0xd5); //display divide ratio/osc. freq. mode
	OLED_write_cmd(0x80);
	OLED_write_cmd(0x81); //contrast control
	OLED_write_cmd(0x50);
	OLED_write_cmd(0xd9); //set pre-charge period
	OLED_write_cmd(0x21);
	OLED_write_cmd(0x20);//Set Memory Addressing Mode
	OLED_write_cmd(0x02);	
	OLED_write_cmd(0xdb); 
	OLED_write_cmd(0x30);
	OLED_write_cmd(0xad); //master configuration
	OLED_write_cmd(0x00);
	OLED_write_cmd(0xa4); //out follows RAM content
	OLED_write_cmd(0xa6); //set normal display
	OLED_write_cmd(0xaf); // display on
}

void OLED_line_nav(int n){
	OLED_write_cmd(0xB0 + n);
}

void OLED_col_set(int col) {
	OLED_write_cmd(0x00 + (col % 16));
	OLED_write_cmd(0x10 + (col / 16));
}



void OLED_clear(){
	for (int line = 0; line < 8; line++) {
		OLED_line_nav(line);
		OLED_col_set(0);
		for (int i = 0; i < 128; i++) {
			OLED_write_buff_data(0b00000000);
		}
	}
}




void OLED_set_pos(int line, int coll){
	OLED_line_nav(line);
	OLED_col_set(coll);
	
}


void OLED_write_ch(char ch) {
	ch -= 32;
	for (int i = 0; i < 8; i++) {
		//change of font8[ch][i] to font8[12][i]
		int curr_byte = pgm_read_byte(&font8[ch][i]);
		OLED_write_buff_data(curr_byte);
	}
}

void OLED_write_str( char ch[]) {
	
	for (int i = 0; i < strlen(ch); i++) {
		
		OLED_write_ch(ch[i]);
	}
}




void OLED_print_arrow ( int row , int col )
{
	OLED_set_pos( row , col );
	OLED_write_buff_data (0b00011000 );
	OLED_write_buff_data (0b00011000 );
	OLED_write_buff_data (0b01111110 );
	OLED_write_buff_data (0b00111100 );
	OLED_write_buff_data (0b00011000 );
}

void OLED_clear_arrow ( int row , int col )
{
	OLED_set_pos( row , col );
	OLED_write_buff_data (0b00000000 );
	OLED_write_buff_data (0b00000000 );
	OLED_write_buff_data (0b00000000 );
	OLED_write_buff_data (0b00000000 );
	OLED_write_buff_data (0b00000000 );
}
