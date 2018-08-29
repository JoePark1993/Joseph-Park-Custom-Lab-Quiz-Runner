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
					} else if ((rand()%20) == 1){
						poison[f] = (rand() % 33);
					} else {
						food[f] = 0;
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
			if(foodout == 1 && gamebool == 1){
				for(unsigned char q = 0; q <15; q++){
					LCD_Cursor(food[q]);
					LCD_WriteData(1);
					LCD_Cursor_Off;
					if(food[q] == 1){
						LCD_Cursor(food[q]);
						LCD_WriteData(' ');
						LCD_Cursor_Off;
					}
				}
				for(unsigned char t = t; t <15; t++){
					LCD_Cursor(poison[t]);
					LCD_WriteData(5);
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
				state = waitfood;
			}
			break;
			case shift:
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
						++scores;
						food[hit] = rand() % 33;
						} else if ((initial) == food[hit]){
						last = hit;
						++scores;
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