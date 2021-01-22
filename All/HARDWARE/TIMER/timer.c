#include "timer.h"
#include "car.h"
#include "led.h"
#include "arm.h"

/* TIM1 PWM ��ʼ�� */
//arr:�Զ���װ��ֵ	ARR�Ĵ�������������
//psc:ʱ��Ԥ��Ƶ��	
//PWM���:PA8		TIM1_CH1		Servo5
//				PA11	TIM1_CH4		Servo6
void TIM1_PWM_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	TIM_TimeBaseInitStructure.TIM_Period = arr;												//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;										//Ԥ��Ƶ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;				//����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		//���ϼ���
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;										//PWM1ģʽ
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;						//��Ч��ƽΪ��
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);														//TIM1���ͨ��1��ʼ��
	TIM_OC4Init(TIM1,&TIM_OCInitStructure);														//TIM1���ͨ��4��ʼ��

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);									//ʹ��TIM1��OC1��Ԥװ�ؼĴ���
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);									//ʹ��TIM1��OC4��Ԥװ�ؼĴ���
	TIM_Cmd(TIM1,ENABLE);

	TIM_CtrlPWMOutputs(TIM1, ENABLE);					//�߼���ʱ�����һ������
}

/* TIM2 PWM ��ʼ�� */
//arr:�Զ���װ��ֵ	ARR�Ĵ�������������
//psc:ʱ��Ԥ��Ƶ��	
//PWM���:PA0		TIM2_CH1		Servo1
//			  PA1		TIM2_CH2		Servo2
//				PA2		TIM2_CH3		Servo3
//				PA3		TIM2_CH4		Servo4
void TIM2_PWM_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;										//�����������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;				
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;				//����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;		//���ϼ���
	TIM_TimeBaseInitStructure.TIM_Period=arr;												//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;										//Ԥ��Ƶ��
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;									//PWM1ģʽ
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;					//��Ч��ƽΪ��
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);												//TIM3���ͨ��1��ʼ��
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);												//TIM3���ͨ��2��ʼ��
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);												//TIM3���ͨ��3��ʼ��
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);												//TIM3���ͨ��4��ʼ��
	
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);								//ʹ��TIM3��OC1��Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);								//ʹ��TIM3��OC2��Ԥװ�ؼĴ���
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);								//ʹ��TIM3��OC3��Ԥװ�ؼĴ���
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);								//ʹ��TIM3��OC4��Ԥװ�ؼĴ���
	TIM_Cmd(TIM2, ENABLE);
}

/* TIM3 PWM ��ʼ�� */
//arr:�Զ���װ��ֵ	ARR�Ĵ�������������
//psc:ʱ��Ԥ��Ƶ��	
//PWM���:PA6		TIM3_CH1		Motor1
//			  PA7		TIM3_CH2		Motor2
//				PB0		TIM3_CH3		Motor3
//				PB1		TIM3_CH4		Motor4
void TIM3_PWM_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;										//�����������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6 | GPIO_Pin_7;						//PA6|PA7
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;										//�����������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1;						//PB0|PB1
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;				//����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;		//���ϼ���
	TIM_TimeBaseInitStructure.TIM_Period=arr;												//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;										//Ԥ��Ƶ��
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;									//PWM1ģʽ
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;					//��Ч��ƽΪ��
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);												//TIM3���ͨ��1��ʼ��
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);												//TIM3���ͨ��2��ʼ��
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);												//TIM3���ͨ��3��ʼ��
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);												//TIM3���ͨ��4��ʼ��
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);								//ʹ��TIM3��OC1��Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);								//ʹ��TIM3��OC2��Ԥװ�ؼĴ���
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);								//ʹ��TIM3��OC3��Ԥװ�ؼĴ���
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);								//ʹ��TIM3��OC4��Ԥװ�ؼĴ���
	TIM_Cmd(TIM3, ENABLE);
}


/* ͨ�ö�ʱ��5�жϳ�ʼ������ɨ�� */
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
void TIM5_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;	//����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;		//���ϼ���
	TIM_TimeBaseInitStructure.TIM_Period=arr;		//��װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;	//Ԥ��Ƶֵ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	
	//TIM5 2:3
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM5, ENABLE);
}

/* ��ʱ��5�жϷ����� */
void TIM5_IRQHandler(void)
{
	static u8 initflag = 50;		//��ʼ��1000ms��֤�����λ
	
	if(TIM_GetITStatus(TIM5, TIM_IT_Update) == SET)	//TIM2�����ж��ѷ���
	{
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
		
		//��ʼ�����
		if(initflag)
		{
			Servo_InitMove();
			if(initflag==1)			//����ɨ��
			{
				Servo1.status = 1;
				Servo2.status = 1;
				Servo3.status = 1;
				Servo4.status = 1;
				Servo5.status = 1;
				Servo6.status = 1;
			}
			initflag--;
		}
		
		Servo_Scan();		//ɨ�裬���ƻ�е���˶�	
		Car_Scan();			//ɨ�裬����С���˶�
	}
}


/* ͨ�ö�ʱ��6�жϳ�ʼ����������ɨ��͵������ */
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
void TIM6_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;	//����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;		//���ϼ���
	TIM_TimeBaseInitStructure.TIM_Period=arr;		//��װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;	//Ԥ��Ƶֵ
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
	
	//TIM6 2:2
	NVIC_InitStructure.NVIC_IRQChannel=TIM6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM6, ENABLE);
}

/* ��ʱ��6�жϷ����� */
void TIM6_IRQHandler(void)
{
	static u16 i = 8000;		//1000msLED��תһ��
	
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) == SET)	//TIM2�����ж��ѷ���
	{
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
		
		if(i==0)
		{
			LED1_Toggle();
			i = 8000;
		}
		else
			i--;

		Car_Correct();
		Car_Scan2();			//ɨ�裬����С���˶�
	}
}









