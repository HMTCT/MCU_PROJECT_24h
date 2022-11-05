/*
 * display7SEG.c
 *
 *  Created on: Nov 3, 2022
 *      Author: HMT
 */

#include "main.h"
#include "display7SEG.h"

void display7SEG(int counter){
	HAL_GPIO_WritePin(GPIOB, a_7SEG_Pin|b_7SEG_Pin|c_7SEG_Pin|d_7SEG_Pin
		  			  		 |e_7SEG_Pin|f_7SEG_Pin|g_7SEG_Pin, 0);
	switch (counter){
		case 0:
			HAL_GPIO_WritePin(GPIOB, g_7SEG_Pin, 1);
	  		break;
		case 1:
			HAL_GPIO_WritePin(GPIOB, a_7SEG_Pin|d_7SEG_Pin|e_7SEG_Pin|f_7SEG_Pin|g_7SEG_Pin, 1);
	  		break;
		case 2:
	  		HAL_GPIO_WritePin(GPIOB, c_7SEG_Pin|f_7SEG_Pin, 1);
	  		break;
	  	  case 3:
	  		HAL_GPIO_WritePin(GPIOB, e_7SEG_Pin|f_7SEG_Pin, 1);
	  		break;
	  	  case 4:
	  		HAL_GPIO_WritePin(GPIOB, a_7SEG_Pin|d_7SEG_Pin|e_7SEG_Pin, 1);
	  		break;
	  	  case 5:
	  		HAL_GPIO_WritePin(GPIOB, b_7SEG_Pin|e_7SEG_Pin, 1);
	  		break;
	  	  case 6:
	  		HAL_GPIO_WritePin(GPIOB, b_7SEG_Pin, 1);
	  		break;
	  	  case 7:
	  		HAL_GPIO_WritePin(GPIOB, d_7SEG_Pin|e_7SEG_Pin|f_7SEG_Pin|g_7SEG_Pin, 1);
	  		break;
	  	  case 8:
	  		break;
	  	  case 9:
	  		HAL_GPIO_WritePin(GPIOB, e_7SEG_Pin, 1);
	  		break;
	  	  default:
	  		HAL_GPIO_WritePin(GPIOB, a_7SEG_Pin|b_7SEG_Pin|c_7SEG_Pin|d_7SEG_Pin
	  			  		             |e_7SEG_Pin|f_7SEG_Pin|g_7SEG_Pin, 1);
	  		break;
	  }
}

void fsm_for_display7SEG(){
	switch (MODE) {
		case INIT:
			MODE = NORMAL_MODE;
			setTimer0(10);
			break;

		case RESET_MODE:
			COUNTER = 0;
			MODE = WAIT_MODE;
			setTimer0(10);
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
