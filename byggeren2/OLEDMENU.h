/*
 * OLEDMENU.h
 *
 * Created: 10/20/2022 11:48:01 AM
 *  Author: seyed
 */ 


#ifndef OLEDMENU_H_
#define OLEDMENU_H_




//typedef enum {
//UP,
//LEFT,
//ENTER,
//RIGHT,
//DOWN
//
//} LCD_joystick_NAV;//

typedef struct {
	char *menuTitle;
	struct menu_t* parent;
	struct menu_t* sibling;
	struct menu_t* child;
	
} menu_t;




//subMenu->text = text; // Setter inn tittel
//subMenu->function = function; // Setter inn peker til funksjon
//subMenu->parent = parent; // Setter inn peker til foreldremenyen
//
//// Legger undermenyelementet til slutten av undermeny-arrayet til foreldremenyen
//
//int i = 0;
//while (parent->subMenu[i] != NULL) {
//i++;
//}
//parent->subMenu[i] = subMenu;
//
//return subMenu; // Returnerer en peker til undermenyelementet vi har opprettet
//
//menue_ptr menu = malloc(sizeof(menu_t)); // Selve menyen initialiseres
//menue_ptr menu_highscore = menu_add(menu, "Show High Score", &show_highscore);
//}

typedef enum {
	MAIN_MENU,
	PLAYGAME,
	
} menuChoice;

void initRightSibling(menu_t* menu, menu_t* child);
void initChildMenu(menu_t* menu, menu_t* childMenu);
menu_t *oled_menu_init(void);



void navigateToParent(menu_t* thisMenu);

void navigateToChild(menu_t* thisMenu);


void printString2OLED(menu_t * menu, char *c);


//void oled_menu_print(menu_t *menu);




#endif /* OLEDMENU_H_ */