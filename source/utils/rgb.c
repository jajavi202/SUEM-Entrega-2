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

#define RGB_WHITE2()		Set_RGB(0,0,0)
#define RGB_CYAN2()			Set_RGB(1,0,0)
#define RGB_MAGENTA2()		Set_RGB(0,1,0)
#define RGB_BLUE2()			Set_RGB(1,1,0)
#define RGB_YELLOW2()		Set_RGB(0,0,1)
#define RGB_GREEN2()		Set_RGB(1,0,1)
#define RGB_RED2()			Set_RGB(0,1,1)
#define RGB_BLACK2()		Set_RGB(1,1,1)

volatile extern bool stopFlag;

void Test_RGB(){
	while(!stopFlag){
		SDK_DelayAtLeastUs(1000000, CLOCK_GetFreq(kCLOCK_CoreSysClk));
		RGB_WHITE2();
		PRINTF("WHITE\r\n");

		SDK_DelayAtLeastUs(1000000, CLOCK_GetFreq(kCLOCK_CoreSysClk));
		RGB_CYAN2();
		PRINTF("CYAN\r\n");

		SDK_DelayAtLeastUs(1000000, CLOCK_GetFreq(kCLOCK_CoreSysClk));
		RGB_MAGENTA2();
		PRINTF("MAGENTA\r\n");

		SDK_DelayAtLeastUs(1000000, CLOCK_GetFreq(kCLOCK_CoreSysClk));
		RGB_BLUE2();
		PRINTF("BLUE\r\n");

		SDK_DelayAtLeastUs(1000000, CLOCK_GetFreq(kCLOCK_CoreSysClk));
		RGB_YELLOW2();
		PRINTF("YELLOW\r\n");

		SDK_DelayAtLeastUs(1000000, CLOCK_GetFreq(kCLOCK_CoreSysClk));
		RGB_GREEN2();
		PRINTF("GREEN\r\n");

		SDK_DelayAtLeastUs(1000000, CLOCK_GetFreq(kCLOCK_CoreSysClk));
		RGB_RED2();
		PRINTF("RED\r\n");

		SDK_DelayAtLeastUs(1000000, CLOCK_GetFreq(kCLOCK_CoreSysClk));
		RGB_BLACK2();
		PRINTF("BLACK\r\n");
	}
}
