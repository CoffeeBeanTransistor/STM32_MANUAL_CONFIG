#include "timer.h"
#include <stdio.h>


void startTimerBase(TIMERHandleType *timer) {
		timer->state = TIMER_STATE_BUSY;
		timer->instance->CR1 |= TIM_CEN;
		timer->state = TIMER_STATE_READY;
	}

Status startTimerBaseIT(TIMERHandleType *timer) {
		timer->instance->DIER |= dmaInterruptEnable;
		timer->instance->CR1 |= TIM_CEN;
		return STATUS_OK;
	}

void setCCxChannel(TimerRegs *timer, uint32_t channel, uint32_t channelState) {
		uint32_t mask = 0;

		mask = 1 << channel;

		timer->CCER = ~mask;
		timer->CCER |= (uint32_t)(channelState << channel);
	}

Status startTimerOC(TIMERHandleType *timer, uint32_t channel) {
		setCCxChannel(timer->instance, channel, tim_CCx_ENABLE);
		timer->instance->CR1 |= TIM_CEN;
		return STATUS_OK;
	}

/*Status initTimerBase(TIMERHandleType *timer) {
	if(timer == NULL)
		return STATUS_ERROR;

	if(timer->state == TIMER_STATE_RESET) {
		timer->lock = UNLOCKED;
		HAL_TIM_Base_MspInit(timer);
	 }

	 timer->state = TIMER_STATE_BUSY;
	 TIM_Base_SetConfig(timer->instance, &timer->init);
	 timer->state = TIMER_STATE_READY;

	 return STATUS_OK;
}*/

void timerInitOutputCompare(TimerRegs *timer, uint32_t channel,  uint32_t mode, uint32_t outPolarity, uint32_t compareValue) {
	timerOcSetMode(timer, channel, mode);
	TIM_SET_OC_VALUE(timer, channel, compareValue);
	TIM_SET_OC_POLARITY(timer, channel, outPolarity);
}

void timerOcSetMode(TimerRegs *timer, uint32_t channel, uint32_t mode) {
	uint32_t numOfShifts = 0;
	IoRegister *ccmr = &timer->CCMR1;

	if(((channel - 1) & 1) == 1)
		numOfShifts = 8;

	if(channel > 2)
		ccmr++;

	*ccmr = mode << (numOfShifts + 4);
}

	/*void setConfigTimerBase(TimerRegs *timer, TIMERBaseInitType *configuration)
	{

	  timer2->instance = tim2;
	  timer2->init->prescaler = 0;
	  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	  htim2.Init.Period = 0;
	  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	}*/

