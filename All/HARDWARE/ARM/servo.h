#ifndef _SERCO_H
#define _SERCO_H

#include "sys.h"

#define SERVO_INIT1		1600
#define SERVO_INIT2		1500
#define SERVO_INIT3		2100
#define SERVO_INIT4		1500
#define SERVO_INIT5		2000
#define SERVO_INIT6		2175

/* ����ṹ�� */
//ֱ�ӿ��ƶ��: void Servo_Move(sServo *Servox)
//							void Arm_Action(void)
//��ӿ��ƶ��: void Servo_MoveConfig(sServo *Servox, u16 period, u16 pwmWidth)
//							void Arm_ActionConfig(u8 action)
//							void Set_ServoStatus(sServo *Servox, const char *configName, ...)
//							void Servo_DebugInit(sServo *Servox)
//							void Servo_DebugConfig(sServo *Servox, u8 tranPwm)
//							void Arm_DebugConfig(u16 depwmWidth1, u16 depwmWidth2, u16 depwmWidth3, u16 depwmWidth4, u16 depwmWidth5)
//���ֱ�ӿ��Ʋ�����status��curPwmWidth��tranPwm��tranTimes
//�����ӿ��Ʋ�����nextPwmWidth��tranPeriod
typedef struct
{
	const u8 num;				//������
	u8 status;					//1:ת��״̬��־	0:�ȶ�״̬��־				//����ʱ������ĳ���������
	u16 curPwmWidth;		//500us~2500us		��ֵ������us��Ӧ
	u16 nextPwmWidth;
	int tranPwm;				//ÿ�α仯pwm�任ֵ
	int remainPwm;			//pwm�任������
	u16 tranPeriod;			//ת�������Ҫʱ�䣬��λ��ms			//ÿ��20ms�仯һ��
	u16 tranTimes;			//ת�������任����							//���㹫ʽ��tranTimes=tranPeriod/20
}sServo;

extern sServo Servo1;
extern sServo Servo2;
extern sServo Servo3;
extern sServo Servo4;
extern sServo Servo5;
extern sServo Servo6;

/* ϵͳ���� */
void Servo_InitMove(void);
void Servo_Move(sServo *Servox);
/* �û����� */
void Servo_MoveConfig(sServo *Servox, u16 period, u16 pwmWidth);			//������������ƶ���ĵײ�ӿ�


#endif

