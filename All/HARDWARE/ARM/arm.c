#include "arm.h"
#include "led.h"
#include "servo.h"
#include "armdebug.h"
#include "delay.h"

u8 action = 0;		//������ʶ

/* ���ж���ɨ�裬�ı����˶�״̬ */
//��Servox��statusΪ1ʱɨ�����Ч
void Servo_Scan(void)
{
	Arm_ActConfig();
	Arm_Action();
}

/* ���ƻ�е�۵�ת�� */
void Arm_Action(void)
{
	Servo_Move(&Servo1);
	Servo_Move(&Servo2);
	Servo_Move(&Servo3);
	Servo_Move(&Servo4);
	Servo_Move(&Servo5);
	Servo_Move(&Servo6);
}


/*************************************************************************************
													����Զ��庯��
**************************************************************************************/

/* ��е�۶���ѡ�� */
//choose: ѡ��ĳ�׶���
void Arm_ActChoose(u8 choose)
{
	action = choose;
}

/* ��е�۶��� */
void Arm_ActConfig(void)
{
	static u8 cnt = 1;
	
	if(!(Servo1.status||Servo2.status||Servo3.status||Servo4.status||Servo5.status||Servo6.status))
	{
		//////////////////////////////////ץ�Ų���/////////////////////////////////////////
		if(action==1)
		{
			switch(cnt)
			{
				case 1:		//��ʼ״̬
					Arm_DebugConfig(1600,1500,2100,1500,2000,2175); cnt++; action = 101; break;
				case 2:		//��е��������
					Arm_DebugConfig(1600,2100,1920,1970,2000,2175); cnt++; action = 101; break;
				case 3:		//�����
					Arm_DebugConfig(1600,2100,1920,1970,1500,2175); cnt++; action = 101; break;
				case 4:		//��е�ۼ������
					Arm_DebugConfig(1600,1500,2100,1500,1500,2175); cnt++; action = 101; break;
				case 5:		//˳ʱ��ת180��-
					Arm_DebugConfig(1600,1700,2100,1500,1500,875); cnt++; action = 101; break;
				case 6:		//�������  
					Arm_DebugConfig(1600,1900,2500,1550,1500,875); cnt++; action = 101; break;
				case 7:		//�ſ����ӷ������
					Arm_DebugConfig(1600,1900,2500,1550,2000,875); cnt++; action = 101; break;
				case 8:		//�ٴ��ջ�
					Arm_DebugConfig(1600,1850,2000,1500,2000,875); cnt++; action = 101; break;
				case 9:		//��ʼ״̬
					Arm_DebugConfig(1600,1500,2100,1500,2000,2175); cnt=1; action = 0; break;
			}
		}
		else if(action==101)
		{
			//delay_ms(300); 
			action = 1;
		}
	}
}






















