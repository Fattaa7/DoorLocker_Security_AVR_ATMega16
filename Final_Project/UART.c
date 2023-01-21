/*
 * UART.c
 *
 *  Created on: Mar 21, 2021
 *      Author: ahmed
 */




#include "UART.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void UART_init(const struct UART *ptr)
{
	uint32 UBBR_value = (F_CPU / (8 * (*ptr).baud_rate)) - 1;


		UCSRA = (1<<U2X); /* Double Transmit Speed */
		UCSRB = (1<<RXEN) | (1<<TXEN); /* Enable Receive and Transmit */
		UCSRC |= (1<<URSEL) | (((*ptr).parity_bit)<<UPM0) | (((*ptr).stop_bit - 1)<<USBS) | (((*ptr).bit_data - 5)<< UCSZ0);
		UBRRH = UBBR_value >> 8;
		UBRRL = UBBR_value;
}

void UART_sendByte(const uint8 data)
{

	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	UDR = data;

}

uint8 UART_receiveByte(void)
{

	while(BIT_IS_CLEAR(UCSRA,RXC)){}

    return UDR;
}

void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}

}

void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;
	Str[i] = UART_receiveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_receiveByte();
	}
	Str[i] = '\0';
}
