#include "servo.h"
#include "usart.h"

sServo Servo1 = {			//���1	
	.num = 1,
	.status = 0,				//��ʼʱɨ��ر�
	.curPwmWidth = SERVO_INIT1,		//��ʼλ��
	.nextPwmWidth = SERVO_INIT1,
	.tranPeriod = 0,
	.tranTimes = 0,
	.tranPwm = 0,
	.remainPwm = 0,
};

sServo Servo2 = {			//���2
	.num = 2,
	.status = 0,
	.curPwmWidth = SERVO_INIT2,
	.nextPwmWidth = SERVO_INIT2,
	.tranPeriod = 0,
	.tranTimes = 0,
	.tranPwm = 0,
	.remainPwm = 0,
};

sServo Servo3 = {			//���3
	.num = 3,
	.status = 0,
	.curPwmWidth = SERVO_INIT3,
	.nextPwmWidth = SERVO_INIT3,
	.tranPeriod = 0,
	.tranTimes = 0,
	.tranPwm = 0,
	.remainPwm = 0,
};

sServo Servo4 = {			//���4
	.num = 4,
	.status = 0,
	.curPwmWidth = SERVO_INIT4,
	.nextPwmWidth = SERVO_INIT4,
	.tranPeriod = 0,
	.tranTimes = 0,
	.tranPwm = 0,
	.remainPwm = 0,
};

sServo Servo5 = {			//���5
	.num = 5,
	.status = 0,
	.curPwmWidth = SERVO_INIT5,
	.nextPwmWidth = SERVO_INIT5,
	.tranPeriod = 0,
	.tranTimes = 0,
	.tranPwm = 0,
	.remainPwm = 0,
};

sServo Servo6 = {			//���6
	.num = 6,
	.status = 0,
	.curPwmWidth = SERVO_INIT6,
	.nextPwmWidth = SERVO_INIT6,
	.tranPeriod = 0,
	.tranTimes = 0,
	.tranPwm = 0,
	.remainPwm = 0,
};

/* ���ƶ����ʼ��ʱ��ת�� */
//ͨ������PWM������ʹ����ٶȲ������
//tranTimes:����������
void Servo_InitMove(void)
{
	static u8 i = 4;
	if(i==0)
	{
		TIM_SetCompare1(TIM2, Servo1.curPwmWidth);	//���1	PA0
		TIM_SetCompare2(TIM2, Servo2.curPwmWidth);	//���2	PA1
		TIM_SetCompare3(TIM2, Servo3.curPwmWidth);	//���3	PA2
		TIM_SetCompare4(TIM2, Servo4.curPwmWidth);	//���4	PA3
		TIM_SetCompare1(TIM1, Servo5.curPwmWidth);	//���5	PA8
		TIM_SetCompare4(TIM1, Servo6.curPwmWidth);	//���6	PA11
		printf("TIM_SetCompare1(TIM2, Servo1.curPwmWidth = %d\r\n", Servo1.curPwmWidth);	//���1	PA0
		printf("TIM_SetCompare2(TIM2, Servo2.curPwmWidth = %d\r\n", Servo2.curPwmWidth);	//���2	PA1
		printf("TIM_SetCompare3(TIM2, Servo3.curPwmWidth = %d\r\n", Servo3.curPwmWidth);	//���3	PA2
		printf("TIM_SetCompare4(TIM2, Servo4.curPwmWidth = %d\r\n", Servo4.curPwmWidth);	//���4	PA3
		printf("TIM_SetCompare1(TIM1, Servo5.curPwmWidth = %d\r\n", Servo5.curPwmWidth);	//���5	PA8
		printf("TIM_SetCompare4(TIM1, Servo6.curPwmWidth = %d\r\n", Servo6.curPwmWidth);	//���6	PA11
		printf("\r\n");
		i = 4;
	}
	else		//��ռ�ձ���Ϊ0��ֹͣPWM���
	{
		TIM_SetCompare1(TIM2, 0);	//���1	PA0
		TIM_SetCompare2(TIM2, 0);	//���2	PA1
		TIM_SetCompare3(TIM2, 0);	//���3	PA2
		TIM_SetCompare4(TIM2, 0);	//���4	PA3
		TIM_SetCompare1(TIM1, 0);	//���5	PA8
		TIM_SetCompare4(TIM1, 0);	//���6	PA11
		printf("TIM_SetCompare1(TIM2, Servo1.curPwmWidth = %d)\r\n", 0);	//���1	PA0
		printf("TIM_SetCompare2(TIM2, Servo2.curPwmWidth = %d)\r\n", 0);	//���2	PA1
		printf("TIM_SetCompare3(TIM2, Servo3.curPwmWidth = %d)\r\n", 0);	//���3	PA2
		printf("TIM_SetCompare4(TIM2, Servo4.curPwmWidth = %d)\r\n", 0);	//���4	PA3
		printf("TIM_SetCompare1(TIM1, Servo5.curPwmWidth = %d)\r\n", 0);	//���5	PA8
		printf("TIM_SetCompare4(TIM1, Servo6.curPwmWidth = %d)\r\n", 0);	//���6	PA11
		printf("\r\n");
		i--;
	}
}

/* ����ĳ�������ת�� */
//Servox:���x
//period:ת��ʱ��,ms
//pwmWidth:����ת��λ�ã�500~2500(us)
void Servo_MoveConfig(sServo *Servox, u16 period, u16 pwmWidth)
{
	Servox->status = 1;
	Servox->tranPeriod = period;
	Servox->nextPwmWidth = pwmWidth;
	
	Servox->tranTimes = Servox->tranPeriod / 20;			//1000/20=50��		����PWMֵ�ı���Ҫ>50���ô˺�������Ч	��50������������
	Servox->tranPwm = (int)(Servox->nextPwmWidth-Servox->curPwmWidth)/(int)Servox->tranTimes;			//���⣺pwm�ı�>50ʱtranPwm����Ч��=1��
	Servox->remainPwm = (int)(Servox->nextPwmWidth-Servox->curPwmWidth)%(int)Servox->tranTimes;
	Servox->tranTimes++;		//���һ�ΰ������������
}


/* ����ĳ�������ת�� */
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
				case 1: TIM_SetCompare1(TIM2, Servox->curPwmWidth); printf("TIM_SetCompare1(TIM2, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); break;	//���1	PA0
				case 2: TIM_SetCompare2(TIM2, Servox->curPwmWidth); printf("TIM_SetCompare2(TIM2, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); break;	//���2	PA1
				case 3: TIM_SetCompare3(TIM2, Servox->curPwmWidth); printf("TIM_SetCompare3(TIM2, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); break;	//���3	PA2
				case 4: TIM_SetCompare4(TIM2, Servox->curPwmWidth); printf("TIM_SetCompare4(TIM2, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); break;	//���4	PA3
				case 5: TIM_SetCompare1(TIM1, Servox->curPwmWidth); printf("TIM_SetCompare1(TIM1, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); break;	//���5	PA8
				case 6: TIM_SetCompare4(TIM1, Servox->curPwmWidth); printf("TIM_SetCompare4(TIM1, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); printf("\r\n"); break;	//���6	PA11
			}			
		}
		else if(Servox->tranTimes == 1)
		{
			Servox->tranTimes--;
			Servox->curPwmWidth += Servox->remainPwm;
			switch(Servox->num)
			{
				case 1: TIM_SetCompare1(TIM2, Servox->curPwmWidth); printf("TIM_SetCompare1(TIM2, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); break;	//���1	PA6
				case 2: TIM_SetCompare2(TIM2, Servox->curPwmWidth); printf("TIM_SetCompare2(TIM2, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); break;	//���2	PA7
				case 3: TIM_SetCompare3(TIM2, Servox->curPwmWidth); printf("TIM_SetCompare3(TIM2, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); break;	//���3	PB0
				case 4: TIM_SetCompare4(TIM2, Servox->curPwmWidth); printf("TIM_SetCompare4(TIM2, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); break;	//���4	PB1
				case 5: TIM_SetCompare1(TIM1, Servox->curPwmWidth); printf("TIM_SetCompare1(TIM1, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); break;	//���5	PA8
				case 6: TIM_SetCompare4(TIM1, Servox->curPwmWidth); printf("TIM_SetCompare4(TIM1, Servox->curPwmWidth = %d\r\n", Servox->curPwmWidth); printf("\r\n"); break;	//���6	PA11
			}	
		}
		else
		{
			Servox->status = 0;
			Servox->tranPwm = 0;
		}
	}
}


