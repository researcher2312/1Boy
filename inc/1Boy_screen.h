/*
 * 1Boy_screen.h
 *
 *  Created on: 11 sty 2020
 *      Author: researcher
 */

#ifndef INC_1BOY_SCREEN_H_
#define INC_1BOY_SCREEN_H_

typedef struct ScreenState{
	uint8_t leds; //all 8 bits
	uint8_t rgb;  //bits 0-2
} ScreenState;

extern ScreenState current_screen;
extern volatile int screen_time;


void updateScreen();
void clearScreen();
void addScreenPoint(uint8_t position);


#endif /* INC_1BOY_SCREEN_H_ */
