//
//  STM8S103F3 LCD1602 control library
//
// FILE: LCD_I2C.c
//
#include "LCD_I2C.h"

// variables
static unsigned char _Addr;
static unsigned char _cols;
static unsigned char _rows;
static unsigned char _backlightval;
static unsigned char _displayfunction;
static unsigned char _displaycontrol;
static unsigned char _displaymode;
static unsigned char _numlines;

// get coloum , row    coloum:hi-byte, row:low-byte
unsigned short getcolrow(void){
  return ((unsigned short)_cols << 8) | ((unsigned short)_rows);
}

// send tx data
static void setTxdata(unsigned char *buf, unsigned char len){
  Wire_beginTransmission(_Addr);
  for(int i = 0 ; i < len ; i++) Wire_write(buf[i] | _backlightval);
  Wire_endTransmission();
  return;
}

// internal function
static void send1bytedata(unsigned char data, unsigned char mode){
  // set tx data
  unsigned char buf[4];
  buf[1] = (data & 0xF0) | mode;
  buf[0] = buf[1] | En;
  buf[3] = (data << 4) | mode;
  buf[2] = buf[3] | En;

  // send data block
  setTxdata(buf, 4);

  //
  return;
}

static void send4bitdata(unsigned char data){
  // set tx data
  unsigned char buf[2];
  buf[1] = data;
  buf[0] = buf[1] | En;

  // setnd data block
  setTxdata(buf, 2);

  //
  return;
}

static void expanderWrite(unsigned char val){
  setTxdata(&val, 1);
  return;
}

// lcd parameter initialize
void LCD_init(unsigned char i2c_addr, unsigned char lcd_cols, unsigned char lcd_rows){
  // set parameters
  _Addr = i2c_addr;
  _cols = lcd_cols;
  _rows = lcd_rows;
  _backlightval = LCD_NOBACKLIGHT;

  // set I2C mode
  Wire_begin();
  _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

  // initial set lcd
  if (lcd_rows > 1) _displayfunction |= LCD_2LINE;
  _numlines = lcd_rows;
  delay(50);

  // set backlight 
  expanderWrite(_backlightval);
  delay(1000);

  // set 8 bit mode to 4 bit mode
  for(int i = 0 ; i < 3 ; i++){    // set 8 bit mode first
    send4bitdata(0x30);
    delayMicroseconds(4500);
  }
  send4bitdata(0x20);              // set 4 bit mode

  // set # lines, font size, etc
  send1bytedata(LCD_FUNCTIONSET | _displayfunction, 0);

  // turn the display on with no cursor or blinking default
  _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
  LCD_display(1);

  // clear it off
  LCD_clear();
  
  // Initialize to default text direction (for roman languages)
  _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

  // set the entry mode
  send1bytedata(LCD_ENTRYMODESET | _displaymode, 0);

  LCD_home();
}

void LCD_clear(void){
  send1bytedata(LCD_CLEARDISPLAY, 0);// clear display, set cursor position to zero
  delayMicroseconds(2000);  // this command takes a long time!
}

void LCD_home(void){
  send1bytedata(LCD_RETURNHOME, 0);  // set cursor position to zero
  delayMicroseconds(2000);  // this command takes a long time!
}

void LCD_display(unsigned char on){  // on = 1:on/0:off
  _displaycontrol &= ~LCD_DISPLAYON;
  if(on > 0) _displaycontrol |= LCD_DISPLAYON;
  send1bytedata(LCD_DISPLAYCONTROL | _displaycontrol, 0);
}

void LCD_blink(unsigned char on){    // on = 1:blink/0:no-blink
  _displaycontrol &= ~LCD_BLINKON;
  if(on > 0) _displaycontrol |= LCD_BLINKON;
  send1bytedata(LCD_DISPLAYCONTROL | _displaycontrol, 0);
}

void LCD_cursor(unsigned char on){   // on = 1:cursor/0:no-cursor
  _displaycontrol &= ~LCD_CURSORON;
  if(on > 0) _displaycontrol |= LCD_CURSORON;
  send1bytedata(LCD_DISPLAYCONTROL | _displaycontrol, 0);
}

void LCD_scroll(unsigned char lft){  // lft = 1:left/0:right
  send1bytedata(LCD_CURSORSHIFT | LCD_DISPLAYMOVE |
        ((lft > 0) ? LCD_MOVELEFT : LCD_MOVERIGHT), 0);
}

void LCD_write(unsigned char chr){   // print text
  send1bytedata(chr, Rs);
}

void LCD_writeStr(unsigned char *str, unsigned char len){ // write string
  // write string
  for(int i = 0 ; i < len ; i++) LCD_write(str[i]);
}

void LCD_letterL2R(unsigned char l2r){  // l2r = 1:left->right/0:right->left
  _displaymode &= ~LCD_ENTRYLEFT;
  if(l2r > 0) _displaymode |= LCD_ENTRYLEFT;
  send1bytedata(LCD_ENTRYMODESET | _displaymode, 0);
}

void LCD_backlight(unsigned char on){  // on = 1:on/0:off
  _backlightval = (on > 0) ? LCD_BACKLIGHT : LCD_NOBACKLIGHT;
  expanderWrite(0);
}

void LCD_autoscroll(unsigned char on){ // on = 1:autoscroll/0:no-autoscroll
  _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
  if(on > 0) _displaymode |= LCD_ENTRYSHIFTINCREMENT;
  send1bytedata(LCD_ENTRYMODESET | _displaymode, 0);
}

void LCD_createChar(unsigned char location, unsigned char charmap[]){
  location &= 0x7; // we only have 8 locations 0-7
  send1bytedata(LCD_SETCGRAMADDR | (location << 3), 0);
  for (int i = 0 ; i < 8; i++){
    LCD_write(charmap[i]);
  }
}

void LCD_setCursor(unsigned char col, unsigned char row){
  int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
  if ( row > _numlines ) {
    row = _numlines-1;    // we count rows starting w/0
  }
  send1bytedata(LCD_SETDDRAMADDR | (col + row_offsets[row]), 0);
}
