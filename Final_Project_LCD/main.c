/*
 * main.c
 *
 *  Created on: Mar 21, 2021
 *      Author: ahmed
 */

#include "main.h"




struct Timer timer = {1,CTC_MODE,0,PRE_SCALER_1024, ONE_SEC};
uint8 display_top = ENTER_PASS;
uint8 state_machine = OPTION_MENU;

int main(void) {

	uint8 password[16];
	uint8 msg;
	uint8 option;
	//struct UART uart = { 8, 2, 1, 9600 };

	struct UART uart = {EIGHT_BIT_DATA,PARITY_EVEN,STOP_BITS_2,9600};
	SET_BIT(SREG,7);

	UART_init(&uart); // initialize UART driver
	LCD_init(); // initialize LCD driver

	enter_new_pass(password, &msg);


	while (1)
	{
		switch(state_machine)
		{
		case OPTION_MENU:
			get_option(&option,password,&msg);
		}

	}
}






void open_door_time(void)
{
	static uint8 timoo = 1;
	if(timoo < 33)
	{
		timoo++;
		timer_init(&timer);
	}
	else
	{
		timoo = 0;
		state_machine = OPTION_MENU;
		timer_stop();
	}
}

void alarm_time(void)
{
	static uint8 timoo = 1;
	if(timoo < 10)
	{
		timoo++;
		timer_init(&timer);

	}
	else
	{
		timoo = 0;
		state_machine = OPTION_MENU;
		timer_stop();
	}
}

void get_pass(uint8 *password)
{
	LCD_clearScreen();
	//LCD_displayStringRowColumn(1,0,"                    ");
	LCD_goToRowColumn(0, 0);
	if(display_top == ENTER_PASS)
	{
		LCD_displayString("Enter Pass:"); // display the string on LCD
	}
	else if(display_top == ENTER_NEW_PASS)
	{
		LCD_displayString("Enter New Pass:"); // display the string on LCD
	}
	LCD_goToRowColumn(1, 0);
	uint8 i = 0;
	password[i] = KeyPad_getPressedKey();
	LCD_displayCharacter('*');
	_delay_ms(40*8);

	while(password[i] != ENTER)
	{
		i++;
		password[i] = KeyPad_getPressedKey();
		if(password[i]==ENTER)
		{
			_delay_ms(40*8);
			break;
		}
		LCD_displayCharacter('*');
		_delay_ms(40*8);
	}
	password[i] = '#';
	password[i+1] = '\0';

	i = 0;

}



void enter_new_pass(uint8 *password, uint8 *msg)
{


	get_pass(password);
	UART_sendString(password);
	get_pass(password);
	UART_sendString(password);

	*msg = UART_receiveByte();

	if(*msg == PASS_MATCH)
	{
		LCD_goToRowColumn(1, 0);
		LCD_displayString("Accepted"); // display the string on LCD
		_delay_ms(300*8);
		return;
	}
	else if(*msg == PASS_NOT_MATCH)
	{
		LCD_goToRowColumn(1, 0);
		LCD_displayString("Pass Error"); // display the string on LCD
		_delay_ms(300*8);
		enter_new_pass(password,msg);
	}


}

/*
 * function to deal with main options screen
 * input:
 * 		option : variable to store option input
 * 		password : array to store the entered password
 * 		msg : the message sent back from the control MC
 */
void get_option(uint8 *option, uint8 *password, uint8 *msg)
{
	LCD_clearScreen();
	LCD_displayString("+ : Change Pass"); // display the string on LCD
	LCD_goToRowColumn(1, 0);
	LCD_displayString("- : Open Door"); // display the string on LCD
	*option = KeyPad_getPressedKey();
	_delay_ms(40*8);
	UART_sendByte(*option);


	if(*option == OPEN_DOOR)
	{
		open_door(password,&msg);
	}
	else if (*option == CHANGE_PASS)
	{
		change_pass(password,&msg);
	}
}



void change_pass(uint8 *password,uint8 *msg)
{
	for(uint8 i = 0; i<3; i++)
	{
		LCD_clearScreen();
		get_pass(password);
		UART_sendString(password);
		*msg = UART_receiveByte();

		if(*msg == PASS_MATCH)
		{
			LCD_clearScreen();
			display_top = ENTER_NEW_PASS;
			enter_new_pass(password,msg);
			display_top = ENTER_PASS;
			return;
		}
		else if (*msg == PASS_NOT_MATCH)
		{
			LCD_clearScreen();
			LCD_displayString("Mismatch Pass");
			_delay_ms(150*8);
		}
	}

	thief_break();
}

void open_door(uint8 *password,uint8 *msg)
{

	for(uint8 i = 0; i<3; i++)
	{
		LCD_clearScreen();
		get_pass(password);
		UART_sendString(password);
		*msg = UART_receiveByte();

		if(*msg == PASS_MATCH)
		{
			timer_stop();
			state_machine = BUSY;
			LCD_clearScreen();
			LCD_displayString("Opeeening Door");
			timer.compare_value = ONE_SEC;
			set_callback(open_door_time);
			timer_init(&timer);
			return;
		}
		else if (*msg == PASS_NOT_MATCH)
		{
			LCD_clearScreen();
			LCD_displayString("Mismatch Pass");
			_delay_ms(150*4);
		}
	}

	thief_break();
}

void thief_break(void)
{
	state_machine = BUSY;
	LCD_clearScreen();
	LCD_displayString("7raaaaaaaaaaaamy");
	set_callback(alarm_time);
	timer.compare_value = ONE_SEC;
	timer_init(&timer);
}
