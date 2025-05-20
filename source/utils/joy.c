/*
 * joy.c
 *
 *  Created on: 17 may. 2025
 *      Author: jajav
 */


#include "joy.h"

#define ADC_V_MAX 3.06
#define ADC_128BIT_MAX 0xFFF
#define ADC_ITOV (float)ADC_V_MAX/(float)ADC_128BIT_MAX

float ReadAdc(uint32_t channel) {
	adc_channel_config_t adcChannelConfigStruct;

	adcChannelConfigStruct.channelNumber = channel;
	adcChannelConfigStruct.enableInterruptOnConversionCompleted = false;
	adcChannelConfigStruct.enableContinuousConversion = false;
	ADC_SetChannelConfig(ADC, &adcChannelConfigStruct);

	while (!ADC_GetChannelStatusFlags(ADC)) {}

	uint32_t axis = ADC_GetChannelConversionValue(ADC);
	return (float) axis * (float) ADC_ITOV ;
}

void ReadJoyStick(uint32_t *fX, uint32_t *fY) {
	*fX = ReadAdc(JOY_X) * 1000;
	*fY = ReadAdc(JOY_Y) * 1000;
}
