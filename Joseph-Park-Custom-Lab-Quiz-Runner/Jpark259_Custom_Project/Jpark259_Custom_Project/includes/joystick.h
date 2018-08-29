#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <avr/io.h>

// Defining cardinal directions as ints
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

#define YAXISINIT 543
#define XAXISINIT 551
//Look up mux value www.pjrc.com/teensy/adc.html
#define REF_AVCC ( 1 << REFS0 )               
#define REF_INIT ( 1 << REFS0 ) | ( 1 << REFS1 )

#define YSENSOR 0x01 //Y-axis sensor is on port ADC1
#define XSENSOR 0x00 //X-axis sensor is on port ADC0

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}

void waiter( unsigned long numOPs ) {
	for (unsigned long i = 0; i < numOPs; i++) {
		asm("nop");
	}
}
unsigned short joystick_Initx(){
	unsigned short initial;
	ADMUX = REF_AVCC |0x00; //y
	waiter(500);
	initial = ADC;
	return initial;
}

unsigned short joystick_Inity(){
	unsigned short initial;
		ADMUX = REF_AVCC | 0x01; //x
		waiter(500);
		initial = ADC;
		
		return initial;
}


/*
unsigned char yaxis(void) {
	unsigned short adcVal;
	
	ADMUX = REF_AVCC | 0x00;
	waiter(300);

	adcVal = ADC;

	if (adcVal > (551 + 30)) {
		return 1;
	}
	else if (adcVal < (551 - 30)) {
		return 3;
	}

	return 0;
}

unsigned char xaxis(void) {
	unsigned short adcVal;

	ADMUX = REF_AVCC | 0x01;
	waiter(300);

	adcVal = ADC;

	if (adcVal > (543 + 30)) {
		return 4;
	}
	else if (adcVal < (543 - 30)) {
		return 2;
	}

	return 0;
}
*/

#endif