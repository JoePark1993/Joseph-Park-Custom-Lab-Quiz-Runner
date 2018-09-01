#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <avr/io.h>

//Look up mux value www.pjrc.com/teensy/adc.html
#define REF_AVCC ( 1 << REFS0 )               
#define REF_INIT ( 1 << REFS0 ) | ( 1 << REFS1 )

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

#endif
