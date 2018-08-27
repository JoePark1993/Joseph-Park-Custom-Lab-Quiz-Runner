#ifndef LED_H
#define LED_H

enum LED_states {waiting,led1,led2,led3,led4,led5} led_state = 0;
	
int LED_tick(int state){
	switch(state){
		case waiting:
			if(led_bool == 0){
				state = waiting;
			} else if(led_bool == 1) {
				if((rand() % 5) == 0){
					state = led1;
				} else if ((rand() % 5) == 1){
					state = led2;
				} else if((rand() % 5) == 2){
					state = led3;
				} else if ((rand() % 5) == 3){
					state = led4;
				} else if ((rand() % 5) == 4){
					state = led5;
				}
			}
			break;
		case led1:
			if(led_bool == 0){
				state = waiting;
			} else{
				state = waiting;
			}
			break;
		case led2:
			if(led_bool == 0){
				state = waiting;
			} else {
				state = waiting;
			}
			break;
		case led3:
			if(led_bool == 0){
				state = waiting;
			} else {
				state = waiting;
			}
			break;
		case led4:
			if(led_bool == 0){
				state = waiting;
			} else {
				state = waiting;
			}
			break;
		case led5:
			if(led_bool == 0){
				state = waiting;
			} else {
				state = waiting;
			}
			break;
	}
	switch(state){
		case waiting:
			PORTB = 0x00;
			break;
		case led1:
			PORTB = 0x01;
			break;
		case led2:
			PORTB = 0x02;
			break;
		case led3:
			PORTB = 0x04;
			break;
		case led4:
			PORTB = 0x08;
			break;
		case led5:
			PORTB = 0x10;
			break;
		default:
			state = waiting;
			break;
	}
	return state;
}
#endif 