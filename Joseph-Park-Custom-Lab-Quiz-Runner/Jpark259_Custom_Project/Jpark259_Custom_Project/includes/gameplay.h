#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include "joystick.h"

enum game_states {wait,player,movement,lose,clears} game_state = 0;
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
unsigned char itime,j = 0;
	
// FOR PLAYER
unsigned char jump = 0;
unsigned char position = 1;
unsigned char initial = 1;
unsigned char lastlocation = 0;
unsigned char currlocation = 0;
unsigned char output = 0;
unsigned short ymove = 0;
unsigned short xmove = 0;
unsigned short initialy = 0;
unsigned short initialx = 0;



int gameplay_tick(int state){
	switch(state){
		case wait:
		initialy = joystick_Inity();
		initialx = joystick_Initx();
			if(gamebool == 1){
				state = player;
			} else {
				state = wait;
			}
			break;
		case player:
			foodout = 1;
			state = movement;
			
			break;
		case movement:
			if(gamebool == 1){
				ADMUX = REF_AVCC | 0x00;
				waiter(300);
				xmove = ADC;
				ADMUX = REF_AVCC | 0x01;
				waiter(300);
				ymove = ADC;
				if ((xmove < (initialx - 10))&& (position != 32) ) {
					position += 1;
				}
				if ((xmove > (initialx + 10)) &&(position != 1)) {
					position -= 1;
				}
				if ((ymove < (initialy - 10)) && (position >= 1 && position <= 16)) {
					position += 16;
				}
				if ((ymove > (initialy + 10)) && (position >=17 && position <= 32)) {
					position -= 16;
				}
				
				state = movement;
			} else if (gamebool == 0){
				state = lose;
			}
			break;
		case lose:
		foodout = 0;
		itime++;
		if(itime == 10){
			itime = 0;
			state = clears;
		} else {
			state = lose;
		}
			break;
		case clears:
			state = wait;
			break;
	}
	switch(state){
		case wait:
			break;
		case player:
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
		case lose:
			LCD_DisplayString(1,"LOSE");
			break;
		case clears:
			initial = 1;
			position = 1;
			foodout = 0;
			break;
		default:
			state = wait;
			break;
	}
	return state;
}

#endif