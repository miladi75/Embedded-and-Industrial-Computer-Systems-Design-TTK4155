/*
 * OLEDMENU.c
 *
 * Created: 10/20/2022 11:49:14 AM
 *  Author: seyed
 */ 
#include <stdio.h>

#include "OLEDMENU.h"

#include "OLED.h"



void OLED_print_menu(){
	
	for(int i = 0; i <= 3; i++){
		OLED_set_pos(i,0);
		OLED_write_str("START GAME");
	}
	OLED_write_str("START");
	
	
}

void OLED_simple_menu(){
	
	OLED_set_pos(0,5);
	OLED_write_str("MENU");
	OLED_set_pos(1,5);
	OLED_write_str("PLAY GAME");
	OLED_set_pos(2,5);
	OLED_write_str("DIFFICULITY:");
	OLED_set_pos(3,5);
	OLED_write_str("EASY");
	OLED_set_pos(4,5);
	OLED_write_str("MEDIUM");
	OLED_set_pos(5,5);
	OLED_write_str("HARD");
	OLED_set_pos(6,5);
	OLED_write_str("HIGHSCORES");
	
}

int highscore[] = {5, 6, 8, 2, 1};

	
void OLED_highscores(){
	OLED_clear();
	OLED_set_pos(0,0);
	
	for( int i = 0; i < 6; i++){
		OLED_set_pos(i,5);
	
		OLED_write_str("%d trym");
		//oled_print(highscore[i]);
		
		
	}
	
	
}




