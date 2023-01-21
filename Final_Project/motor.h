/*
 * motor.h
 *
 *  Created on: Feb 17, 2021
 *      Author: ahmed
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "micro_config.h"
#include "common_macros.h"
#include "std_types.h"

/****************** Configurations ********************/

#define INPUT1 PB0
#define INPUT2 PB1
#define ENABLE PB3
#define INPUT_DIR DDRB
#define INPUT_PORT PORTB

/********************** Function prototypes ***********************/

void motor_init();
void motor_toggleDirection(void);
void motor_changeSpeed(uint16 dutyCycle);




#endif /* MOTOR_H_ */
