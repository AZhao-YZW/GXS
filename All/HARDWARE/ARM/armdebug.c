#include "armdebug.h"
#include "servo.h"
#include "usart.h"			//串口打印显示数据
#include "stdarg.h"		//实现可变参数功能
#include "stdio.h"
#include "string.h"

/* 配置调试某个舵机的转动（微调） */
//tranPwm：调试舵机速度，即每20ms改变的pwm值
void Servo_DebugConfig(sServo *Servox, int tranPwm)
{
		Servox->status = 1;
		Servox->tranPwm = tranPwm;
		Servox->nextPwmWidth += Servox->tranPwm;
		Servox->tranTimes = 1;		//PWM值改变1次
		Servox->tranPeriod = 20;	//改变时间为20ms
}

/* 配置调试机械臂运动状态 */
//depwmWidth1~5: 设置舵机角度
void Arm_DebugConfig(u16 depwmWidth1, u16 depwmWidth2, u16 depwmWidth3, u16 depwmWidth4, u16 depwmWidth5, u16 depwmWidth6)
{
	Servo_MoveConfig(&Servo1, 1000, depwmWidth1);
	Servo_MoveConfig(&Servo2, 1000, depwmWidth2);
	Servo_MoveConfig(&Servo3, 1000, depwmWidth3);
	Servo_MoveConfig(&Servo4, 1000, depwmWidth4);
	Servo_MoveConfig(&Servo5, 1000, depwmWidth5);
	Servo_MoveConfig(&Servo6, 1000, depwmWidth6);
}

/* 配置调试机械臂运动状态 */
//deperiod1~5: 设置舵机角度
//depwmWidth1~5: 设置舵机角度
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

/* USMART配置调试单个舵机 */
//num: 舵机编号
//tranPwm：调试舵机速度，即每20ms改变的pwm值
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

/* USMART配置某个舵机的转动 */
//num: 舵机编号
//period:转动时间,ms
//pwmWidth:控制转动位置，500~2500(us)
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

/* 打印显示某个舵机当前状态 */
//configName：参数："brief": 简略信息；"whole": 详细信息
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

/* USMART打印显示某个舵机当前状态 */
//num: 舵机编号
//configName：参数："brief": 简略信息；"whole": 详细信息
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

/* USMART打印显示所有舵机当前状态 */
//configName：参数："brief": 简略信息；"whole": 详细信息
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




