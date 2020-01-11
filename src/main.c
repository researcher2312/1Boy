#include <avr/io.h>
#include <avr/interrupt.h>
#include "1Boy.h"
#include "1Boy_screen.h"

volatile unsigned int time_ms = 0;

int main(){
	DDRB |= LED1 | LED2 | LED3 | LED4 | LED5 | LED6 | LED7 | LED8;
	DDRD |= LED_RD | LED_GR | LED_BL;
	PORTD |= BT1 | BT2 | LED_RD | LED_GR | LED_BL;

	TCCR0A |= (1<<WGM01); //CTC mode
	TCCR0B |= (1<<CS00) | (1<<CS01); //64 prescaler, timer on
	OCR0A = 125; //delay, 1 KHz
	TIMSK |= (1<<OCIE0A); //interrupt enable

	uint8_t delta_time = 0;
	uint8_t previous_button_state [2] = {0};
	uint8_t button_state [2] = {0};

	sei();

	while(1){
		if (time_ms > 10){ //100 Hz main loop
			delta_time = time_ms;
			screen_time += delta_time;
			time_ms = 0;

			previous_button_state[0] = button_state[0];
			previous_button_state[1] = button_state[1];
			button_state[0] = BT1_DOWN;
			button_state[1] = BT2_DOWN;
		}
	}


}

ISR(TIMER0_COMPA_vect){
	++time_ms;
}
