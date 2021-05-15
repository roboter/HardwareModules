//
//  STM8S103F3 header file
//
// FILE: stm8s103f_sdcc.h
//
#ifndef STM8S103F_H
#define STM8S103F_H

/* GPIO */
#define PA_ODR *(unsigned char*)0x5000
#define PA_IDR *(unsigned char*)0x5001
#define PA_DDR *(unsigned char*)0x5002
#define PA_CR1 *(unsigned char*)0x5003
#define PA_CR2 *(unsigned char*)0x5004

#define PB_ODR *(unsigned char*)0x5005
#define PB_IDR *(unsigned char*)0x5006
#define PB_DDR *(unsigned char*)0x5007
#define PB_CR1 *(unsigned char*)0x5008
#define PB_CR2 *(unsigned char*)0x5009

#define PC_ODR *(unsigned char*)0x500A
#define PC_IDR *(unsigned char*)0x500B
#define PC_DDR *(unsigned char*)0x500C
#define PC_CR1 *(unsigned char*)0x500D
#define PC_CR2 *(unsigned char*)0x500E

#define PD_ODR *(unsigned char*)0x500F
#define PD_IDR *(unsigned char*)0x5010
#define PD_DDR *(unsigned char*)0x5011
#define PD_CR1 *(unsigned char*)0x5012
#define PD_CR2 *(unsigned char*)0x5013

/* FLASH */
#define FLASH_CR1 *(unsigned char*)0x505A
#define FLASH_CR2 *(unsigned char*)0x505B
#define FLASH_NCR2 *(unsigned char*)0x505C
#define FLASH_FPR *(unsigned char*)0x505D
#define FLASH_NFPR *(unsigned char*)0x505E
#define FLASH_IAPSR *(unsigned char*)0x505F
#define FLASH_PUKR *(unsigned char*)0x5062
#define FLASH_DUKR *(unsigned char*)0x5064

/* EXTERNAL INTERRUPT */
#define EXTI_CR1 *(unsigned char*)0x50A0
#define EXTI_CR2 *(unsigned char*)0x50A1

/* RESET */
#define RST_SR *(unsigned char*)0x50B3

/* CLOCK */
#define CLK_ICKR	*(unsigned char*)0x50C0
#define CLK_ECKR	*(unsigned char*)0x50C1
#define CLK_CMSR	*(unsigned char*)0x50C3
#define CLK_SWR 	*(unsigned char*)0x50C4
#define CLK_SWCR	*(unsigned char*)0x50C5
#define CLK_CKDIVR	*(unsigned char*)0x50C6
#define CLK_PCKENR1	*(unsigned char*)0x50C7
#define CLK_CSSR	*(unsigned char*)0x50C8
#define CLK_CCOR	*(unsigned char*)0x50C9
#define CLK_PCKENR2	*(unsigned char*)0x50CA
#define CLK_CANCCR  *(unsigned char*)0x50CB
#define CLK_HSITRIMR  *(unsigned char*)0x50CC
#define CLK_SWIMCCR *(unsigned char*)0x50CD


/* WINDOW WATCHDOG */
#define WWDG_CR *(unsigned char*)0x50D1
#define WWDG_WR *(unsigned char*)0x50D2


/* INDEPENDENT WATCHDOG */
#define IWDG_KR *(unsigned char*)0x50E0
#define IWDG_PR *(unsigned char*)0x50E1
#define IWDG_RLR *(unsigned char*)0x50E2

/* AUTO WAKEUP */
#define AWU_CSR *(unsigned char*)0x50F0
#define AWU_APR *(unsigned char*)0x50F1
#define AWU_TBR *(unsigned char*)0x50F2

/* BEEP */
#define BEEP_CSR *(unsigned char*)0x50F3

/* SPI */
#define SPI_CR1	*(unsigned char*)0x5200
#define SPI_CR2	*(unsigned char*)0x5201
#define SPI_ICR	*(unsigned char*)0x5202
#define SPI_SR	*(unsigned char*)0x5203
#define SPI_DR	*(unsigned char*)0x5204
#define SPI_CRCPR	*(unsigned char*)0x5205
#define SPI_RXCRCR	*(unsigned char*)0x5206
#define SPI_TXCRCR	*(unsigned char*)0x5207

/* I2C */
#define I2C_CR1	*(unsigned char*)0x5210
#define I2C_CR2	*(unsigned char*)0x5211
#define I2C_FREQR	*(unsigned char*)0x5212
#define I2C_OARL	*(unsigned char*)0x5213
#define I2C_OARH	*(unsigned char*)0x5214
#define I2C_DR	*(unsigned char*)0x5216
#define I2C_SR1	*(unsigned char*)0x5217
#define I2C_SR2	*(unsigned char*)0x5218
#define I2C_SR3	*(unsigned char*)0x5219
#define I2C_ITR	*(unsigned char*)0x521A
#define I2C_CCRL	*(unsigned char*)0x521B
#define I2C_CCRH	*(unsigned char*)0x521C
#define I2C_TRISER	*(unsigned char*)0x521D
#define I2C_PECR	*(unsigned char*)0x521E

/* USART */
#define USART1_SR *(unsigned char*)0x5230
#define USART1_DR *(unsigned char*)0x5231
#define USART1_BRR1 *(unsigned char*)0x5232
#define USART1_BRR2 *(unsigned char*)0x5233
#define USART1_CR1 *(unsigned char*)0x5234
#define USART1_CR2 *(unsigned char*)0x5235
#define USART1_CR3 *(unsigned char*)0x5236
#define USART1_CR4 *(unsigned char*)0x5237
#define USART1_CR5 *(unsigned char*)0x5238
#define USART1_GTR *(unsigned char*)0x5239
#define USART1_PSCR *(unsigned char*)0x523A

/* USART_CR1 bits */
#define USART_CR1_R8 (1 << 7)
#define USART_CR1_T8 (1 << 6)
#define USART_CR1_UARTD (1 << 5)
#define USART_CR1_M (1 << 4)
#define USART_CR1_WAKE (1 << 3)
#define USART_CR1_PCEN (1 << 2)
#define USART_CR1_PS (1 << 1)
#define USART_CR1_PIEN (1 << 0)

/* USART_CR2 bits */
#define USART_CR2_TIEN (1 << 7)
#define USART_CR2_TCIEN (1 << 6)
#define USART_CR2_RIEN (1 << 5)
#define USART_CR2_ILIEN (1 << 4)
#define USART_CR2_TEN (1 << 3)
#define USART_CR2_REN (1 << 2)
#define USART_CR2_RWU (1 << 1)
#define USART_CR2_SBK (1 << 0)

/* USART_CR3 bits */
#define USART_CR3_LINEN (1 << 6)
#define USART_CR3_STOP2 (1 << 5)
#define USART_CR3_STOP1 (1 << 4)
#define USART_CR3_CLKEN (1 << 3)
#define USART_CR3_CPOL (1 << 2)
#define USART_CR3_CPHA (1 << 1)
#define USART_CR3_LBCL (1 << 0)

/* USART_SR bits */
#define USART_SR_TXE (1 << 7)
#define USART_SR_TC (1 << 6)
#define USART_SR_RXNE (1 << 5)
#define USART_SR_IDLE (1 << 4)
#define USART_SR_OR (1 << 3)
#define USART_SR_NF (1 << 2)
#define USART_SR_FE (1 << 1)
#define USART_SR_PE (1 << 0)

/* TIMER1 */
#define TIM1_CR1 *(unsigned char*)0x5250
#define TIM1_CR2 *(unsigned char*)0x5251
#define TIM1_SMCR *(unsigned char*)0x5252
#define TIM1_ETR *(unsigned char*)0x5253
#define TIM1_IER *(unsigned char*)0x5254
#define TIM1_SR1 *(unsigned char*)0x5255
#define TIM1_SR2 *(unsigned char*)0x5256
#define TIM1_EGR *(unsigned char*)0x5257
#define TIM1_CCMR1 *(unsigned char*)0x5258
#define TIM1_CCMR2 *(unsigned char*)0x5259
#define TIM1_CCMR3 *(unsigned char*)0x525A
#define TIM1_CCMR4 *(unsigned char*)0x525B
#define TIM1_CCER1 *(unsigned char*)0x525C
#define TIM1_CCER2 *(unsigned char*)0x525D
#define TIM1_CNTR *(unsigned int*)0x525E
#define TIM1_CNTRH *(unsigned char*)0x525E
#define TIM1_CNTRL *(unsigned char*)0x525F
#define TIM1_PSCR *(unsigned int*)0x5260
#define TIM1_PSCRH *(unsigned char*)0x5260
#define TIM1_PSCRL *(unsigned char*)0x5261
#define TIM1_ARR *(unsigned int*)0x5262
#define TIM1_ARRH *(unsigned char*)0x5262
#define TIM1_ARRL *(unsigned char*)0x5263
#define TIM1_RCR *(unsigned char*)0x5264
#define TIM1_CCR1 *(unsigned int*)0x5265
#define TIM1_CCR1H *(unsigned char*)0x5265
#define TIM1_CCR1L *(unsigned char*)0x5266
#define TIM1_CCR2 *(unsigned int*)0x5267
#define TIM1_CCR2H *(unsigned char*)0x5267
#define TIM1_CCR2L *(unsigned char*)0x5268
#define TIM1_CCR3 *(unsigned int*)0x5269
#define TIM1_CCR3H *(unsigned char*)0x5269
#define TIM1_CCR3L *(unsigned char*)0x526A
#define TIM1_CCR4 *(unsigned int*)0x526B
#define TIM1_CCR4H *(unsigned char*)0x526B
#define TIM1_CCR4L *(unsigned char*)0x526C
#define TIM1_BKR *(unsigned char*)0x526D
#define TIM1_DTR *(unsigned char*)0x526E
#define TIM1_OISR *(unsigned char*)0x526F

/* TIMER2 */
#define TIM2_CR1 *(unsigned char*)0x5300
#define TIM2_IER *(unsigned char*)0x5303
#define TIM2_SR1 *(unsigned char*)0x5304
#define TIM2_SR2 *(unsigned char*)0x5305
#define TIM2_EGR *(unsigned char*)0x5306
#define TIM2_CCMR1 *(unsigned char*)0x5307
#define TIM2_CCMR2 *(unsigned char*)0x5308
#define TIM2_CCMR3 *(unsigned char*)0x5309
#define TIM2_CCER1 *(unsigned char*)0x530A
#define TIM2_CCER2 *(unsigned char*)0x530B
#define TIM2_CNTR  *(unsigned int*)0x530C
#define TIM2_CNTRH *(unsigned char*)0x530C
#define TIM2_CNTRL *(unsigned char*)0x530D
#define TIM2_PSCR *(unsigned char*)0x530E
#define TIM2_ARR *(unsigned int*)0x530F
#define TIM2_ARRH *(unsigned char*)0x530F
#define TIM2_ARRL *(unsigned char*)0x5310
#define TIM2_CCR1  *(unsigned int*)0x5311
#define TIM2_CCR1H *(unsigned char*)0x5311
#define TIM2_CCR1L *(unsigned char*)0x5312
#define TIM2_CCR2 *(unsigned int*)0x5313
#define TIM2_CCR2H *(unsigned char*)0x5313
#define TIM2_CCR2L *(unsigned char*)0x5314
#define TIM2_CCR3 *(unsigned int*)0x5315
#define TIM2_CCR3H *(unsigned char*)0x5315
#define TIM2_CCR3L *(unsigned char*)0x5316

/* TIM4 */
#define TIM4_CR1 *(unsigned char*)0x5340
#define TIM4_IER *(unsigned char*)0x5343
#define TIM4_SR *(unsigned char*)0x5344
#define TIM4_EGR *(unsigned char*)0x5345
#define TIM4_CNTR *(unsigned char*)0x5346
#define TIM4_PSCR *(unsigned char*)0x5347
#define TIM4_ARR *(unsigned char*)0x5348

/* TIM_IER bits */
#define TIM_IER_BIE (1 << 7)
#define TIM_IER_TIE (1 << 6)
#define TIM_IER_COMIE (1 << 5)
#define TIM_IER_CC4IE (1 << 4)
#define TIM_IER_CC3IE (1 << 3)
#define TIM_IER_CC2IE (1 << 2)
#define TIM_IER_CC1IE (1 << 1)
#define TIM_IER_UIE (1 << 0)

/* TIM_CR1 bits */
#define TIM_CR1_APRE (1 << 7)
#define TIM_CR1_CMSH (1 << 6)
#define TIM_CR1_CMSL (1 << 5)
#define TIM_CR1_DIR (1 << 4)
#define TIM_CR1_OPM (1 << 3)
#define TIM_CR1_URS (1 << 2)
#define TIM_CR1_UDIS (1 << 1)
#define TIM_CR1_CEN (1 << 0)

/* TIM_SR1 bits */
#define TIM_SR1_BIF (1 << 7)
#define TIM_SR1_TIF (1 << 6)
#define TIM_SR1_COMIF (1 << 5)
#define TIM_SR1_CC4IF (1 << 4)
#define TIM_SR1_CC3IF (1 << 3)
#define TIM_SR1_CC2IF (1 << 2)
#define TIM_SR1_CC1IF (1 << 1)
#define TIM_SR1_UIF (1 << 0)

/* ADC */
#define ADC_DB0R *(unsigned int*)0x53E0
#define ADC_DB0RH *(unsigned char*)0x53E0
#define ADC_DB0RL *(unsigned char*)0x53E1
#define ADC_DB1R *(unsigned int*)0x53E2
#define ADC_DB1RH *(unsigned char*)0x53E2
#define ADC_DB1RL *(unsigned char*)0x53E3
#define ADC_DB2R *(unsigned int*)0x53E4
#define ADC_DB2RH *(unsigned char*)0x53E4
#define ADC_DB2RL *(unsigned char*)0x53E5
#define ADC_DB3R *(unsigned int*)0x53E6
#define ADC_DB3RH *(unsigned char*)0x53E6
#define ADC_DB3RL *(unsigned char*)0x53E7
#define ADC_DB4R *(unsigned int*)0x53E8
#define ADC_DB4RH *(unsigned char*)0x53E8
#define ADC_DB4RL *(unsigned char*)0x53E9
#define ADC_DB5R *(unsigned int*)0x53EA
#define ADC_DB5RH *(unsigned char*)0x53EA
#define ADC_DB5RL *(unsigned char*)0x53EB
#define ADC_DB6R *(unsigned int*)0x53EC
#define ADC_DB6RH *(unsigned char*)0x53EC
#define ADC_DB6RL *(unsigned char*)0x53ED
#define ADC_DB7R *(unsigned int*)0x53EE
#define ADC_DB7RH *(unsigned char*)0x53EE
#define ADC_DB7RL *(unsigned char*)0x53EF
#define ADC_DB8R *(unsigned int*)0x53F0
#define ADC_DB8RH *(unsigned char*)0x53F0
#define ADC_DB8RL *(unsigned char*)0x53F1
#define ADC_DB9R *(unsigned int*)0x53F2
#define ADC_DB9RH *(unsigned char*)0x53F2
#define ADC_DB9RL *(unsigned char*)0x53F3
#define ADC_CSR *(unsigned char*)0x5400
#define ADC_CR1 *(unsigned char*)0x5401
#define ADC_CR2 *(unsigned char*)0x5402
#define ADC_CR3 *(unsigned char*)0x5403
#define ADC_DR *(unsigned int*)0x5404
#define ADC_DRH *(unsigned char*)0x5404
#define ADC_DRL *(unsigned char*)0x5405
#define ADC_TDR *(unsigned int*)0x5406
#define ADC_TDRH *(unsigned char*)0x5406
#define ADC_TDRL *(unsigned char*)0x5407
#define ADC_HTR *(unsigned int*)0x5408
#define ADC_HTRH *(unsigned char*)0x5408
#define ADC_HTRL *(unsigned char*)0x5409
#define ADC_LTR *(unsigned int*)0x540A
#define ADC_LTRH *(unsigned char*)0x540A
#define ADC_LTRL *(unsigned char*)0x540B
#define ADC_AWSR *(unsigned int*)0x540C
#define ADC_AWSRH *(unsigned char*)0x540C
#define ADC_AWSRL *(unsigned char*)0x540D
#define ADC_AWCR *(unsigned int*)0x540E
#define ADC_AWCRH *(unsigned char*)0x540E
#define ADC_AWCRL *(unsigned char*)0x540F

/* CFG */
#define CFG_GCR *(unsigned char*)0x7F60

/* ITC */
#define ITC_SPR1 *(unsigned char*)0x7F70
#define ITC_SPR2 *(unsigned char*)0x7F71
#define ITC_SPR3 *(unsigned char*)0x7F72
#define ITC_SPR4 *(unsigned char*)0x7F73
#define ITC_SPR5 *(unsigned char*)0x7F74
#define ITC_SPR6 *(unsigned char*)0x7F75
#define ITC_SPR7 *(unsigned char*)0x7F76

/* Interrupt commands */
#define enableInterrupts()    {__asm__("rim\n");}  /* enable interrupts */
#define disableInterrupts()   {__asm__("sim\n");}  /* disable interrupts */
#define rim()                 {__asm__("rim\n");}  /* enable interrupts */
#define sim()                 {__asm__("sim\n");}  /* disable interrupts */
#define nop()                 {__asm__("nop\n");}  /* No Operation */
#define trap()                {__asm__("trap\n");} /* Trap (soft IT) */
#define wfi()                 {__asm__("wfi\n");}  /* Wait For Interrupt */
#define halt()                {__asm__("halt\n");} /* Halt */

/* Interrupt numbers */
#define TIM1_OVR_UIF_IRQ 11
#define TIM2_OVR_UIF_IRQ 13
#define TIM3_OVR_UIF_IRQ 15
#define ADC1_EOC_IRQ 22
#define TIM4_OVR_UIF_IRQ 23
/*
Interrupts:

0 TLI
1 AWU Auto Wake up from Halt
2 CLK Clock controller
3 EXTI0 Port A external interrupts
4 EXTI1 Port B external interrupts
5 EXTI2 Port C external interrupts
6 EXTI3 Port D external interrupts
7 EXTI4 Port E external interrupts
8 CAN CAN RX interrupt
9 CAN CAN TX/ER/SC interrupt
10 SPI End of Transfer
11 TIM1 Update /Overflow/Underflow/Trigger/Break
12 TIM1 Capture/Compare
13 TIM2 Update /Overflow
14 TIM2 Capture/Compare
15 TIM3 Update /Overflow
16 TIM3 Capture/Compare
17 UART1 Tx complete
18 UART1 Receive Register DATA FULL
19 I2C I2C interrupt
20 UART2/3 Tx complete
21 UART2/3 Receive Register DATA FULL
22 ADC End of Conversion
23 TIM4 Update/Overflow
24 FLASH EOP/WR_PG_DIS

TLI 0
AWU 1
CLK 2
EXTI_PORTA 3
EXTI_PORTB 4
EXTI_PORTC
EXTI_PORTD
EXTI_PORTE
CAN_RX
CAN_TX
SPI
TIM1_UPD_OVF_TRG_BRK
TIM1_CAP_COM
TIM2_UPD_OVF_BRK
TIM2_CAP_COM
TIM3_UPD_OVF_BRK
TIM3_CAP_COM
UART1_TX
UART1_RX
I2C 19
ADC1 22
TIM4_UPD_OVF 23
EEPROM_EEC 24
*/

#endif     /* STM8S103F_H */
