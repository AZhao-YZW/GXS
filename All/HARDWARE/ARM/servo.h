#ifndef _SERCO_H
#define _SERCO_H

#include "sys.h"

#define SERVO_INIT1		1600
#define SERVO_INIT2		1500
#define SERVO_INIT3		2100
#define SERVO_INIT4		1500
#define SERVO_INIT5		2000
#define SERVO_INIT6		2175

/* 舵机结构体 */
//直接控制舵机: void Servo_Move(sServo *Servox)
//							void Arm_Action(void)
//间接控制舵机: void Servo_MoveConfig(sServo *Servox, u16 period, u16 pwmWidth)
//							void Arm_ActionConfig(u8 action)
//							void Set_ServoStatus(sServo *Servox, const char *configName, ...)
//							void Servo_DebugInit(sServo *Servox)
//							void Servo_DebugConfig(sServo *Servox, u8 tranPwm)
//							void Arm_DebugConfig(u16 depwmWidth1, u16 depwmWidth2, u16 depwmWidth3, u16 depwmWidth4, u16 depwmWidth5)
//舵机直接控制参数：status、curPwmWidth、tranPwm、tranTimes
//舵机间接控制参数：nextPwmWidth、tranPeriod
typedef struct
{
	const u8 num;				//舵机编号
	u8 status;					//1:转动状态标志	0:稳定状态标志				//调试时可以让某个舵机不动
	u16 curPwmWidth;		//500us~2500us		其值正好与us对应
	u16 nextPwmWidth;
	int tranPwm;				//每次变化pwm变换值
	int remainPwm;			//pwm变换的余数
	u16 tranPeriod;			//转动完成需要时间，单位：ms			//每隔20ms变化一次
	u16 tranTimes;			//转动完成需变换次数							//计算公式：tranTimes=tranPeriod/20
}sServo;

extern sServo Servo1;
extern sServo Servo2;
extern sServo Servo3;
extern sServo Servo4;
extern sServo Servo5;
extern sServo Servo6;

/* 系统调用 */
void Servo_InitMove(void);
void Servo_Move(sServo *Servox);
/* 用户调用 */
void Servo_MoveConfig(sServo *Servox, u16 period, u16 pwmWidth);			//舵机驱动，控制舵机的底层接口


#endif

