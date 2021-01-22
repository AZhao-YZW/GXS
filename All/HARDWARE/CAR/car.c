#include "car.h"
#include "led.h"
#include "delay.h"

sCarMove MyCar = {0, 0, CarForward, 0, 0, 0};		//初始化

/* 小车方向控制初始化 */
void Car_DirectInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//复用推挽输出
	GPIO_Init(GPIOF,&GPIO_InitStructure);
}

/* 小车红外模块初始化 */
void Car_RedInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;		//输入
	GPIO_Init(GPIOD,&GPIO_InitStructure);
}

/* 小车初始化 */
void Car_Init(void)
{
	Car_DirectInit();
	Car_RedInit();
}

/* 产生脉冲 */
void Car_MovePulse(u16 pwmValue)
{
	TIM_SetCompare1(TIM3,pwmValue);
	TIM_SetCompare2(TIM3,pwmValue);
	TIM_SetCompare3(TIM3,pwmValue);
	TIM_SetCompare4(TIM3,pwmValue);
}

/* 配置小车速度 */
void Car_MoveSpeed(u16 arr)
{
	TIM_SetAutoreload(TIM3, arr);
}

/* 小车运动 */
void Car_Run(void)
{
	Car_MovePulse(10);
}

/* 修正模式小车运动 */
void Car_RunCorrect(u8 direct)
{
	
}

/* 小车停止 */
void Car_Stop(void)
{
	Car_MovePulse(0);
}

/* 配置小车方向 */
//direct: 方向值
void Car_DirectConfig(u8 direct)
{
	switch(direct)
	{
		case CarForward: DirectFL = 1; DirectFR = 0; DirectBL = 1; DirectBR = 0; break;
		case CarBehind:  DirectFL = 0; DirectFR = 1; DirectBL = 0; DirectBR = 1; break;
		case CarLeft:    DirectFL = 0; DirectFR = 0; DirectBL = 1; DirectBR = 1; break;
		case CarRight:   DirectFL = 1; DirectFR = 1; DirectBL = 0; DirectBR = 0; break;
		case CarCircle1: DirectFL = 1; DirectFR = 1; DirectBL = 1; DirectBR = 1; break;
		case CarCircle2: DirectFL = 0; DirectFR = 0; DirectBL = 0; DirectBR = 0; break;
	}	
}

/* 小车数格子 */
void Car_Count()
{
	static u8 flag = 0;		//数黑线标志
	static u8 cnt = 0;		//数黑线计数
	static u8 first = 0;			//先巡到黑线
	static u8 second = 0;			//后巡到黑线
	
	switch(MyCar.direct)		//前进后退用左边的数，左右移动用右边的数
	{
		case CarForward: first = RedRL; second = RedRR; break;
		case CarBehind:  first = RedRR; second = RedRL; break;
		case CarLeft:    first = RedFL; second = RedFR; break;
		case CarRight:   first = RedFR; second = RedFL; break;
	}
	
	if(first==1 && second==0)
		flag = 1;
	if(first==0 && second==1 && flag)
	{
		cnt++; flag = 0;
	}
	
	if(cnt >= MyCar.times)
	{
		MyCar.isMove = 0;
		MyCar.times = 0;
		cnt = 0;
	}
	
}

/* 配置小车移动（按格子） */
//注：都是停在格线上
//times: 移动格子数
//direct: 移动时方向
void Car_Move(u8 times, u8 direct)
{
	Car_Run();	//开始运动
	MyCar.isMove = 1;
	MyCar.mode = 1;
	MyCar.times = times;
	Car_DirectConfig(direct);
	MyCar.direct = direct;
}

/* 配置小车自由移动 */
//len: 移动距离 cm  当为旋转时，len是旋转角度
//direct: 移动方向
void Car_FreeMove(float len, u8 direct)
{
	Car_Run();	//开始运动
	MyCar.isMove = 1;
	MyCar.mode = 0;
	if(direct==CarForward || direct==CarBehind)
		MyCar.len = len*OneCm;
	else if(direct==CarLeft || direct==CarRight)
		MyCar.len = len*OneCm2;
	else if(direct==CarCircle1 || direct==CarCircle2)
		MyCar.len = len*OneDegree;
	Car_DirectConfig(direct);
	MyCar.direct = direct;
}

/* 小车修正方向 */
void Car_Correct()
{
	static u8 flag = 0;			//标记前个状态
//	static u8 lastMode;			//上一次模式
//	static u8 lastDirect;		//上一次方向
	static u8 left = 0;			//左边巡黑线
	static u8 right = 0;		//右边巡黑线
	
	switch(MyCar.direct)
	{
		case CarForward: left = RedCrtFL; right = RedCrtFR; break;
		case CarBehind:  left = RedCrtFR; right = RedCrtFL; break;
		case CarLeft:    left = RedCrtRR; right = RedCrtRL; break;
		case CarRight:   left = RedCrtRL; right = RedCrtRR; break;
	}
	
	//if(left==0 && right==0) lastMode = MyCar.mode;
	if(left==0 && right==0) { Car_DirectConfig(MyCar.direct); flag = 1; }
	if(left==1 && right==0 && flag) Car_DirectConfig(CarCircle2);
	if(left==0 && right==1 && flag) Car_DirectConfig(CarCircle1);
	//if(left==1 && right==1) MyCar.mode = lastMode;
	if(left==1 && right==1) { Car_DirectConfig(MyCar.direct); flag = 0; }
}

///* 小车修正方向配置 */
////direct: 修正方向
//void Car_CorrectConfig(u8 direct)
//{
//	Car_Run();	//开始运动
//	MyCar.isMove = 1;
//	MyCar.mode = 2;
//	Car_DirectConfig(direct);
//	MyCar.direct = direct;
//}

/* 在中断6中扫描，给电机计数产生脉冲 */
void Car_Scan2(void)
{
	if(MyCar.isMove)		//小车为运动状态
	{
		if(MyCar.mode == Count)		//计数模式
		{
			Car_Count();
		}
		else if(MyCar.mode == FreeMove)		//自由移动模式
		{
			MyCar.len -= 1;
			if(MyCar.len < 0)
				MyCar.isMove = 0;
		}
		else if(MyCar.mode == Correct)		//修正模式
		{
			
		}
	}
	else
		Car_Stop();
}


/* 在中断2中扫描，改变小车运动状态 */
void Car_Scan(void)
{
	static u8 point=0;	//指向某个action的其中一步

	
	if(MyCar.isMove==0)		//小车运动状态结束时
	{
		////////////////////////////////////////////蛇形走位/////////////////////////////////////////
		if(MyCar.action==1)		//例如第一个动作
		{
			switch(point)
			{
				case 0: Car_Move(1, CarForward); point++; MyCar.action = 100; break;
				case 1: Car_Move(1, CarLeft);    point++; MyCar.action = 100; break;
				case 2: Car_Move(1, CarForward); point++; MyCar.action = 100; break;
				case 3: Car_Move(2, CarRight);   point++; MyCar.action = 100; break;
				case 4: Car_Move(1, CarForward); point++; MyCar.action = 100; break;
				case 5: Car_Move(2, CarLeft);    point++; MyCar.action = 100; break;
				case 6: Car_Move(1, CarForward); point++; MyCar.action = 100; break;
				case 7: Car_Move(2, CarRight);   point++; MyCar.action = 100; break;
				case 8: Car_Move(1, CarForward); point++; MyCar.action = 100; break;
				case 9: Car_Move(2, CarLeft);    point++; MyCar.action = 100; break;
				case 10: Car_Move(1, CarForward); point++; MyCar.action = 100; break;
				case 11: Car_Move(2, CarRight);   point++; MyCar.action = 100; break;
				case 12: Car_Move(1, CarForward); point++; MyCar.action = 100; break;
				case 13: Car_Move(2, CarLeft);    point++; MyCar.action = 100; break;
				case 14: Car_Move(1, CarForward); point++; MyCar.action = 100; break;
				case 15: Car_Move(2, CarRight);   point++; MyCar.action = 100; break;
				case 16: point=0; MyCar.action = 2; break;
			}
		}
		else if(MyCar.action==2)
		{
			switch(point)
			{
				case 0: Car_Move(1, CarBehind); point++; MyCar.action = 101; break;
				case 1: Car_Move(1, CarLeft);   point++; MyCar.action = 101; break;
				case 2: Car_Move(1, CarBehind); point++; MyCar.action = 101; break;
				case 3: Car_Move(2, CarRight);  point++; MyCar.action = 101; break;
				case 4: Car_Move(1, CarBehind); point++; MyCar.action = 101; break;
				case 5: Car_Move(2, CarLeft);   point++; MyCar.action = 101; break;
				case 6: Car_Move(1, CarBehind); point++; MyCar.action = 101; break;
				case 7: Car_Move(2, CarRight);  point++; MyCar.action = 101; break;
				case 8: Car_Move(1, CarBehind); point++; MyCar.action = 101; break;
				case 9: Car_Move(2, CarLeft);   point++; MyCar.action = 101; break;
				case 10: Car_Move(1, CarBehind); point++; MyCar.action = 101; break;
				case 11: Car_Move(2, CarRight);  point++; MyCar.action = 101; break;
				case 12: Car_Move(1, CarBehind); point++; MyCar.action = 101; break;
				case 13: Car_Move(2, CarLeft);   point++; MyCar.action = 101; break;
				case 14: Car_Move(1, CarBehind); point++; MyCar.action = 101; break;
				case 15: Car_Move(2, CarRight);  point=0; MyCar.action = 0; Car_Stop(); break;
			}
		}
		else if(MyCar.action==100)
		{
			Car_Stop();delay_ms(300);MyCar.action = 1;
		}
		else if(MyCar.action==101)
		{
			Car_Stop();delay_ms(300);MyCar.action = 2;
		}
		
		//////////////////////////////////工训赛测试路线1////////////////////////////////////
		else if(MyCar.action==3)
		{
			switch(point)
			{
				case 0: Car_FreeMove(5, CarForward); point++; break;
				case 1: Car_Move(1, CarForward); point++; MyCar.action = 103; break;
				case 2: Car_FreeMove(5, CarLeft); point++; break;
				case 3: Car_Move(1, CarLeft);    point++; MyCar.action = 103; break;
				case 4: Car_FreeMove(5, CarBehind); point++; break;
				case 5: Car_Move(1, CarBehind);  point++; MyCar.action = 103; break;
				case 6: Car_FreeMove(5, CarRight); point++; break;
				case 7: Car_Move(1, CarRight);   point=0; MyCar.action = 103; break;
			}
		}
		else if(MyCar.action==103)
		{
			Car_Stop();delay_ms(300);MyCar.action = 3;
		}
		
		
		//////////////////////////////////工训赛测试路线2////////////////////////////////////
		else if(MyCar.action==4)
		{
			switch(point)
			{
				case 0: Car_Move(4, CarForward); point++; MyCar.action = 104; break;
				case 1: Car_Move(3, CarLeft);    point++; MyCar.action = 104; break;
				case 2: Car_Move(4, CarBehind);  point++; MyCar.action = 104; break;
				case 3: Car_Move(4, CarRight);   point++; MyCar.action = 0; break;
			}
		}
		else if(MyCar.action==104)
		{
			Car_Stop();delay_ms(300);MyCar.action = 4;
		}
		
		
		//////////////////////////////////工训赛测试路线3////////////////////////////////////
		else if(MyCar.action==5)
		{
			switch(point)
			{
				case 0: Car_FreeMove(10, CarForward); point++; MyCar.action = 105; break;
				case 1: Car_Move(1, CarForward); point++; MyCar.action = 105; break;
				case 2: Car_Move(6, CarRight);   point++; MyCar.action = 105; break;
				case 3: Car_Move(4, CarForward); point++; MyCar.action = 105; break;
				case 4: Car_Move(6, CarLeft);    point++; MyCar.action = 105; break;
				case 5: Car_FreeMove(15, CarLeft);    point++; MyCar.action = 105; break;
				case 6: Car_FreeMove(45, CarForward); point++; MyCar.action = 0; break;
			}
		}
		else if(MyCar.action==105)
		{
			Car_Stop();delay_ms(300);MyCar.action = 5;
		}
		
		
		//////////////////////////////////工训赛测试-转圈////////////////////////////////////
		else if(MyCar.action==6)
		{
			switch(point)
			{
				case 0: Car_FreeMove(360, CarCircle1); point++; MyCar.action = 106; break;
				case 1: Car_FreeMove(360, CarCircle2); point--; MyCar.action = 106; break;
			}
		}
		else if(MyCar.action==106)
		{
			Car_Stop();delay_ms(300);MyCar.action = 6;
		}
		
		//////////////////////////////////工训赛测试路线-简化路线////////////////////////////////////
		else if(MyCar.action==7)
		{
			switch(point)
			{
				case 0: Car_FreeMove(25, CarLeft); point++; break;
				case 1: Car_Move(1, CarLeft);    point++; MyCar.action = 107; break;
				case 2: Car_Move(6, CarForward); point++; MyCar.action = 107; break;
				case 3: Car_FreeMove(15, CarLeft); point++; break;
				case 4: Car_Move(4, CarLeft);   point++; MyCar.action = 107; break;
				case 5: Car_FreeMove(15, CarBehind); point++; break;
				case 6: Car_Move(2, CarBehind);  point++; MyCar.action = 107; break;
				case 7: Car_FreeMove(15, CarRight); point++; break;
				case 8: Car_Move(4, CarRight);  point++; MyCar.action = 107; break;
				case 9: Car_FreeMove(15, CarForward); point++; break;
				case 10: Car_Move(2, CarForward); point++; MyCar.action = 107; break;
				case 11: Car_FreeMove(15, CarLeft); point++; break;
				case 12: Car_Move(4, CarLeft);   point++; MyCar.action = 107; break;
				case 13: Car_FreeMove(15, CarBehind); point++; break;
				case 14: Car_Move(5, CarBehind); point++; MyCar.action = 107; break;
				case 15: Car_FreeMove(15, CarBehind);    point++; MyCar.action = 107; break;	//结束
				case 16: Car_FreeMove(45, CarLeft); point++; MyCar.action = 0; break;
			}
		}
		else if(MyCar.action==107)
		{
			Car_Stop();delay_ms(300);MyCar.action = 7;
		}
	}
}



