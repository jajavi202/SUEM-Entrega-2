#ifndef SOURCES_LCD_H_
#define SOURCES_LCD_H_

#include <stdint.h>

//https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library/blob/master/LiquidCrystal_I2C.h
// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00


#define LCD_En 0x04 //B00000100  // Enable bit
#define LCD_Rw 0x02 //B00000010  // Read/Write bit
#define LCD_Rs 0x01 //B00000001  // Register select bit





uint8_t LCD_Init(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t charsize);
void LCD_clear();
void LCD_home();
void LCD_setCursor(uint8_t col, uint8_t row);
void LCD_noDisplay();
void LCD_display();
void LCD_noCursor();
void LCD_cursor();
void LCD_noBlink();
void LCD_blink();
void LCD_scrollDisplayLeft(void);
void LCD_scrollDisplayRight(void);
void LCD_leftToRight(void);
void LCD_rightToLeft(void);
void LCD_autoscroll(void);
void LCD_noAutoscroll(void);
void LCD_createChar(uint8_t location, uint8_t charmap[]);
void LCD_noBacklight(void);
void LCD_backlight(void);

void LCD_command(uint8_t value);
uint8_t LCD_write(uint8_t value);

void LCD_expanderWrite(uint8_t _data);
void LCD_write4bits(uint8_t value);
void LCD_send(uint8_t value, uint8_t mode);
void LCD_pulseEnable(uint8_t _data);

void LCD_load_custom_character(uint8_t char_num, uint8_t *rows);
void LCD_setBacklight(uint8_t new_val);
void LCD_printstr(const char * c);



#endif /* SOURCES_LCD_H_ */
