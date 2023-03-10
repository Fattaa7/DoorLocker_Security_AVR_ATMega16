/*
 * keypad.c
 *
 *  Created on: Feb 15, 2021
 *      Author: ahmed
 */

#include "keypad.h"

#if (N_col == 3)
static uint8 Keypad_4x3_adjustSwitchNumber(uint8 button_number);
#elif (N_col == 4)
static uint8 Keypad_4x4_adjustSwitchNumber(uint8 button_number);
#endif


uint8 KeyPad_getPressedKey(void){

	uint8 row , col;
while(1){
	for(col = 0; col < N_col ; col++){
		/*
		 * setting the columns as output but one by one to check on them
		 *
		 */
		KEYPAD_PORT_DIR = (0b00010000<<col);
		/*
		 * enable internal pull up and setting the value on the output pin by 0
		 */
		KEYPAD_PORT_OUT = (~(0b00010000<<col));

		for(row = 0; row < N_row ; row++){

			if(BIT_IS_CLEAR(KEYPAD_PORT_IN, row)){

#if(N_col == 3)
				return (Keypad_4x3_adjustSwitchNumber((row*N_col)+col+1));
#elif(N_col == 4)
				return (Keypad_4x4_adjustSwitchNumber((row*N_col)+col+1));
#endif

			}
		}

	}
}

}

#if (N_col == 3)

static uint8 Keypad_4x3_adjustSwitchNumber(uint8 a_btnNum){

	switch(a_btnNum){

	case 10: return '*';
	case 11: return 0;
	case 12: return '#';
	default: return a_btnNum;
	}


}

#elif (N_col == 4)
static uint8 Keypad_4x4_adjustSwitchNumber(uint8 a_btnNum){

	switch(a_btnNum){

	case 1: return 7;
					break;
			case 2: return 8;
					break;
			case 3: return 9;
					break;
			case 4: return '%'; // ASCII Code of %
					break;
			case 5: return 4;
					break;
			case 6: return 5;
					break;
			case 7: return 6;
					break;
			case 8: return '*'; /* ASCII Code of '*' */
					break;
			case 9: return 1;
					break;
			case 10: return 2;
					break;
			case 11: return 3;
					break;
			case 12: return '-'; /* ASCII Code of '-' */
					break;
			case 13: return 13;  /* ASCII of Enter */
					break;
			case 14: return 0;
					break;
			case 15: return '='; /* ASCII Code of '=' */
					break;
			case 16: return '+'; /* ASCII Code of '+' */
					break;
	default: return a_btnNum;
	}


}

#endif

