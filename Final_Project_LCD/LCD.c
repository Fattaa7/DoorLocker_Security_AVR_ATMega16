/*
 * LCD.c
 *
 *  Created on: Feb 15, 2021
 *      Author: ahmed
 */

#include "LCD.h"

void LCD_init(void){


	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW);

#if (DATA_BITS_MODE == 4)
#ifdef UPPER_PORTS_PIN
	LCD_DATA_PORT_DIR = 0xF0;
#else
	LCD_DATA_PORT_DIR = 0x0F;
#endif
	LCD_sendCommand(0x2);
	LCD_sendCommand(TWO_LINES_FOUR_BIT);
#elif (DATA_BITS_MODE == 8)

	LCD_DATA_PORT_DIR = 0xFF;
	LCD_sendCommand(TWO_LINES_EIGHT_BIT);
#endif

	LCD_sendCommand(CLEAR_COMMAND);
	LCD_sendCommand(CURSOR_OFF);




}

void LCD_sendCommand(uint8 a_command){

	CLEAR_BIT(LCD_CTRL_PORT, RS); /* command mode */
	CLEAR_BIT(LCD_CTRL_PORT, RW); /* Write mode */
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT, E); /* enable E */
	_delay_ms(1);
#if (DATA_BITS_MODE == 4)
	#ifdef UPPER_PORTS_PIN
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (a_command & 0xF0) ;
	#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((a_command & 0xF0) >> 4) ;
	#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT, E);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT, E);
	#ifdef UPPER_PORTS_PIN
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((a_command & 0x0F) << 4) ;
	#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((a_command & 0x0F)) ;
	#endif

#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT = a_command;
#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT, E);
	_delay_ms(1);

}

void LCD_displayCharacter(uint8 a_char){

	SET_BIT(LCD_CTRL_PORT, RS); /* Data mode */
	CLEAR_BIT(LCD_CTRL_PORT, RW); /* Write mode */
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT, E); /* enable E */
	_delay_ms(1);
#if (DATA_BITS_MODE == 4)
	#ifdef UPPER_PORTS_PIN
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (a_char & 0xF0) ;
	#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((a_char & 0xF0) >> 4) ;
	#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT, E);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT, E);
	#ifdef UPPER_PORTS_PIN
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((a_char & 0x0F) << 4) ;
	#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((a_char & 0x0F)) ;
	#endif

#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT = a_char;
#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT, E);
	_delay_ms(1);
}

void LCD_displayString(const char *a_string){

	for(uint8 i = 0 ; a_string[i] != '\0'; i++){

		LCD_displayCharacter(a_string[i]);
	}
}

void LCD_goToRowColumn(uint8 row, uint8 col){
	uint8 address;
	switch(row){
	case 0:
		address = col;
		break;
	case 1:
		address = 0x40 + col;
		break;
	case 2:
		address = 0x10 + col;
		break;
	case 3:
		address = 0x50 + col;
		break;
	default:
		address = col;
		break;
	}

	LCD_sendCommand(SET_CURSOR_LOCATION | address );
}

void LCD_displayStringRowColumn(uint8 a_row, uint8 a_col, const char *a_str){

	LCD_goToRowColumn(a_row, a_col);
	LCD_displayString(a_str);
}

void LCD_clearScreen(void){
	LCD_sendCommand(CLEAR_COMMAND);
}

void LCD_intgerToString(int a_int){

	char store[16];
	itoa(a_int,store,10);
	LCD_displayString(store);

}






