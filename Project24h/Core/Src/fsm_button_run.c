/*
 * fsm_button_run.c
 *
 *  Created on: Nov 5, 2022
 *      Author: HMT
 */


#include "fsm_button_run.h"

void fsm_for_countdown(){
	switch (MODE) {
		case INIT:
			MODE = NORMAL_MODE;
			setTimer0(10);
			setTimer2(10);
			break;
		case NORMAL_MODE:
			if (timer0_flag == 1){
				COUNTER--;
				if (COUNTER < 0)
					COUNTER = 9;
				display7SEG(COUNTER);
				setTimer0(1000);
			}
			break;
		default:
			break;
	}
}

void fsm_for_setting_mode(){
	switch (MODE) {
		case RESET_MODE:
			COUNTER = 0;
			MODE = WAIT_MODE;
			setTimer0(10);
			break;

		case INC_MODE:
			++COUNTER;
			if (COUNTER > 9)
				COUNTER = 0;
			MODE = WAIT_MODE;
			setTimer0(10);
			break;

		case DEC_MODE:
			COUNTER--;
			if (COUNTER < 0)
				COUNTER = 9;
			MODE = WAIT_MODE;
			setTimer0(10);
			break;

		case WAIT_MODE:
			if (timer0_flag == 1){
				display7SEG(COUNTER);
				MODE = NORMAL_MODE;
				setTimer0(10000);
			}
			break;
		default:
			break;
	}
}

void fsm_for_long_press(){
	switch (MODE) {
		case AUTO_INC:
			if (timer1_flag == 1){
				++COUNTER;
				if (COUNTER > 9)
					COUNTER = 0;
				display7SEG(COUNTER);
				setTimer1(1000);
			}
			break;

		case AUTO_DEC:
			if (timer1_flag == 1){
				--COUNTER;
				if (COUNTER < 0)
					COUNTER = 9;
				display7SEG(COUNTER);
				setTimer1(1000);
			}
			break;
		default:
			break;
	}
}
