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
volatile extern uint8_t Frequency;

volatile extern bool kbi0Pressed;

void Reaction() {
	uint32_t timeMilis = 0;
	setGreenStatus();

	SDK_DelayAtLeastUs(1000000, CLOCK_GetFreq(kCLOCK_CoreSysClk));
	SwitchR();
	SDK_DelayAtLeastUs(1000000/Frequency, CLOCK_GetFreq(kCLOCK_CoreSysClk));
	SwitchR();
	SwitchY();
	SDK_DelayAtLeastUs(1000000/Frequency, CLOCK_GetFreq(kCLOCK_CoreSysClk));
	SwitchY();
	SwitchG();

	KBI0->SC |= KBI_SC_RSTKBSP_MASK | KBI_SC_KBACK_MASK;
	KBI_EnableInterrupts(KBI0);

	GPIO_PortToggle(SALEAE_INIT, SALEAE_INIT_MASK);
	while (!kbi0Pressed) {
		timeMilis++;
		SDK_DelayAtLeastUs(1000, CLOCK_GetFreq(kCLOCK_CoreSysClk));
	}

	GPIO_PortToggle(SALEAE_INIT, SALEAE_INIT_MASK);
	GPIO_PortToggle(SALEAE_END, SALEAE_END_MASK);
	SDK_DelayAtLeastUs(10000, CLOCK_GetFreq(kCLOCK_CoreSysClk));
	GPIO_PortToggle(SALEAE_END, SALEAE_END_MASK);

	kbi0Pressed = false;
	reactionLCD(timeMilis);
	SwitchG();
	State = STATE_WAITING;
	KBI1->SC |= KBI_SC_RSTKBSP_MASK | KBI_SC_KBACK_MASK;
	KBI_EnableInterrupts(KBI1);
}
