#include <avr/io.h>
#include <bit.h>
#include <timer.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "io.c"
#include "keypad.h"
#include "menu.h"
#include "gameplay.h"
#include "food.h"
#include "joystick.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>


unsigned short numTasks = 2;


typedef struct _task {
	/*Tasks should have members that include: state, period,
		a measurement of elapsed time, and a function pointer.*/
	signed char state; //Task's current state
	unsigned long int period; //Task period
	unsigned long int elapsedTime; //Time elapsed since last task tick
	int (*TickFct)(int); //Task tick function
} task;




char* from_key = " ";	
unsigned char in;
unsigned char scorebool = 0;
unsigned char charbool = 0;
unsigned char map = 32;
unsigned char in;




int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00; // PORTB set to output, outputs init 0s
	DDRC = 0xFF; PORTC = 0x00; // PC7..4 outputs init 0s, PC3..0 inputs init 1s
	DDRD = 0xFF; PORTD = 0xFF;
	static task task1, gameplay,food;
	time_t t;
	srand((unsigned) time(&t));
	LCD_man();
	LCD_food();
	LCD_poison();
	LCD_hole();
	ADC_init();
	//eeprom_write_byte(0,0);
	if(eeprom_read_byte(0)==255){
		eeprom_write_byte(0,0);
	}
	task1.state = keypad_state;
	task1.period = 250;
	task1.elapsedTime = 0;
	task1.TickFct = &keypad_tick;
	
	gameplay.state = game_state;
	gameplay.period = 250;
	gameplay.elapsedTime = 0;
	gameplay.TickFct = &gameplay_tick;
	
	food.state = food_state;
	food.period = 250;
	food.elapsedTime = 0;
	food.TickFct = &food_tick;
	
	LCD_init();

	in = 0;
	
	task *tasks[] = { &task1, &gameplay,&food };
	
	TimerSet(1);
	TimerOn();
	unsigned short i;
	while(1) {
		
		
		
		for ( i = 0; i < 3; i++ ) {
			// Task is ready to tick
			if ( tasks[i]->elapsedTime == tasks[i]->period ) {
				// Setting next state for task
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				// Reset the elapsed time for next tick.
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}
}
