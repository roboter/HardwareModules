//
//  STM8S103F3 board LCD1602 control sample program
//
// FILE: lcd1602_i2c.c
//
//    Wiring  STM8S103F3   LCD1602/2004
//                PB4           SCL
//                PB5           SDA
//                 5V           VCC
//                GND           GND
//
//                PD5(UART-TX)
//                PD6(UART-RX)
//
#include "stm8s103f_sdcc.h"
#include "wrapper.h"
#include <mini-printf.h>
#include <LCD_I2C.h>

#define I2CADR  0x27                 // for PCF8574
//#define I2CADR  0x3F                 // for PCF8574A
//#define LCD2004                      // comment out for LCD 1602
#ifdef LCD2004   // LCD 2004
  #define COLNUM   20                // 20 colums
  #define LNNUM     4                // 4 lines
#else            // LCD 1602
  #define COLNUM   16                // 16 colums
  #define LNNUM     2                // 2 lines
#endif

// global variables
unsigned int lcnt;

// setup process
void setup(void){
  // set lcd init
  lcnt = 0;
  LCD_init(I2CADR, COLNUM, LNNUM);
  LCD_clear();
  LCD_backlight(1);
}

// loop process
void loop(void){
    // variables
    unsigned char dbuf[16];
    int dlen;

    // display message
    for(int i = 0 ; i < 5 ; i++){
      // display start message for 2004
      LCD_clear();
      LCD_letterL2R((i + 1) & 1);
#ifdef LCD2004
      LCD_setCursor((i & 1) ? 14 : 4, 0);
      LCD_writeStr("Hello world.", 12);
      LCD_setCursor((i & 1) ? 13 : 5, 1);
      LCD_writeStr("LCD 2004", 8);
      LCD_setCursor((i & 1) ? 15 : 4, 2);
      LCD_writeStr("June 2020", 9);
      LCD_setCursor((i & 1) ? 16 : 3, 3);
      LCD_writeStr("By Itaru Satoh", 14);
#else  // LCD1602
      LCD_setCursor((i & 1) ? 13 : 2, 0);
      LCD_writeStr("Hello world.", 12);
      LCD_setCursor((i & 1) ? 13 : 2, 1);
      LCD_writeStr("LCD 1602", 8);
#endif
      delay(1000);
    }

    delay(1000);

    // blink
    for(int i = 0 ; i < 6 ; i++){
      LCD_display(i & 1);
      delay(1000);
    }

    delay(1000);

    // scroll
    for(int i = 0 ; i < 12 ; i++){
      LCD_scroll(((i < 3) || (i > 8)) ? 1 : 0);
      delay(1000);
    }

    delay(1000);

    // display all character
    LCD_clear();
    unsigned char dspchr = 0x20;
    for(int lp = 0 ; lp < (COLNUM/2) ; lp++){
      for(int i = 0 ; i < LNNUM ; i++){
        LCD_setCursor(0, i);
        for(int j = 0 ; j < COLNUM ; j++){
          if(dspchr == 0x80) dspchr = 0xa0;
          if(dspchr < 0x20) dspchr = 0x20;
          LCD_write(dspchr++);
        }
      }

      delay(1000);
    }

    delay(1000);
    
    // counter number display
    lcnt++;
    LCD_clear();
    LCD_home();
    dlen = mini_snprintf(dbuf, sizeof(dbuf), "Count = %d", lcnt);
    LCD_writeStr(dbuf, dlen);

    delay(2000);
}

