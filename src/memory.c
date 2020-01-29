/*
 * memory.c
 *
 *  Created on: 28 sty 2020
 *      Author: researcher
 */
#include <avr/io.h>
#include "1Boy.h"
#include "1Boy_screen.h"

uint8_t memory(uint16_t *game_time){
	static uint32_t leftright = 3141885613;//0 = left, 1 = right
	static uint8_t step = 0;
	static uint32_t current_bit = 0;
	static uint8_t hightest_bit = 1;
	switch(step){
	case 0:
		if(*game_time > 700){
			clearScreen();
			*game_time = 0;
			step = 1;
			if(current_bit == hightest_bit){
				current_bit = 0;
				step = 2;
			}
		}
		break;
	case 1:
		if(*game_time > 100){
			clearScreen();
			*game_time = 0;
			addBar(leftright & (1<<current_bit), 5);
			current_bit++;
			step = 0;
		}
		break;
	case 2:
		clearScreen();
		setRGBColor(BLUE);
		if(pressedNow(0)){
			if(!(leftright & (1<<current_bit)))
				++current_bit;
			else{
				*game_time = 0;
				step = 3;
			}
		}
		else if(pressedNow(1)){
			if(leftright & (1<<current_bit))
				++current_bit;
			else{
				*game_time = 0;
				step = 3;
			}
		}
		if(current_bit == hightest_bit){
			current_bit = 0;
			++hightest_bit;
			step = 0;
		}

		break;
	case 3:
		setRGBColor(MAGENTA);
		if(*game_time > 3000){
			step = 0;
			current_bit = 0;
			hightest_bit = 1;
			return 1;
		}
		break;
	}

	return 0;
}

