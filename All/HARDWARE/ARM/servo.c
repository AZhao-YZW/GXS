#include "servo.h"
#include "usart.h"

sServo Servo1 = {			//舵机1	
	.num = 1,
	.status = 0,				//初始时扫描关闭
	.curPwmWidth = SERVO_INIT1,		//初始位置
	.nextPwmWidth = SERVO_INIT1,
	.tranPeriod = 0,
	.tranTimes = 0,
	.tranPwm = 0,
	.remainPwm = 0,
};

sServo Servo2 = {			//舵机2
	.num = 2,
	.status = 0,
	.curPwmWidth = SERVO_INIT2,
	.nextPwmWidth = SERVO_INIT2,
	.tranPeriod = 0,
	.tranTimes = 0,
	.tranPwm = 0,
	.remainPwm = 0,
};

sServo Servo3 = {			//舵机3
	.num = 3,
	.status = 0,
	.curPwmWidth = SERVO_INIT3,
	.nextPwmWidth = SERVO_INIT3,
	.tranPeriod = 0,
	.tranTimes = 0,
	.tranPwm = 0,
	.remainPwm = 0,
};

sServo Servo4 = {			//舵机4
	.num = 4,
	.status = 0,
	.curPwmWidth = SERVO_INIT4,
	.nextPwmWidth = SERVO_INIT4,
	.tranPeriod = 0,
	.tranTimes = 0,
	.tranPwm = 0,
	.remainPwm = 0,
};

sServo Servo5 = {			//舵机5
	.num = 5,
	.status = 0,
	.curPwmWidth = SERVO_INIT5,
	.nextPwmWidth = SERVO_INIT5,
	.tranPeriod = 0,
	.tranTimes = 0,
	.tranPwm = 0,
	.remainPwm = 0,
};

sServo Servo6 = {			//舵机6
	.num = 6,
	.status = 0,
	.curPwmWidth = SERVO_INIT6,
	.nextPwmWidth = SERVO_INIT6,
	.tranPeriod = 0,
	.tranTimes = 0,
	.tranPwm = 0,
	.remainPwm = 0,
};

/* 控制舵机初始化时的转动 */
//通过控制PWM间断输出使舵机速度不会过快
//tranTimes:间断输出次数
void Servo_InitMove(void)
{
	static u8 i = 4;
	if(i==0)
	{
		TIM_SetCompare1(TIM2, Servo1.curPwmWidth);	//舵机1	PA0
		TIM_SetCompare2(TIM2, Servo2.curPwmWidth);	//舵机2	PA1
		TIM_SetCompare3(TIM2, Servo3.curPwmWidth);	//舵机3	PA2
		TIM_SetCompare4(TIM2, Servo4.curPwmWidth);	//舵机4	PA3
		TIM_SetCompare1(TIM1, Servo5.curPwmWidth);	//舵机5	PA8
		TIM_SetCompare4(TIM1, Servo6.curPwmWidth);	//舵机6	PA11
		printf("TIM_SetCompare1(TIM2, Servo1.curPwmWidth = %d\r\n", Servo1.curPwmWidth);	//舵机1	PA0
		printf("TIM_SetCompare2(TIM2, Servo2.curPwmWidth = %d\r\n", Servo2.curPwmWidth);	//舵机2	PA1
		printf("TIM_SetCompare3(TIM2, Servo3.curPwmWidth = %d\r\n", Servo3.curPwmWidth);	//舵机3	PA2
		printf("TIM_SetCompare4(TIM2, Servo4.curPwmWidth = %d\r\n", Servo4.curPwmWidth);	//舵机4	PA3
		printf("TIM_SetCompare1(TIM1, Servo5.curPwmWidth = %d\r\n", Servo5.curPwmWidth);	//舵机5	PA8
		printf("TIM_SetCompare4(TIM1, Servo6.curPwmWidth = %d\r\n", Servo6.curPwmWidth);	//舵机6	PA11
		printf("\r\n");
		i = 4;
	}
	else		//将占空比设为0，停止PWM输出
	{
		TIM_SetCompare1(TIM2, 0);	//舵机1	PA0
		TIM_SetCompare2(TIM2, 0);	//舵机2	PA1
		TIM_SetCompare3(TIM2, 0);	//舵机3	PA2
		TIM_SetCompare4(TIM2, 0);	//舵机4	PA3
		TIM_SetCompare1(TIM1, 0);	//舵机5	PA8
		TIM_SetCompare4(TIM1, 0);	//舵机6	PA11
		printf("TIM_SetCompare1(TIM2, Servo1.curPwmWidth = %d)\r\n", 0);	//舵机1	PA0
		printf("TIM_SetCompare2(TIM2, Servo2.curPwmWidth = %d)\r\n", 0);	//舵机2	PA1
		printf("TIM_SetCompare3(TIM2, Servo3.curPwmWidth = %d)\r\n", 0);	//舵机3	PA2
		printf("TIM_SetCompare4(TIM2, Servo4.curPwmWidth = %d)\r\n", 0);	//舵机4	PA3
		printf("TIM_SetCompare1(TIM1, Servo5.curPwmWidth = %d)\r\n", 0);	//舵机5	PA8
		printf("TIM_SetCompare4(TIM1, Servo6.curPwmWidth = %d)\r\n", 0);	//舵机6	PA11
		printf("\r\n");
		i--;
	}
}

/* 配置某个舵机的转动 */
//Servox:舵机x
//period:转动时间,ms
//pwmWidth:控制转动位置，500~2500(us)
void Servo_MoveConfig(sServo *Servox, u16 period, u16 pwmWidth)
{
	Servox->status = 1;
	Servox->tranPeriod = period;
	Servox->nextPwmWidth = pwmWidth;
	
	Servox->tranTimes = Servox->tranPeriod / 20;			//1000/20=50次		导致PWM值改变需要>50调用此函数才有效	除50的余数被舍弃
	Servox->tranPwm = (int)(Servox->nextPwmWidth-Servox->curPwmWidth)/(int)Servox->tranTimes;			//问题：pwm改变>50时tranPwm才有效（=1）
	Servox->remainPwm = (int)(Servox->nextPwmWidth-Servox->curPwmWidth)%(int)Servox->tranTimes;
	Servox->tranTimes++;		//多加一次把最后的余数完成
}


/* 控制某个舵机的转动 */
void Servo_Move(sServo *Servox)
{
	if(Servox->status == 1)
	{
		if(Servox->tranTimes > 1)
		{
			Servox->tranTimes--;
			Servox->curPwmWidth += Servox->tranPwm;
			switch(Servox->num)
			{
				case 1: TIM_SetCompare1(TIM2, Servox->curPwmWidth); printf("TIM_SetCompare1(TIM2, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); break;	//舵机1	PA0
				case 2: TIM_SetCompare2(TIM2, Servox->curPwmWidth); printf("TIM_SetCompare2(TIM2, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); break;	//舵机2	PA1
				case 3: TIM_SetCompare3(TIM2, Servox->curPwmWidth); printf("TIM_SetCompare3(TIM2, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); break;	//舵机3	PA2
				case 4: TIM_SetCompare4(TIM2, Servox->curPwmWidth); printf("TIM_SetCompare4(TIM2, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); break;	//舵机4	PA3
				case 5: TIM_SetCompare1(TIM1, Servox->curPwmWidth); printf("TIM_SetCompare1(TIM1, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); break;	//舵机5	PA8
				case 6: TIM_SetCompare4(TIM1, Servox->curPwmWidth); printf("TIM_SetCompare4(TIM1, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); printf("\r\n"); break;	//舵机6	PA11
			}			
		}
		else if(Servox->tranTimes == 1)
		{
			Servox->tranTimes--;
			Servox->curPwmWidth += Servox->remainPwm;
			switch(Servox->num)
			{
				case 1: TIM_SetCompare1(TIM2, Servox->curPwmWidth); printf("TIM_SetCompare1(TIM2, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); break;	//舵机1	PA6
				case 2: TIM_SetCompare2(TIM2, Servox->curPwmWidth); printf("TIM_SetCompare2(TIM2, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); break;	//舵机2	PA7
				case 3: TIM_SetCompare3(TIM2, Servox->curPwmWidth); printf("TIM_SetCompare3(TIM2, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); break;	//舵机3	PB0
				case 4: TIM_SetCompare4(TIM2, Servox->curPwmWidth); printf("TIM_SetCompare4(TIM2, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); break;	//舵机4	PB1
				case 5: TIM_SetCompare1(TIM1, Servox->curPwmWidth); printf("TIM_SetCompare1(TIM1, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); break;	//舵机5	PA8
				case 6: TIM_SetCompare4(TIM1, Servox->curPwmWidth); printf("TIM_SetCompare4(TIM1, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); printf("\r\n"); break;	//舵机6	PA11
			}	
		}
		else
		{
			Servox->status = 0;
			Servox->tranPwm = 0;
		}
	}
}


