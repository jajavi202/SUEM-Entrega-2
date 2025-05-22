/*
 * configuration.c
 *
 *  Created on: 20 may. 2025
 *      Author: jajav
 */

#include <stdint.h>
#include <stdbool.h>
#include "fsl_clock.h"
#include "configuration.h"
#include "states.h"

#define AXIS_TOP_THRES 2000
#define AXIS_BOT_THRES 1000

#define MAX_FREQ 10
#define MIN_FREQ 1

volatile uint8_t Frequency = 1U; // Hz
volatile extern uint8_t State;

void Configure() {
	uint32_t fX, fY;

	fX = 0;
	fY = 0;


	uint32_t mask = JOY_ADC_MASK;

	ADC_EnableAnalogInput(ADC, mask, true);

	clearLCD();
	setRedStatus();
	while (State == STATE_CONFIG) {
		frequencyLCD(Frequency);
		SwitchR();
		SDK_DelayAtLeastUs(1000000/Frequency, CLOCK_GetFreq(kCLOCK_CoreSysClk));
		SwitchR();

		ReadJoyStick(&fX, &fY);

		if (fX >= AXIS_TOP_THRES) {
			ModifyFreqRegulated(true);
		}
		if (fX <= AXIS_BOT_THRES) {
			ModifyFreqRegulated(false);
		}
	}

	ADC_EnableAnalogInput(ADC, mask, false);
}

void ModifyFreqRegulated(bool increase) {
	if (increase)
		Frequency++;
	else
		Frequency--;

	if (Frequency > MAX_FREQ) {
		Frequency = MIN_FREQ;
		return;
	}
	if (Frequency < MIN_FREQ) {
		Frequency = MAX_FREQ;
		return;
	}

	SDK_DelayAtLeastUs(1000000, CLOCK_GetFreq(kCLOCK_CoreSysClk));
}
