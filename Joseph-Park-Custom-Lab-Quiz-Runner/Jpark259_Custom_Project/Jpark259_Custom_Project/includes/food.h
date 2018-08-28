#ifndef FOOD_H
#define FOOD_H


enum food_states {waitfood,foodtime} food_state = 0;
unsigned char foodtotal = 14;
unsigned char poisontotal = 14;
unsigned char food[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char poison[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char last = 0;
unsigned char plast = 0;

int food_tick(int state){
	switch(state){
		case waitfood:
			if(foodout == 0){
				state = waitfood;
			} else {
				state = foodtime;
			}
			break;
		case foodtime:
			if(((rand() % 6) == 3) && foodout == 1 && foodtotal !=14){
				food[foodtotal] = 17;
				foodtotal++;
			} else if(((rand() % 6) == 1) && foodout == 1 && foodtotal != 14) {
				food[foodtotal] = 32;
				foodtotal++;
			} else if (((rand() % 10)==1) && foodout == 1 && poisontotal != 14) {
				poison[poisontotal] = rand() % 32;
				for(unsigned char t = 0; t<15; t++){
					if(food[t] == poison[t]){
						poison[t] = 0;
					}
				}
				poisontotal++;
			} else if (foodout == 0 && gamebool ==1){
				state = waitfood;
				break;
			}
			for(unsigned char f = 0; f < 15; f++){   //poison decrement
				food[f] -=1;
			}
			for(unsigned char p = 0; p < 15; p++){
				poison[p] -=1;
			}
			for(unsigned char hit = 0; hit < 15; hit++){
				if(position == food[hit]){
					last = hit;
					++scores;
					food[hit] = 0;
				} else if ((initial-1) == food[hit]){
					last = hit;
					++scores;
					food[hit] = 0;
				}
				
			}
			for(unsigned char phit = 0; phit < 15; phit++){
				if(position == poison[phit]){
					plast = phit;
					gamebool = 0;
					poison[phit] = 0;
					state = waitfood;
					} else if ((initial-1) == poison[phit]){
					plast = phit;
					gamebool = 0;
					poison[phit] = 0;
				}
			}
			state = foodtime;
			break;
	}
	switch(state){
		case waitfood:
			for(unsigned char d = 0; d < 15; d++){
				food[d] = 0;
			}
			foodtotal = 0;
			for(unsigned char e = 0; e < 15; e++){
				poison[e] = 0;
			}
			break;
		case foodtime:
			for(unsigned char g = 0; g < 15; g++){
				if(food[g] == 0){
					LCD_Cursor(position+1);
					LCD_WriteData(' ');
					LCD_Cursor_Off();
				} else if (food[g] > 0) {
					LCD_Cursor(food[g]);
					LCD_WriteData(3);
					LCD_Cursor_Off();
				}
			}
			for(unsigned char h = 0; h < 15; h++){
				LCD_Cursor(food[h]+1);
				LCD_WriteData(' ');
				LCD_Cursor_Off;
			}
			for(unsigned char y = 0; y < 15; y++){
				if(poison[y] == 0){
					LCD_Cursor(position+1);
					LCD_WriteData(' ');
					LCD_Cursor_Off();
				} else if (poison[y] > 0) {
					LCD_Cursor(poison[y]);
					LCD_WriteData(2);
					LCD_Cursor_Off();
				}
			}
			for(unsigned char u = 0; u < 15; u++){
				LCD_Cursor(poison[u]+1);
				LCD_WriteData(' ');
				LCD_Cursor_Off;
			}
			break;
		default:
			state = waitfood;
	}
	return state;
}

#endif FOOD_H