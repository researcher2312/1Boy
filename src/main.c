#include <avr/io.h>
#include <avr/interrupt.h>
#include "1Boy.h"
#include "1Boy_screen.h"

volatile unsigned int time_ms = 0;
uint8_t previous_button_state [2] = {0};
uint8_t button_state [2] = {0};

extern uint8_t football(uint16_t *game_time);
extern uint8_t memory(uint16_t *game_time);


int main(){
	DDRB |= LED1 | LED2 | LED3 | LED4 | LED5 | LED6 | LED7 | LED8;
	DDRD |= LED_RD | LED_GR | LED_BL;
	PORTD |= BT1 | BT2 | LED_RD | LED_GR | LED_BL;

	TCCR0A |= (1<<WGM01); //CTC mode
	TCCR0B |= (1<<CS00) | (1<<CS01); //64 prescaler, timer on
	OCR0A = 125; //delay, 1 KHz
	TIMSK |= (1<<OCIE0A); //interrupt enable

	sei();

	uint16_t delta_time = 0;
	uint16_t game_time = 0;
	uint8_t game_played = 5;
	uint8_t game_choice = 0;

	uint8_t intro_step = 0;

	while(1){
		if (time_ms > 10){ //100 Hz main loop
			delta_time = time_ms;
			game_time += time_ms;
			time_ms = 0;

			previous_button_state[0] = button_state[0];
			previous_button_state[1] = button_state[1];
			button_state[0] = BT1_DOWN;
			button_state[1] = BT2_DOWN;

			switch(game_played){
			case 0:
				startBlink(500);
				clearScreen();
				addScreenPoint(8-game_choice);
				if (pressedNow(1)){
					++game_choice;
					if(game_choice > 3)
						game_choice = 0;
				}
				if (pressedNow(0)){
					startBlink(0);
					game_time = 0;
					game_played = game_choice + 1;
				}
				break;

			case 1:
				if(football(&game_time) == 1)
					game_played = 0;
				break;

			case 2:
				if(memory(&game_time) == 1)
					game_played = 0;
				break;

			case 3:
				break;

			case 4:
				break;
			case 5:
				if(game_time > (250*intro_step + 250)){
					addScreenPoint(intro_step);
					addScreenPoint(8-intro_step);
					setRGBColor(BLACK + intro_step);
					++intro_step;
					if(intro_step == 8){
						clearScreen();
						game_played = 0;
					}
				}
				break;
			}



			updateScreen(delta_time);
		}
	}
}

uint8_t pressedNow(uint8_t button_number){
	if(button_state [button_number] == 1 && previous_button_state [button_number] == 0)
		return 1;
	else
		return 0;
}

ISR(TIMER0_COMPA_vect){
	++time_ms;
}
