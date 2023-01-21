/*
 * motor.c
 *
 *  Created on: Feb 17, 2021
 *      Author: ahmed
 */

#include "motor.h"

void motor_init(void)
{
	TCNT0 = 0;
	/*
	 * setting three control pins as outputs
	 */
	INPUT_DIR |= (1<<INPUT1) | (1<<INPUT2) | (1<<ENABLE);


	OCR0 = 0; /* output initially set to 0

	/*
	 * clockwise rotation as default
	 */
	SET_BIT(INPUT_PORT,INPUT1);
	CLEAR_BIT(INPUT_PORT,INPUT2);

	/*
	 * PWM Mode with F_CPU/8 clock
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
}

void motor_toggleDirection(void)
{
	TOGGLE_BIT(INPUT_PORT,INPUT1);
	TOGGLE_BIT(INPUT_PORT,INPUT2);
}

void motor_changeSpeed(uint16 dutyCycle)
{
	OCR0 = dutyCycle;
}
