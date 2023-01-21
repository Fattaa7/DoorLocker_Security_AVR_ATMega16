/*
 * main.h
 *
 *  Created on: Mar 23, 2021
 *      Author: ahmed
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "LCD.h"
#include "UART.h"
#include "keypad.h"
#include "timer.h"

#define START 0
#define OPTION_MENU 1
#define BUSY 2

#define PASS_MATCH 1
#define PASS_NOT_MATCH 0
#define ENTER_PASS 10
#define ENTER_NEW_PASS 13


#define ENTER 13

#define CHANGE_PASS '+'
#define OPEN_DOOR '-'

#define ONE_SEC 7812UL


void get_pass(uint8 *password); //handles input from keypad and displays it on LCD
void get_option(uint8 *option, uint8 *password, uint8 *msg); // main function to handle program states
void enter_new_pass(uint8 *password, uint8 *msg); // handles sequence of storing new password --
void change_pass(uint8 *password,uint8 *msg); // handles the state of changing password
void open_door(uint8 *password,uint8 *msg); // handles sequence of opening door
void open_door_time(void); //call back function when the door is opening
void thief_break(void); //main function if a thief is spotted
void alarm_time(void); //call back function when there is a thief break







#endif /* MAIN_H_ */
