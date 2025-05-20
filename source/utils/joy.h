/*
 * joy.h
 *
 *  Created on: 17 may. 2025
 *      Author: jajav
 */

#ifndef DEVICES_JOY_H_
#define DEVICES_JOY_H_

#include "pin_mux.h"
#include <stdbool.h>
#include "fsl_adc.h"
#include "fsl_gpio.h"

#define JOY_X (2U)
#define JOY_Y (3U)

#define JOY_ADC_MASK ((1U << JOY_X) | (1U << JOY_Y))

float ReadAdc(uint32_t channel);
void ReadJoyStick();

#endif /* DEVICES_JOY_H_ */
