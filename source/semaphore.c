/*
 * semaphore.c
 *
 *  Created on: 14 may. 2025
 *      Author: jajav
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "board.h"
#include "time.h"
#include "semaphore.h"
#include "pin_mux.h"

void SwitchR() {
	GPIO_PortToggle(BOARD_INITPINS_LED_R_GPIO_PORT, BOARD_INITPINS_LED_R_PIN_MASK);
}

void SwitchY() {
	GPIO_PortToggle(BOARD_INITPINS_LED_Y_GPIO_PORT, BOARD_INITPINS_LED_Y_PIN_MASK);
}

void SwitchG() {
	GPIO_PortToggle(BOARD_INITPINS_LED_G_GPIO_PORT, BOARD_INITPINS_LED_G_PIN_MASK);
}
