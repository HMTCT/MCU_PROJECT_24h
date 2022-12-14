/*
 * input_processing.c
 *
 *  Created on: Nov 3, 2022
 *      Author: HMT
 */

#include "main.h"
#include "input_processing.h"

#define NO_OF_BUTTONS	3

enum ButtonState{BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND} ;
enum ButtonState buttonState[NO_OF_BUTTONS] = {BUTTON_RELEASED};


void fsm_for_input_processing(void){
	for (int i = 0; i < NO_OF_BUTTONS; i++){
		switch(buttonState[i]){
			case BUTTON_RELEASED:
				if(is_button_pressed(i)){
					buttonState[i] = BUTTON_PRESSED;
					//Update MODE
					switch (i) {
						case 0:
							MODE = RESET_MODE;
							break;
						case 1:
							MODE = INC_MODE;
							break;
						case 2:
							MODE = DEC_MODE;
							break;
						default:
							break;
					}
					//Refresh led for debugging
					setTimer2(10);
				}
				break;

			case BUTTON_PRESSED:
				if(!is_button_pressed(i)){
					buttonState[i] = BUTTON_RELEASED;
				}
				else {
					if(is_button_pressed_1s(i)){
						buttonState[i] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
						switch (i) {
							case 1:
								MODE = AUTO_INC;
								break;
							case 2:
								MODE = AUTO_DEC;
							default:
								break;
						}
						//Set timer for fsm_long_press
						setTimer1(10);
						//Refresh led for debugging
						setTimer2(10);
					}
				}
				break;

			case BUTTON_PRESSED_MORE_THAN_1_SECOND:
				if(!is_button_pressed(i)){
					buttonState[i] = BUTTON_RELEASED;

					//Reset timer for time out
					setTimer0(10);
					//Refresh led for debugging
					setTimer2(10);

					MODE = WAIT_MODE;
				}
				break;
			default:
				break;
			}
	}
}

