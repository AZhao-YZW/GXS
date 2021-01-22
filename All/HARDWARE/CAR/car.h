#ifndef _CAR_H
#define _CAR_H

#include "sys.h"

#define OneCircle 12800		//���һȦ������
#define OneCm     12800/25.1327		//С���ƶ�1cm
#define OneCm2    (12800/25.1327)*1.025		//С�������ƶ�1cm
#define OneDegree OneCircle/60		//С����ת1��
//С��ģʽ
#define FreeMove 		0
#define Count		 		1
#define Correct		 	2
//С������
#define CarForward 1
#define CarBehind  2
#define CarLeft    3
#define CarRight   4

#define CarCircle1 5
#define CarCircle2 6
//����ģ������
#define RedFL PDin(8)
#define RedFR PDin(9)
//#define RedBL PDin(10)
//#define RedBR PDin(11)
//#define RedLL PDin(12)
//#define RedLR PDin(13)
#define RedRL PDin(14)
#define RedRR PDin(15)
#define RedCrtFL PDin(10)
#define RedCrtFR PDin(11)
#define RedCrtRL PDin(12)
#define RedCrtRR PDin(13)
//�������ת
#define DirectFL PFout(12)
#define DirectFR PFout(13)
#define DirectBL PFout(14)
#define DirectBR PFout(15)

//С�������ṹ��
typedef struct
{
	u8 mode;		//1: ������ģʽ  0: �����ƶ�ģʽ  
	u8 action;	//С�����ж���
	u8 direct;	//С���ƶ�����
	u8 isMove;	//С���Ƿ��˶�	1: �˶�  0:ֹͣ
	u8 times;		//������ģʽ�£�������
	float len;	//�����ƶ�ģʽ�£��ƶ�����
}sCarMove;

extern sCarMove MyCar;

void Car_MovePulse(u16 pwmValue);
void Car_Run(void);
void Car_Stop(void);
void Car_Init(void);
//void Car_MoveSpeed(u16 arr);
//void Car_DirectConfig(u8 direct);
void Car_Move(u8 times, u8 direct);
void Car_FreeMove(float len, u8 direct);
void Car_Correct(void);
void Car_Scan2(void);
void Car_Scan(void);

#endif
