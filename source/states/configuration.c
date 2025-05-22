/*
 * configuration.c
 *
 *  Created on: 20 may. 2025
 *      Author: jajav
 */

#include <stdint.h>
#include <stdbool.h>
#include "fsl_clock.h"
#include "fsl_kbi.h"
#include "kbi_pins.h"
#include "configuration.h"
#include "states.h"

#define AXIS_TOP_THRES 2000
#define AXIS_BOT_THRES 1000

#define MAX_FREQ 10
#define MIN_FREQ 1

volatile uint8_t Frequency = 1U; // Hz
volatile extern uint8_t State;
volatile extern bool kbi1Pressed;

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

		if (fY >= AXIS_TOP_THRES) {
			ModifyFreqRegulated(false);
		}
		if (fY <= AXIS_BOT_THRES) {
			ModifyFreqRegulated(true);
		}

		if (kbi1Pressed) {
			if (KBI_GetSourcePinStatus(KBI1) & KBI1_BOARD_KEY1)
				State = STATE_REACTION;
			else {
				kbi1Pressed = false;
				KBI1->SC |= KBI_SC_RSTKBSP_MASK;
				KBI_EnableInterrupts(KBI1);
			}
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
