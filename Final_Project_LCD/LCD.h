/*
 * LCD.h
 *
 *  Created on: Feb 15, 2021
 *      Author: ahmed
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdlib.h>
#include "micro_config.h"
#include "common_macros.h"
#include "std_types.h"

/***************** LCD Configurations ***************/
#define DATA_BITS_MODE 8

#if (DATA_BITS_MODE == 4)
#define UPPER_PORTS_PIN
#endif


/*************** LCD HW PINS *************************/
#define RS PD4
#define RW PD5
#define E PD6
#define LCD_CTRL_PORT PORTD
#define LCD_CTRL_PORT_DIR DDRD

#define LCD_DATA_PORT PORTC
#define LCD_DATA_PORT_DIR DDRC

/* **************** Common Commands **********************/

#define CLEAR_COMMAND (0x01)
#define TWO_LINES_EIGHT_BIT (0x38)
#define TWO_LINES_FOUR_BIT (0x28)
#define CURSOR_OFF (0x0C)
#define CURSOR_ON (0x0E)
#define SET_CURSOR_LOCATION (0x80)

/****************** Function Prototypes ********************/

void LCD_init(void);
void LCD_sendCommand(uint8);
void LCD_displayCharacter(uint8);
void LCD_displayString(const char *a_string);
void LCD_goToRowColumn(uint8 row, uint8 col);
void LCD_displayStringRowColumn(uint8 a_row, uint8 a_col, const char *a_str);
void LCD_clearScreen(void);
void LCD_intgerToString(int a_int);







#endif /* LCD_H_ */
