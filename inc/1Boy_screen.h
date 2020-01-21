/*
 * 1Boy_screen.h
 *
 *  Created on: 11 sty 2020
 *      Author: researcher
 */

#ifndef INC_1BOY_SCREEN_H_
#define INC_1BOY_SCREEN_H_

#define BLACK	0x00
#define RED		0x01
#define GREEN	0x02
#define BLUE	0x04
#define YELLOW	0x03
#define MAGENTA	0x05
#define CYAN	0x06
#define WHITE	0x07

typedef struct ScreenState{
	uint8_t leds; //all 8 bits
	uint8_t rgb;  //bits 0-2
} ScreenState;


extern ScreenState current_screen;

void updateScreen();
void clearScreen();
void addScreenPoint(uint8_t position);
void rmScreenPoint(uint8_t position);
void addBar(uint8_t side, uint8_t size);
void setRGBColor(uint8_t color);
void fullGreen();

int intro(uint8_t delta_time);


#endif /* INC_1BOY_SCREEN_H_ */
