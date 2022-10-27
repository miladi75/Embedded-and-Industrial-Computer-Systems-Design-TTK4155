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


void oled_clear();


void oled_goto_line(int n);
void oled_goto_column(int column);

void oled_pos(int line, int coll);
int pos2menu(int line, int col);

void oled_print_char(char ch);

void oled_print( char ch[]);




void OLED_print_arrow ( int row , int col );




#endif /* OLED_H_ */