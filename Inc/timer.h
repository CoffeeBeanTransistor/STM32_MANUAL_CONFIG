#ifndef __TIMER_H__
#define __TIMER_H__
#include <stdio.h>
#include "Common.h"

typedef enum {
	TIMER_STATE_RESET = 0,
	TIMER_STATE_READY,
	TIMER_STATE_BUSY,
	TIMER_STATE_TIMEOUT,
	TIMER_STATE_ERROR,
}TIMERState;

typedef enum {
	UNLOCKED = 0,
	LOCKED,
} LockType;

typedef enum {
	STATUS_OK = 0,
	STATUS_ERROR,
	STATUS_BUSY,
	STATUS_TIMEOUT,
} Status;

typedef struct TimerRegs TimerRegs;
struct TimerRegs {
	IoRegister CR1;					//0x00
	IoRegister CR2;					//0x04
	IoRegister SMCR;		    	//0x08
	IoRegister DIER;				//0x0C
	IoRegister SR;					//0x10
	IoRegister EGR;					//0x14
	IoRegister CCMR1;				//0x18
	IoRegister CCMR2;				//0x1C
	IoRegister CCER;				//0x20
	IoRegister CNT;					//0x24
	IoRegister PSC;					//0x28
	IoRegister ARR;					//0x2C
	IoRegister Reserved0;			//0x30
	IoRegister CCR1;				//0x34
	IoRegister CCR2;				//0x38
	IoRegister CCR3;				//0x3C
	IoRegister CCR4;				//0x40
	IoRegister Reserved1;			//0x44
	IoRegister DCR;					//0x48
	IoRegister DMAR;				//0x4C
	IoRegister OR;					//0x50
};

typedef struct {
	uint32_t PSC;
	uint32_t CNTMode;
	uint32_t period;
	uint32_t clockDivision;
	uint32_t repetitionCNT;
} TIMERBaseInitType;

typedef struct {
	TimerRegs 			*instance;
	TIMERState			 state;
	TIMERBaseInitType 	 init;
	LockType			 lock;
}TIMERHandleType;

TIMERHandleType	timer2;
TIMERHandleType	timer3;
TIMERHandleType	timer4;
TIMERHandleType	timer5;
TIMERHandleType	timer6;
TIMERHandleType	timer7;
TIMERHandleType	timer12;
TIMERHandleType	timer13;
TIMERHandleType	timer14;

//Timers Pointers
#define tim2  				((TimerRegs *)0x40000000)
#define tim3 				((TimerRegs *)0x40000400)
#define tim4 	 			((TimerRegs *)0x40000800)
#define tim5 	 			((TimerRegs *)0x40000C00)
#define tim6  				((TimerRegs *)0x40001000)
#define tim7  				((TimerRegs *)0x40001400)
#define tim12  				((TimerRegs *)0x40001800)
#define tim13  				((TimerRegs *)0x40001C00)
#define tim14 	 			((TimerRegs *)0x40002000)

#define tim_channel_1 		0x00000000
#define tim_channel_2 		0x00000004
#define tim_channel_3 		0x00000008
#define tim_channel_4 		0x0000000C
#define tim_channel_all 	0x00000018

#define tim_CCx_ENABLE     	1
#define tim_CCx_DISABLE   	0
#define tim_CCxN_ENABLE    	4
#define tim_CCxN_DISABLE  	0

//SR
#define TIM_UIF				 1
#define TIM_CC1IF			(1 << 1)
#define TIM_CC2IF			(1 << 2)
#define TIM_CC3IF			(1 << 3)
#define TIM_CC4IF			(1 << 4)
#define TIM_TIF				(1 << 6)
#define TIM_CC1OF			(1 << 9)
#define TIM_CC2OF			(1 << 10)
#define TIM_CC3OF			(1 << 11)
#define TIM_CC4OF			(1 << 12)

//CCMR
#define OC_FROZEN				0	//000
#define OC_ACTIVE_ON_MATCH  	1	//001
#define OC_INACTIVE_ON_MATCH 	2	//010
#define OC_TOGGLE				3	//011
#define OC_FORCE_INACTIVE  		4	//100
#define OC_FORCE_ACTIVE 		5	//101
#define OC_PWM1  				6	//110
#define OC_PWM2 				7	//111
#define OC_PRELOAD_ENABLE		1
#define OC_FAST_ENABLE			1

#define CC_SELECT_OC			0
#define CC_SELECT_IC_DIRECT		1
#define CC_SELECT_IC_INDIRECT	2
#define CC_SELECT_IC_TRC		3

//CCER
#define OC_NORMAL_POLARITY		0
#define OC_INVERSE_POLARITY		1

//EGR
#define TIM_UG					1

//CR1
#define TIM_CEN 		  		1

//DIER
#define dmaInterruptEnable  	1

//Timer Macros
#define TIM_CAPTURE_COMPARE_ENABLE(tim, ch)		(tim)->CCER |= 1 << (((ch) - 1) * 4)
#define TIM_CAPTURE_COMPARE_DISABLE(tim, ch)	(tim)->CCER &= ~(1 << (((ch) - 1) * 4))
#define TIM_SET_CNT(tim, value)				(tim)->CNT = (value)
#define TIM_SET_OC_VALUE(tim, ch, value)		*(&((tim)->CCR1) + ch - 1) = (value)
#define TIM_SET_OC_POLARITY(tim, ch, polarity)								\
			do {															\
			(tim)->CCER &= ~(2 << ((ch) - 1) * 4);				\
			(tim)->CCER |= polarity << ((((ch) - 1) * 4) + 1);	\
			} while(0)


/*Clear Status Register of Timer, which FLAG should be one of the following :
	TIM_UIF		Update Interrupt Flag
	TIM_CC1IF	Capture/Compare 1 Interrupt Flag
	TIM_CC2IF	Capture/Compare 2 Interrupt Flag
	TIM_CC3IF	Capture/Compare 3 Interrupt Flag
	TIM_CC4IF	Capture/Compare 4 Interrupt Flag
	TIM_TIF		Trigger Interrupt Flag
	TIM_CC1OF	Capture/Compare 1 Overcapture Flag
	TIM_CC2OF	Capture/Compare 2 Overcapture Flag
	TIM_CC3OF	Capture/Compare 3 Overcapture Flag
	TIM_CC4OF	Capture/Compare 4 Overcapture Flag */
#define TIM_CLEAR_FLAG(tim, flag)			(tim)->SR = ~(flag)
#define TIM_GET_FLAG(tim, flag)				(tim)->SR & (flag)
#define TIM_COUNTER_ENABLE(tim)				(tim)->CR1 |= TIM_CEN
#define TIM_COUNTER_DISABLE(tim)			(tim)->CR1 &= ~TIM_CEN
#define TIM_UPDATE_GENERATION(tim)			(tim)->EGR |= TIM_UG

Status startTimerBaseIT(TIMERHandleType *timer);
void setCCxChannel(TimerRegs *timer, uint32_t channel, uint32_t channelState);
Status startTimerOC(TIMERHandleType *timer, uint32_t channel);
void startTimerBase(TIMERHandleType *timer);
Status initTimerBase(TIMERHandleType *timer);
void timerOcSetMode(TimerRegs *timer, uint32_t channel, uint32_t mode);
void timerInitOutputCompare(TimerRegs *timer, uint32_t channel,  uint32_t mode, uint32_t outPolarity, uint32_t compareValue);

#endif //__TIMER_H__
