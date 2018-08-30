#ifndef FOOD_H
#define FOOD_H
#include "gameplay.h"

enum food_states {waitfood,display,losescore, shift} food_state = 0;
unsigned char foodtotal = 14;
unsigned char food[15] = {5,12,0,0,10,0,8,0,0,7,30,3,0,20,0};
unsigned char poison[15] = {15,25,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char last = 0;
unsigned char scores = 0;
unsigned char scores2 = 0;
unsigned char scorestot = 0;
unsigned char b = 0;
unsigned char seed = 0;
unsigned char nseed = 1;

int food_tick(int state){
	switch(state){
		case waitfood:
			seed+=1;
			nseed+=2;
			scorestot = 0;
			scores = 0;
			scores2 = 0;
			if(foodout == 0){
				for(unsigned char f = 0; f<15;f++){
					if((srand(seed)%50)==1){
						//food[f] = (rand()%33);
					} else {
					food[f] = 0;
					}
					if ((srand(nseed)%20) == 1){
						//poison[f] = (rand() % 33);
					} 
				}
				for(unsigned char poi = 0; poi < 15; poi++){
					for(unsigned char pois = 0;pois < 15; pois++){
						if(poison[poi] == food[pois]){
							poison[poi] = 0;
						}
					}
				}
				state = waitfood;
			} else {
				state = display;
			}
			break;
		case display:
		if(reset){
			state = waitfood;
			break;
		}else {
			if(foodout == 1 && gamebool == 1){
				for(unsigned char q = 0; q <15; q++){
					LCD_Cursor(food[q]);
					LCD_WriteData(2);
					LCD_Cursor_Off;
					if(food[q] == 1){
						LCD_Cursor(food[q]);
						LCD_WriteData(' ');
						LCD_Cursor_Off;
					}
				}
				for(unsigned char t = t; t <15; t++){
					LCD_Cursor(poison[t]);
					LCD_WriteData(3);
					LCD_Cursor_Off;
					if(poison[t] == 1){
						LCD_Cursor(poison[t]);
						LCD_WriteData(' ');
						LCD_Cursor_Off;
					}
				}
				for(unsigned char hit = 0; hit < 15; hit++){
					if(position == food[hit]){
						last = hit;
						if(scores >= 9){
							scores=0;
							//++scores2;
							//scorestot++;
						} else {
							//++scores;
							//++scorestot;
						}
						food[hit] = rand() % 33;
						} else if ((initial-1) == food[hit]){
						last = hit;
						//++scores;
						food[hit] = rand() % 33;
					}
					
				}
				for(unsigned char s = 0; s <15; s++){
					if((food[s]-1)==0){
						food[s] = 32;
					}
					if(food[s] >= 3){
						food[s]--;
					} else if(food[s] == 2){
						LCD_Cursor(food[s]);
						LCD_WriteData(' ');
						LCD_Cursor_Off();
						food[s] = 32;
					}
				}
				for(unsigned char p = 0; p <15; p++){
					if((poison[p]-1)==0){
						poison[p] = 32;
					}
					if(poison[p] >= 3){
						poison[p]--;
					} else if(poison[p] == 2){
						LCD_Cursor(poison[p]);
						LCD_WriteData(' ');
						LCD_Cursor_Off();
							poison[p] = 32;
							
					}
				}
				for(unsigned char h = 0; h < 15; h++){
					if(position == poison[h]){
							gamebool = 0;
							foodout = 0;
						} 
				}
				state = shift;
			} else {
				state = losescore;
				}
			}
			break;
			case shift:
			if(reset){
				state = waitfood;
				break;
			} else{
				if(foodout == 1 && gamebool == 1){
					for(unsigned char q = 0; q <15; q++){
						if(food[q] == 0){
							continue;
						}
						LCD_Cursor(food[q]+1);
						LCD_WriteData(' ');
						LCD_Cursor_Off();
					
					}
					for(unsigned char hit = 0; hit < 15; hit++){
						if(position == food[hit]){
							last = hit;
						
							if(scores >= 9){
								scores=0;
								scores2++;
								scorestot++;
								} else {
								++scores;
								scorestot++;
							}
							food[hit] = rand() % 33;
							} else if ((initial) == food[hit]){
							last = hit;
							//scores++;
							food[hit] = rand() % 33;
						}
					
					}
					for(unsigned char r = 0; r <15; r++){
						if(poison[r] == 0){
							continue;
						}
						LCD_Cursor(poison[r]+1);
						LCD_WriteData(' ');
						LCD_Cursor_Off();
					}
					for(unsigned char hitp = 0; hitp < 15; hitp++){
						if(position == poison[hitp] || position == 2){
							gamebool = 0;
							foodout = 0;
							state = waitfood;
						} 
					}
					
					state = display;
				} else {
					state = losescore;
				}
			}
			break;
		case losescore:
			b++;
			if(b == 10){
				b = 0;
				
				if(scorestot > eeprom_read_byte(0)){
					eeprom_write_byte(0,scorestot);
				}			
				state = waitfood; 
			} else {
				state = losescore;
			}
	}
	switch(state){
		case waitfood:
			break;
		case display:
			LCD_Cursor(2);
			LCD_WriteData(4);
			LCD_Cursor_Off();
			break;
		case losescore:
			LCD_DisplayString(1,"Your Score:");
			LCD_Cursor(12);
			LCD_WriteData(scores2 + '0');
			LCD_Cursor(13);
			LCD_WriteData(scores + '0');
			LCD_Cursor_Off();
			break;
		case shift:
			break;
	}
	return state;
}

#endif FOOD_H