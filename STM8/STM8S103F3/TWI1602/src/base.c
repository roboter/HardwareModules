//
//  STM8S103F3 board base platform process
//
// FILE: base.c
//
#include "stm8s103f_sdcc.h"
#include "wrapper.h"

// external reference
extern void setup(void);
extern void loop(void);
extern void Serial_read_end(void);

// global varialbes
char rxecnt;

/*       --- Setup system ---       */
//  Setup the system clock to run at 16MHz using the internal oscillator.
void InitialiseSystemClock()
{
  CLK_ICKR = 1;                   //  set Enable the HSI.
  CLK_ECKR = 0;                   //  Disable the external clock.
  while ((CLK_ICKR & 2) == 0);    //  Wait for the HSI to be ready for use.
  CLK_CKDIVR = 0;                 //  Ensure the clocks are running at full speed.
  CLK_PCKENR1 = 0xff;             //  Enable all peripheral clocks.
  CLK_PCKENR2 = 0xff;             //  Ditto.
  CLK_CCOR = 0;                   //  Turn off CCO.
  CLK_HSITRIMR = 0;               //  Turn off any HSIU trimming.
  CLK_SWIMCCR = 0;                //  Set SWIM to run at clock / 2.
  CLK_SWR = 0xe1;                 //  Use HSI as the clock source.
  CLK_SWCR = 2;                   //  set Enable switching.
  while ((CLK_SWCR & 1) != 0);    //  Pause while the clock switch is busy.
  //
  rxecnt = 0;
  return;
}

// interrupt function registration
#ifdef USET4I
void TIM4_UPD_OVF_IRQHandler(void) __interrupt(23);     // timer 4 interrupt
#endif
// external interrupt handler (enable when use handler)
#ifdef USEEXI
void  EXTI_PORTA_IRQHandler(void) __interrupt(3);      // Port A external input interrupts
void  EXTI_PORTB_IRQHandler(void) __interrupt(4);      // Port B external input interrupts
void  EXTI_PORTC_IRQHandler(void) __interrupt(5);      // Port C external input interrupts
void  EXTI_PORTD_IRQHandler(void) __interrupt(6);      // Port D external input interrupts
#endif

/*       --- Setup Timer 2 for tick timer & PWM ---       */
//  Timer 2 interrupt handler.
unsigned long elpstime;   // elapse timer (mS)
void TIM2_UPD_OVF_IRQHandler(void) __interrupt(13)
{
  // check serial rx block end counter
  if(rxecnt > 0){
    rxecnt--;
    if(rxecnt == 0) Serial_read_end();  // call serial read end
  }

  elpstime++;             //  timer increment
  TIM2_SR1 &= 0xFE;       //  Reset the interrupt
  return;
}

// report system clock (mS)
unsigned long millis(void){
  return elpstime;
}

// report system clock micro second (uS)
unsigned long micros(void){
  disableInterrupts();
  unsigned long tim2cnt = TIM2_CNTRH;
  tim2cnt = (tim2cnt << 8) + TIM2_CNTRL;
  unsigned long rlt = (unsigned long)elpstime * 1000 + (unsigned long)tim2cnt;
  enableInterrupts();
  return rlt;
}

/*  Time chick functions  */
// delay mS
void delay(unsigned long dly){
  unsigned long lmttime = elpstime + dly;
  while(lmttime >= elpstime);
  return;
}

// delay micro seconds (dly uS)
void delayMicroseconds(unsigned long dly){
  unsigned long elpsmicroend = micros() + dly;
  while(elpsmicroend > micros());
  return;
}

//  Setup Timer 2 to generate an interrupt every 1mS based on a 16MHz clock.
void SetupTimer2(void)
{
  TIM2_PSCR = 0x04;       //  Prescaler = 16.
  TIM2_ARRH = 0x03;       //  High byte of 1000.
  TIM2_ARRL = 0xe8;       //  Low byte of 1000.
  TIM2_IER |= 1;          //  Enable timer2 update interrupts.
  TIM2_CR1 |= 1;          //  Finally enable the timer2.
  //
  return;
}

// set up ADC initial
void SetupADC(void)
{
  ADC_CR1 |= 1;           // ADC power on
  ADC_CR2 |= 8;           //  Data is right aligned.
  return;
}

/*       --- Main process ---      */
//  Main program loop.
void main()
{
  // system setup
  InitialiseSystemClock();
  SetupADC();
  SetupTimer2();
  enableInterrupts();
  // application setup call
  setup();
  
  // application loop process call
  while(1) loop();
}

