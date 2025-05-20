/*
 * lcd_controller.c
 *
 *  Created on: 20 may. 2025
 *      Author: lex30
 */

#include <stdio.h>
#include "lcd.h"
#include "clock_config.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "lcd_controller.h"
#define I2C_MASTER_SLAVE_ADDR_7BIT 0x3FU


void prepareLCD(){
	LCD_Init(I2C_MASTER_SLAVE_ADDR_7BIT, 16, 2, LCD_5x8DOTS);

	LCD_backlight();
	LCD_clear();
}

void frequencyLCD(uint8_t freq){
	char buffer[25];
	sprintf(buffer, "FRECUENCIA: %02uHz", freq);
	LCD_setCursor(0, 0);
	LCD_printstr(buffer);
}

void reactionLCD(uint8_t time){
	char buffer[25];
	sprintf(buffer, "REAC: %08uus", time);
	LCD_setCursor(0, 1);
	LCD_printstr(buffer);
}

void clearLCD() {
	LCD_backlight();
	LCD_clear();
}
