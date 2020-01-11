#include <avr/io.h>
#include "1Boy.h"
#include "1Boy_screen.h"

volatile int screen_time;
ScreenState current_screen;

void clearScreen(){
	current_screen.leds = 0;
	current_screen.rgb = 0;
}

void addScreenPoint(uint8_t position){
	if (position < 4)
		current_screen.leds |= (1<<position);
	else if (position > 4)
		current_screen.leds |= (1<<(position-1));
	else if (position == 4)
		current_screen.rgb = 0x02;
}

void updateScreen(){
	PORTB = current_screen.leds;
	if (current_screen.rgb & 0x01)
		LED_RD_ON;
	else
		LED_RD_OFF;
	if (current_screen.rgb & 0x02)
		LED_GR_ON;
	else
		LED_GR_OFF;
	if (current_screen.rgb & 0x04)
		LED_BL_ON;
	else
		LED_BL_OFF;
}
