/*
 *   Arduino platform wrapper process for STM8S101F3 board
 *
 *     wrapper.c
 *
 */

#include <stdarg.h>
#include "wrapper.h"
#include "stm8s103f_sdcc.h"

/*  Arduino funtion wrapper  */
// digital write
void digitalWrite(unsigned char pin, unsigned char value){
  // variable
  unsigned short regad = 0x5000 + (pin >> 4) * 5;
  unsigned char bitp = 1 << (pin & 0x0f);

  // write port data
  if(value > 0) *(unsigned char*)regad |= bitp;
  else *(unsigned char*)regad &= ~bitp;

  // end of process
  return;
}

// digial read
unsigned char digitalRead(unsigned char pin){
  // variable
  unsigned short regad = 0x5000 + (pin >> 4) * 5;
  unsigned char bitp = 1 << (pin & 0x0f);

  // set output
  return (((*(unsigned char*)(regad + 1) & bitp) > 0) ? HIGH : LOW );
}

// clear pwm mode
void clrPwmmode(unsigned char pin){
  if((pin == PA3) || (pin == PD3) || (pin == PD4)){
    switch(pin){
      case PA3: TIM2_CCER2 &= 0xFE; break;      // TIM2_CCER2_CC3E = 0
      case PD3: TIM2_CCER1 &= 0xEF; break;      // TIM2_CCER1_CC2E = 0
      case PD4: TIM2_CCER1 &= 0xFE; break;      // TIM2_CCER1_CC1E = 0
    }
  }
}

// set pin mode
void pinMode(unsigned char pin, unsigned char mode){
  // variables
  unsigned short regad = 0x5000 + (pin >> 4) * 5;
  unsigned char bitp = 1 << (pin & 0x0f);

  // clear pwm mode
  clrPwmmode(pin);

  // set port input mode
  if((mode == INPUT) || (mode == INPUT_PULLUP)){
    // set direction port to input
    *(unsigned char*)(regad + 2) &= ~bitp;
    // set CCR1
    if(mode == INPUT) *(unsigned char*)(regad + 3) &= ~bitp;
    else *(unsigned char*)(regad + 3) |= bitp;
  
  // set output mode
  } else if(mode == OUTPUT){
    // set direction port to output
    *(unsigned char*)(regad + 2) |= bitp;
    // set CR1 registor
    *(unsigned char*)(regad + 3) |= bitp;
  }
  
  // set CR2 (no interrupt input and 2MH out speed)
  *(unsigned char*)(regad + 4) &= ~bitp;
}

#ifdef USEANI
// read analog
unsigned long analogRead(unsigned char pin){
  // set channel
  ADC_CSR = (ADC_CSR & 0xF0) | pin;
  delayMicroseconds(1);
  // start ADC
  ADC_CSR &= 0x7F;    // ADC_CSR_EOC = 0
  ADC_CR1 |= 1;       // ADC_CR1_ADON = 1
  // wait ADC complete
  while(!(ADC_CSR & 0x80));  // !ADC_CSR_EOC
  unsigned long rlt = (unsigned long)(ADC_DRH & 0x03) << 8;
  rlt += ADC_DRL;
  //
  return rlt;
}

// write analog
void analogWrite(unsigned pin, unsigned int val){
  // set val
  unsigned long setv = ((unsigned long)(val & 0xff) * 1000) / 255;
  
  // check pin number
  switch(pin){
    case CH1:
      TIM2_CCMR1 = (TIM2_CCMR1 & 0x8F) | 0x60;        // TIM2_CCMR1_OC1M = 6 PWM mode 1.
      TIM2_CCER1 |= 1;            // TIM2_CCER1_CC1E = 1
      TIM2_CCR1H = setv >> 8;
      TIM2_CCR1L = setv & 0xff;
      break;
    case CH2:
      TIM2_CCMR2 = (TIM2_CCMR2 & 0x8F) | 0x60;        // TIM2_CCMR2_OC2M = 6 PWM mode 1.
      TIM2_CCER1 |= 0x10;         // TIM2_CCER1_CC2E = 1
      TIM2_CCR2H = setv >> 8;
      TIM2_CCR2L = setv & 0xff;
      break;
    case CH3:
      TIM2_CCMR3 = (TIM2_CCMR3 & 0x8F) | 0x60;        // TIM2_CCMR3_OC3M = 6 PWM mode 1.
      TIM2_CCER2 |= 1;            // TIM2_CCER2_CC3E = 1
      TIM2_CCR3H = setv >> 8;
      TIM2_CCR3L = setv & 0xff;
      break;
  }
}
#endif

/*  HC-SR04 functions   */  //****************************************
#ifdef USERNS
//
// pulse length check (timeout xuS)
unsigned long checkRange(unsigned char pin, unsigned char value, unsigned long timeout){
  // variables
  unsigned long endtime = micros() + timeout;
  unsigned long duration = 0;
  unsigned long sttime = 0;
  // check pulse start
  while(1){
    unsigned long tchk = micros();
    if(tchk > endtime) break;
    else {
      unsigned char pl = digitalRead(pin);
      if(pl == value){
        sttime = tchk;
        break;
      }
    }
  }
  // check pulse end
  if(sttime != 0){
    while(1){
      unsigned long tchk = micros();
      if(tchk > endtime) break;
      else {
        unsigned char pl = digitalRead(pin);
        if(pl != value){
          duration = tchk - sttime;
          break;
        }
      }
    }
  }
  return duration;
}

// pulse length check (timeout 1sec)
unsigned long checkRange_w1(unsigned char pin, unsigned char value){
  return checkRange(pin, value, 1000000);
}
#endif

/*  SPI functions   */  //****************************************
#ifdef USESPI
//
// set SPI as master mode
void SPI_begin(void){
  // set SPI data port to input
  PC_DDR &= 0x7F;    // PC_DDR_DDR7 = 0 PC7 set input mode
  PC_CR1 |= 0x80;    // PC_CR1_C17 = 1 input pull up mode
  PC_CR2 &= 0x7F;    // PC_CR2_C27 = 0 no interrupt mode
  // set SPI data port to output
  PC_DDR |= 0x40;    // PC_DDR_DDR6 = 1 PC6 set output mode
  PC_CR1 |= 0x40;    // PC_CR1_C16 = 1 push pull mode
  PC_CR2 |= 0x40;    // PC_CR2_C26 = 1 high speed mode
  PC_ODR &= 0xBF;    // PC_ODR_ODR6 = 0 PC6 output set 0
  // set SPI clock port high
  PC_DDR |= 0x20;    // PC_DDR_DDR5 = 1 PC5 set output mode
  PC_CR1 |= 0x20;    // PC_CR1_C15 = 1 push pull mode
  PC_CR2 |= 0x20;    // PC_CR2_C25 = 1 high speed mode
  PC_ODR &= 0xDF;    // PC_ODR_ODR5 = 0 PC5 output set 1
  // SPI mode set
  SPI_CR1 = (SPI_CR1 & 0xC7) | 0x10;    // SPI_CR1_BR = 2 fmaster / 8 (2M baud).
  SPI_CR1 |= 4;      // SPI_CR1_MSTR = 1 Master device.
  SPI_CR1 |= 0x40;   // SPI_CR1_SPE = 1 Enable SPI
  SPI_CR2 = 0;
}

// terminate SPI mode
void SPI_end(void){
  SPI_CR1 &= 0xBF;   // SPI_CR1_SPE = 0
}

// set SPI data mode
void SPI_setDataMode(unsigned char mode){
  SPI_CR1 = ((mode == SPI_MODE0) || (mode == SPI_MODE1)) ? SPI_CR1 & 0xFD : SPI_CR1 | 2;  // SPI_CR1_CPOL =
  PC_ODR = ((mode == SPI_MODE0) || (mode == SPI_MODE1)) ? PC_ODR & 0xDF : PC_ODR | 0x20;  // PC_ODR_ODR5
  SPI_CR1 = ((mode == SPI_MODE0) || (mode == SPI_MODE2)) ? SPI_CR1 & 0xFE : SPI_CR1 | 1;  // SPI_CR1_CPHA
}

// set SPI clock devider
void SPI_setClockDivider(unsigned char div){
   SPI_CR1 = SPI_CR1 & 0xC7 | ((div & 7) << 3);
}

// set SPI bit order
void SPI_setBitOrder(unsigned char order){
  if(order == LSBFIRST) *(unsigned char*)0x5200 |= 0x80;
  else *(unsigned char*)0x5200 &= ~0x80;
}

void SPI_beginTransaction(unsigned char setting){ ;}
void SPI_endTransaction(void){ ;}

// TX/RX SPI 1 byte data
unsigned char SPI_transfer(unsigned char data){
  // check SPI start
  if(!(SPI_CR1 & 0x40)) return 0;  // check SPI_CR1_SPE
  while(SPI_SR & 0x80);  // check SPI_SR_BSY wait until line not busy  
  SPI_DR = data;         // data send
  while(!(SPI_SR & 2));  // check SPI_SR_TXE wait until tx start
  millis();              // dummy access to wait
  while(!(SPI_SR & 1));  // check SPI_SR_RXNE wait until rx end
  unsigned char rxd = SPI_DR;    // data read
  return rxd;            // return rx data
}

// TX/RX SPI data buffer
int SPI_transferBuf(unsigned char *txbuf, unsigned char *rxbuf, int len){
  // check SPI start
  if(!(SPI_CR1 & 0x40) || !txbuf || !rxbuf) return 0;
  while(SPI_SR & 0x80);    // check SPI_SR_BSY wait until line not busy
  // tx/rx data
  for(int i = 0 ; i < len ; i++){
    SPI_DR = txbuf[i];
    while(!(SPI_SR & 2));  // check SPI_SR_TXE wait until tx start
    millis();              // dummy access to wait
    while(!(SPI_SR & 1));  // check SPI_SR_RXNE wait until rx end 
    rxbuf[i] = SPI_DR;
  }
  return 1;
}

// TX only SPI buffer data
int SPI_transferonlyBuf(unsigned char *buf, int len){
  // check SPI start
  if(!(SPI_CR1 & 0x40)) return 0;
  while(SPI_SR & 0x80);    // check SPI_SR_BSY wait until line not busy
  // tx data
  for(int i = 0 ; i < len ; i++){
    SPI_DR = buf[i];
    while(!(SPI_SR & 2));   // check SPI_SR_TXE wait until tx start
  }
  return 1;
}
#endif

/*  I2C functions   */  //*****************************************
#ifdef USEI2C
//
#define I2C_READ                1
#define I2C_WRITE               0
struct I2CPRM {
  unsigned char rxdp;            // rx data point
  unsigned char rxlen;           // rx data length
  unsigned char rxbuf[I2CRXDBL]; // rx data buffer
};
struct I2CPRM i2c;
//
// set I2C master mode
void Wire_begin_wspd(unsigned char spd){
  // check clock speed
  if((spd != I2C_HIGH) && (spd != I2C_MID) && (spd != I2C_STD)) return;
  // Setup the I2C clock information.
  I2C_FREQR = 16;               // Set the internal clock frequency (MHz).
  I2C_CCRH &= 0x3F;             // I2C_CCRH_F_S = 0 I2C running is standard mode.
                                // I2C_CCRH_DUTY = 0 I2C pulse duty standard mode
  I2C_CCRL = spd;               // SCL clock speed
  I2C_CCRH &= 0xF0;             // I2C_CCRH_CCR = 0x00

  //  Set the address mode of this device.
  I2C_OARH &= 0x7F;             // I2C_OARH_ADDMODE = 0 7 bit address mode.
  I2C_OARH |= 0x40;             // I2C_OARH_ADDCONF = 1 Docs say this must always be 1.

  //  Setup the bus characteristics.
  I2C_TRISER = 17;              // setting I2C_FREQR + 1

  //  Setup I2C port pullup
  PB_CR1 |= 0x10;               // PB_CR1_C14 = 1
  PB_CR1 |= 0x20;               // PB_CR1_C15 = 1

  // wait for port setup
  delay(100);

  // clear rxbuf
  i2c.rxdp = 0;
  i2c.rxlen = 0;
}

// set I2C master mode with default speed
void Wire_begin(void){
  Wire_begin_wspd(I2C_STD);
}

// set I2C master TX mode (return : error flag, 1 error)
int Wire_beginTransmission(unsigned char addr){
  // variables
  volatile unsigned char dum;   // read dummy buffer
  unsigned long waitlmt;        // wait limit time (mS)
  #define  CHKWAIT 15           // check wait time (mS)
  int rlt = 0;                  // return

  // enable I2C
  I2C_CR1 |= 1;                 // I2C_CR1_PE = 1 enable I2C

  // start I2C
  I2C_SR2 &= 0xf0;              // clear error flag
  I2C_CR2 &= 0xF9;              // I2C_CR2_ACK = 0 ack return clear
                                // I2C_CR2_STOP = 0 stop bit set clear
  I2C_CR2 |= 1;                 // I2C_CR2_START = 1 set start bit
  waitlmt = millis() + (CHKWAIT << 1); // set timeout
  while(!(I2C_SR1 & 1) && (millis() < waitlmt));  // check SB
  if(millis() >= waitlmt) rlt = 1;
  dum = I2C_SR1;                // clear start bit set flag

  // set I2C address
  if(!rlt){
    I2C_DR = (addr << 1) | I2C_WRITE;  // set device address
    waitlmt = millis() + CHKWAIT;      // set timeout
    while(!(I2C_SR1 & 2) && (millis() < waitlmt)); // check ADDR
    if(millis() >= waitlmt) rlt = 1;   // timeout error
    dum = I2C_SR1;              // clear addres transmitted flag
    dum = I2C_SR3;
  }

  // process end
  return rlt;
}

// tx I2C data (return : error flag, 1 error)
int Wire_write(unsigned char data){
  unsigned long waitlmt;        // wait limit time (mS)
  int rlt = 0;                  // return
  waitlmt = millis() + CHKWAIT; // set timeout
  while(!(I2C_SR1 & 0x80) && (millis() < waitlmt)); // check TXE wait tx buffer enmpty
  if(millis() >= waitlmt) rlt = 1;   // timeout error
  else I2C_DR = data;
  return rlt;
}

// I2C data tx end with stp flag control
unsigned char Wire_endTransmission_wstpctrl(int stp){
  unsigned long waitlmt;        // wait limit time (mS)
  int rlt = 0;                  // return

  // wait last data tx end
  waitlmt = millis() + CHKWAIT; // set timeout
  while((!(I2C_SR1 & 0x80) || !(I2C_SR1 & 4)) && (millis() < waitlmt)); // check TXE, BTF
  if(millis() >= waitlmt) rlt = 1;   // timeout error

  // end of process (set stop condition)
  if(stp){                      // 
    I2C_CR2 |= 2;               // I2C_CR2_STOP = 1 set stop bit
    waitlmt = millis() + CHKWAIT; // set timeout
    while((I2C_SR3 & 2) && (millis() < waitlmt));  // check I2C_SR3_BUSY wait I2C bus end
    I2C_CR1 &= 0xFE;            // I2C_CR1_PE = 0 disable I2C
  }

  // process end
  return (rlt ? 4 : 0);
}

// normal I2C data tx end
unsigned char Wire_endTransmission(void){
  return Wire_endTransmission_wstpctrl(1);
}

// request I2C data from device
unsigned char Wire_requestFrom(unsigned char addr, unsigned char len){
  // variables
  volatile unsigned char dum;   // read dummy buffer
  unsigned long waitlmt;        // wait limit time (mS)
  int rlt = 0;                  // return

  // initial set
  i2c.rxlen = 0; i2c.rxdp = 0;

  // enable I2C
  I2C_CR1 |= 1;                 // set PE enable I2C

  // start I2C
  I2C_SR2 &= 0xf0;              // clear error flag
  I2C_CR2 |= 4;                 // I2C_CR2_ACK = 1 ack return set
  I2C_CR2 &= 0xFD;              // I2C_CR2_STOP = 0 stop bit set clear
  I2C_CR2 |= 1;                 // I2C_CR2_START = 1 set start bit
  waitlmt = millis() + CHKWAIT; // set timeout
  while(!(I2C_SR1 & 1) && (millis() < waitlmt));  // check SB
  if(millis() >= waitlmt) rlt = 1;
  dum = I2C_SR1;                // clear start bit set flag

  // set I2C address
  if(!rlt){
    I2C_DR = (addr << 1) | I2C_READ;   // set device address
    waitlmt = millis() + CHKWAIT;      // set timeout
    while(!(I2C_SR1 & 2) && (millis() < waitlmt)); // check ADDR
    if(millis() >= waitlmt) rlt = 1;   // timeout error
    dum = I2C_SR1;              // clear addres transmitted flag
    dum = I2C_SR3;
  }

  // get data
  for(int i = 0 ; !rlt && (i < len) ; i++){
    if(i >= (len - 1)){
      I2C_CR2 &= 0xFB;          // I2C_CR2_ACK = 0
      I2C_CR2 |= 2;             // I2C_CR2_STOP = 1
    }
    waitlmt = millis() + CHKWAIT;         // set timeout
    while(!(I2C_SR1 & 0x40) && (millis() < waitlmt)); // check RXNE wait rx buffer enmpty
    if(millis() >= waitlmt) rlt = 1;   // timeout error
    dum = I2C_DR;
    if(!rlt){
      i2c.rxbuf[i] = dum;
      i2c.rxlen++;
    }
  }

  // end of process
  waitlmt = millis() + CHKWAIT;   // set timeout
  while((I2C_SR3 & 2) && !rlt && (millis() < waitlmt));   // check BUSY wait I2C bus end
  I2C_CR2 &= 0xFB;                // I2C_CR2_ACK = 0
  I2C_CR1 &= 0xFE;                // I2C_CR1_PE = 0 disable I2C
  return i2c.rxlen;                   // return rx byte number
}

// get rx data
unsigned char Wire_read(void){
  unsigned char rxd = 0;
  if(i2c.rxdp < i2c.rxlen) rxd = i2c.rxbuf[i2c.rxdp++];
  return rxd;
}
#endif

/*  Uart functions  */   //************************************
#ifdef USEURT
//
struct USARTPRM {
  unsigned char rxbuf[RXDBL];     // internal rx buffer
  unsigned char rxbwpt;           // rx buffer write pointer
  unsigned char rxendflg;         // rx read end flag
  unsigned char rxdbuf[RXDBL];    // rx data buffer
  unsigned char rxdlen;           // rx data length
  unsigned char chkint;           // rx end check interval
};
struct USARTPRM  urt;
// set serial begin with external rx buffer
void Serial_begin(unsigned long spd){
  // set initial value
  urt.rxendflg = 0; urt.rxbwpt = 0; urt.rxdlen = 0;

  // buffer initial clear
  for(int i = 0 ; i < RXDBL ; i++){
    urt.rxbuf[i] = 0; urt.rxdbuf[i] = 0;
  }

  // set rx end check interval
  urt.chkint = (unsigned char)(4800 / spd) * 3 + 3;

  // clear flag with dummy read
  unsigned char tmp = USART1_SR;
  tmp = USART1_DR;

  //  Reset the USART registers
  USART1_CR1 = 0; USART1_CR2 = 0; USART1_CR4 = 0; USART1_CR3 = 0;
  USART1_CR5 = 0; USART1_GTR = 0; USART1_PSCR = 0;

  // set USART mode
  USART1_CR1 &= 0xEB;     // USART1_CR1_M = 0 8 Data bits.
                          // USART1_CR1_PCEN = 0 Disable parity.
  USART1_CR3 &= 0xCF;     // USART1_CR3_STOP = 0 1 stop bit.
  unsigned long brset = (16000000 + (unsigned long)(spd >> 1)) / (unsigned long)spd;
  USART1_BRR2 = (unsigned char)(((brset & 0xf000) >> 8) | (brset & 0x0f));
  USART1_BRR1 = (unsigned char)((brset & 0x0ff0) >> 4);

  // set the clock polarity, lock phase and last bit clock pulse.
  USART1_CR3 |= 7;        // USART1_CR3_CPOL = 1
                          // USART1_CR3_CPHA = 1
                          // USART1_CR3_LBCL = 1

  // USART tx/rx enable
  USART1_CR2 |= 0x0C;     // USART1_CR2_TEN = 1
                          // USART1_CR2_REN = 1;

  // set rx interrupt enable
  USART1_CR2 |= 0x20;     // USART1_CR2_RIEN = 1
}

// release serial setting
void Serial_end(void){
  // disable USART tx/rx interrupt
  USART1_CR2 &= 0x53;      // USART1_CR2_TIEN = 0
                           // USART1_CR2_RIEN = 0
  // disable USART tx/rx
                           // USART1_CR2_TEN = 0
                           // USART1_CR2_REN = 0
}

// serial data read
int Serial_readBuf(char *buff, unsigned char blen){
  // set rx data length
  unsigned char rlt = urt.rxdlen;

  // check rx status
  if(rlt > 0){
    // set rx data
    for(int i = 0 ; i < blen ; i++){
      buff[i] = (i < rlt) ? urt.rxdbuf[i] : 0;
    }

    // check read end
    if(rlt <= blen){       // clear data
      urt.rxdlen = 0;
      urt.rxendflg = 0;
    } else {               // data shift
      for(int i = blen ; i < rlt ; i++)
        urt.rxdbuf[i - blen] = urt.rxdbuf[i];
      urt.rxdlen -= blen;
    }
  }

  // end
  return rlt;
}

// serial rx check
int Serial_available(void){
  return (int)((urt.rxendflg > 0) ? urt.rxdlen : 0);
}

// serial buffer data write
void Serial_writeBuf(char *data, unsigned char len){
  // variables
  unsigned long waitlmt;
  #define SCHKWAIT 5             // serial check wait
  // serial data tx
  for(int i = 0 ; i < len ; i++){
    USART1_SR &= 0xBF;           // TC flag clear
    USART1_DR = data[i];
    waitlmt = millis() + SCHKWAIT;
    while(!(USART1_SR & 0x40) && (millis() < waitlmt));  // check TC complete
  }
}

#if 0
// serial write string
void Serial_print(const char *fmt, ...){
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
}
#endif

// Uart RX interrupt
void UartRxHandler(void)  __interrupt(18)
{
  extern char rxecnt = urt.chkint; // rx end wait counter set
  disableInterrupts();
  unsigned char rxd = USART1_DR;
  if(USART1_SR & 0x0F) return;     // check error status
  // set rx data to buffer
  if(urt.rxbwpt < RXDBL) urt.rxbuf[urt.rxbwpt++] = rxd;
  // check buffer full
  if(urt.rxbwpt == RXDBL){
    for(int i = 0 ; i < RXDBL ; i++) urt.rxdbuf[i] = urt.rxbuf[i];
    urt.rxdlen = RXDBL;
    urt.rxendflg = 1;
    urt.rxbwpt = 0;
  }
  enableInterrupts();
}

// serial read end process
void Serial_read_end(void){
  for(int i = 0 ; i < RXDBL ; i++){
    urt.rxdbuf[i] = (i < urt.rxbwpt) ? urt.rxbuf[i] : 0;
  }
  urt.rxdlen = urt.rxbwpt;
  urt.rxbwpt = 0;
  urt.rxendflg = 1;
}
#else
// serial read end dummy process
void Serial_read_end(void){
  // empty
}
#endif

// set 1 byte tx routine for printf function of SDCC
int putchar(int c) __reentrant
{
#ifdef USEURT
  USART1_SR &= 0xBF;           // TC flag clear
  USART1_DR = (c & 0xFF);
  while(!(USART1_SR & 0x40));  // check TC complete
#endif
  return c;
}

/*  EEPROM functions  */   //************************************
#ifdef USEEPM
// write to EEPROM memory
void EEPROM_write(unsigned short addr, unsigned char value){
  //  unlock write protect
  if ((FLASH_IAPSR & 8) == 0){  // FLASH_IAPSR_DUL == 0
     FLASH_DUKR = 0xae;
     FLASH_DUKR = 0x56;
  }
  //  write byte data
  *((char *)(0x4000 + addr)) = value;
  // set write protect
  FLASH_IAPSR &= 0xF7;          // FLASH_IAPSR_DUL = 0
}

// read from EEPROM memory
unsigned char EEPROM_read(unsigned short addr){
  return *((char *)(0x4000 + addr));
}
#endif


