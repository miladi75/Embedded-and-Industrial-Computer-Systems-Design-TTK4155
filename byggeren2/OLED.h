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

void show_highscore();void oled_write_command(int command);//void oled_write_command(int command);void oled_write_data(int data) ;void oled_init();
void oled_clear();


void oled_goto_line(int n);
void oled_goto_column(int column);
void oled_pos(int line, int coll);


void oled_print_char(char ch);

void oled_print( char ch[]);




void OLED_print_arrow ( int row , int col );




#endif /* OLED_H_ */