/*
 * timer.h
 *
 *  Created on: Mar 24, 2021
 *      Author: ahmed
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

struct Timer {
	uint8 timer_num;
	uint8 mode;
	uint8 initial_value;
	uint8 pre_scaler;
	uint32 compare_value;
};

#define NORMAL_MODE 0
#define CTC_MODE 2

#define TIMER0 0
#define TIMER1 1
#define TIMER2 2


#define PRE_SCALER_0 1
#define PRE_SCALER_8 2
#define PRE_SCALER_64 3
#define PRE_SCALER_256 4
#define PRE_SCALER_1024 5

#define PRE_SCALER_T2_0 1
#define PRE_SCALER_T2_8 2
#define PRE_SCALER_T2_32 3
#define PRE_SCALER_T2_64 4
#define PRE_SCALER_T2_128 5
#define PRE_SCALER_T2_256 6
#define PRE_SCALER_T2_1024 7

void timer_init(const struct Timer *ptr);
void timer_stop(void);
void set_callback(void (*fnc)());



#endif /* TIMER_H_ */
