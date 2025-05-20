/*
 * waiting.c
 *
 *  Created on: 20 may. 2025
 *      Author: jajav
 */

#include <stdbool.h>
#include "waiting.h"
#include "kbi_pins.h"
#include "fsl_kbi.h"
#include "states.h"

volatile extern uint8_t State;
volatile extern bool kbi1Pressed;

void Waiting() {
	while (State == STATE_WAITING) {
		if (kbi1Pressed) {
			kbi1Pressed = false;

			if (KBI_GetSourcePinStatus(KBI1) & KBI1_BOARD_KEY1)
				State = STATE_CONFIG;
			if (KBI_GetSourcePinStatus(KBI1) & KBI1_BOARD_KEY2)
				State = STATE_REACTION;

			KBI1->SC |= KBI_SC_RSTKBSP_MASK;
			KBI_EnableInterrupts(KBI1);
		}
	}
}
