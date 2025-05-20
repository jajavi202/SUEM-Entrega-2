/*
 * reaction.c
 *
 *  Created on: 20 may. 2025
 *      Author: jajav
 */

#include "states.h"
#include "utils/utils.h"
#include "fsl_clock.h"
#include "fsl_kbi.h"

volatile extern uint8_t State;
volatile extern uint32_t Frequency;

volatile extern bool kbi0Pressed;

void Reaction() {
	uint32_t time = 0;

	SwitchR();
	SDK_DelayAtLeastUs(1000000, Frequency);
	SwitchR();
	SwitchY();
	SDK_DelayAtLeastUs(1000000, Frequency);
	SwitchY();
	SwitchG();

	KBI0->SC |= KBI_SC_RSTKBSP_MASK;
	KBI_EnableInterrupts(KBI0);
	// SEND 1 TO SALAE
	while (!kbi0Pressed) {
		time++;
		SDK_DelayAtLeastUs(1000, CLOCK_GetFreq(kCLOCK_CoreSysClk));
	}
	// SEND 1 TO SALAE PRESSED
	// SEND 0 TO SALAE PRESSED
	// SEND 0 TO SALAE

	clearLCD();
	reactionLCD(time);
	SwitchG();
	State = STATE_WAITING;
}
