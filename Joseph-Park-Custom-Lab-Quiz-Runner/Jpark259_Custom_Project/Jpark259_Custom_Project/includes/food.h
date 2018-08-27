#ifndef FOOD_H
#define FOOD_H

enum food_states {waitfood,foodtime} food_state = 0;
unsigned char foodtotal = 14;
unsigned char food[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

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
			if(((rand() % 4) == 3) && foodout == 1 && foodtotal !=14){
				food[foodtotal] = 17;
				foodtotal++;
			} else if(((rand() % 4) == 1) && foodout == 1 && foodtotal != 14) {
				food[foodtotal] = 32;
				foodtotal++;
			} else if (foodout == 0){
				state = waitfood;
				break;
			}
			for(unsigned char f = 0; f < 15; f++){
				food[f] -=1;
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
			break;
		case foodtime:
			for(unsigned char g = 0; g < 15; g++){
				LCD_Cursor(food[g]);
				LCD_WriteData(2);
				LCD_Cursor_Off();
			}
			for(unsigned char h = 0; h < 15; h++){
				LCD_Cursor(food[h]+1);
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