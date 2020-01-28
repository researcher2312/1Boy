#include <avr/io.h>
#include "1Boy.h"
#include "1Boy_screen.h"

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
		current_screen.rgb = GREEN;
}

void rmScreenPoint(uint8_t position){
	if (position < 4)
		current_screen.leds &= ~(1<<position);
	else if (position > 4)
		current_screen.leds &= ~(1<<(position-1));
	else if (position == 4)
		current_screen.rgb = BLACK;
}

void addBar(uint8_t side, uint8_t size){ //0 = left 1 = right
	uint8_t i;
	for (i=0; i<size; ++i){
		if(side)
			addScreenPoint(i);
		else
			addScreenPoint(8-i);
	}
}


void fullGreen(){
	current_screen.rgb = GREEN;
	current_screen.leds = 0xff;
}

void setRGBColor(uint8_t color){
	current_screen.rgb = color;
}

void startBlink(uint16_t new_blink_delay){//if blink delay = 0 then blink is disabled
	current_screen.blink_delay = new_blink_delay;
}

void updateScreen(uint16_t delta_time){
	if (current_screen.blink_delay > 0){
		current_screen.current_blink += delta_time;
		if (current_screen.current_blink > current_screen.blink_delay)
			current_screen.current_blink = 0;
	}
	if (current_screen.blink_delay > 0 && current_screen.current_blink < current_screen.blink_delay/2){
			PORTB = 0x00;
			LED_GR_OFF;
			LED_BL_OFF;
			LED_RD_OFF;
	}
	else{
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
}
