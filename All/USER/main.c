#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "led.h"
#include "usmart.h"
#include "car.h"
#include "key.h"
#include "armdebug.h"

u16 pwm=2000;

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//配置中断优先级
	usmart_dev.init(72);
	uart_init(115200);
	delay_init();
		
	TIM1_PWM_Init(19999, 71);		//舵机  周期为20ms	注：1ms-90度-1000份	 arr-20000	 ccr-500~2500
	TIM2_PWM_Init(19999, 71);		//舵机
	TIM3_PWM_Init(500,17);		  //电机  频率是8Kh
	TIM5_Int_Init(1999,719);		//中断  定时20ms
	TIM6_Int_Init(500,17);	    //电机计数
	
	LED_Init();
	KEY_Init();
	Car_Init();

	MyCar.action = 0;
	while(1)
	{
		
		switch(KEY_Scan(0))
		{
			case KEY0_PRES:
				pwm+=100;
				Servo_UsmartMoveConfig(6,1,pwm);
				break;
			
			case KEY1_PRES:
				pwm-=100;
				Servo_UsmartMoveConfig(6,1,pwm);
				break;			
		}
	}
}

