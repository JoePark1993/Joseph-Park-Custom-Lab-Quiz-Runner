#ifndef GAMEPLAY_H
#define GAMEPLAY_H

enum game_states {wait,player,question,clears} game_state = 0;
enum map_states {waitmap, object, roundover,clear} map_state = 0;
#define gametime 80
#define questiontime 8
#define up 1
#define down 17

//OBJECT SCROLLING & LOCATION
unsigned char index = 32;
	
//Time for round
unsigned char i = 0;
	
// FOR PLAYER
unsigned char jump = 0;
unsigned char position = 1;
unsigned char initial = 17;
unsigned char lastlocation = 0;
unsigned char currlocation = 0;
unsigned char hit = 0;

int gameplay_tick(int state){
	switch(state){
		case wait:
			if(gamebool == 1){
				state = player;
			} else {
				state = wait;
			}
			break;
		case player:
			i++;
			x = GetKeypadKey();
			if(i != gametime){
				if(jump == 0){
					initial = 1;
					position = 17;
					switch(x){
						case '2':
							jump += 2;
							initial = 17;
							position = 1;
							break;
					}
				} else if (jump > 0){
					jump -= 1;
				}
				state = player;
			} else {
				i = 0;
				state = question;
			}
			break;
		case question:
			i++;
			if(i != questiontime){
				state = roundover;
			} else {
				i = 0;
				state = clears;
			}
		case clears:
			state = player;
			break;
	}
	switch(state){
		case waitmap:
			break;
		case player:
			LCD_Cursor(initial);
			LCD_WriteData(' ');
			LCD_Cursor(position);
			LCD_WriteData(2);
			LCD_Cursor_Off();
			break;
		case question:
			break;
		case clears:
			break;
		default:
			state = waitmap;
	}
	return state;
}

int map_tick (int state){
	switch(state){
		case waitmap:
			if(gamebool == 1){
				state = object;
			} else {
				state = wait;
			}
			break;
		case object:
			LCD_Cursor(index);
			LCD_WriteData(' ');
			LCD_Cursor_Off();
			i++;
			index--;
			if(index == position){
				hit++;
			}
			if(i != gametime){
				state = object;
			} else {
				i = 0;
				index = 32;
				state = roundover;
			}
			break;
		case roundover:
			i++;
			if(i != questiontime){
				state = roundover;
			} else {
				i = 0;
				state = clear;
			}
			break;
		case clear:
			state = object;
		default:
			state = wait;
	}
	switch(state){
		case wait:
			break;
		case object:
			if(index == 16){
				index = 32;
			}
			LCD_Cursor(index);
			LCD_WriteData(1);
			LCD_Cursor_Off();
			break;
		case roundover:
			if(hit > 0){
				LCD_DisplayString(1,"You got hit");
			} else {
				LCD_DisplayString(1,"no hits detected");
			}
			break;
		case clear:
			LCD_ClearScreen();
			break;
		default:
			break;
	}
	return state;
}

#endif