/*
 * swTimer.c
 *
 *  Created on: Dec 3, 2024
 *      Author: HP
 */
#include "swTimer.h"

UserTimer timer[NO_OF_TIMER];

void setTimer(int idx, uint16_t duration) {
	timer[idx].counter = duration / TIMER_CYCLE;
	timer[idx].flag = 0;
}

void timerRun(void) {
	for (int i = 0; i < NO_OF_TIMER; i++) {
		if (timer[i].counter > 0) {
			timer[i].counter--;
			if (timer[i].counter <= 0)
				timer[i].flag = 1;
		}
	}
}

int is_avail(int idx) {
	if (timer[idx].flag == 1) {
		timer[idx].flag = 0;
		return 1;
	}
	else return 0;
}
