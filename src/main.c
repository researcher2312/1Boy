#include <avr/io.h>
#include <avr/interrupt.h>
#include "1Boy.h"
#include "1Boy_screen.h"

volatile unsigned int time_ms = 0;
uint8_t previous_button_state [2] = {0};
uint8_t button_state [2] = {0};

uint8_t pressedNow(uint8_t button_number);
void displayScore(uint8_t player_1, uint8_t player_2);

int main(){
	DDRB |= LED1 | LED2 | LED3 | LED4 | LED5 | LED6 | LED7 | LED8;
	DDRD |= LED_RD | LED_GR | LED_BL;
	PORTD |= BT1 | BT2 | LED_RD | LED_GR | LED_BL;

	TCCR0A |= (1<<WGM01); //CTC mode
	TCCR0B |= (1<<CS00) | (1<<CS01); //64 prescaler, timer on
	OCR0A = 125; //delay, 1 KHz
	TIMSK |= (1<<OCIE0A); //interrupt enable

	uint16_t delta_time = 0;

//	uint8_t rgb []= {BLACK, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE};
//	uint8_t rgb_num = 0;
//
//	int (*program)(uint8_t);
//	program = intro;

	sei();

	uint8_t step = 0;
	uint16_t delay = 250;
	uint8_t points [2] = {0};
	uint16_t game_time = 0;

	int8_t position = 4;
	uint8_t direction = 1; //0 = left 1 = right



	while(1){
		if (time_ms > 10){ //100 Hz main loop
			delta_time = time_ms;
			game_time += time_ms;
			time_ms = 0;

			previous_button_state[0] = button_state[0];
			previous_button_state[1] = button_state[1];
			button_state[0] = BT1_DOWN;
			button_state[1] = BT2_DOWN;


			switch (step){
			case 0: //initial ball view
				clearScreen();
				addScreenPoint(4);
				if (game_time > 1000){
					++step;
					game_time = 0;
				}
				break;

			case 1: //normal game routine
				if (game_time > delay){
					clearScreen();
					if (direction){
						if (position == 0){
							points[0] += 1;
							step = 2;
							position = 4;
							direction = 0;
							delay = 2000;
						}
						else
							--position;
					}
					else{
						if (position == 8){
							points[1] += 1;
							step = 2;
							position = 4;
							direction = 1;
							delay = 2000;
						}
						else
							++position;
					}
					addScreenPoint(position);
					game_time = 0;
				}


				if (position == 8 && pressedNow(0)){
					direction = 1;
					delay = delay - delay/10;
				}

				if (position == 0 && pressedNow(1)){
					direction = 0;
					delay = delay - delay/10;
				}
				break;

			case 2: //points display
				clearScreen();
				addBar(0, points[0]);
				addBar(1, points[1]);
				if (points[0] == 5 || points[1] == 5){
					step = 3;
					break;
				}
				setRGBColor(BLUE);
				if (game_time > delay){
					delay = 250;
					game_time = 0;
					step = 0;
				}
				break;

			case 3:
				addBar(points[0]>points[1] ? 0 : 1, 5);
				_delay_ms(500);
				return;
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
