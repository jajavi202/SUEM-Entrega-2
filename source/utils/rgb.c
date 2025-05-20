/*
 * rgb.c
 *
 *  Created on: 18 may. 2025
 *      Author: lex30
 */
#include "board.h"
#include "clock_config.h"
#include "pin_mux.h"
#include "rgb.h"
#include "fsl_debug_console.h"


void Set_RGB(uint8_t R, uint8_t G, uint8_t B){
	uint8_t mask_set=0UL;
	uint8_t mask_clear=0UL;

	if (R) mask_set+=1UL<<BOARD_LED_RED_GPIO_PIN;
	else mask_clear+=1UL<<BOARD_LED_RED_GPIO_PIN;

	if (G) mask_set+=1UL<<BOARD_LED_GREEN_GPIO_PIN;
	else mask_clear+=1UL<<BOARD_LED_GREEN_GPIO_PIN;

	if (B) mask_set+=1UL<<BOARD_LED_BLUE_GPIO_PIN;
	else mask_clear+=1UL<<BOARD_LED_BLUE_GPIO_PIN;

	GPIO_PortClear(BOARD_LED_GREEN_GPIO_PORT, mask_clear);
	GPIO_PortSet(BOARD_LED_GREEN_GPIO_PORT, mask_set);
}

void setGreenStatus(){
	Set_RGB(1, 0, 1);
}

void setRedStatus(){
	Set_RGB(0, 1, 1);
}
