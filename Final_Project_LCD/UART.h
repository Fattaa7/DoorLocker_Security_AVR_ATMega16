/*
 * UART.h
 *
 *  Created on: Mar 21, 2021
 *      Author: ahmed
 */

#ifndef UART_H_
#define UART_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

struct UART {
	uint8 bit_data;
	uint8 parity_bit;
	uint8 stop_bit;
	uint16 baud_rate;
};

#define PARITY_DISABLED 0
#define PARITY_ODD 1
#define PARITY_EVEN 2

#define STOP_BITS_1 0
#define STOP_BITS_2 1

#define FIVE_BIT_DATA 5
#define SIX_BIT_DATA 6
#define SEVEN_BIT_DATA 7
#define EIGHT_BIT_DATA 8
#define NINE_BIT_DATA 12

#define MC_RDY 0x10

void UART_init(const struct UART *ptr);
void UART_sendByte(const uint8 data);
uint8 UART_receiveByte(void);
void UART_sendString(const uint8 *Str);
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
