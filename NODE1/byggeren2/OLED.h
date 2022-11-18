/*
 * OLED.h
 *
 * Created: 10/20/2022 11:32:25 AM
 *  Author: seyed
 */ 


#ifndef OLED_H_
#define OLED_H_

#include <avr/pgmspace.h>
#include <string.h>

void OLED_show_highscore();void OLED_write_cmd(int command);//void oled_write_command(int command);void OLED_write_buff_data(int data) ;void OLED_init();
void OLED_clear();


void OLED_line_nav(int n);
void OLED_col_set(int column);

void OLED_set_pos(int line, int coll);
int pos2menu(int line, int col);

void OLED_write_ch(char ch);

void OLED_write_str( char ch[]);




void OLED_print_arrow ( int row , int col );void OLED_clear_arrow ( int row , int col );




#endif /* OLED_H_ */