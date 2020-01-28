/*
 * 1Boy.h
 *
 *  Created on: 30 gru 2019
 *      Author: researcher
 */

#ifndef INC_1BOY_H_
#define INC_1BOY_H_

#define LED1 (1<<PB7)
#define LED2 (1<<PB6)
#define LED3 (1<<PB5)
#define LED4 (1<<PB4)
#define LED5 (1<<PB3)
#define LED6 (1<<PB2)
#define LED7 (1<<PB1)
#define LED8 (1<<PB0)

#define LED_RD (1<<PD6)
#define LED_GR (1<<PD5)
#define LED_BL (1<<PD4)

#define LED_RD_OFF PORTD |= LED_RD
#define LED_GR_OFF PORTD |= LED_GR
#define LED_BL_OFF PORTD |= LED_BL

#define LED_RD_ON PORTD &= ~LED_RD
#define LED_GR_ON PORTD &= ~LED_GR
#define LED_BL_ON PORTD &= ~LED_BL

#define BT1 (1<<PD0)
#define BT2 (1<<PD1)

#define BT1_DOWN !(PIND & BT1)
#define BT2_DOWN !(PIND & BT2)

uint8_t pressedNow(uint8_t button_number);



#endif /* INC_1BOY_H_ */
