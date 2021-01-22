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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//�����ж����ȼ�
	usmart_dev.init(72);
	uart_init(115200);
	delay_init();
		
	TIM1_PWM_Init(19999, 71);		//���  ����Ϊ20ms	ע��1ms-90��-1000��	 arr-20000	 ccr-500~2500
	TIM2_PWM_Init(19999, 71);		//���
	TIM3_PWM_Init(500,17);		  //���  Ƶ����8Kh
	TIM5_Int_Init(1999,719);		//�ж�  ��ʱ20ms
	TIM6_Int_Init(500,17);	    //�������
	
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

