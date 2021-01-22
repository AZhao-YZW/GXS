#ifndef _CAR_H
#define _CAR_H

#include "sys.h"

#define OneCircle 12800		//电机一圈脉冲数
#define OneCm     12800/25.1327		//小车移动1cm
#define OneCm2    (12800/25.1327)*1.025		//小车左右移动1cm
#define OneDegree OneCircle/60		//小车旋转1度
//小车模式
#define FreeMove 		0
#define Count		 		1
#define Correct		 	2
//小车方向
#define CarForward 1
#define CarBehind  2
#define CarLeft    3
#define CarRight   4

#define CarCircle1 5
#define CarCircle2 6
//红外模块输入
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
//电机正反转
#define DirectFL PFout(12)
#define DirectFR PFout(13)
#define DirectBL PFout(14)
#define DirectBR PFout(15)

//小车动作结构体
typedef struct
{
	u8 mode;		//1: 数格子模式  0: 自由移动模式  
	u8 action;	//小车运行动作
	u8 direct;	//小车移动方向
	u8 isMove;	//小车是否运动	1: 运动  0:停止
	u8 times;		//数格子模式下，数几格
	float len;	//自由移动模式下，移动距离
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
