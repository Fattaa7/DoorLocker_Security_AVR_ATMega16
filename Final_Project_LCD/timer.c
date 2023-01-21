/*
 * timer.c
 *
 *  Created on: Mar 24, 2021
 *      Author: ahmed
 */


#include "timer.h"

 void (*g_fnc)();

void timer_init(const struct Timer *ptr)
{
	if((*ptr).timer_num == TIMER0)
	{
		TCNT0 = (*ptr).initial_value ;

		if((*ptr).mode == NORMAL_MODE)
		{
			TCCR0 = (1<<FOC0) | ((*ptr).pre_scaler);
			TIMSK |= (1<<TOIE0);
		}
		else if ((*ptr).mode == CTC_MODE)
		{
			TCCR0 = (1<<FOC0) | (1<<WGM01) | ((*ptr).pre_scaler);
			OCR0 = (*ptr).compare_value;
			TIMSK |= (1<<OCIE0);
		}
	}

	else if ((*ptr).timer_num == TIMER1)
	{
		TCNT1 = (*ptr).initial_value;

		if((*ptr).mode == NORMAL_MODE)
		{
			TCCR1A = (1<<FOC1A) | (1<<FOC1B);
			TCCR1B = ((*ptr).pre_scaler);
			TIMSK |= (1<<TOIE1);
		}
		else if ((*ptr).mode == CTC_MODE)
		{
			TCCR1A = (1<<FOC1A) | (1<<FOC1B) ;
			TCCR1B = (1<<WGM12) | ((*ptr).pre_scaler);
			OCR1A = (*ptr).compare_value;
			TIMSK |= (1<<OCIE1A); // Enable Timer int for compare
		}

	}

	else if ((*ptr).timer_num == TIMER2)
	{
		TCNT2 = (*ptr).initial_value;

		if((*ptr).mode == NORMAL_MODE)
		{
			TCCR2 = (1<<FOC2) | ((*ptr).pre_scaler);
			TIMSK |= (1<<TOIE2);
		}
		else if ((*ptr).mode == CTC_MODE)
		{
			TCCR2 = (1<<FOC2) |(1<<WGM21) | ((*ptr).pre_scaler);
			OCR2 = (*ptr).compare_value;
			TIMSK |= (1<<OCIE2);
		}
	}
}

void timer_stop(void)
{
	TCCR0 = 0;
	TCCR1B = 0;
	TCCR2 = 0;
}

void set_callback(void (*fnc)())
{
	g_fnc = fnc;
}

ISR(TIMER0_OVF_vect)
{
	g_fnc();
}

ISR(TIMER1_OVF_vect)
{
	g_fnc();
}

ISR(TIMER2_OVF_vect)
{
	g_fnc();
}

ISR(TIMER0_COMP_vect)
{
	g_fnc();
}

ISR(TIMER1_COMPA_vect)
{
	g_fnc();
}

ISR(TIMER2_COMP_vect)
{
	g_fnc();
}
