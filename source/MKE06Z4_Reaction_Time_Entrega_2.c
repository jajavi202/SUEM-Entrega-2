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
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
#define STATE_CONFIG 0

/*
 * @brief   Application entry point.
 */

volatile uint8_t State;

int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    State = STATE_CONFIG;

    while (1) {
		switch(State) {

		}
    }


    return 0 ;
}
