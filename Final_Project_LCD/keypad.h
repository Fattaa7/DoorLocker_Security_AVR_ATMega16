/*
 * keypad.h
 *
 *  Created on: Feb 15, 2021
 *      Author: ahmed
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "micro_config.h"
#include "common_macros.h"
#include "std_types.h"

/* ------------------- Static Configurations ------------------ */

#define N_col 4
#define N_row 4

#define KEYPAD_PORT_OUT PORTA
#define KEYPAD_PORT_IN PINA
#define KEYPAD_PORT_DIR DDRA

uint8 KeyPad_getPressedKey(void);



#endif /* KEYPAD_H_ */
