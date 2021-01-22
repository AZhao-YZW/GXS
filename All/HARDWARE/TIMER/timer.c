#include "timer.h"
#include "car.h"
#include "led.h"
#include "arm.h"

/* TIM1 PWM 初始化 */
//arr:自动重装载值	ARR寄存器，控制周期
//psc:时钟预分频数	
//PWM输出:PA8		TIM1_CH1		Servo5
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

	TIM_TimeBaseInitStructure.TIM_Period = arr;												//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;										//预分频数
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;				//不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		//向上计数
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;										//PWM1模式
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;						//有效电平为高
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);														//TIM1输出通道1初始化
	TIM_OC4Init(TIM1,&TIM_OCInitStructure);														//TIM1输出通道4初始化

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);									//使能TIM1和OC1的预装载寄存器
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);									//使能TIM1和OC4的预装载寄存器
	TIM_Cmd(TIM1,ENABLE);

	TIM_CtrlPWMOutputs(TIM1, ENABLE);					//高级定时器多的一个配置
}

/* TIM2 PWM 初始化 */
//arr:自动重装载值	ARR寄存器，控制周期
//psc:时钟预分频数	
//PWM输出:PA0		TIM2_CH1		Servo1
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
		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;										//复用推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;				
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;				//不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;		//向上计数
	TIM_TimeBaseInitStructure.TIM_Period=arr;												//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;										//预分频数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;									//PWM1模式
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;					//有效电平为高
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);												//TIM3输出通道1初始化
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);												//TIM3输出通道2初始化
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);												//TIM3输出通道3初始化
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);												//TIM3输出通道4初始化
	
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);								//使能TIM3和OC1的预装载寄存器
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);								//使能TIM3和OC2的预装载寄存器
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);								//使能TIM3和OC3的预装载寄存器
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);								//使能TIM3和OC4的预装载寄存器
	TIM_Cmd(TIM2, ENABLE);
}

/* TIM3 PWM 初始化 */
//arr:自动重装载值	ARR寄存器，控制周期
//psc:时钟预分频数	
//PWM输出:PA6		TIM3_CH1		Motor1
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
		
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;										//复用推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6 | GPIO_Pin_7;						//PA6|PA7
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;										//复用推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1;						//PB0|PB1
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;				//不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;		//向上计数
	TIM_TimeBaseInitStructure.TIM_Period=arr;												//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;										//预分频数
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;									//PWM1模式
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;					//有效电平为高
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);												//TIM3输出通道1初始化
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);												//TIM3输出通道2初始化
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);												//TIM3输出通道3初始化
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);												//TIM3输出通道4初始化
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);								//使能TIM3和OC1的预装载寄存器
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);								//使能TIM3和OC2的预装载寄存器
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);								//使能TIM3和OC3的预装载寄存器
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);								//使能TIM3和OC4的预装载寄存器
	TIM_Cmd(TIM3, ENABLE);
}


/* 通用定时器5中断初始化，做扫描 */
//arr：自动重装值。
//psc：时钟预分频数
void TIM5_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;	//不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;		//向上计数
	TIM_TimeBaseInitStructure.TIM_Period=arr;		//重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;	//预分频值
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

/* 定时器5中断服务函数 */
void TIM5_IRQHandler(void)
{
	static u8 initflag = 50;		//初始化1000ms保证舵机归位
	
	if(TIM_GetITStatus(TIM5, TIM_IT_Update) == SET)	//TIM2更新中断已发生
	{
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
		
		//初始化舵机
		if(initflag)
		{
			Servo_InitMove();
			if(initflag==1)			//开启扫描
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
		
		Servo_Scan();		//扫描，控制机械臂运动	
		Car_Scan();			//扫描，控制小车运动
	}
}


/* 通用定时器6中断初始化，做按键扫描和电机计数 */
//arr：自动重装值。
//psc：时钟预分频数
void TIM6_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;	//不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;		//向上计数
	TIM_TimeBaseInitStructure.TIM_Period=arr;		//重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;	//预分频值
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

/* 定时器6中断服务函数 */
void TIM6_IRQHandler(void)
{
	static u16 i = 8000;		//1000msLED反转一次
	
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) == SET)	//TIM2更新中断已发生
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
		Car_Scan2();			//扫描，控制小车运动
	}
}









