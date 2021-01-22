#include "key.h"
#include "delay.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
//	//WK_UP
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//KEY1
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY3按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY_UP!!
u8 KEY_Scan(u8 mode)
{
	static u8 key_up=1;
	
	if(mode)key_up=1;
	if(key_up&&(KEY0==0||KEY1==0))		//按键按下
	{
		delay_ms(10);		//消抖
		key_up = 0;
		//判断哪个按键按下
		if(KEY0==0)return KEY0_PRES;		//KEY0 优先级最高
		else if(KEY1==0)return KEY1_PRES;
	}else if(KEY0==1&&KEY1==1)key_up=1;		//都弹起
	return 0;		//无按键按下
}


