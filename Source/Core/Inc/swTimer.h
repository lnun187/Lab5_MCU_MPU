/*
 * swTimer.h
 *
 *  Created on: Dec 3, 2024
 *      Author: HP
 */

#ifndef INC_SWTIMER_H_
#define INC_SWTIMER_H_
#include "main.h"

#define NO_OF_TIMER 	1
#define TIMER_CYCLE 	10 //ms
typedef struct {
  uint8_t flag;
  uint16_t counter;
} UserTimer;

void setTimer(int idx, uint16_t duration);
void timerRun(void);
int is_avail(int idx);

#endif /* INC_SWTIMER_H_ */
