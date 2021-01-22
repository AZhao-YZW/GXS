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
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY3���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY_UP!!
u8 KEY_Scan(u8 mode)
{
	static u8 key_up=1;
	
	if(mode)key_up=1;
	if(key_up&&(KEY0==0||KEY1==0))		//��������
	{
		delay_ms(10);		//����
		key_up = 0;
		//�ж��ĸ���������
		if(KEY0==0)return KEY0_PRES;		//KEY0 ���ȼ����
		else if(KEY1==0)return KEY1_PRES;
	}else if(KEY0==1&&KEY1==1)key_up=1;		//������
	return 0;		//�ް�������
}


