#ifndef MENU_H
#define MENU_H

char msg[] = "Welcome to The Game. Press 1 to start!";
enum keypad_states {title,menu,game,score,game2,loses} keypad_state = 0;
unsigned char x;
unsigned char t;     //Time for lose screen
unsigned char selection = 0;
unsigned char ind = 0;
char reading[25];
unsigned char gamebool = 0;
#define button ~PINA & 0x01

int keypad_tick (int state) {
	switch(state) {
		case title:
		if(button){
			selection = 0;
			state = menu;
			} else {
			state = title;
		}
		break;
		case menu:
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
		selection = 0;
		break;
		case game2:
		selection = 0;
		break;
		case loses:		
			t++;
			if(t == 10){
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
		case title:
		x = GetKeypadKey();
		switch(x){
			case '/0':
			break;
			case '1':
			x = 0;
			selection = 4;
			break;
			default:
			strncpy(reading, msg + ind, 16);
			reading[16] = '\0';
			LCD_ClearScreen();
			LCD_DisplayString(1, (const) reading);
			ind++;
			ind = ind % 23;
			
			break;
		}
		
		break;
		case menu:
		LCD_DisplayString(1,"A-Play! B-Score  C-Character");
		LCD_Cursor_Off();
		x = GetKeypadKey();
		switch (button) {
			case '\0':
			break;
			case 0x01:
			LCD_ClearScreen();
			selection = 1;
			
			break;
			case 'B':
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
		LCD_DisplayString(1,"SCORE");
		break;
		case game2:
		LCD_DisplayString(1,"Character");
		break;
		case loses:
		break;
		default:
		state = title;
		break;
	}
	
	return state;
}


#endif 