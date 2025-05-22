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
#include "fsl_adc.h"

/* TODO: insert other include files here. */
#include "kbi_pins.h"
#include "states/states.h"

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

volatile uint8_t State;

volatile bool kbi0Pressed = false;
volatile bool kbi1Pressed = false;

void KBI0_Setup() {
	kbi_config_t kbi0Config;
	kbi0Config.mode = kKBI_EdgesDetect;
	kbi0Config.pinsEnabled = (uint32_t) (KBI0_MASK);
	kbi0Config.pinsEdge = ~((uint32_t) (KBI0_MASK));
	KBI_Init(KBI0, &kbi0Config);
}

void KBI1_Setup() {
	kbi_config_t kbi1Config;
	kbi1Config.mode = kKBI_EdgesDetect;
	kbi1Config.pinsEnabled = (uint32_t) (KBI1_MASK);
	kbi1Config.pinsEdge = ~((uint32_t) (KBI1_MASK));
	KBI_Init(KBI1, &kbi1Config);
}

void KBI0_IRQHandler(void){
	if(KBI_IsInterruptRequestDetected(KBI0)){
		KBI_DisableInterrupts(KBI0);
		KBI_ClearInterruptFlag(KBI0);
		kbi0Pressed = true;
	}

	SDK_ISR_EXIT_BARRIER;
}
void KBI1_IRQHandler(void){
	if(KBI_IsInterruptRequestDetected(KBI1)){
		KBI_DisableInterrupts(KBI1);
		KBI_ClearInterruptFlag(KBI1);

		if (State != STATE_REACTION)
			kbi1Pressed = true;

		if (!kbi1Pressed) {
			KBI1->SC |= KBI_SC_RSTKBSP_MASK;
			KBI_EnableInterrupts(KBI1);
		}
	}

	SDK_ISR_EXIT_BARRIER;
}

int main(void) {

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    BOARD_InitDebugConsole();
#endif

    State = STATE_CONFIG;

    // KBI
    KBI0_Setup();
    KBI1_Setup();

    // LCD INIT
    prepareLCD();

    // ADC INIT
    adc_config_t adcConfigStruct;
	ADC_GetDefaultConfig(&adcConfigStruct);
	adcConfigStruct.ResolutionMode = kADC_Resolution12BitMode;
	ADC_Init(ADC, &adcConfigStruct);

    while (1) {
		switch(State) {
			case STATE_CONFIG:
				Configure();
				break;
			case STATE_REACTION:
				Reaction();
				break;
			case STATE_WAITING:
				Waiting();
				break;
			default:
				State = STATE_CONFIG;
				break;
		}
    }


    KBI_Deinit(KBI0);
    KBI_Deinit(KBI1);

    return 0 ;
}
