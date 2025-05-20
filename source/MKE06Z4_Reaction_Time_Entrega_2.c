/**
 * @file    MKE06Z4_Reaction_Time_Entrega_2.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKE06Z4.h"
#include "fsl_debug_console.h"
#include "fsl_kbi.h"

/* TODO: insert other include files here. */
#include "kbi_pins.h"
#include "states/states.h"

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

volatile uint8_t State;

void KBI0_Setup() {

}

void KBI1_Setup() {
	kbi_config_t kbi1Config;
	kbi1Config.mode = kKBI_EdgesDetect;
	kbi1Config.pinsEnabled = (uint32_t) (KBI1_MASK);
	kbi1Config.pinsEdge = ~((uint32_t) (KBI1_MASK));
	KBI_Init(KBI1, &kbi1Config);
}

int main(void) {

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    BOARD_InitDebugConsole();
#endif

    State = STATE_CONFIG;
    prepareLCD();

    while (1) {
		switch(State) {
			case STATE_CONFIG:
				break;
		}
    }


    return 0 ;
}
