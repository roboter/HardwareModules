//
//  STM8S103F3 LCD1602 control library header file
//
// FILE: LCD_I2C.h
//
#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "../../include/wrapper.h"

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

//
#define En 0x04  // Enable bit
#define Rw 0x02  // Read/Write bit
#define Rs 0x01  // Register select bit

// functions
unsigned short getcolrow(void);
void LCD_init(unsigned char i2c_addr, unsigned char lcd_cols, unsigned char lcd_rows);
void LCD_clear(void);
void LCD_home(void);
void LCD_display(unsigned char on);  // on = 1:on/0:off
void LCD_blink(unsigned char on);    // on = 1:blink/0:no-blink
void LCD_cursor(unsigned char on);   // on = 1:cursor/0:no-cursor
void LCD_scroll(unsigned char lft);  // lft = 1:left/0:right
void LCD_write(unsigned char chr);   // write char
void LCD_writeStr(unsigned char *str, unsigned char len); // write string
void LCD_letterL2R(unsigned char l2r); // l2r = 1:left->right/0:right->left
void LCD_backlight(unsigned char on);  // on = 1:on/0:off
void LCD_autoscroll(unsigned char on); // on = 1:autoscroll/0:no-autoscroll
void LCD_createChar(unsigned char location, unsigned char charmap[]);
void LCD_setCursor(unsigned char col, unsigned char row);

#endif /* LCD_I2C_H */
