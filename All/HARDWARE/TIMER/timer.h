/**************************************************************************
													��ʱ������
				TIM2	Ϊ���ɨ���ṩ�ж�
				TIM6	Ϊ����ɨ���ṩ�ж�
				TIM3	4��PWM����������	PA6 PA7 PB0 PB1
				TIM1	1��PWM����������	PA8
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

