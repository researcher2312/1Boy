#include <avr/io.h>
#include <avr/interrupt.h>
#include "1Boy.h"

volatile int time_ms = 0;

int main(){
	uint8_t leds[] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8};
	uint8_t rgb[] = {LED_RD, LED_GR, LED_BL};

	DDRB |= LED1 | LED2 | LED3 | LED4 | LED5 | LED6 | LED7 | LED8;
	DDRD |= LED_RD | LED_GR | LED_BL;
	PORTD |= BT1 | BT2 | LED_RD | LED_GR | LED_BL;

	TCCR0A |= (1<<WGM01); //CTC mode
	TCCR0B |= (1<<CS00) | (1<<CS01); //64 prescaler, timer on
	OCR0A = 125; //delay, 1 KHz
	TIMSK |= (1<<OCIE0A); //interrupt enable

	sei();

	while(1){

	}


}

ISR(TIMER0_COMPA_vect){
	++time_ms;
}
