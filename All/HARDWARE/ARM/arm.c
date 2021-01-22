#include "arm.h"
#include "led.h"
#include "servo.h"
#include "armdebug.h"
#include "delay.h"

u8 action = 0;		//动作标识

/* 在中断中扫描，改变舵机运动状态 */
//当Servox的status为1时扫描才有效
void Servo_Scan(void)
{
	Arm_ActConfig();
	Arm_Action();
}

/* 控制机械臂的转动 */
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
													添加自定义函数
**************************************************************************************/

/* 机械臂动作选择 */
//choose: 选择某套动作
void Arm_ActChoose(u8 choose)
{
	action = choose;
}

/* 机械臂动作 */
void Arm_ActConfig(void)
{
	static u8 cnt = 1;
	
	if(!(Servo1.status||Servo2.status||Servo3.status||Servo4.status||Servo5.status||Servo6.status))
	{
		//////////////////////////////////抓放测试/////////////////////////////////////////
		if(action==1)
		{
			switch(cnt)
			{
				case 1:		//初始状态
					Arm_DebugConfig(1600,1500,2100,1500,2000,2175); cnt++; action = 101; break;
				case 2:		//机械臂往下伸
					Arm_DebugConfig(1600,2100,1920,1970,2000,2175); cnt++; action = 101; break;
				case 3:		//夹物块
					Arm_DebugConfig(1600,2100,1920,1970,1500,2175); cnt++; action = 101; break;
				case 4:		//机械臂夹起物块
					Arm_DebugConfig(1600,1500,2100,1500,1500,2175); cnt++; action = 101; break;
				case 5:		//顺时针转180度-
					Arm_DebugConfig(1600,1700,2100,1500,1500,875); cnt++; action = 101; break;
				case 6:		//放下物块  
					Arm_DebugConfig(1600,1900,2500,1550,1500,875); cnt++; action = 101; break;
				case 7:		//张开夹子放下物块
					Arm_DebugConfig(1600,1900,2500,1550,2000,875); cnt++; action = 101; break;
				case 8:		//再次收回
					Arm_DebugConfig(1600,1850,2000,1500,2000,875); cnt++; action = 101; break;
				case 9:		//初始状态
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






















