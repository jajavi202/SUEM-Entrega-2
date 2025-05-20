#include "lcd.h"
#include "fsl_common.h"
#include <stdio.h>
#include "fsl_i2c.h"

uint8_t g_lcd_addr;
uint8_t g_lcd_cols;
uint8_t g_lcd_rows;
uint8_t g_lcd_charsize;
uint8_t g_lcd_backlightval;

uint8_t g_lcd_displayfunction;
uint8_t g_lcd_displaycontrol;
uint8_t g_lcd_displaymode;

#define I2C_MASTER_SLAVE_ADDR_7BIT 0x3F

void WAIT1_Waitms_LCD(unsigned long int ms)
{
	SDK_DelayAtLeastUs(ms*1000,CLOCK_GetFreq(kCLOCK_CoreSysClk));
}

void WAIT1_Waitus(unsigned long int us)
{
	SDK_DelayAtLeastUs(us,CLOCK_GetFreq(kCLOCK_CoreSysClk));
}
// ADRR:
//   0 1 0 0 A2 A1 A0 0

uint8_t LCD_Init(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t charsize)
{
	uint8_t select;

	g_lcd_addr=lcd_addr;
	g_lcd_cols=lcd_cols;
	g_lcd_rows=lcd_rows;
	g_lcd_charsize=charsize;
	g_lcd_backlightval=LCD_BACKLIGHT;

	// Selecciona el esclavo
	select = g_lcd_addr;


	g_lcd_displayfunction = LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS;


	// for some 1 line displays you can select a 10 pixel high font
	if ((g_lcd_charsize != 0) && (g_lcd_rows == 1)) {
		g_lcd_displayfunction |= LCD_5x10DOTS;
	}

	// SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
	// according to datasheet, we need at least 40ms after power rises above 2.7V
	// before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
	//delay(50);
	WAIT1_Waitms_LCD(50);

	// Now we pull both RS and R/W low to begin commands
	LCD_expanderWrite(g_lcd_backlightval);	// reset expanderand turn backlight off (Bit 8 =1)

	//delay(1000);
	WAIT1_Waitms_LCD(1000);

	//put the LCD into 4 bit mode
	// this is according to the hitachi HD44780 datasheet
	// figure 24, pg 46

	// we start in 8bit mode, try to set 4 bit mode
	LCD_write4bits(0x03 << 4);
	WAIT1_Waitus(6000);
	//delayMicroseconds(4500); // wait min 4.1ms

	// second try
	LCD_write4bits(0x03 << 4);
	WAIT1_Waitus(6000);
	//delayMicroseconds(4500); // wait min 4.1ms

	// third go!
	LCD_write4bits(0x03 << 4);
	WAIT1_Waitus(300);
	//delayMicroseconds(150);

	// finally, set to 4-bit interface
	LCD_write4bits(0x02 << 4);


	WAIT1_Waitms_LCD(1);
	// set # lines, font size, etc.
	LCD_command(LCD_FUNCTIONSET | g_lcd_displayfunction);
	WAIT1_Waitms_LCD(1);
	// turn the display on with no cursor or blinking default
	g_lcd_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	LCD_display();
	WAIT1_Waitms_LCD(1);
	// clear it off
	LCD_clear();
	WAIT1_Waitms_LCD(1);
	// Initialize to default text direction (for roman languages)
	g_lcd_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

	// set the entry mode
	LCD_command(LCD_ENTRYMODESET | g_lcd_displayfunction);
	WAIT1_Waitms_LCD(1);
	LCD_home();
	WAIT1_Waitms_LCD(1);
	return select;
}

/********** high level commands, for the user! */
void LCD_clear()
{
	LCD_command(LCD_CLEARDISPLAY);// clear display, set cursor position to zero
	//delayMicroseconds(2000);  // this command takes a long time!
	WAIT1_Waitms_LCD(3);
}

void LCD_home()
{
	LCD_command(LCD_RETURNHOME);  // set cursor position to zero
	//delayMicroseconds(2000);  // this command takes a long time!
	WAIT1_Waitms_LCD(3);
}

void LCD_setCursor(uint8_t col, uint8_t row)
{
	int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	if (row > g_lcd_rows) {
		row = g_lcd_rows-1;    // we count rows starting w/0
	}
	LCD_command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turn the display on/off (quickly)
void LCD_noDisplay()
{
	g_lcd_displaycontrol &= ~LCD_DISPLAYON;
	LCD_command(LCD_DISPLAYCONTROL | g_lcd_displaycontrol);
}

void LCD_display()
{
	g_lcd_displaycontrol |= LCD_DISPLAYON;
	LCD_command(LCD_DISPLAYCONTROL | g_lcd_displaycontrol);
}

// Turns the underline cursor on/off
void LCD_noCursor()
{
	g_lcd_displaycontrol &= ~LCD_CURSORON;
	LCD_command(LCD_DISPLAYCONTROL | g_lcd_displaycontrol);
}
void LCD_cursor()
{
	g_lcd_displaycontrol |= LCD_CURSORON;
	LCD_command(LCD_DISPLAYCONTROL | g_lcd_displaycontrol);
}

// Turn on and off the blinking cursor
void LCD_noBlink()
{
	g_lcd_displaycontrol &= ~LCD_BLINKON;
	LCD_command(LCD_DISPLAYCONTROL | g_lcd_displaycontrol);
}
void LCD_blink()
{
	g_lcd_displaycontrol |= LCD_BLINKON;
	LCD_command(LCD_DISPLAYCONTROL | g_lcd_displaycontrol);
}

// These commands scroll the display without changing the RAM
void LCD_scrollDisplayLeft(void)
{
	LCD_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void LCD_scrollDisplayRight(void)
{
	LCD_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void LCD_leftToRight(void)
{
	g_lcd_displaymode |= LCD_ENTRYLEFT;
	LCD_command(LCD_ENTRYMODESET | g_lcd_displaymode);
}

// This is for text that flows Right to Left
void LCD_rightToLeft(void)
{
	g_lcd_displaymode &= ~LCD_ENTRYLEFT;
	LCD_command(LCD_ENTRYMODESET | g_lcd_displaymode);
}

// This will 'right justify' text from the cursor
void LCD_autoscroll(void)
{
	g_lcd_displaymode |= LCD_ENTRYSHIFTINCREMENT;
	LCD_command(LCD_ENTRYMODESET | g_lcd_displaymode);
}

// This will 'left justify' text from the cursor
void LCD_noAutoscroll(void)
{
	g_lcd_displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	LCD_command(LCD_ENTRYMODESET | g_lcd_displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void LCD_createChar(uint8_t location, uint8_t charmap[])
{
	location &= 0x7; // we only have 8 locations 0-7
	LCD_command(LCD_SETCGRAMADDR | (location << 3));
	for (int i=0; i<8; i++) {
		LCD_write(charmap[i]);
	}
}

// Turn the (optional) backlight off/on
void LCD_noBacklight(void)
{
	g_lcd_backlightval=LCD_NOBACKLIGHT;
	LCD_expanderWrite(0);
}

void LCD_backlight(void)
{
	g_lcd_backlightval=LCD_BACKLIGHT;
	LCD_expanderWrite(0);
}



// FUNCIONES DE ESCRITURA
i2c_master_transfer_t masterXfer;
uint8_t sd[2];

void LCD_expanderWrite(uint8_t data)
{
	/*Wire.beginTransmission(_addr);
	Wire.write((int)(_data) | _backlightval);
	Wire.endTransmission();*/

	//uint8_t data=(_data) | g_lcd_backlightval;
	//printf("EW: %x\r\n",data);

	//II2C_SendChar((_data) | g_lcd_backlightval);

	data=data| g_lcd_backlightval;

    /* subAddress = 0x01, data = g_master_txBuff - write to slave.
      start + slaveaddress(w) + subAddress + length of data buffer + data buffer + stop*/
    uint8_t deviceAddress     = 0x01U;
    masterXfer.slaveAddress   = g_lcd_addr;
    masterXfer.direction      = kI2C_Write;
    masterXfer.subaddress     = (uint32_t)deviceAddress;
    masterXfer.subaddressSize = 0;
    masterXfer.data           = &data;
    masterXfer.dataSize       = 1;
    masterXfer.flags          = kI2C_TransferDefaultFlag;

    I2C_MasterTransferBlocking(I2C1, &masterXfer);



}

void LCD_write4bits(uint8_t value)
{
	LCD_expanderWrite(value);

//	while(II2C_CheckBus()!=II2C_IDLE) WAIT1_Waitus(10);
	WAIT1_Waitms_LCD(1);
	LCD_pulseEnable(value);
//	while(II2C_CheckBus()!=II2C_IDLE) WAIT1_Waitus(10);
	WAIT1_Waitms_LCD(1);
}


// write either command or data
void LCD_send(uint8_t value, uint8_t mode)
{
	uint8_t highnib=value&0xf0;
	uint8_t lownib=(value<<4)&0xf0;
	LCD_write4bits((highnib)|mode);
	LCD_write4bits((lownib)|mode);
}



void LCD_pulseEnable(uint8_t _data)
{
	LCD_expanderWrite(_data | LCD_En);	// En high
	//delayMicroseconds(1);		// enable pulse must be >450ns
	//WAIT1_Waitus(100);
	WAIT1_Waitms_LCD(1);
	//while (II2C_CheckBus()!=II2C_IDLE);
	LCD_expanderWrite(_data & ~LCD_En);	// En low
	//delayMicroseconds(50);		// commands need > 37us to settle
	//WAIT1_Waitus(100);
	WAIT1_Waitms_LCD(1);
	//while (II2C_CheckBus()!=II2C_IDLE);
}


void LCD_command(uint8_t value)
{
	LCD_send(value, 0);
}

uint8_t LCD_write(uint8_t value)
{
	LCD_send(value, LCD_Rs);
	return 1;
}


void LCD_load_custom_character(uint8_t char_num, uint8_t *rows){
	LCD_createChar(char_num, rows);
}

void LCD_setBacklight(uint8_t new_val)
{
	if (new_val) {
		LCD_backlight();		// turn backlight on
	} else {
		LCD_noBacklight();		// turn backlight off
	}
}


void LCD_printstr(const char * c)
{
	//This function is not identical to the function used for "real" I2C displays
	//it's here so the user sketch doesn't have to be changed

	while (*c)
	{
		LCD_write(*c);
		c++;
	}
}
