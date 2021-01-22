#include "armdebug.h"
#include "servo.h"
#include "usart.h"			//���ڴ�ӡ��ʾ����
#include "stdarg.h"		//ʵ�ֿɱ��������
#include "stdio.h"
#include "string.h"

/* ���õ���ĳ�������ת����΢���� */
//tranPwm�����Զ���ٶȣ���ÿ20ms�ı��pwmֵ
void Servo_DebugConfig(sServo *Servox, int tranPwm)
{
		Servox->status = 1;
		Servox->tranPwm = tranPwm;
		Servox->nextPwmWidth += Servox->tranPwm;
		Servox->tranTimes = 1;		//PWMֵ�ı�1��
		Servox->tranPeriod = 20;	//�ı�ʱ��Ϊ20ms
}

/* ���õ��Ի�е���˶�״̬ */
//depwmWidth1~5: ���ö���Ƕ�
void Arm_DebugConfig(u16 depwmWidth1, u16 depwmWidth2, u16 depwmWidth3, u16 depwmWidth4, u16 depwmWidth5, u16 depwmWidth6)
{
	Servo_MoveConfig(&Servo1, 1000, depwmWidth1);
	Servo_MoveConfig(&Servo2, 1000, depwmWidth2);
	Servo_MoveConfig(&Servo3, 1000, depwmWidth3);
	Servo_MoveConfig(&Servo4, 1000, depwmWidth4);
	Servo_MoveConfig(&Servo5, 1000, depwmWidth5);
	Servo_MoveConfig(&Servo6, 1000, depwmWidth6);
}

/* ���õ��Ի�е���˶�״̬ */
//deperiod1~5: ���ö���Ƕ�
//depwmWidth1~5: ���ö���Ƕ�
void Arm_DebugConfig2(u16 deperiod1, 	 u16 deperiod2, 	u16 deperiod3, 	 u16 deperiod4, 	u16 deperiod5, 	 u16 deperiod6, 
											u16 depwmWidth1, u16 depwmWidth2, u16 depwmWidth3, u16 depwmWidth4, u16 depwmWidth5, u16 depwmWidth6)
{
	Servo_MoveConfig(&Servo1, deperiod1, depwmWidth1);
	Servo_MoveConfig(&Servo2, deperiod2, depwmWidth2);
	Servo_MoveConfig(&Servo3, deperiod3, depwmWidth3);
	Servo_MoveConfig(&Servo4, deperiod4, depwmWidth4);
	Servo_MoveConfig(&Servo5, deperiod5, depwmWidth5);
	Servo_MoveConfig(&Servo6, deperiod6, depwmWidth6);
}

/* USMART���õ��Ե������ */
//num: ������
//tranPwm�����Զ���ٶȣ���ÿ20ms�ı��pwmֵ
void Servo_UsmartDebugConfig(u8 num, int tranPwm)
{
	switch(num)
	{
		case 1: Servo_DebugConfig(&Servo1, tranPwm); break;
		case 2: Servo_DebugConfig(&Servo2, tranPwm); break;
		case 3: Servo_DebugConfig(&Servo3, tranPwm); break;
		case 4: Servo_DebugConfig(&Servo4, tranPwm); break;
		case 5: Servo_DebugConfig(&Servo5, tranPwm); break;
		case 6: Servo_DebugConfig(&Servo6, tranPwm); break;
	}
}

/* USMART����ĳ�������ת�� */
//num: ������
//period:ת��ʱ��,ms
//pwmWidth:����ת��λ�ã�500~2500(us)
void Servo_UsmartMoveConfig(u8 num, u16 period, u16 pwmWidth)
{
	switch(num)
	{
		case 1: Servo_MoveConfig(&Servo1, period, pwmWidth); break;
		case 2: Servo_MoveConfig(&Servo2, period, pwmWidth); break;
		case 3: Servo_MoveConfig(&Servo3, period, pwmWidth); break;
		case 4: Servo_MoveConfig(&Servo4, period, pwmWidth); break;
		case 5: Servo_MoveConfig(&Servo5, period, pwmWidth); break;
		case 6: Servo_MoveConfig(&Servo6, period, pwmWidth); break;
	}
}

/* ��ӡ��ʾĳ�������ǰ״̬ */
//configName��������"brief": ������Ϣ��"whole": ��ϸ��Ϣ
void Servo_PrintStatus(sServo *Servox, const char *configName)
{
	if(strcmp(configName, "brief")==0)
	{
		printf("Servo%d: curPwmWidth: %d, nextPwmWidth: %d, tranPeriod: %d", \
					 Servox->num, Servox->curPwmWidth, Servox->nextPwmWidth, Servox->tranPeriod);
	}
	else if(strcmp(configName, "whole")==0)
	{
		printf("Servo%d: status: %d, curPwmWidth: %d, nextPwmWidth: %d, tranPwm: %d, tranPeriod: %d, tranTimes: %d", \
					 Servox->num, Servox->status, Servox->curPwmWidth+Servox->tranPwm, Servox->nextPwmWidth, Servox->tranPwm, Servox->tranPeriod, Servox->tranTimes);
	}	
}

/* USMART��ӡ��ʾĳ�������ǰ״̬ */
//num: ������
//configName��������"brief": ������Ϣ��"whole": ��ϸ��Ϣ
void Servo_UsmartPrintStatus(u8 num, const char *configName)
{
	switch(num)
	{
		case 1: Servo_PrintStatus(&Servo1, configName); break;
		case 2: Servo_PrintStatus(&Servo2, configName); break;
		case 3: Servo_PrintStatus(&Servo3, configName); break;
		case 4: Servo_PrintStatus(&Servo4, configName); break;
		case 5: Servo_PrintStatus(&Servo5, configName); break;
		case 6: Servo_PrintStatus(&Servo6, configName); break;
	}
}

/* USMART��ӡ��ʾ���ж����ǰ״̬ */
//configName��������"brief": ������Ϣ��"whole": ��ϸ��Ϣ
void Arm_UsmartPrintStatus(const char *configName)
{
	Servo_PrintStatus(&Servo1, configName);
	Servo_PrintStatus(&Servo2, configName);
	Servo_PrintStatus(&Servo3, configName);
	Servo_PrintStatus(&Servo4, configName);
	Servo_PrintStatus(&Servo5, configName);
	Servo_PrintStatus(&Servo6, configName);
	printf("\r\n");
}




