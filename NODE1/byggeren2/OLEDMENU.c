/*
 * OLEDMENU.c
 *
 * Created: 10/20/2022 11:49:14 AM
 *  Author: seyed
 */ 
#include <stdio.h>

#include "OLEDMENU.h"

#include "OLED.h"



#define OLED_COMMAND_START 0x1000
#define OLED_DATA_START 0x1200





volatile menu_t* currentMenu;


menu_t* allocNewMenu(menu_t* currParent, char* menuName ){
		// dynamically allocate new menu
		menu_t* menu = malloc(sizeof(menu_t));
		menu->menuTitle = menuName;
		menu->parent = currParent;
		menu->sibling = NULL;
		menu->child = NULL;
		return menu;
}


void initRightSibling(menu_t* menu, menu_t* child) {
	menu->sibling = child;
}


void initChildMenu(menu_t* menu, menu_t* childMenu) {
	menu->child = childMenu;
}

menu_t *oled_menu_init(void) {
	menu_t* mainMenu = allocNewMenu(currentMenu, "Main Menu");
	return currentMenu;
}



void menu_run(void);

void navigateToParent(menu_t* thisMenu){
	
}

void navigateToChild(menu_t* thisMenu){
	
}

void oled_print_menu(){
	
	for(int i = 0; i <= 3; i++){
		oled_pos(i,0);
		oled_print("START GAME");
	}
	oled_print("START");
	
	
}

void oled_simple_menu(){
	
	oled_pos(0,5);
	oled_print("MENU");
	oled_pos(1,5);
	oled_print("PLAY GAME");
	oled_pos(2,5);
	oled_print("DIFFICULITY:");
	oled_pos(3,5);
	oled_print("EASY");
	oled_pos(4,5);
	oled_print("MEDIUM");
	oled_pos(5,5);
	oled_print("HARD");
	oled_pos(6,5);
	oled_print("HIGHSCORES");
	
}

int highscore[] = {5, 6, 8, 2, 1};
	//ex, add highscore sort?
	
void oled_highscores(){
	oled_clear();
	oled_pos(0,0);
	
	for( int i = 0; i < 6; i++){
		oled_pos(i,5);
	
		oled_print("%d trym");
		//oled_print(highscore[i]);
		
		
	}
	
	
}


void printString2OLED(menu_t *thisMenu,char *str){
	//int i;
	//char buf[15];
	if(thisMenu->menuTitle == "MAIN_MENU"){
		
		oled_print("Main Menu");
	//while (str[i])
	//{
		//oled_print_char(str[i]);
		//i++;
		//
	//}
}
}

//void oled_goto_line(int n){
	//oled_write_command(0xB0 + n);
//
//}
/*



void oled_goto_column(int column) {
	oled_write_command(0x00 + (column % 16)); // Lower nibble
	oled_write_command(0x10 + (column / 16)); // Higher nibble
}





*/



//void oled_menu_print(menu_t *menu) {
	//
	//
	//oled_clear();
//
	//int line = 2;
	//
	////menu = menu->child;
	//
	////for (int i = 0; i < display_line_offset; i++){
		////menu = menu->right_sibling;
	////}
	////
	//
	//while (menu != NULL && line < 7) {
		//
		//oled_pos(line,0);
		//
		//oled_print(menu->menuTitle);
		//
		//++line;
	//}
	//
//}