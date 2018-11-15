#ifndef __RCC_H__
#define __RCC_H__
#include <stdio.h>
#include "Common.h"

typedef struct RccRegs RccRegs;
struct RccRegs {
	IoRegister CR;						//0x00
	IoRegister PLLCFGR;					//0x04
	IoRegister CFGR;				    //0x08
	IoRegister CIR;						//0x0C
	IoRegister AHB1RSTR;				//0x10
	IoRegister AHB2RSTR;				//0x14
	IoRegister AHB3RSTR;				//0x18
	IoRegister Reserved0;				//0x1C
	IoRegister APB1RSTR;				//0x20
	IoRegister APB2RSTR;				//0x24
	IoRegister Reserved1[2];			//0x28
	IoRegister AHB1ENR;					//0x30
	IoRegister AHB2ENR;					//0x34
	IoRegister AHB3ENR;					//0x38
	IoRegister Reserved2;				//0x3C
	IoRegister APB1ENR;					//0x40
	IoRegister APB2ENR;					//0x44
	IoRegister Reserved3[2];			//0x48
	IoRegister AHB1ELPENR;				//0x50
	IoRegister AHB2ELPENR;				//0x54
	IoRegister AHB3ELPENR;				//0x58
	IoRegister Reserved4;				//0x5C
	IoRegister APB1ELPENR;				//0x60
	IoRegister APB2ELPENR;				//0x64
	IoRegister Reserved5[2];			//0x68
	IoRegister BDCR;					//0x70
	IoRegister CSR;						//0x74
	IoRegister Reserved6[2];			//0x78
	IoRegister SSCGR;					//0x80
	IoRegister PLL12SCFGR;				//0x84
};

//RCC Pointers
#define rcc										((RccRegs *)0x40023800)

#define ENABLE_TIMER_2_CLK_GATING()				rcc->APB1ENR |= (1 << 0)
#define ENABLE_TIMER_3_CLK_GATING()				rcc->APB1ENR |= (1 << 1)
#define ENABLE_TIMER_4_CLK_GATING()				rcc->APB1ENR |= (1 << 2)
#define ENABLE_TIMER_5_CLK_GATING()				rcc->APB1ENR |= (1 << 3)
#define ENABLE_TIMER_6_CLK_GATING()				rcc->APB1ENR |= (1 << 4)
#define ENABLE_TIMER_7_CLK_GATING()				rcc->APB1ENR |= (1 << 5)
#define ENABLE_TIMER_12_CLK_GATING()			rcc->APB1ENR |= (1 << 6)
#define ENABLE_TIMER_13_CLK_GATING()			rcc->APB1ENR |= (1 << 7)
#define ENABLE_TIMER_14_CLK_GATING()			rcc->APB1ENR |= (1 << 8)

#define DISABLE_TIMER_2_CLK_GATING()			rcc->APB1ENR &= ~(1 << 0)
#define DISABLE_TIMER_3_CLK_GATING()			rcc->APB1ENR &= ~(1 << 1)
#define DISABLE_TIMER_4_CLK_GATING()			rcc->APB1ENR &= ~(1 << 2)
#define DISABLE_TIMER_5_CLK_GATING()			rcc->APB1ENR &= ~(1 << 3)
#define DISABLE_TIMER_6_CLK_GATING()			rcc->APB1ENR &= ~(1 << 4)
#define DISABLE_TIMER_7_CLK_GATING()			rcc->APB1ENR &= ~(1 << 5)
#define DISABLE_TIMER_12_CLK_GATING()			rcc->APB1ENR &= ~(1 << 6)
#define DISABLE_TIMER_13_CLK_GATING()			rcc->APB1ENR &= ~(1 << 7)
#define DISABLE_TIMER_14_CLK_GATING()			rcc->APB1ENR &= ~(1 << 8)

#define UNRESET_TIMER_2()						rcc->APB1RSTR &= ~(1 << 0)
#define UNRESET_TIMER_3()						rcc->APB1RSTR &= ~(1 << 1)
#define UNRESET_TIMER_4()						rcc->APB1RSTR &= ~(1 << 2)
#define UNRESET_TIMER_5()						rcc->APB1RSTR &= ~(1 << 3)
#define UNRESET_TIMER_6()						rcc->APB1RSTR &= ~(1 << 4)
#define UNRESET_TIMER_7()						rcc->APB1RSTR &= ~(1 << 5)
#define UNRESET_TIMER_12()						rcc->APB1RSTR &= ~(1 << 6)
#define UNRESET_TIMER_13()						rcc->APB1RSTR &= ~(1 << 7)
#define UNRESET_TIMER_14()						rcc->APB1RSTR &= ~(1 << 8)

#define RESET_TIMER_2()							rcc->APB1RSTR |= (1 << 0)
#define RESET_TIMER_3()							rcc->APB1RSTR |= (1 << 1)
#define RESET_TIMER_4()							rcc->APB1RSTR |= (1 << 2)
#define RESET_TIMER_5()							rcc->APB1RSTR |= (1 << 3)
#define RESET_TIMER_6()							rcc->APB1RSTR |= (1 << 4)
#define RESET_TIMER_7()							rcc->APB1RSTR |= (1 << 5)
#define RESET_TIMER_12()						rcc->APB1RSTR |= (1 << 6)
#define RESET_TIMER_13()						rcc->APB1RSTR |= (1 << 7)
#define RESET_TIMER_14()						rcc->APB1RSTR |= (1 << 8)

#endif //__RCC_H__
