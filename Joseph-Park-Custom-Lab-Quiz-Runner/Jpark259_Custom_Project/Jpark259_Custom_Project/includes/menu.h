#ifndef MENU_H
#define MENU_H
#include <avr/eeprom.h>
char msg[] = "Welcome to Package Collector. Press Button 1 to start!";
enum keypad_states {menu,game,score,game2,loses} keypad_state = 0;
unsigned char x;
unsigned char t;     //Time for lose screen
unsigned char selection = 0;
unsigned char ind = 0;
char reading[25];
unsigned char gamebool = 0;
unsigned char trans = 0;
unsigned char trans2 = 0;
unsigned char trans3 = 0;
#define button ~PINA &0x0C
#define button2 ~PINA & 0x18
#define reset ~PINA & 0x20
unsigned char it = 0;

int keypad_tick (int state) {
	switch(state) {
		case menu:
		gamebool = 0;
		if(selection == 1){
			selection = 0;
			gamebool = 1;
			state = game;
			} else if (selection == 2){
			selection = 0;
			state = score;
			} else if (selection == 3){
			selection = 0;
			state = game2;
			} else {
			state = menu;
		}
		break;
		case game:
		if (gamebool == 1){
		selection = 0;
		state = game;
		} else if (gamebool == 0){
			state = loses;
		}
		break;
		case score:
		it++;
		selection = 0;
			if(it == 10){
				it = 0;
				state = menu;
			} else {
				state = score;
			}
		break;
		case game2:
		selection = 0;
		break;
		case loses:		
			t++;
			if(t == 6){
				t = 0;
				state = menu;
			} else{
				state = loses;
			}
		break;
		default:
		state = menu;
		break;
	}
	
	switch(state) {
		case menu:
		LCD_DisplayString(1,"Button 3-Play!  Button 2-Score");
		LCD_Cursor_Off();
		x = GetKeypadKey();
		switch (button2) {
			case '\0':
			break;
			case 0x10:
			LCD_ClearScreen();
			selection = 1;
			
			break;
			case 0x08:
			LCD_ClearScreen();
			selection = 2;
			break;
			case 'C':
			selection = 3;
			default:
			break;
		}
		break;
		case game:
		break;
		case score:
		LCD_DisplayString(1,"Highest Score:");
		LCD_Cursor(17);
		trans = eeprom_read_byte(0)%10;
		trans2 = eeprom_read_byte(0)/10;	
		LCD_WriteData(trans2 + '0');
		LCD_Cursor(18);
		LCD_WriteData(trans + '0');
		LCD_Cursor_Off();
		break;
		case game2:
		LCD_DisplayString(1,"Character");
		break;
		case loses:
		break;
		default:
		state = menu;
		break;
	}
	
	return state;
}


#endif 