/*
 * configuration.c
 *
 *  Created on: 20 may. 2025
 *      Author: jajav
 */

#include <stdint.h>
#include <stdbool.h>
#include "configuration.h"
#include "states.h"

#define AXIS_TOP_THRES 2000
#define AXIS_BOT_THRES 1000

#define MAX_FREQ 10
#define MIN_FREQ 0


volatile uint8_t Frequency = 0; // Hz
volatile extern uint8_t State;

void Configure() {
	uint32_t fX, fY;

	fX = 0;
	fY = 0;

	while (State == STATE_CONFIG) {
		ReadJoyStick(&fX, &fY);

		if (fX >= AXIS_TOP_THRES) {
			ModifyFreqRegulated(true);
		}
		if (fX <= AXIS_BOT_THRES) {
			ModifyFreqRegulated(false);
		}

		frequencyLCD(Frequency);
	}
}

void ModifyFreqRegulated(bool increase) {
	if (Frequency == MAX_FREQ) {
		return;
	}
	if (Frequency == MIN_FREQ) {
		return;
	}

	if (increase)
		Frequency++;
	else
		Frequency--;
}
