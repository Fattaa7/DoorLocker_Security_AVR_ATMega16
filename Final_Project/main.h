/*
 * main.h
 *
 *  Created on: Mar 23, 2021
 *      Author: ahmed
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <string.h>
#include "UART.h"
#include "motor.h"
#include "timer.h"
#include "external_eeprom.h"


#define START_HANDLER 0
#define OPTION_HANDLER 1
#define BUSY 2

#define BUZZER_DIR DDRA
#define BUZZER_DATA PORTA
#define BUZZER_PIN PA0

#define PASS_MATCH 1
#define PASS_NOT_MATCH 0

#define CHANGE_PASS '+'
#define OPEN_DOOR '-'

#define ONE_SEC 7812UL //one second in timer

#define MOTOR_MAX 1023UL

void get_new_pass(void); //gets sequence of storing a new password
void option_handler(uint8 *option); // handles main state machine
void open_door(void); // execute the door opening sequence
void stop_buzzer(void); //turns on buzzer for 1 min
void thief_handler(void); //main function if a thief spotted
void store_password(uint8 *password); //stores password in EEPROM
uint8 check_memory_password(void); // returns true if the password matches with the pass in EEPROM







#endif /* MAIN_H_ */
