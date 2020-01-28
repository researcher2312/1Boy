/*
 * football.c
 *
 *  Created on: 21 sty 2020
 *      Author: researcher
 */
#include <avr/io.h>
#include "1Boy_screen.h"

extern uint16_t delay;
extern uint8_t pressedNow (uint8_t button_number);

uint8_t football(uint16_t *game_time){
	static int8_t position = 4;
	static uint8_t direction = 1; //0 = left 1 = right
	static uint8_t step = 0;
	static uint8_t points [2] = {0};
	static uint16_t delay = 250;
	switch (step){
	case 0: //initial ball view
		clearScreen();
		addScreenPoint(4);
		if (*game_time > 1000){
			++step;
			*game_time = 0;
		}
		break;

	case 1: //normal game routine
		if (*game_time > delay){
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
			*game_time = 0;
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
		if (*game_time > delay){
			delay = 250;
			*game_time = 0;
			step = 0;
		}
		break;

	case 3:
		clearScreen();
		addBar(points[0]>points[1] ? 0 : 1, 4);
		setRGBColor(RED);
		if (*game_time > 3000){
			*game_time = 0;
			step = 0;
			delay = 250;
			points[0] = 0;
			points[1]=1;
			return 1;
		}
	}
	return 0;
}
