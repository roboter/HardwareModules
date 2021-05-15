/*
 *   Arduino wrapper process header for STM8S101F3 board
 *
 *     wrapper.h
 *
 */

#ifndef WAPPER_H
#define WAPPER_H

// include file
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "stm8s103f_sdcc.h"

// implement function selection
#define USEANI        // enable use Analog input
//#define USESPI        // enable use SPI function
#define USEI2C        // enable use I2C function
#define USEURT        // enable use Uart function
//#define USEEPM        // enable use EEPROM function
//#define USESIN        // enable use SIN/COSINE table function
//#define USERNS        // enalbe use HC-SR04 range sensor function

// interrupt handler registration
//#define USET4I        // enable timer 4 interrupt handler
//#define USEEXI        // enable external input interrupt

// definition
#define HIGH    1
#define LOW     0
#define RXDBL  16    // rx data buffer length
#define I2CRXDBL 16  // I2C rx data buffer length

// pin mode
#define INPUT         0
#define INPUT_PULLUP  1
#define OUTPUT        2

// SPI param
#define SPI_MODE0     0
#define SPI_MODE1     1
#define SPI_MODE2     2
#define SPI_MODE3     3
#define MSBFIRST      0
#define LSBFIRST      1

// port A
#define PA1   0x01
#define PA2   0x02
#define PA3   0x03

// port B
#define PB4   0x14
#define PB5   0x15

// port C
#define PC3   0x23
#define PC4   0x24
#define PC5   0x25
#define PC6   0x26
#define PC7   0x27

// port D
#define PD1   0x31
#define PD2   0x32
#define PD3   0x33
#define PD4   0x34
#define PD5   0x35
#define PD6   0x36

// analog port input
#define AIN2     2    // PC4 port
#define AIN3     3    // PD2 port
#define AIN4     4    // PD3 port
#define AIN5     5    // PD5 port
#define AIN6     6    // PD6 port

// PWM output port (TIM2 out)
#define CH1    PD4    // PD4 port
#define CH2    PD3    // PD3 port
#define CH3    PA3    // PA3 port

// UART
#define UART_RX  PD6  // PD6 port
#define UART_TX  PD5  // PD5 port
#define BIN        2  // binary value
#define OCT        8  // octibal value
#define DEC       10  // decimal value
#define HEX       16  // hexadecimal value

// I2C
#define I2C_SCL  PB4  // PB4 port
#define I2C_SDA  PB5  // PB5 port
#define I2C_HIGH  20  // 400KHz mode
#define I2C_MID   30  // 267KHz mode
#define I2C_STD   80  // 100KHz mode

// SPI param definition
#define MOSI   PC6    // PC6 port
#define MISO   PC7    // PC7 port
#define SCK    PC5    // PC5 port
#define SS     PA3    // PA3 port
#define SPI_MODE0    0
#define SPI_MODE1    1
#define SPI_MODE2    2
#define SPI_MODE3    3
#define SPI_CLOCK_DIV2   0
#define SPI_CLOCK_DIV4   1
#define SPI_CLOCK_DIV8   2
#define SPI_CLOCK_DIV16  3
#define SPI_CLOCK_DIV32  4
#define SPI_CLOCK_DIV64  5
#define SPI_CLOCK_DIV128 6

// other definition
#define PI 3.141592

/*  --- external reference ---*/
// timer
extern unsigned long elpstime;           // elapse timer
extern void delay(unsigned long dly);
extern unsigned long millis(void);
extern unsigned long micros(void);
extern void delayMicroseconds(unsigned long dly);
// GPIO
extern void digitalWrite(unsigned char pin, unsigned char value);
extern unsigned char digitalRead(unsigned char pin);
extern void pinMode(unsigned char pin, unsigned char mode);
// analog I/O
extern unsigned long analogRead(unsigned char pin);         // pin is AIN2 to AIN6, return 0 - 1023 
extern void analogWrite(unsigned pin, unsigned int val);    // pin is CH1 to CH3, input 0 - 255

// HC-SR04 range sensor check
#ifdef USERNS
extern unsigned long checkRange(unsigned char pin,          // parameter (pin, 
     unsigned char value, unsigned long timeout);           // level(HIGH or LOW), timeout(uS)
extern unsigned long checkRange_w1(unsigned char pin,       // parameter (pin, 
     unsigned char value);                                  // level(HIGH or LOW)) default time out 1 Sec
#endif

// SPI (MISO:PC7, MOSI:PC6, SCK:PC5)
#ifdef USESPI
void SPI_begin(void);
void SPI_end(void);
void SPI_setDataMode(unsigned char mode);
void SPI_setClockDivider(unsigned char div);
void SPI_setBitOrder(unsigned char order);
void SPI_beginTransaction(unsigned char setting);
void SPI_endTransaction(void);
unsigned char SPI_transfer(unsigned char data);
int SPI_transferBuf(unsigned char *txbuf, unsigned char *rxbuf, int len);
int SPI_transferonlyBuf(unsigned char *buf, int len);
#endif

// I2C (SCL:PB4, SDA:PB5)
#ifdef USEI2C
void Wire_begin_wspd(unsigned char spd);  // spd:I2C_HIGH, I2C_MID, I2C_STD
void Wire_begin(void);
int Wire_beginTransmission(unsigned char addr);
int Wire_write(unsigned char);
unsigned char Wire_endTransmission_wstpctrl(int stp);
unsigned char Wire_endTransmission(void);
unsigned char Wire_requestFrom(unsigned char addr, unsigned char len);
unsigned char Wire_available(void);//{ return rxlen;}
unsigned char Wire_read(void);
#endif

// Uart (RX:PD6, TX:PD5)
#ifdef USEURT
void Serial_begin(unsigned long spd);
void Serial_end(void);
int Serial_available(void);
int Serial_readBuf(char *buff, unsigned char blen);
void Serial_writeBuf(char *data, unsigned char len);
//#define Serial_print printf
//void Serial_print(const char *fmt, ...);
void UartRxHandler(void)  __interrupt(18);
#endif

// EEPROM
#ifdef USEEPM
void EEPROM_write(unsigned short addr, unsigned char value);
unsigned char EEPROM_read(unsigned short addr);
#endif

// Sine/Cosine function (output -100 to 100)
#ifdef USESIN
extern int Sin_l(int angle);
extern int Cos_l(int angle);
#endif

#endif /* WAPPER_H */
