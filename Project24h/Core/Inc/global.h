/*
 * global.h
 *
 *  Created on: Nov 3, 2022
 *      Author: HMT
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_


#define INIT 			0
#define AUTO_RED 		1
#define AUTO_GREEN 		2
#define AUTO_YELLOW 	3

#define MAN_RED 		12
#define MAN_GREEN 		13
#define MAN_YELLOW 		14

extern int status1;
extern int status2;

extern int RED_DURATION;
extern int YELLOW_DURATION;
extern int GREEN_DURATION;

extern int MODE;

extern int led_buffer[4];

extern int countdown1;
extern int countdown2;

#endif /* INC_GLOBAL_H_ */
