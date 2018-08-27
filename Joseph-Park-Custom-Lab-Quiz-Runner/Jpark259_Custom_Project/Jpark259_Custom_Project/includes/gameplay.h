#ifndef GAMEPLAY_H
#define GAMEPLAY_H

enum game_states {wait,player,movement,question,clears} game_state = 0;
enum map_states {waitmap, object, roundover,clear} map_state = 0;
#define gametime 40
#define questiontime 10
#define up 1
#define down 17

//FOOD RELEASE
unsigned char foodout = 0;
unsigned char scores = 0;

//OBJECT SCROLLING & LOCATION
unsigned char index = 32;
	
//Time for round
unsigned char i,j = 0;
	
// FOR PLAYER
unsigned char jump = 0;
unsigned char position = 1;
unsigned char initial = 1;
unsigned char lastlocation = 0;
unsigned char currlocation = 0;

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
			j++;
			state = movement;
			break;
		case movement:
			j++;
			if(j == gametime){
				j = 0;
				state = question;
				break;
			}
			x = GetKeypadKey();
			switch(x){
				case '2':
					if(initial <= 32 && initial >= 17){
						position -= 16;
					}
				break;
				case'5':
					if(initial >= 1 && initial <= 16){
						position += 16;
					}
				break;
				case'6':
					if(initial < 32){
						position += 1;
					}
				break;
				case'4':
					if(initial > 1){
						position -= 1;
					}
				break;
			}
			
			state = movement;
			break;
		case question:
			j++;
			if(j != questiontime){
				state = question;
			} else {
				j = 0;
				state = clears;
			}
			break;
		case clears:
			state = player;
			break;
	}
	switch(state){
		case waitmap:
			break;
		case player:
			foodout = 1;      //FOOD RELEASE
			LCD_Cursor(initial);
			LCD_WriteData(1);
			LCD_Cursor_Off();
			break;
		case movement:
			LCD_Cursor(initial);
			LCD_WriteData(' ');
			LCD_Cursor(position);
			LCD_WriteData(1);
			LCD_Cursor_Off();
			initial = position;
			break;
		case question:
			foodout = 0;
			break;
		case clears:
			initial = 1;
			position = 1;
			foodout = 1;
			break;
		default:
			state = waitmap;
			break;
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
			i++;
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
			break;
		default:
			state = wait;
			break;
	}
	switch(state){
		case wait:
			break;
		case object:
			foodout = 1;
			break;
		case roundover:
			LCD_WriteData( scores + '0');
			foodout = 0;
			break;
		case clear:
			foodout = 1;
			LCD_ClearScreen();
			break;
		default:
			break;
	}
	return state;
}

#endif