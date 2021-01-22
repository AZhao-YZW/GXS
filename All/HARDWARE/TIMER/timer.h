/**************************************************************************
													定时器分配
				TIM2	为舵机扫描提供中断
				TIM6	为按键扫描提供中断
				TIM3	4个PWM输出驱动舵机	PA6 PA7 PB0 PB1
				TIM1	1个PWM输出驱动舵机	PA8
***************************************************************************/
#ifndef _TIMER_H
#define _TIMER_H

#include "sys.h"

void TIM1_PWM_Init(u16 arr, u16 psc);
void TIM2_PWM_Init(u16 arr, u16 psc);
void TIM3_PWM_Init(u16 arr, u16 psc);
void TIM5_Int_Init(u16 per,u16 psc);
void TIM6_Int_Init(u16 arr, u16 psc);

#endif

