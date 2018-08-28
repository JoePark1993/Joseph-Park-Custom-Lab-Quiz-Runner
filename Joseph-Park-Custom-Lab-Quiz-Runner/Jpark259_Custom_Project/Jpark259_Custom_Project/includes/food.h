#ifndef FOOD_H
#define FOOD_H


enum food_states {waitfood,display, shift} food_state = 0;
unsigned char foodtotal = 14;
unsigned char food[15] = {5,12,0,0,0,0,15,0,0,0,30,0,0,20,0};
unsigned char poison[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char last = 0;

int food_tick(int state){
	switch(state){
		case waitfood:
			if(foodout == 0){
				for(unsigned char f = 0; f<15;f++){
					if((rand()%6)==1){
						food[f] = (rand()%33);
					} else if ((rand()%10) == 1){
						poison[f] = (rand() % 33);
					} else {
						food[f] = 0;
					}
				}
				state = waitfood;
			} else {
				state = display;
			}
			break;
		case display:
			if(foodout == 1 && gamebool == 1){
				for(unsigned char q = 0; q <15; q++){
					LCD_Cursor(food[q]);
					LCD_WriteData(3);
					LCD_Cursor_Off;
				}
				for(unsigned char q = 0; q <15; q++){
					LCD_Cursor(poison[q]);
					LCD_WriteData(5);
					LCD_Cursor_Off;
				}
				for(unsigned char hit = 0; hit < 15; hit++){
					if(position == food[hit]){
						last = hit;
						++scores;
						food[hit] = rand() % 33;
						} else if ((initial-1) == food[hit]){
						last = hit;
						++scores;
						food[hit] = rand() % 33;;
					}
					
				}
				for(unsigned char s = 0; s <15; s++){
					if((food[s]-1)==0){
						food[s] = 32;
					}
					if(food[s] > 1){
						food[s]--;
					} else if(food[s] == 1 || food[s] == 0){
						food[s] = 0;
					}
				}
				state = shift;
			} else {
				state = waitfood;
			}
			break;
			case shift:
			if(foodout == 1 && gamebool == 1){
				for(unsigned char q = 0; q <15; q++){
					LCD_Cursor(food[q]+1);
					LCD_WriteData(' ');
					LCD_Cursor_Off;
				}
				for(unsigned char hit = 0; hit < 15; hit++){
					if(position == food[hit]){
						last = hit;
						++scores;
						food[hit] = rand() % 33;
						} else if ((initial-1) == food[hit]){
						last = hit;
						++scores;
						food[hit] = rand() % 33;
					}
					
				}
				state = display;
			} else {
				state = waitfood;
			}
			break;
	}
	switch(state){
		case waitfood:
			break;
		case display:
			break;
		case shift:
			break;
	}
	return state;
}

#endif FOOD_H