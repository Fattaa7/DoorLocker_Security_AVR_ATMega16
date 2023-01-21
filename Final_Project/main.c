/*
 * main.c
 *
 *  Created on: Mar 21, 2021
 *      Author: ahmed
 */

#include "main.h"

struct Timer timer = {1,CTC_MODE,0,PRE_SCALER_1024, ONE_SEC};
uint8 password[16];
uint8 password2[16];
uint8 state_machine = OPTION_HANDLER;




int main(void)
{
	SET_BIT(SREG,7);
	uint8 option;
	//struct UART uart = {8,2,1,9600};

	struct UART uart = {EIGHT_BIT_DATA,PARITY_EVEN,STOP_BITS_2,9600};

	SET_BIT(BUZZER_DIR,BUZZER_PIN);
	CLEAR_BIT(BUZZER_DATA,BUZZER_PIN);
	UART_init(&uart); // initialize UART
	EEPROM_init();

	get_new_pass();


    while(1)
    {
    	switch(state_machine)
    	{
    	case OPTION_HANDLER :
    		option_handler(&option);
    	}

    }

}

void stop_buzzer(void)
{
	static uint8 i = 1;

	if(i < 60)
	{
		i++;
		timer_init(&timer);

	}
	else
	{
		i = 0;
		state_machine = OPTION_HANDLER;
		CLEAR_BIT(BUZZER_DATA,BUZZER_PIN);
		timer_stop();
	}


}

void door_sequence_time(void)
{
	static uint8 i = 1;

	if(i == 15)
	{
		motor_changeSpeed(0);
		timer_init(&timer);
		i++;
	}
	else if(i == 18)
	{
		motor_toggleDirection();
		motor_changeSpeed(MOTOR_MAX);
		timer_init(&timer);
		i++;
	}
	else if(i == 33)
	{
		i = 0;
		motor_toggleDirection();
		motor_changeSpeed(0);
		timer_stop();
		state_machine = OPTION_HANDLER;
	}
	else
	{
		i++;
		timer_init(&timer);
	}
}

void get_new_pass(void)
{
	UART_receiveString(password);
	UART_receiveString(password2);

	if(!(strcmp(password,password2))) // in case Password matches
	{

		store_password(password);
		UART_sendByte(PASS_MATCH);
		return;
	}
	else
	{
		UART_sendByte(PASS_NOT_MATCH);
		get_new_pass();
	}
}

void option_handler(uint8 *option)
{
	*option = UART_receiveByte();

	if(*option == CHANGE_PASS)
	{
		for(uint8 i = 0; i<3 ; i++)
		{
			UART_receiveString(password);
			if(check_memory_password()) // in case Password matches
				{
					store_password(password);
					UART_sendByte(PASS_MATCH);
					get_new_pass();
					return;
				}
			else
				{
					UART_sendByte(PASS_NOT_MATCH);
				}

		}

	}
	else if(*option == OPEN_DOOR)
	{

		for(uint8 i = 0; i<3 ; i++)
		{
			UART_receiveString(password);
			if(check_memory_password()) // in case Password matches
				{
					UART_sendByte(PASS_MATCH);
					open_door();
					return;
				}
			else
				{
					UART_sendByte(PASS_NOT_MATCH);
				}
		}
	}
	thief_handler();

}

void open_door(void)
{
	timer_stop();
	motor_init();
	state_machine = BUSY;
	set_callback(door_sequence_time);
	timer.compare_value = ONE_SEC;
	motor_changeSpeed(MOTOR_MAX);
	timer_init(&timer);
}

void thief_handler(void)
{
	state_machine = BUSY;
	set_callback(stop_buzzer);
	timer.compare_value = ONE_SEC ;
	SET_BIT(BUZZER_DATA,BUZZER_PIN);
	timer_init(&timer);
}

void store_password(uint8 *password)
{

	for(uint8 i = 0; password[i] != '\0'; i++)
	{
		EEPROM_writeByte(0x0311+i, password[i]);
		_delay_ms(10*8);
	}

}
uint8 check_memory_password()
{
	uint8 val;

	for(uint8 i = 0; password[i] != '\0'; i++)
	{
		EEPROM_readByte(0x0311+i, &val);
		if(val != password[i])
			return 0;
	}
	return 1;

}
